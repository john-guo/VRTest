/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2012 Andres Hernandez

File <dllmain.cpp> :
Copyright (C) 2012 by Andres Hernandez

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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3d11.h>
#include "hijackdll.h"
#include "apihijack.h"
#include "Direct3D9.h"
#include <string>

// Text buffer for sprintf
char targetExe[256];
char targetPath[256];
char lastExe[256];
std::string targetPathString;

#if HIJACK_D3D11
LPCSTR realDll = "D3D11.DLL";
LPCWSTR realDllW = L"D3D11.DLL";
#else
LPCSTR realDll = "D3D9.DLL";
LPCWSTR realDllW = L"D3D9.DLL";
#endif

LPCSTR proxyDll = NULL;
LPCWSTR proxyDllW = NULL;
LPCSTR dllDir = NULL;

HINSTANCE hDLL;

typedef HMODULE (WINAPI *LoadLibraryExW_Type)(LPCWSTR lpFileName, HANDLE hFile, DWORD dwFlags);   

HMODULE WINAPI MyLoadLibraryExW(LPCWSTR lpFileName, HANDLE hFile, DWORD dwFlags);   

typedef IDirect3D9* (WINAPI *Direct3DCreate9_t)(UINT sdk_version);
IDirect3D9* WINAPI MyDirect3DCreate9(UINT sdk_version);

