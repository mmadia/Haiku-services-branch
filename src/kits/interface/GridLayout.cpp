/*
 * Copyright 2010, Haiku Inc.
 * Copyright 2006, Ingo Weinhold <bonefish@cs.tu-berlin.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */


#include <GridLayout.h>

#include <algorithm>
#include <new>
#include <string.h>

#include <LayoutItem.h>
#include <List.h>
#include <Message.h>

#include "ViewLayoutItem.h"


using std::nothrow;
using std::swap;


enum {
	MAX_COLUMN_ROW_COUNT	= 1024,
};


namespace {
	// a placeholder we put in our grid array to make a cell occupied
	BLayoutItem* const OCCUPIED_GRID_CELL = (BLayoutItem*)0x1;

	const char* kRowCountField = "gridlayout:rowcount";
	const char* kRowMinSizeField = "gridlayout:rowminsize";
	const char* kRowMaxSizeField = "gridlayout:rowmaxsize";
	const char* kRowWeightField = "gridlayout:rowweight";
	const char* kColumnCountField = "gridlayout:columncount";
	const char* kColumnMinSizeField = "gridlayout:columnminsize";
	const char* kColumnMaxSizeField = "gridlayout:columnmaxsize";
	const char* kColumnWeightField = "gridlayout:columnweight";
	const char* kItemHeight = "gridlayout:item:height";
	const char* kItemWidth = "gridlayout:item:width";
	const char* kItemX = "gridlayout:item:x";
	const char* kItemY = "gridlayout:item:y";
}


struct BGridLayout::ItemLayoutData {
	Dimensions	dimensions;

	ItemLayoutData()
	{
		dimensions.x = 0;
		dimensions.y = 0;
		dimensions.width = 1;
		dimensions.height = 1;
	}
};


class BGridLayout::RowInfoArray {
public:
	RowInfoArray()
	{
	}

	~RowInfoArray()
	{
		for (int32 i = 0; Info* info = (Info*)fInfos.ItemAt(i); i++)
			delete info;
	}

	int32 Count() const
	{
		return fInfos.CountItems();
	}

	float Weight(int32 index) const
	{
		if (Info* info = _InfoAt(index))
			return info->weight;
		return 1;
	}

	void SetWeight(int32 index, float weight)
	{
		if (Info* info = _InfoAt(index, true))
			info->weight = weight;
	}

	float MinSize(int32 index) const
	{
		if (Info* info = _InfoAt(index))
			return info->minSize;
		return -1;
	}

	void SetMinSize(int32 index, float size)
	{
		if (Info* info = _InfoAt(index, true))
			info->minSize = size;
	}

	float MaxSize(int32 index) const
	{
		if (Info* info = _InfoAt(index))
			return info->maxSize;
		return B_SIZE_UNLIMITED;
	}

	void SetMaxSize(int32 index, float size)
	{
		if (Info* info = _InfoAt(index, true))
			info->maxSize = size;
	}

private:
	struct Info {
		float	weight;
		float	minSize;
		float	maxSize;
	};

	Info* _InfoAt(int32 index) const
	{
		return (Info*)fInfos.ItemAt(index);
	}

	Info* _InfoAt(int32 index, bool resize)
	{
		if (index < 0 || index >= MAX_COLUMN_ROW_COUNT)
			return NULL;

		// resize, if necessary and desired
		int32 count = Count();
		if (index >= count) {
			if (!resize)
				return NULL;

			for (int32 i = count; i <= index; i++) {
				Info* info = new Info;
				info->weight = 1;
				info->minSize = 0;
				info->maxSize = B_SIZE_UNLIMITED;
				fInfos.AddItem(info);
			}
		}

		return _InfoAt(index);
	}

	BList		fInfos;
};


BGridLayout::BGridLayout(float horizontal, float vertical)
	:
	fGrid(NULL),
	fColumnCount(0),
	fRowCount(0),
	fRowInfos(new RowInfoArray),
	fColumnInfos(new RowInfoArray),
	fMultiColumnItems(0),
	fMultiRowItems(0)
{
	SetSpacing(horizontal, vertical);
}


