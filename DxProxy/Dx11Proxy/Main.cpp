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
#include "Direct3DDevice11.h"
#include "Direct3DDeviceContext11.h"
#include "VireioD3DProxyDevice.h"
#include "VireioDXGIFactory.h"

// Function pointer trypedefs
typedef HRESULT(WINAPI *LPDirect3DCreate11)(
	_In_   IDXGIAdapter *pAdapter,
	_In_   D3D_DRIVER_TYPE DriverType,
	_In_   HMODULE Software,
	_In_   UINT Flags,
	_In_   const D3D_FEATURE_LEVEL *pFeatureLevels,
	_In_   UINT FeatureLevels,
	_In_   UINT SDKVersion,
	_Out_  ID3D11Device **ppDevice,
	_Out_  D3D_FEATURE_LEVEL *pFeatureLevel,
	_Out_  ID3D11DeviceContext **ppImmediateContext
	);

typedef HRESULT(WINAPI *LPD3D11CreateDeviceAndSwapChain)(
	_In_   IDXGIAdapter *pAdapter,
	_In_   D3D_DRIVER_TYPE DriverType,
	_In_   HMODULE Software,
	_In_   UINT Flags,
	_In_   const D3D_FEATURE_LEVEL *pFeatureLevels,
	_In_   UINT FeatureLevels,
	_In_   UINT SDKVersion,
	_In_   const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
	_Out_  IDXGISwapChain **ppSwapChain,
	_Out_  ID3D11Device **ppDevice,
	_Out_  D3D_FEATURE_LEVEL *pFeatureLevel,
	_Out_  ID3D11DeviceContext **ppImmediateContext
	);

//typedef int (WINAPI *LPD3DPERF_BeginEvent)( D3DCOLOR col, LPCWSTR wszName );
//typedef int (WINAPI *LPD3DPERF_EndEvent)( void );
//typedef void (WINAPI *LPD3DPERF_SetMarker)( D3DCOLOR col, LPCWSTR wszName );
//typedef void (WINAPI *LPD3DPERF_SetRegion)( D3DCOLOR col, LPCWSTR wszName );
//typedef BOOL (WINAPI *LPD3DPERF_QueryRepeatFrame)( void );
//typedef void (WINAPI *LPD3DPERF_SetOptions)( DWORD dwOptions );
//typedef DWORD (WINAPI *LPD3DPERF_GetStatus)( void );

// Globals from d3d9.dll
HMODULE g_hDll = NULL;
LPDirect3DCreate11 g_pfnDirect3DCreate11 = NULL;
LPD3D11CreateDeviceAndSwapChain g_pfnD3D11CreateDeviceAndSwapChain = NULL;
VireioDXGIFactory *g_factory = NULL;

//LPD3DPERF_BeginEvent g_pfnD3DPERF_BeginEvent = NULL;
//LPD3DPERF_EndEvent g_pfnD3DPERF_EndEvent = NULL;
//LPD3DPERF_SetMarker g_pfnD3DPERF_SetMarker = NULL;
//LPD3DPERF_SetRegion g_pfnD3DPERF_SetRegion = NULL;
//LPD3DPERF_QueryRepeatFrame g_pfnD3DPERF_QueryRepeatFrame = NULL;
//LPD3DPERF_SetOptions g_pfnD3DPERF_SetOptions = NULL;
//LPD3DPERF_GetStatus g_pfnD3DPERF_GetStatus = NULL;

static bool LoadDll()
{
	if(g_hDll)
		return true;

	// Load DLL
	char szBuff[MAX_PATH+64];
	GetSystemDirectory(szBuff, sizeof(szBuff));
	szBuff[MAX_PATH] = 0;
	strcat(szBuff, "\\d3d11.dll");
	g_hDll = LoadLibrary(szBuff);
	if(!g_hDll)
		return false;

	// Get function addresses
	g_pfnDirect3DCreate11 = (LPDirect3DCreate11)GetProcAddress(g_hDll, "D3D11CreateDevice");
	if (!g_pfnDirect3DCreate11)
	{
		FreeLibrary(g_hDll);
		return false;
	}

	g_pfnD3D11CreateDeviceAndSwapChain = (LPD3D11CreateDeviceAndSwapChain)GetProcAddress(g_hDll, "D3D11CreateDeviceAndSwapChain");
	if (!g_pfnD3D11CreateDeviceAndSwapChain)
	{
		FreeLibrary(g_hDll);
		return false;
	}
	//g_pfnD3DPERF_BeginEvent = (LPD3DPERF_BeginEvent)GetProcAddress(g_hDll, "D3DPERF_BeginEvent");
	//g_pfnD3DPERF_EndEvent = (LPD3DPERF_EndEvent)GetProcAddress(g_hDll, "D3DPERF_EndEvent");
	//g_pfnD3DPERF_SetMarker = (LPD3DPERF_SetMarker)GetProcAddress(g_hDll, "D3DPERF_SetMarker");
	//g_pfnD3DPERF_SetRegion = (LPD3DPERF_SetRegion)GetProcAddress(g_hDll, "D3DPERF_SetRegion");
	//g_pfnD3DPERF_QueryRepeatFrame = (LPD3DPERF_QueryRepeatFrame)GetProcAddress(g_hDll, "D3DPERF_QueryRepeatFrame");
	//g_pfnD3DPERF_SetOptions = (LPD3DPERF_SetOptions)GetProcAddress(g_hDll, "D3DPERF_SetOptions");
	//g_pfnD3DPERF_GetStatus = (LPD3DPERF_GetStatus)GetProcAddress(g_hDll, "D3DPERF_GetStatus");

	// Done
	return true;
}

