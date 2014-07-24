/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2012 Andres Hernandez

File <Direct3DStateBlock9.h> and
Class <BaseDirect3DStateBlock9> :
Copyright (C) 2013 Chris Drain

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
#pragma once

#ifndef DIRECT3DSTATEBLOCK9_H_INCLUDED
#define DIRECT3DSTATEBLOCK9_H_INCLUDED

#include <d3d9.h>
#include "Direct3DDevice9.h"

/**
*  Direct 3D state block class. 
*  Overwrites IDirect3DStateBlock9 and imbeds the actual state block.
*/
class BaseDirect3DStateBlock9 : public IDirect3DStateBlock9
{
public:
	BaseDirect3DStateBlock9(IDirect3DStateBlock9* pActualStateBlock, IDirect3DDevice9* pOwningDevice);
	virtual ~BaseDirect3DStateBlock9();

	/*** IUnknown methods ***/
	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG   WINAPI AddRef();
	virtual ULONG   WINAPI Release();

	/*** IDirect3DStateBlock9 methods ***/
	virtual HRESULT WINAPI GetDevice(IDirect3DDevice9 **ppDevice);
	virtual HRESULT WINAPI Capture();
	virtual HRESULT WINAPI Apply();

protected:
	/**
	* The actual state block embedded. 
	***/
	IDirect3DStateBlock9* m_pActualStateBlock;
	/**
	* Pointer to the D3D device that owns the block. 
	***/
	IDirect3DDevice9* const m_pOwningDevice;
	/**
	* Internal reference counter. 
	***/
	ULONG m_nRefCount;
};

#endif

