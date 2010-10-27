/*
 * Copyright 2010, Haiku.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Clemens Zeidler <haiku@clemens-zeidler.de>
 */

#include "VolumeWatcher.h"

#include <sys/stat.h>

#include <Directory.h>
#include <NodeMonitor.h>
#include <Path.h>
#include <VolumeRoster.h>
#include <Query.h>


#include "IndexServerPrivate.h"


const bigtime_t kSecond = 1000000;


WatchNameHandler::WatchNameHandler(VolumeWatcher* volumeWatcher)
	:
	fVolumeWatcher(volumeWatcher)
{

}


void
WatchNameHandler::EntryCreated(const char *name, ino_t directory, dev_t device,
	ino_t node)
{
	entry_ref ref(device, directory, name);
	fVolumeWatcher->fCreatedList.CurrentList()->push_back(ref);
	fVolumeWatcher->_NewEntriesArrived();
}


void
WatchNameHandler::EntryRemoved(const char *name, ino_t directory, dev_t device,
	ino_t node)
{
	entry_ref ref(device, directory, name);
	fVolumeWatcher->fDeleteList.CurrentList()->push_back(ref);
	fVolumeWatcher->_NewEntriesArrived();
}


void
WatchNameHandler::EntryMoved(const char *name, const char *fromName,
	ino_t from_directory, ino_t to_directory, dev_t device, ino_t node,
	dev_t nodeDevice)
{
	entry_ref ref(device, to_directory, name);
	entry_ref refFrom(device, from_directory, fromName);
	
	fVolumeWatcher->fMovedList.CurrentList()->push_back(ref);
	fVolumeWatcher->fMovedFromList.CurrentList()->push_back(refFrom);
	fVolumeWatcher->_NewEntriesArrived();
}


void
WatchNameHandler::StatChanged(ino_t node, dev_t device, int32 statFields)
{
	if ((statFields & B_STAT_MODIFICATION_TIME) == 0)
		return;
}


AnalyserDispatcher::AnalyserDispatcher()
	:
	BLooper(NULL, B_LOW_PRIORITY),

	fStopped(0)
{

}


AnalyserDispatcher::~AnalyserDispatcher()
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		delete fFileAnalyserList.ItemAt(i);
}


void
AnalyserDispatcher::Stop()
{
	atomic_set(&fStopped, 1);
}


bool
AnalyserDispatcher::Stopped()
{
	return (atomic_get(&fStopped) != 0);
}


void
AnalyserDispatcher::AnalyseEntry(const entry_ref& ref)
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		fFileAnalyserList.ItemAt(i)->AnalyseEntry(ref);
}


void
AnalyserDispatcher::DeleteEntry(const entry_ref& ref)
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		fFileAnalyserList.ItemAt(i)->DeleteEntry(ref);
}


void
AnalyserDispatcher::MoveEntry(const entry_ref& oldRef, const entry_ref& newRef)
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		fFileAnalyserList.ItemAt(i)->MoveEntry(oldRef, newRef);
}


void
AnalyserDispatcher::LastEntry()
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		fFileAnalyserList.ItemAt(i)->LastEntry();
}


bool
AnalyserDispatcher::AddAnalyser(FileAnalyser* analyser)
{
	if (analyser == NULL)
		return false;

	bool result;
	Lock();
	if (_FindAnalyser(analyser->Name())) {
		Unlock();
		return false;
	}
	result = fFileAnalyserList.AddItem(analyser);
	Unlock();
	return result;
}


bool
AnalyserDispatcher::RemoveAnalyser(const BString& name)
{
	Lock();
	FileAnalyser* analyser = _FindAnalyser(name);
	if (analyser) {
		fFileAnalyserList.RemoveItem(analyser);
		delete analyser;
		Unlock();
		return true;
	}
	Unlock();
	return false;
}


FileAnalyser*
AnalyserDispatcher::_FindAnalyser(const BString& name)
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++) {
		FileAnalyser* analyser = fFileAnalyserList.ItemAt(i);
		if (analyser->Name() == name)
			return analyser;
	}
	return NULL;
}


void
AnalyserDispatcher::WriteAnalyserSettings()
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		fFileAnalyserList.ItemAt(i)->Settings()->WriteSettings();
}


