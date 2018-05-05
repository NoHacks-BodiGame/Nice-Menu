#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "..\Definitions\Definitions.h"

class Interface
{
private:
	friend class IBaseClientDLL;
	friend class ClientModeShared;
	friend class IVEngineClient;
	friend class IClientEntityList;
	friend class IEngineTrace;
	friend class IPanel;
	friend class ISurface;
	friend class IInputSystem;
	friend class IInputInternal;
	friend class CBaseEntity;
	friend class IGameEvent;
	friend class CGlobalVarsBase;
public:
	IBaseClientDLL* Client();
	ClientModeShared* ClientMode();
	IVEngineClient* Engine();
	IClientEntityList* EntityList();
	IEngineTrace* EngineTrace();
	IPanel* Panel();
	ISurface* Surface();
	IInputSystem* InputSystem();
	IInputInternal* InputInternal();
	IGameEvent* GameEvent();
	CGlobalVarsBase* Globals();
private:
	IBaseClientDLL* clientInterface;
	ClientModeShared* clientModeInterface;
	IVEngineClient* engineInterface;
	IClientEntityList* entityListInterface;
	IEngineTrace* engineTraceInterface;
	IPanel* panelInterface;
	ISurface* surfaceInterface;
	IInputSystem* inputSystemInterface;
	IInputInternal* inputInternalInterface;
	IGameEvent* gameEventInterface;
	CGlobalVarsBase* GlobalsInterface;
private:
	template<typename T>
	T* FindInterface(const std::string _moduleName, const std::string &_interfaceName)
	{
		typedef void* (*CreateInterfaceFn)(const char*, int*);
		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandle(_moduleName.c_str()), "CreateInterface");

		void* interfacePtr = nullptr;

		for (int i = 1; i < 100; ++i)
		{
			std::ostringstream interfaceNameStream;
			interfaceNameStream << _interfaceName << std::setw(3) << std::setfill('0') << i;

			interfacePtr = (void*)CreateInterface(interfaceNameStream.str().c_str(), NULL);

			if (interfacePtr)
			{
				std::cout << interfaceNameStream.str() << std::endl;
				break;
			}
		}

		return (T*)interfacePtr;
	}
protected:
	template<typename functionType, typename ...typesOfFunctionParameters, class C>
	functionType __forceinline CallVirtualFunction(C* _ECX, int _functionIndex, typesOfFunctionParameters... _functionParameters)
	{
		typedef functionType(__thiscall* functionPrototype)(void*, typesOfFunctionParameters...);
		functionPrototype originalFunction = (functionPrototype)this->GetVirtualFunction(_ECX, _functionIndex);
		return originalFunction(_ECX, _functionParameters...);
	}
private:
	__forceinline void* GetVirtualFunction(void* _base, int _index)
	{
		void** VTable = *(void***)_base;
		return VTable[_index];
	}
};

extern Interface gInterface;