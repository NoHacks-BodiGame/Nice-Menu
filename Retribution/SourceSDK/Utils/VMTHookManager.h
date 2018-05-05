#pragma once
#define READABLE_AND_WRITEABLE (PAGE_READONLY|PAGE_READWRITE|PAGE_WRITECOPY|PAGE_EXECUTE_READ|PAGE_EXECUTE_READWRITE|PAGE_EXECUTE_WRITECOPY)
#include <Windows.h>

class VMTHookManager
{
public:
	VMTHookManager(void* _interface);
	void Init(void* _interface);
public:
	void HookFunction(int _index, void* _hookedFunction);
	void* GetOriginalFunction(int _index);
	void Hook(void* _interface);
	void UnHook(void* _interface);
private:
	int GetTableSize(void* _interface);
	bool CanReadPtr(void* _tablePtr);
private:
	void* originalTable;
	void* newTable;
	int tableSize;
};