/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2012 Andres Hernandez

File <StereoView.h> and
Class <StereoView> :
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

#ifndef STEREOVIEW_H_INCLUDED
#define STEREOVIEW_H_INCLUDED

#include "ProxyHelper.h"
#include "VireioD3DProxyDevice.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <map>
#include <string.h>
#include <assert.h>
#include "VireioD3DProxyResource.h"
#include "d3dx11effect.h"

/**
* Stereo-view render class.
* Basic class to render in stereo.
*/
class StereoView
{
public:
	StereoView(ProxyHelper::ProxyConfig& config);
	virtual ~StereoView();

	/*** StereoView public methods ***/
	virtual void Init(ID3D11Device* pActualDevice, ID3D11DeviceContext *pContext, IDXGISwapChain *swapChain);
	virtual void ReleaseEverything();
	virtual void Draw(VireioD3DProxyResource* stereoCapableSurface);
	virtual void SaveScreen();
	virtual void PostReset();

	/**
	* Stereo render options.
	***/
	static enum StereoTypes
	{
		DISABLED = 0,                       /**< Disabled. */
		ANAGLYPH_RED_CYAN = 1,              /**< Anaglyph render in complementary colors red, cyan. */
		ANAGLYPH_RED_CYAN_GRAY = 2,         /**< Anaglyph render in complementary colors cyan, gray. */
		ANAGLYPH_YELLOW_BLUE = 5,           /**< Anaglyph render in complementary colors yellow, blue. */
		ANAGLYPH_YELLOW_BLUE_GRAY = 6,      /**< Anaglyph render in complementary colors blue, grey. */
		ANAGLYPH_GREEN_MAGENTA = 10,        /**< Anaglyph render in complementary colors green, magenta. */
		ANAGLYPH_GREEN_MAGENTA_GRAY = 11,   /**< Gray anaglyph render in complementary colors red,cyan. */
		SIDE_BY_SIDE = 20,                  /**< Left and right image. */
		DIY_RIFT = 25,                      /**< For do-it-yourself Oculus Rift kits. */
		OCULUS_RIFT = 26,                   /**< Standard Oculus Rift render method. */
		OCULUS_RIFT_CROPPED = 27,           /**< Cropped Oculus Rift render method. */
		OVER_UNDER = 30,                    /**< Upper and lower image. */
		INTERLEAVE_HORZ = 40,               /**< Horizontally interleaved for polarized 3D systems. */
		INTERLEAVE_VERT = 50,               /**< Vertically interleaved for polarized 3D systems. */
		CHECKERBOARD = 60                   /**< Checkerboard for 3D Digital Light Processing Displays. */
	};
	/**
	* Left and right enumeration.
	***/
	static enum Eyes
	{
		LEFT_EYE,
		RIGHT_EYE
	};
	/**
	* Current Direct3D Viewport.
	***/
	D3D11_VIEWPORT viewport;
	/**
	* Option to swap the eye output for different 3D systems.
	***/	
	bool swapEyes;
	/**
	* True if class is initialized. Needed since initialization is not done in constructor.
	***/
	bool initialized;
	/**
	* Type of the game or engine as configured in cfg file.
	***/
	int game_type;
	/**
	* Stereo render option as enumerated in StereoTypes.
	***/
	int stereo_mode;
	/**
	* True if stereo is enabled.
	***/
	bool stereoEnabled() { return (stereo_mode != DISABLED); }; 
	/**
	* Should be used by OculusRiftView and D3DProxyDevice.
	***/
	float DistortionScale;	
	/**
	* Should be used by OculusRiftView and D3DProxyDevice.
	***/
	float YOffset;	

protected:
	/*** StereoView protected methods ***/
	virtual void InitTextureBuffers();
	virtual void InitVertexBuffers();
	virtual void InitShaderEffects();
	virtual void SetViewEffectInitialValues(); 
	virtual void CalculateShaderVariables();
	virtual void SaveState();
	virtual void SetState();
	virtual void RestoreState();
	virtual void SaveAllRenderStates(ID3D11Device* pDevice);
	virtual void SetAllRenderStatesDefault(ID3D11Device* pDevice);
	virtual void RestoreAllRenderStates(ID3D11Device* pDevice);

	/**
	* The actual, unwrapped Direct3D Device. 
	* Class cannot be initialized with wrapped device.
	***/
	ID3D11Device* m_pActualDevice;
	ID3D11DeviceContext *m_pContext;
	IDXGISwapChain *m_pSwapChain;