BGridLayout::BGridLayout(BMessage* from)
	:
	BTwoDimensionalLayout(BUnarchiver::PrepareArchive(from)),
	fGrid(NULL),
	fColumnCount(0),
	fRowCount(0),
	fRowInfos(new RowInfoArray),
	fColumnInfos(new RowInfoArray),
	fMultiColumnItems(0),
	fMultiRowItems(0)
{
	int32 rows;
	int32 columns;
	BUnarchiver unarchiver(from);

	if (from->FindInt32(kRowCountField, &rows) != B_OK)
		fRowCount = 0;

	if (from->FindInt32(kColumnCountField, &columns) != B_OK)
		fColumnCount = 0;

	// sets fColumnCount && fRowCount on success
	if (!_ResizeGrid(columns, rows)) {
		unarchiver.Finish(B_NO_MEMORY);
		return;
	}

	for (int32 i = 0; i < fRowCount; i++) {
		float getter;
		if (from->FindFloat(kRowWeightField, i, &getter) == B_OK)
			fRowInfos->SetWeight(i, getter);

		if (from->FindFloat(kRowMinSizeField, i, &getter) == B_OK)
			fRowInfos->SetMinSize(i, getter);

		if (from->FindFloat(kRowMaxSizeField, i, &getter) == B_OK)
			fRowInfos->SetMaxSize(i, getter);
	}

	for (int32 i = 0; i < fColumnCount; i++) {
		float getter;
		if (from->FindFloat(kColumnWeightField, i, &getter) == B_OK)
			fColumnInfos->SetWeight(i, getter);

		if (from->FindFloat(kColumnMinSizeField, i, &getter) == B_OK)
			fColumnInfos->SetMinSize(i, getter);

		if (from->FindFloat(kColumnMaxSizeField, i, &getter) == B_OK)
			fColumnInfos->SetMaxSize(i, getter);
	}
}


BGridLayout::~BGridLayout()
{
	delete fRowInfos;
	delete fColumnInfos;
}


int32
BGridLayout::CountColumns() const
{
	return fColumnCount;
}


int32
BGridLayout::CountRows() const
{
	return fRowCount;
}


float
BGridLayout::HorizontalSpacing() const
{
	return fHSpacing;
}


float
BGridLayout::VerticalSpacing() const
{
	return fVSpacing;
}


void
BGridLayout::SetHorizontalSpacing(float spacing)
{
	if (spacing != fHSpacing) {
		fHSpacing = spacing;

		InvalidateLayout();
	}
}


void
BGridLayout::SetVerticalSpacing(float spacing)
{
	if (spacing != fVSpacing) {
		fVSpacing = spacing;

		InvalidateLayout();
	}
}


void
BGridLayout::SetSpacing(float horizontal, float vertical)
{
	if (horizontal != fHSpacing || vertical != fVSpacing) {
		fHSpacing = horizontal;
		fVSpacing = vertical;

		InvalidateLayout();
	}
}


float
BGridLayout::ColumnWeight(int32 column) const
{
	return fColumnInfos->Weight(column);
}


void
BGridLayout::SetColumnWeight(int32 column, float weight)
{
	fColumnInfos->SetWeight(column, weight);
}


float
BGridLayout::MinColumnWidth(int32 column) const
{
	return fColumnInfos->MinSize(column);
}


void
BGridLayout::SetMinColumnWidth(int32 column, float width)
{
	fColumnInfos->SetMinSize(column, width);
}


float
BGridLayout::MaxColumnWidth(int32 column) const
{
	return fColumnInfos->MaxSize(column);
}


void
BGridLayout::SetMaxColumnWidth(int32 column, float width)
{
	fColumnInfos->SetMaxSize(column, width);
}


float
BGridLayout::RowWeight(int32 row) const
{
	return fRowInfos->Weight(row);
}


void
BGridLayout::SetRowWeight(int32 row, float weight)
{
	fRowInfos->SetWeight(row, weight);
}


