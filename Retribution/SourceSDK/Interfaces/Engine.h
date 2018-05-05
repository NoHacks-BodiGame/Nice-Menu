#pragma once
#include "Interfaces.h"
#include "..\Misc\player_info.h"

class IVEngineClient
{
public:
	inline void GetScreenSize(int &_width, int &_height);
	inline bool GetPlayerInfo(int _entNum, player_info_t* _info);
	inline int GetLocalPlayer();
	inline void SetViewAngles(QAngle &_viewAngles);
	inline int GetMaxClients();
	inline bool IsInGame();
	inline bool IsConnected();
	inline VMatrix& WorldToScreenMatrix();
	inline void ClientCmd(const char* _cmdString);
};

inline void IVEngineClient::GetScreenSize(int &_width, int &_height)
{
	return gInterface.CallVirtualFunction<void>(this, Indexes::Engine::GetScreenSize, std::ref(_width), std::ref(_height));
}

inline bool IVEngineClient::GetPlayerInfo(int _entNum, player_info_t* _info)
{
	return gInterface.CallVirtualFunction<bool>(this, Indexes::Engine::GetPlayerInfo, _entNum, _info);
}

inline int IVEngineClient::GetLocalPlayer()
{
	return gInterface.CallVirtualFunction<int>(this, Indexes::Engine::GetLocalPlayer);
}

inline void IVEngineClient::SetViewAngles(QAngle &_viewAngles)
{
	return gInterface.CallVirtualFunction<void>(this, Indexes::Engine::SetViewAngles, std::ref(_viewAngles));
}

inline int IVEngineClient::GetMaxClients()
{
	return gInterface.CallVirtualFunction<int>(this, Indexes::Engine::GetMaxClients);
}

inline bool IVEngineClient::IsInGame()
{
	return gInterface.CallVirtualFunction<bool>(this, Indexes::Engine::IsInGame);
}

inline bool IVEngineClient::IsConnected()
{
	return gInterface.CallVirtualFunction<bool>(this, Indexes::Engine::IsConnected);
}

inline VMatrix& IVEngineClient::WorldToScreenMatrix()
{
	return gInterface.CallVirtualFunction<VMatrix&>(this, Indexes::Engine::WorldToScreenMatrix);
}

inline void IVEngineClient::ClientCmd(const char* _cmdString)
{
	return gInterface.CallVirtualFunction<void>(this, Indexes::Engine::ClientCmd, _cmdString);
}