typedef HRESULT(WINAPI *D3D11CreateDevice_t)(
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
HRESULT WINAPI MyD3D11CreateDevice(
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

typedef HRESULT (WINAPI *CreateDXGIFactory_t)(
	_In_   REFIID riid,
	_Out_  void **ppFactory
	);
HRESULT WINAPI MyCreateDXGIFactory(
	_In_   REFIID riid,
	_Out_  void **ppFactory
	);

void ParsePaths();
void SaveExeName(char*, char*);

// Hook structure.
enum
{
	KERNEL32_LoadLibraryExW = 3
};

enum
{
	D3DFN_Direct3DCreate9 = 0
};

enum
{
	D3D11FN_D3D11CreateDevice = 0,
	D3D11FN_CreateDXGIFactory = 1
};

SDLLHook KernelHook = 
{
	"KERNEL32.DLL",
	false, NULL,		// Default hook disabled, NULL function pointer.
	{
		{ "LoadLibraryExW", MyLoadLibraryExW },   
		{ NULL, NULL }
	}
};

SDLLHook D3DHook = 
{
	"D3D9.DLL",
	false, NULL,		// Default hook disabled, NULL function pointer.
	{
		{ "Direct3DCreate9", MyDirect3DCreate9},
		{ NULL, NULL }
	}
};

SDLLHook D3D11HOOK =
{
	"D3D11.DLL",
	false, NULL,
	{
		{ "D3D11CreateDevice", MyD3D11CreateDevice },
		{ "CreateDXGIFactory", MyCreateDXGIFactory },
		{ NULL, NULL }
	}
};

HMODULE WINAPI MyLoadLibraryExW(LPCWSTR lpFileName, HANDLE hFile, DWORD dwFlags)   
{   
	OutputDebugString("LoadLibraryExW ENTERED!\n");

	// Get the old function    
	LoadLibraryExW_Type OldFn = (LoadLibraryExW_Type)KernelHook.Functions[KERNEL32_LoadLibraryExW].OrigFn;    

	// A Place to store the module, that is returned    
	HMODULE retval;    

	OutputDebugString("LoadLibraryExW( lpLibFileName ");    
	OutputDebugStringW(lpFileName);    
	OutputDebugString(" )\n");    

	if(lstrcmpiW(lpFileName, realDllW) == 0)
	{
		OutputDebugString("Inject Proxy DLL ");    
		lpFileName = proxyDllW;
		OutputDebugStringW(lpFileName); 
		OutputDebugString("\n");
	} 

	// Time to call the original function    
	retval = OldFn(lpFileName, hFile, dwFlags);    

	//HookAPICalls(&KernelHook, retval);    

	return retval;   
}

IDirect3D9* WINAPI MyDirect3DCreate9(UINT sdk_version)
{
	OutputDebugString( "Direct3D-Hook: MyDirect3DCreate9 called.\n" );

	Direct3DCreate9_t old_func = (Direct3DCreate9_t) D3DHook.Functions[D3DFN_Direct3DCreate9].OrigFn;
	IDirect3D9* d3d = old_func(sdk_version);

	return d3d;
	//return d3d ? new BaseDirect3D9(d3d) : 0;
}

HRESULT WINAPI MyD3D11CreateDevice(
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
	OutputDebugString("Direct3D-Hook: MyD3D11CreateDevice called.\n");

	D3D11CreateDevice_t old_func = (D3D11CreateDevice_t)D3D11HOOK.Functions[D3D11FN_D3D11CreateDevice].OrigFn;
	HRESULT ret = old_func(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);

	return ret;
}

HRESULT WINAPI MyCreateDXGIFactory(
	_In_   REFIID riid,
	_Out_  void **ppFactory
	)
{
	OutputDebugString("Direct3D-Hook: MyCreateDXGIFactory called.\n");
	CreateDXGIFactory_t old_func = (CreateDXGIFactory_t)D3D11HOOK.Functions[D3D11FN_CreateDXGIFactory].OrigFn;
	HRESULT ret = old_func(riid, ppFactory);
	
	return ret;
}

// CBT Hook-style injection.
BOOL APIENTRY DllMain( HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved )
{
	if (fdwReason == DLL_PROCESS_ATTACH)  // When initializing....
	{
		hDLL = hModule;

		// We don't need thread notifications for what we're doing.  Thus, get
		// rid of them, thereby eliminating some of the overhead of this DLL
		DisableThreadLibraryCalls(hModule);

		// Only hook the APIs if this is the right process.
		GetModuleFileName(GetModuleHandle(NULL), targetExe, sizeof(targetExe));
		PathStripPath(targetExe);

		GetModuleFileName(GetModuleHandle(NULL), targetPath, sizeof(targetPath));
		targetPathString = std::string(targetPath);
		targetPathString = targetPathString.substr(0, targetPathString.find_last_of("\\/") + 1);

		OutputDebugString("HIJACKDLL checking process: ");
		OutputDebugString(targetExe);
		OutputDebugString("\n");

		ParsePaths();
		ProxyHelper helper = ProxyHelper();

		if (helper.HasProfile(targetExe))
		{
			if (HookAPICalls(&KernelHook))
			{
				OutputDebugString("HookAPICalls(Kernel): TRUE\n");
			}
			else if (HookAPICalls(&D3D11HOOK))
			{
				OutputDebugString("HookAPICalls(D3D11): TRUE\n");
			}
			else if (HookAPICalls(&D3DHook))
			{
				OutputDebugString("HookAPICalls(D3D): TRUE\n");
			} 
			else 
			{
				OutputDebugString("HookAPICalls(Both): FALSE\n");
			}

			SetDllDirectory(dllDir);
			SaveExeName(targetExe, (char*)targetPathString.c_str());
		}
	}

	return TRUE;
}

// This segment must be defined as SHARED in the .DEF
#pragma data_seg (".HookSection")		
// Shared instance for all processes.
HHOOK hHook = NULL;
#pragma data_seg ()

HIJACKDLL_API LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	return CallNextHookEx(hHook, nCode, wParam, lParam); 
}

HIJACKDLL_API void InstallHook()
{
	OutputDebugString( "HIJACKDLL hook installed.\n" );
	hHook = SetWindowsHookEx( WH_CBT, HookProc, hDLL, 0 );
}

HIJACKDLL_API void RemoveHook()
{
	OutputDebugString( "HIJACKDLL hook removed.\n" );
	UnhookWindowsHookEx( hHook );
}

void ParsePaths()
{
	dllDir = (LPCSTR)malloc(512*sizeof(char));
	proxyDll = (LPCSTR)malloc(512*sizeof(char));
	proxyDllW = (LPCWSTR)malloc(512*sizeof(wchar_t));

	ProxyHelper helper = ProxyHelper();
	helper.GetPath((char*)dllDir, "bin\\");

#if HIJACK_D3D11
	helper.GetPath((char*)proxyDll, "bin\\d3d11.dll");
#else
	helper.GetPath((char*)proxyDll, "bin\\d3d9.dll");
#endif
	mbstowcs_s(NULL, (wchar_t*)proxyDllW, 512, proxyDll, 512);
}

void SaveExeName(char* data, char* path)
{
	HKEY hKey;
	LPCTSTR sk = TEXT("SOFTWARE\\Vireio\\Perception");

	LONG openRes = RegOpenKeyEx(HKEY_CURRENT_USER, sk, 0, KEY_ALL_ACCESS , &hKey);

	if (openRes==ERROR_SUCCESS) {
		OutputDebugString("Hx // Success opening key.\n");
	} else {
		OutputDebugString("Hx // Error opening key.\n");
	}

	LPCTSTR value = TEXT("TargetExe");

	LONG setRes = RegSetValueEx(hKey, value, 0, REG_SZ, (LPBYTE)data, strlen(data)+1);

	if (setRes == ERROR_SUCCESS) {
		OutputDebugString("Hx // Success writing to Registry.\n");
	} else {
		OutputDebugString("Hx // Error writing to Registry.\n");
	}

	value = TEXT("TargetPath");

	setRes = RegSetValueEx(hKey, value, 0, REG_SZ, (LPBYTE)path, strlen(path)+1);

	if (setRes == ERROR_SUCCESS) {
		OutputDebugString("Hx // Success writing to Registry.\n");
	} else {
		OutputDebugString("Hx // Error writing to Registry.\n");
	}

	LONG closeOut = RegCloseKey(hKey);

	if (closeOut == ERROR_SUCCESS) {
		OutputDebugString("Hx // Success closing key.\n");
	} else {
		OutputDebugString("Hx // Error closing key.\n");
	}
}