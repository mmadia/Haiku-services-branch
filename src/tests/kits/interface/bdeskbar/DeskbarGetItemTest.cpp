/*
	$Id: DeskbarGetItemTest.cpp,v 1.2 2002/09/13 03:51:09 jrand Exp $
	
	This file implements tests for the following use cases of BDeskbar:
	  - Count Items
	  - Has Item 1
	  - Has Item 2
	  - Get Item Info 1
	  - Get Item Info 2
	
	*/


#include "DeskbarGetItemTest.h"
#include <Deskbar.h>


/*
 *  Method:  DeskbarGetItemTest::DeskbarGetItemTest()
 *   Descr:  This is the constructor for this class.
 */
		

	DeskbarGetItemTest::DeskbarGetItemTest(std::string name) :
		TestCase(name)
{
	}


/*
 *  Method:  DeskbarGetItemTest::~DeskbarGetItemTest()
 *   Descr:  This is the destructor for this class.
 */
 

	DeskbarGetItemTest::~DeskbarGetItemTest()
{
	}


/*
 *  Method:  DeskbarGetItemTest::PerformTest()
 *   Descr:  This member function iterates over all of the items in the 
 *           deskbar shelf and gets information about each item and confirms
 *           that all of the information is self-consistent.
 */


	void DeskbarGetItemTest::PerformTest(void)
{
	BDeskbar myDeskbar;
	
	int32 itemCount = myDeskbar.CountItems();
	assert(itemCount >= 0);
	
	
	int32 id=0;
	int32 lastFoundId = -1;
	char buffer[1024];
	const char *name = buffer;
	
	assert(!myDeskbar.HasItem("NameThatDoesNotExistWeHope!!"));
	assert(myDeskbar.GetItemInfo("NameThatDoesNotExistWeHope!!", &id) == B_NAME_NOT_FOUND);
	
	for(id = 0; ((id < 10000) && (itemCount > 0)); id++) {
		int32 tmpId;
		
		if (myDeskbar.HasItem(id)) {
			itemCount--;
			
			name = NULL;
			assert(myDeskbar.GetItemInfo(id, &name) == B_BAD_VALUE);
			
			name = buffer;
			assert(myDeskbar.GetItemInfo(id, &name) == B_OK);
			
			assert(name != buffer);
			assert(myDeskbar.HasItem(name));
			assert(myDeskbar.GetItemInfo(name, &tmpId) == B_OK);
			delete[] name;
			name = buffer;
			assert(tmpId == id);
			lastFoundId = id;
		} else {
			assert(myDeskbar.GetItemInfo(id, &name) == B_NAME_NOT_FOUND);
			assert(name == buffer);
		}
	}
	assert(itemCount == 0);
	if (lastFoundId >= 0) {
		for(id = lastFoundId + 1; id < lastFoundId + 200; id++) {
			assert(!myDeskbar.HasItem(id));
			assert(myDeskbar.GetItemInfo(id, &name) == B_NAME_NOT_FOUND);
			assert(name == buffer);
		}
	}
}
	

/*
 *  Method:  PropertyConstructionTest::suite()
 *   Descr:  This static member function returns a test caller for performing 
 *           all combinations of "DeskbarGetItemTest".
 */

 Test *DeskbarGetItemTest::suite(void)
{	
	typedef CppUnit::TestCaller<DeskbarGetItemTest>
		DeskbarGetItemTestCaller;
		
	return(new DeskbarGetItemTestCaller("BDeskbar::Get Item Test", &DeskbarGetItemTest::PerformTest));
	}