float
BGridLayout::MinRowHeight(int row) const
{
	return fRowInfos->MinSize(row);
}


void
BGridLayout::SetMinRowHeight(int32 row, float height)
{
	fRowInfos->SetMinSize(row, height);
}


float
BGridLayout::MaxRowHeight(int32 row) const
{
	return fRowInfos->MaxSize(row);
}


void
BGridLayout::SetMaxRowHeight(int32 row, float height)
{
	fRowInfos->SetMaxSize(row, height);
}


BLayoutItem*
BGridLayout::AddView(BView* child)
{
	return BTwoDimensionalLayout::AddView(child);
}


BLayoutItem*
BGridLayout::AddView(int32 index, BView* child)
{
	return BTwoDimensionalLayout::AddView(index, child);
}


BLayoutItem*
BGridLayout::AddView(BView* child, int32 column, int32 row, int32 columnCount,
	int32 rowCount)
{
	if (!child)
		return NULL;

	BLayoutItem* item = new BViewLayoutItem(child);
	if (!AddItem(item, column, row, columnCount, rowCount)) {
		delete item;
		return NULL;
	}

	return item;
}


bool
BGridLayout::AddItem(BLayoutItem* item)
{
	// find a free spot
	for (int32 row = 0; row < fRowCount; row++) {
		for (int32 column = 0; column < fColumnCount; column++) {
			if (_IsGridCellEmpty(row, column))
				return AddItem(item, column, row, 1, 1);
		}
	}

	// no free spot, start a new column
	return AddItem(item, fColumnCount, 0, 1, 1);
}


bool
BGridLayout::AddItem(int32 index, BLayoutItem* item)
{
	return AddItem(item);
}


bool
BGridLayout::AddItem(BLayoutItem* item, int32 column, int32 row,
	int32 columnCount, int32 rowCount)
{
	if (!_AreGridCellsEmpty(column, row, columnCount, rowCount))
		return false;

	bool success = BTwoDimensionalLayout::AddItem(-1, item);
	if (!success)
		return false;

	// set item dimensions
	if (ItemLayoutData* data = _LayoutDataForItem(item)) {
		data->dimensions.x = column;
		data->dimensions.y = row;
		data->dimensions.width = columnCount;
		data->dimensions.height = rowCount;
	}

	if (!_InsertItemIntoGrid(item)) {
		RemoveItem(item);
		return false;
	}

	if (columnCount > 1)
		fMultiColumnItems++;
	if (rowCount > 1)
		fMultiRowItems++;

	return success;
}


status_t
BGridLayout::Archive(BMessage* into, bool deep) const
{
	BArchiver archiver(into);
	status_t err = BTwoDimensionalLayout::Archive(into, deep);

	if (err == B_OK)
		err = into->AddInt32(kRowCountField, fRowCount);
	if (err == B_OK)
		err = into->AddInt32(kColumnCountField, fColumnCount);

	for (int32 i = 0; i < fRowCount && err == B_OK; i++) {
		err = into->AddFloat(kRowWeightField, fRowInfos->Weight(i));
		if (err == B_OK)
			err = into->AddFloat(kRowMinSizeField, fRowInfos->MinSize(i));
		if (err == B_OK)
			err = into->AddFloat(kRowMaxSizeField, fRowInfos->MaxSize(i));
	}

	for (int32 i = 0; i < fColumnCount && err == B_OK; i++) {
		err = into->AddFloat(kColumnWeightField, fRowInfos->Weight(i));
		if (err == B_OK)
			err = into->AddFloat(kColumnMinSizeField, fRowInfos->MinSize(i));
		if (err == B_OK)
			err = into->AddFloat(kColumnMaxSizeField, fRowInfos->MaxSize(i));
	}

	return archiver.Finish(err);
}


BArchivable*
BGridLayout::Instantiate(BMessage* from)
{
	if (validate_instantiation(from, "BGridLayout"))
		return new BGridLayout(from);
	return NULL;
}


