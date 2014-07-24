/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2012 Andres Hernandez

File <Main.cpp> :
Copyright (C) 2012 Andres Hernandez

Vireio Perception Version History:
v1.0.0 2012 by Andres Hernandez
v1.0.X 2013 by John Hicks, Neil Schneider
v1.1.x 2013 by Primary Coding Author: Chris Drain
Team Support: John Hicks, Phil Larkson, Neil Schneider
v2.0.x 2013 by Denis Reischl, Neil Schneider, Joshua Brown

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "comm.h"
#include <windows.h>
#include <d3d11.h>
#include <stdio.h>
#include "BaseDXGIFactory.h"
#include "VireioDXGIFactory.h"


// Function pointer trypedefs
typedef HRESULT(WINAPI *LPCreateDXGIFactory)(
	_In_   REFIID riid,
	_Out_  void **ppFactory
	);

//typedef HRESULT(WINAPI *LPCreateDXGIFactory2)(
//	_In_   UINT flags,
//	_In_   const IID &riid,
//	_Out_  void **ppFactory
//	);
//typedef HRESULT(WINAPI *LPDXGIGetDebugInterface)(
//	REFIID riid,
//	void **ppDebug
//	);
//typedef HRESULT(WINAPI *LPDXGIGetDebugInterface1)(
//	UINT Flags,
//	REFIID riid,
//	_Out_  void **ppOut
//	);

HMODULE g_hDll = NULL;
LPCreateDXGIFactory g_pfnCreateDXGIFactory = NULL;
LPCreateDXGIFactory g_pfnCreateDXGIFactory1 = NULL;
//LPCreateDXGIFactory2 g_pfnCreateDXGIFactory2 = NULL;
//LPDXGIGetDebugInterface g_pfnDXGIGetDebugInterface = NULL;
//LPDXGIGetDebugInterface1 g_pfnDXGIGetDebugInterface1 = NULL;

static bool LoadDll()
{
	if(g_hDll)
		return true;

	// Load DLL
	char szBuff[MAX_PATH+64];
	GetSystemDirectory(szBuff, sizeof(szBuff));
	szBuff[MAX_PATH] = 0;
	strcat(szBuff, "\\dxgi.dll");
	g_hDll = LoadLibrary(szBuff);
	if(!g_hDll)
		return false;

	// Get function addresses
	g_pfnCreateDXGIFactory = (LPCreateDXGIFactory)GetProcAddress(g_hDll, "CreateDXGIFactory");
	if (!g_pfnCreateDXGIFactory)
	{
		FreeLibrary(g_hDll);
		return false;
	}

	g_pfnCreateDXGIFactory1 = (LPCreateDXGIFactory)GetProcAddress(g_hDll, "CreateDXGIFactory1");
	if (!g_pfnCreateDXGIFactory1)
	{
		FreeLibrary(g_hDll);
		return false;
	}

	//g_pfnCreateDXGIFactory2 = (LPCreateDXGIFactory2)GetProcAddress(g_hDll, "CreateDXGIFactory2");
	//if (!g_pfnCreateDXGIFactory2)
	//{
	//	FreeLibrary(g_hDll);
	//	return false;
	//}

	//g_pfnDXGIGetDebugInterface = (LPDXGIGetDebugInterface)GetProcAddress(g_hDll, "DXGIGetDebugInterface");
	//if (!g_pfnDXGIGetDebugInterface)
	//{
	//	FreeLibrary(g_hDll);
	//	return false;
	//}

	//g_pfnDXGIGetDebugInterface1 = (LPDXGIGetDebugInterface1)GetProcAddress(g_hDll, "DXGIGetDebugInterface1");
	//if (!g_pfnDXGIGetDebugInterface1)
	//{
	//	FreeLibrary(g_hDll);
	//	return false;
	//}

	// Done
	return true;
}

HRESULT WINAPI CreateDXGIFactory(
	_In_   REFIID riid,
	_Out_  void **ppFactory
	)
{
	Log("CreateDXGIFactory\n");

	if (!LoadDll())
		return S_FALSE;

	HRESULT result = g_pfnCreateDXGIFactory(riid, ppFactory);

	if (result != S_OK)
	{
		Log("call fail %d\n", result);
		return result;
	}


	*ppFactory = new VireioDXGIFactory((IDXGIFactory*)*ppFactory);

	Log("CreateDXGIFactory %p", *ppFactory);

	SetFactory(*ppFactory);

	return result;
}

HRESULT WINAPI CreateDXGIFactory1(
	_In_   REFIID riid,
	_Out_  void **ppFactory
	)
{
	Log("CreateDXGIFactory1\n");

	if (!LoadDll())
		return S_FALSE;

	HRESULT result = g_pfnCreateDXGIFactory1(riid, ppFactory);

	if (result != S_OK)
	{
		Log("call fail %d\n", result);
		return result;
	}

	*ppFactory = new VireioDXGIFactory((IDXGIFactory*)*ppFactory);

	Log("CreateDXGIFactory1 %p", *ppFactory);

	SetFactory(*ppFactory);

	return result;
}

/*
HRESULT WINAPI CreateDXGIFactory2(
	_In_   UINT flags,
	_In_   const IID &riid,
	_Out_  void **ppFactory
	)
{
	Log("CreateDXGIFactory2\n");

	if (!LoadDll())
		return S_FALSE;

	return g_pfnCreateDXGIFactory2(flags, riid, ppFactory);
}

HRESULT WINAPI DXGIGetDebugInterface(
	REFIID riid,
	void **ppDebug
	)
{
	Log("DXGIGetDebugInterface\n");

	if (!LoadDll())
		return S_FALSE;

	return g_pfnDXGIGetDebugInterface(riid, ppDebug);
}

HRESULT WINAPI DXGIGetDebugInterface1(
	UINT Flags,
	REFIID riid,
	_Out_  void **ppOut
	)
{
	Log("DXGIGetDebugInterface1\n");

	if (!LoadDll())
		return S_FALSE;

	return g_pfnDXGIGetDebugInterface1(Flags, riid, ppOut);
}
*/
