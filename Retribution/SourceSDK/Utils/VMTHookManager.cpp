#include "VMTHookManager.h"

VMTHookManager::VMTHookManager(void* _interface)
{
	this->Init(_interface);
}

void VMTHookManager::Init(void* _interface)
{
	this->tableSize = this->GetTableSize(_interface);
	
	this->newTable = VirtualAlloc(nullptr, sizeof(void*) * this->tableSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(this->newTable, this->originalTable, sizeof(void*) * this->tableSize);

	this->Hook(_interface);
}

int VMTHookManager::GetTableSize(void* _interface)
{
	this->originalTable = *(void**)_interface;

	int index = 0;

	while (this->CanReadPtr(((void**)this->originalTable)[index]))
		++index;

	return index;
};

bool VMTHookManager::CanReadPtr(void* _tablePtr)
{
	if (!_tablePtr)
		return false;

	MEMORY_BASIC_INFORMATION mbi;

	if (!VirtualQuery(_tablePtr, &mbi, sizeof(MEMORY_BASIC_INFORMATION)))
		return false;

	if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
		return false;

	if (!(mbi.Protect & (READABLE_AND_WRITEABLE)))
		return false;

	return true;
}

void VMTHookManager::HookFunction(int _index, void* _hookedFunction)
{
	if (this->newTable && _index && _index < this->tableSize)
		((void**)this->newTable)[_index] = _hookedFunction;
}

void* VMTHookManager::GetOriginalFunction(int _index)
{
	return (this->originalTable && _index && _index < this->tableSize) ? ((void**)this->originalTable)[_index] : nullptr;
}

void VMTHookManager::Hook(void* _interface)
{
	if (this->newTable)
		*(void**)_interface = this->newTable;
}

void VMTHookManager::UnHook(void* _interface)
{
	if (this->originalTable)
		*(void**)_interface = this->originalTable;
}