status_t
BGridLayout::ItemArchived(BMessage* into, BLayoutItem* item, int32 index) const
{
	ItemLayoutData* data =	_LayoutDataForItem(item);
	if (!data) // TODO: remove this check once AddItem() returns a bool
		return B_ERROR;

	status_t err = into->AddInt32(kItemX, data->dimensions.x);
	if (err == B_OK)
		err = into->AddInt32(kItemY, data->dimensions.y);
	if (err == B_OK)
		err = into->AddInt32(kItemWidth, data->dimensions.width);
	if (err == B_OK)
		err = into->AddInt32(kItemHeight, data->dimensions.height);

	return err;
}


status_t
BGridLayout::ItemUnarchived(const BMessage* from,
	BLayoutItem* item, int32 index)
{
	ItemLayoutData* data = _LayoutDataForItem(item);
	if (!data) { // TODO: remove this check once AddItem() returns a bool
		data = new ItemLayoutData();
		item->SetLayoutData(data);
	}

	Dimensions& dimensions = data->dimensions;
	status_t err = from->FindInt32(kItemX, index, &dimensions.x);
	if (err == B_OK)
		err = from->FindInt32(kItemY, index, &dimensions.y);

	if (err == B_OK)
		err = from->FindInt32(kItemWidth, index, &dimensions.width);

	if (err == B_OK)
		err = from->FindInt32(kItemHeight, index, &dimensions.height);

	if (err == B_OK && !_AreGridCellsEmpty(dimensions.x, dimensions.y,
		dimensions.width, dimensions.height))
		err = B_BAD_DATA;

	if (err == B_OK && !_InsertItemIntoGrid(item))
		err = B_NO_MEMORY;

	if (err == B_OK && dimensions.width > 1)
		fMultiColumnItems++;
	if (err == B_OK && dimensions.height > 1)
		fMultiRowItems++;

	return err;
}


void
BGridLayout::ItemAdded(BLayoutItem* item)
{
	item->SetLayoutData(new ItemLayoutData);
}


void
BGridLayout::ItemRemoved(BLayoutItem* item)
{
	ItemLayoutData* data = _LayoutDataForItem(item);
// TODO: Once ItemAdded() returns a bool, we can remove this check.
	if (!data)
		return;

	Dimensions itemDimensions = data->dimensions;
	item->SetLayoutData(NULL);
	delete data;

	if (itemDimensions.width > 1)
		fMultiColumnItems--;
	if (itemDimensions.height > 1)
		fMultiRowItems--;

	// remove the item from the grid
	for (int x = 0; x < itemDimensions.width; x++) {
		for (int y = 0; y < itemDimensions.height; y++)
			fGrid[itemDimensions.x + x][itemDimensions.y + y] = NULL;
	}

	// check whether we can shrink the grid
	if (itemDimensions.x + itemDimensions.width == fColumnCount
		|| itemDimensions.y + itemDimensions.height == fRowCount) {
		int32 columnCount = fColumnCount;
		int32 rowCount = fRowCount;

		// check for empty columns
		bool empty = false;
		for (; columnCount > 0; columnCount--) {
			for (int32 row = 0; empty && row < rowCount; row++)
				empty &= (fGrid[columnCount - 1][row] == NULL);

			if (!empty)
				break;
		}

		// check for empty rows
		empty = false;
		for (; rowCount > 0; rowCount--) {
			for (int32 column = 0; empty && column < columnCount; column++)
				empty &= (fGrid[column][rowCount - 1] == NULL);

			if (!empty)
				break;
		}

		// resize the grid
		if (columnCount != fColumnCount || rowCount != fRowCount)
			_ResizeGrid(columnCount, rowCount);
	}
}


bool
BGridLayout::HasMultiColumnItems()
{
	return (fMultiColumnItems > 0);
}


bool
BGridLayout::HasMultiRowItems()
{
	return (fMultiRowItems > 0);
}


int32
BGridLayout::InternalCountColumns()
{
	return fColumnCount;
}


int32
BGridLayout::InternalCountRows()
{
	return fRowCount;
}