void
AnalyserDispatcher::SetSyncPosition(bigtime_t time)
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		fFileAnalyserList.ItemAt(i)->Settings()->SetSyncPosition(time);
}


void
AnalyserDispatcher::SetWatchingStart(bigtime_t time)
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		fFileAnalyserList.ItemAt(i)->Settings()->SetWatchingStart(time);
}


void
AnalyserDispatcher::SetWatchingPosition(bigtime_t time)
{
	for (int i = 0; i < fFileAnalyserList.CountItems(); i++)
		fFileAnalyserList.ItemAt(i)->Settings()->SetWatchingPosition(time);
}


VolumeWorker::VolumeWorker(VolumeWatcher* watcher)
	:
	fVolumeWatcher(watcher),
	fBusy(0)
{

}


void
VolumeWorker::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case kTriggerWork:
			_Work();
			break;

		default:
			BLooper::MessageReceived(message);
	}
}


bool
VolumeWorker::IsBusy()
{
	return (atomic_get(&fBusy) != 0);
}


void
VolumeWorker::_Work()
{
	list_collection collection;
	fVolumeWatcher->GetSecureEntries(collection);

	if (collection.createdList->size() == 0
		&& collection.deletedList->size() == 0
		&& collection.modifiedList->size() == 0
		&& collection.movedList->size() == 0)
		return;

	_SetBusy(true);
	for (unsigned int i = 0; i < collection.createdList->size() || Stopped();
		i++)
		AnalyseEntry(collection.createdList->at(i));
	collection.createdList->clear();

	for (unsigned int i = 0; i < collection.modifiedList->size() || Stopped();
		i++)
		AnalyseEntry(collection.modifiedList->at(i));
	collection.modifiedList->clear();

	for (unsigned int i = 0; i < collection.createdList->size() || Stopped();
		i++)
		AnalyseEntry(collection.createdList->at(i));
	collection.createdList->clear();

	for (unsigned int i = 0; i < collection.movedList->size() || Stopped();
		i++)
		MoveEntry(collection.movedFromList->at(i), collection.movedList->at(i));
	collection.movedList->clear();
	collection.movedFromList->clear();

	LastEntry();
	PostMessage(kTriggerWork);

	_SetBusy(false);
}


void
VolumeWorker::_SetBusy(bool busy)
{
	if (busy)
		atomic_set(&fBusy, 1);
	else
		atomic_set(&fBusy, 0);
}


VolumeWatcherBase::VolumeWatcherBase(const BVolume& volume)
	:
	fVolume(volume),
	fEnabled(true),
	fLastUpdated(0)
{
	ReadSettings();
}


const char* kEnabledAttr = "Enabled";


bool
VolumeWatcherBase::ReadSettings()
{
	// TODO remove this
	BVolume bootVolume;
	BVolumeRoster roster;
	roster.GetBootVolume(&bootVolume);
	if (bootVolume == fVolume) {
		fEnabled = true;
		WriteSettings();
	}

	BDirectory rootDir;
	fVolume.GetRootDirectory(&rootDir);
	BPath path(&rootDir);
	path.Append(kIndexServerDirectory);
	path.Append(kVolumeStatusFileName);
	BFile file(path.Path(), B_READ_ONLY);
	if (file.InitCheck() != B_OK)
		return false;

	uint32 enabled;
	file.WriteAttr(kEnabledAttr, B_UINT32_TYPE, 0, &enabled, sizeof(uint32));
	fEnabled = enabled == 0 ? false : true;

	return true;
}


bool
VolumeWatcherBase::WriteSettings()
{
	BDirectory rootDir;
	fVolume.GetRootDirectory(&rootDir);
	BPath path(&rootDir);
	path.Append(kIndexServerDirectory);
	if (create_directory(path.Path(), 777) != B_OK)
		return false;

	path.Append(kVolumeStatusFileName);
	BFile file(path.Path(), B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);
	if (file.InitCheck() != B_OK)
		return false;

	uint32 enabled = fEnabled ? 1 : 0;
	file.WriteAttr(kEnabledAttr, B_UINT32_TYPE, 0, &enabled, sizeof(uint32));

	return true;
}


SwapEntryRefVector::SwapEntryRefVector()
{
	fCurrentList = &fFirstList;
	fNextList = &fSecondList;
}


