/*
 * Copyright 2006, Haiku.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Stephan Aßmus <superstippi@gmx.de>
 */

#include "CommandStack.h"

#include <stdio.h>
#include <string.h>

#include <Locker.h>
#include <String.h>

#include "Command.h"

// constructor
CommandStack::CommandStack()
	: BLocker("history"),
	  Observable(),
	  fSavedCommand(NULL)
{
}

// destructor
CommandStack::~CommandStack()
{
	Clear();
}

// Perform
status_t
CommandStack::Perform(Command* command)
{
	status_t ret = command ? B_OK : B_BAD_VALUE;
	if (Lock()) {
		if (ret == B_OK)
			ret = command->InitCheck();
	
		if (ret == B_OK)
			ret = command->Perform();
	
		if (ret == B_OK)
			ret = AddCommand(command);
	
		if (ret != B_OK) {
			// no one else feels responsible...
			delete command;
		}
		Unlock();
	}
	return ret;
}


// AddCommand
status_t
CommandStack::AddCommand(Command* command)
{
	status_t status = B_ERROR;
	if (Lock()) {
		if (command && (status = command->InitCheck()) == B_OK) {
			// try to collapse commands to a single command
			bool add = true;
			if (!fUndoHistory.empty()) {
				if (Command* top = fUndoHistory.top()) {
					if (top->CombineWithNext(command)) {
						add = false;
						delete command;
					} else if (command->CombineWithPrevious(top)) {
						fUndoHistory.pop();
						delete top;
					}
				}
			}
			if (add)
				fUndoHistory.push(command);

			// the redo stack needs to be empty
			// as soon as an command was added (also in case of collapsing)
			while (!fRedoHistory.empty()) {
				delete fRedoHistory.top();
				fRedoHistory.pop();
			}
		}
		Unlock();
	}

	Notify();

	return status;
}

// Undo
status_t
CommandStack::Undo()
{
	status_t status = B_ERROR;
	if (Lock()) {
		if (!fUndoHistory.empty()) {
			Command* command = fUndoHistory.top();
			fUndoHistory.pop();
			status = command->Undo();
			if (status == B_OK)
				fRedoHistory.push(command);
			else
				fUndoHistory.push(command);
		}
		Unlock();
	}

	Notify();

	return status;
}

// Redo
status_t
CommandStack::Redo()
{
	status_t status = B_ERROR;
	if (Lock()) {
		if (!fRedoHistory.empty()) {
			Command* command = fRedoHistory.top();
			fRedoHistory.pop();
			status = command->Redo();
			if (status == B_OK)
				fUndoHistory.push(command);
			else
				fRedoHistory.push(command);
		}
		Unlock();
	}

	Notify();

	return status;
}

// UndoName
bool
CommandStack::GetUndoName(BString& name)
{
	bool success = false;
	if (Lock()) {
		if (!fUndoHistory.empty()) {
			name << " ";
			fUndoHistory.top()->GetName(name);
			success = true;
		}
		Unlock();
	}
	return success;
}

// RedoName
bool
CommandStack::GetRedoName(BString& name)
{
	bool success = false;
	if (Lock()) {
		if (!fRedoHistory.empty()) {
			name << " ";
			fRedoHistory.top()->GetName(name);
			success = true;
		}
		Unlock();
	}
	return success;
}

// Clear
void
CommandStack::Clear()
{
	if (Lock()) {
		while (!fUndoHistory.empty()) {
			delete fUndoHistory.top();
			fUndoHistory.pop();
		}
		while (!fRedoHistory.empty()) {
			delete fRedoHistory.top();
			fRedoHistory.pop();
		}
		Unlock();
	}

	Notify();
}

// Save
void
CommandStack::Save()
{
	if (Lock()) {
		if (!fUndoHistory.empty())
			fSavedCommand = fUndoHistory.top();
		Unlock();
	}

	Notify();
}

// IsSaved
bool
CommandStack::IsSaved()
{
	bool saved = false;
	if (Lock()) {
		saved = fUndoHistory.empty();
		if (fSavedCommand && !saved) {
			if (fSavedCommand == fUndoHistory.top())
				saved = true;
		}
		Unlock();
	}
	return saved;
}