	/**
	* Saved game vertex shader to be restored after drawing stereoscopic.
	***/
	IDirect3DVertexShader9* lastVertexShader;
	/**
	* Saved game pixel shader to be restored after drawing stereoscopic.
	***/
	IDirect3DPixelShader9* lastPixelShader;
	/**
	* Saved game texture 0 to be restored after drawing stereoscopic.
	***/
	IDirect3DBaseTexture9* lastTexture;
	/**
	* Saved game texture 1 to be restored after drawing stereoscopic.
	***/
	IDirect3DBaseTexture9* lastTexture1;
	/**
	* Saved game vertex declaration to be restored after drawing stereoscopic.
	***/
	IDirect3DVertexDeclaration9* lastVertexDeclaration;
	/**
	* Saved game render target 0 to be restored after drawing stereoscopic.
	***/
	IDirect3DSurface9* lastRenderTarget0;
	/**
	* Saved game render target 1 to be restored after drawing stereoscopic.
	***/
	IDirect3DSurface9* lastRenderTarget1;
	/**
	* Left eye (or upper) target texture buffer.
	* Surface data from D3D9ProxySurface is copied on that. To be swapped with right texture if swap_eyes set to true.
	***/
	ID3D11Texture2D* leftTexture;
	/**
	* Right eye (or lower) target texture buffer.
	* Surface data from D3D9ProxySurface is copied on that. To be swapped with left texture if swap_eyes set to true.
	***/
	ID3D11Texture2D* rightTexture;
	/**
	* Current render target.
	***/
	ID3D11Texture2D* backBuffer;
	/**
	* Surface of the left eye texture.
	***/
	ID3D11Resource* leftSurface;
	/**
	* Surface of the right eye texture.
	***/
	ID3D11Resource* rightSurface;
	/**
	* Full screen render vertex buffer containing 4 vertices.
	***/
	ID3D11Buffer* screenVertexBuffer;
	/**
	* Render state block.
	* Stores all render states to be restored after drawing stereoscopic.
	* To be renamed.
	***/
	IDirect3DStateBlock9* sb;
	/**
	* Stores render states.
	* For games (Half Life 2?) that do not work with direct 3d state block for some reason.
	***/
	DWORD renderStates[256];
	/**
	* View effect according to the stereo mode preset in stereo_mode.
	***/
	ID3DX11Effect* viewEffect;
	/**
	* Map of the shader effect file names.
	***/
	std::map<int, std::string> shaderEffect;
	DWORD tssColorOp;            /**< Various states. */
	DWORD tssColorArg1;          /**< Various states. */
	DWORD tssAlphaOp;            /**< Various states. */
	DWORD tssAlphaArg1;          /**< Various states. */
	DWORD tssConstant;           /**< Various states. */
	DWORD rsAlphaEnable;         /**< Various states. */
	DWORD rsZEnable;             /**< Various states. */
	DWORD rsZWriteEnable;        /**< Various states. */
	DWORD rsDepthBias;           /**< Various states. */
	DWORD rsSlopeScaleDepthBias; /**< Various states. */
	DWORD rsSrgbEnable;          /**< Various states. */
	DWORD ssSrgb;                /**< Various states. */  
	DWORD ssSrgb1;               /**< Various states. */
	DWORD ssAddressU;            /**< Various states. */
	DWORD ssAddressV;            /**< Various states. */
	DWORD ssAddressW;            /**< Various states. */
	DWORD ssMag0;                /**< Various states. */
	DWORD ssMag1;                /**< Various states. */
	DWORD ssMin0;                /**< Various states. */
	DWORD ssMin1;                /**< Various states. */
	DWORD ssMip0;                /**< Various states. */
	DWORD ssMip1;                /**< Various states. */
	/**
	* Determines how to save render states for stereo view output.
	***/
	enum HowToSaveRenderStates
	{
		STATE_BLOCK,
		SELECTED_STATES_MANUALLY,
		ALL_STATES_MANUALLY,
		DO_NOT_SAVE_AND_RESTORE,
	} howToSaveRenderStates;
};

/**
* Declaration of texture vertex used for full screen render.
***/
const DWORD D3DFVF_TEXVERTEX = D3DFVF_XYZRHW | D3DFVF_TEX1;
/**
* Texture vertex used for full screen render.
***/
struct TEXVERTEX
{
	float x;
	float y;
	float z;
	float rhw;
	float u;
	float v;
};

#endif