EntryRefVector*
SwapEntryRefVector::SwapList()
{
	EntryRefVector* temp = fCurrentList;
	fCurrentList = fNextList;
	fNextList = temp;
	return fCurrentList;
}


EntryRefVector*
SwapEntryRefVector::CurrentList()
{
	return fCurrentList;
}


VolumeWatcher::VolumeWatcher(const BVolume& volume)
	:
	VolumeWatcherBase(volume),

	fWatching(false),
	fWatchNameHandler(this),
	fCatchUpManager(volume)
{
	AddHandler(&fWatchNameHandler);

	fVolumeWorker = new VolumeWorker(this);
	fVolumeWorker->Run();
}


VolumeWatcher::~VolumeWatcher()
{
printf("~VolumeWatcher()\n");
	Stop();
	thread_id threadId = fVolumeWorker->Thread();
	fVolumeWorker->PostMessage(B_QUIT_REQUESTED);
	status_t error;
	wait_for_thread(threadId, &error);
}


void
VolumeWatcher::MessageReceived(BMessage *message)
{
	int32 opcode;
	switch (message->what) {
		case B_QUERY_UPDATE:
			message->FindInt32("opcode", &opcode);
			if (opcode == B_ATTR_CHANGED || opcode == B_ENTRY_CREATED) {
				const char *name;
				ino_t directory;
				dev_t device;
				if ((message->FindString("name", &name) != B_OK) ||
					(message->FindInt64("directory", &directory) != B_OK) ||
					(message->FindInt32("device", &device) != B_OK))
					break;
				entry_ref ref(device, directory, name);
				fModifiedList.CurrentList()->push_back(ref);
				_NewEntriesArrived();
			}
			break;

		default:
			BLooper::MessageReceived(message);
	}
}


bool
VolumeWatcher::StartWatching()
{
	Run();

	watch_volume(fVolume.Device(), B_WATCH_NAME | B_WATCH_STAT,
		&fWatchNameHandler);
	if (fModfiedNotifications.StartWatching(fVolume.Device(), real_time_clock(),
		this) != B_OK)
		return false;
	// set the time after start watching to not miss anything
	fVolumeWorker->SetWatchingStart(real_time_clock_usecs());

	char name[255];
	fVolume.GetName(name);

	fCatchUpManager.CatchUp();

	fWatching = true;
	return true;
}


void
VolumeWatcher::Stop()
{
	
	char name[255];
	fVolume.GetName(name);

	// set the time before stop watching to not miss anything
	fVolumeWorker->SetWatchingPosition(real_time_clock_usecs());

	stop_watching(&fWatchNameHandler);

	fVolumeWorker->WriteAnalyserSettings();

	// don't stop the work because we have to handle all entries after writing
	// the watching position
	//fVolumeWorker->Stop();
	fCatchUpManager.Stop();
}


bool
VolumeWatcher::AddAnalyser(FileAnalyser* analyser)
{
	if (!fVolumeWorker->AddAnalyser(analyser))
		return false;

	Lock();
	if (!fCatchUpManager.AddAnalyser(analyser)) {
		Unlock();
		return false;
	}
	if (fWatching)
		fCatchUpManager.CatchUp();
	Unlock();

	return true;
}


bool
VolumeWatcher::RemoveAnalyser(const BString& name)
{
	if (!fVolumeWorker->RemoveAnalyser(name))
		return false;

	Lock();
	fCatchUpManager.RemoveAnalyser(name);
	Unlock();
	return true;
}


void
VolumeWatcher::GetSecureEntries(list_collection& collection)
{
	collection.createdList = fCreatedList.SwapList();
	collection.deletedList = fDeleteList.SwapList();
	collection.modifiedList = fModifiedList.SwapList();
	collection.movedList = fMovedList.SwapList();
	collection.movedFromList = fMovedFromList.SwapList();
}


bool
VolumeWatcher::FindEntryRef(ino_t node, dev_t device, entry_ref& entry)
{
	return false;
}


void
VolumeWatcher::_NewEntriesArrived()
{
	// The fVolumeWorker has to exist as long as we live so directly post to
	// the queue.
	if (fVolumeWorker->IsBusy())
		return;
	fVolumeWorker->PostMessage(kTriggerWork);
}