void
BGridLayout::GetColumnRowConstraints(enum orientation orientation, int32 index,
	ColumnRowConstraints* constraints)
{
	if (orientation == B_HORIZONTAL) {
		constraints->min = MinColumnWidth(index);
		constraints->max = MaxColumnWidth(index);
		constraints->weight = ColumnWeight(index);
	} else {
		constraints->min = MinRowHeight(index);
		constraints->max = MaxRowHeight(index);
		constraints->weight = RowWeight(index);
	}
}


void
BGridLayout::GetItemDimensions(BLayoutItem* item, Dimensions* dimensions)
{
	if (ItemLayoutData* data = _LayoutDataForItem(item))
		*dimensions = data->dimensions;
}


bool
BGridLayout::_IsGridCellEmpty(int32 column, int32 row)
{
	if (column < 0 || row < 0)
		return false;
	if (column >= fColumnCount || row >= fRowCount)
		return true;

	return (fGrid[column][row] == NULL);
}


bool
BGridLayout::_AreGridCellsEmpty(int32 column, int32 row, int32 columnCount,
	int32 rowCount)
{
	if (column < 0 || row < 0)
		return false;
	int32 toColumn = min_c(column + columnCount, fColumnCount);
	int32 toRow = min_c(row + rowCount, fRowCount);

	for (int32 x = column; x < toColumn; x++) {
		for (int32 y = row; y < toRow; y++) {
			if (fGrid[x][y] != NULL)
				return false;
		}
	}

	return true;
}


bool
BGridLayout::_InsertItemIntoGrid(BLayoutItem* item)
{
	BGridLayout::ItemLayoutData* data = _LayoutDataForItem(item);
	int32 column = data->dimensions.x;
	int32 columnCount = data->dimensions.width;
	int32 row = data->dimensions.y;
	int32 rowCount = data->dimensions.height;

	// resize the grid, if necessary
	int32 newColumnCount = max_c(fColumnCount, column + columnCount);
	int32 newRowCount = max_c(fRowCount, row + rowCount);
	if (newColumnCount > fColumnCount || newRowCount > fRowCount) {
		if (!_ResizeGrid(newColumnCount, newRowCount))
			return false;
	}

	// enter the item in the grid
	for (int32 x = 0; x < columnCount; x++) {
		for (int32 y = 0; y < rowCount; y++) {
			if (x == 0 && y == 0)
				fGrid[column + x][row + y] = item;
			else
				fGrid[column + x][row + y] = OCCUPIED_GRID_CELL;
		}
	}
	return true;
}


bool
BGridLayout::_ResizeGrid(int32 columnCount, int32 rowCount)
{
	if (columnCount == fColumnCount && rowCount == fRowCount)
		return true;

	int32 rowsToKeep = min_c(rowCount, fRowCount);

	// allocate new grid
	BLayoutItem*** grid = new(nothrow) BLayoutItem**[columnCount];
	if (!grid)
		return false;
	memset(grid, 0, sizeof(BLayoutItem**) * columnCount);

	bool success = true;
	for (int32 i = 0; i < columnCount; i++) {
		BLayoutItem** column = new(nothrow) BLayoutItem*[rowCount];
		if (!column) {
			success = false;
			break;
		}
		grid[i] = column;

		memset(column, 0, sizeof(BLayoutItem*) * rowCount);
		if (i < fColumnCount && rowsToKeep > 0)
			memcpy(column, fGrid[i], sizeof(BLayoutItem*) * rowsToKeep);
	}

	// if everything went fine, set the new grid
	if (success) {
		swap(grid, fGrid);
		swap(columnCount, fColumnCount);
		swap(rowCount, fRowCount);
	}

	// delete the old, respectively on error the partially created grid
	for (int32 i = 0; i < columnCount; i++)
		delete grid[i];
	delete[] grid;

	return success;
}


BGridLayout::ItemLayoutData*
BGridLayout::_LayoutDataForItem(BLayoutItem* item) const
{
	if (!item)
		return NULL;
	return (ItemLayoutData*)item->LayoutData();
}