HRESULT WINAPI D3D11CreateDeviceAndSwapChain(
	_In_   IDXGIAdapter *pAdapter,
	_In_   D3D_DRIVER_TYPE DriverType,
	_In_   HMODULE Software,
	_In_   UINT Flags,
	_In_   const D3D_FEATURE_LEVEL *pFeatureLevels,
	_In_   UINT FeatureLevels,
	_In_   UINT SDKVersion,
	_In_   const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
	_Out_  IDXGISwapChain **ppSwapChain,
	_Out_  ID3D11Device **ppDevice,
	_Out_  D3D_FEATURE_LEVEL *pFeatureLevel,
	_Out_  ID3D11DeviceContext **ppImmediateContext
	)
{
	Log("D3D11CreateDeviceAndSwapChain\n");

	if (!LoadDll())
		return S_FALSE;

	// Create real interface
	HRESULT result = g_pfnD3D11CreateDeviceAndSwapChain(pAdapter,
		DriverType,
		Software,
		Flags,
		pFeatureLevels,
		FeatureLevels,
		SDKVersion,
		pSwapChainDesc,
		ppSwapChain,
		ppDevice,
		pFeatureLevel,
		ppImmediateContext);

	if (result != S_OK)
	{
		Log("call fail %d\n", result);
		return result;
	}


	return result;
}

HRESULT WINAPI D3D11CreateDevice(
	_In_   IDXGIAdapter *pAdapter,
	_In_   D3D_DRIVER_TYPE DriverType,
	_In_   HMODULE Software,
	_In_   UINT Flags,
	_In_   const D3D_FEATURE_LEVEL *pFeatureLevels,
	_In_   UINT FeatureLevels,
	_In_   UINT SDKVersion,
	_Out_  ID3D11Device **ppDevice,
	_Out_  D3D_FEATURE_LEVEL *pFeatureLevel,
	_Out_  ID3D11DeviceContext **ppImmediateContext
)
{
	// Log
	Log("D3D11CreateDevice\n");

	// Load DLL
	if(!LoadDll())
		return S_FALSE;

	// Create real interface
	HRESULT result = g_pfnDirect3DCreate11(pAdapter, 
		DriverType, 
		Software, 
		Flags, 
		pFeatureLevels, 
		FeatureLevels, 
		SDKVersion,
		ppDevice,
		pFeatureLevel,
		ppImmediateContext);

	if (result != S_OK)
	{
		Log("call fail %d\n", result);
		return result;
	}

	Log("D3D11CreateDevice real %p %p %p", *ppDevice, *ppImmediateContext, g_factory);

	*ppDevice = new VireioD3DProxyDevice(*ppDevice);
	*ppImmediateContext = new Direct3DDeviceContext11(*ppImmediateContext);

	if (g_factory != NULL)
		g_factory->SetD3DProxy(*ppDevice);

	Log("D3D11CreateDevice proxy %p %p", *ppDevice, *ppImmediateContext);
	
	// Create and return proxy interface
	//BaseDirect3D9* pWrapper = new BaseDirect3D9(pD3D);

	return result;
}

//int WINAPI D3DPERF_BeginEvent( D3DCOLOR col, LPCWSTR wszName )
//{
//	return g_pfnD3DPERF_BeginEvent(col, wszName);
//}
//
//int WINAPI D3DPERF_EndEvent( void )
//{
//	return g_pfnD3DPERF_EndEvent();
//}
//
//void WINAPI D3DPERF_SetMarker( D3DCOLOR col, LPCWSTR wszName )
//{
//	g_pfnD3DPERF_SetMarker(col, wszName);
//}
//
//void WINAPI D3DPERF_SetRegion( D3DCOLOR col, LPCWSTR wszName )
//{
//	g_pfnD3DPERF_SetRegion(col, wszName);
//}
//
//BOOL WINAPI D3DPERF_QueryRepeatFrame( void )
//{
//	return g_pfnD3DPERF_QueryRepeatFrame();
//}
//
//void WINAPI D3DPERF_SetOptions( DWORD dwOptions )
//{
//	g_pfnD3DPERF_SetOptions(dwOptions);
//}
//
//DWORD WINAPI D3DPERF_GetStatus( void )
//{
//	return g_pfnD3DPERF_GetStatus();
//}

void Log(const char* szFormat, ...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg, szFormat);
	_vsnprintf(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);

	static FILE* pFile = NULL;
	if(!pFile)
		pFile = fopen("C:/D3D9Proxy.log", "w");

	OutputDebugString(szBuff);
	OutputDebugString("\n");
	if(pFile) {
		fwrite(szBuff, 1, strlen(szBuff), pFile);
		fflush(pFile);
	} else {
		OutputDebugString("Couldn't open log file for writing.\n");
	}
}

void SetFactory(void *factory)
{
	if (g_factory != NULL)
	{
		((IUnknown*)g_factory)->Release();
	}

	((IUnknown*)factory)->AddRef();

	g_factory = (VireioDXGIFactory*)factory;
	
	Log("SetFactory %p", g_factory);
}
