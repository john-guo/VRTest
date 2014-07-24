#pragma once


#define MAX_VRBOOST_VALUES 256
#define BRASSA_PIXEL_WIDTH 1920
#define BRASSA_PIXEL_HEIGHT 1080

#include "Direct3DDevice11.h"
#include "Direct3DDeviceContext11.h"

class VireioD3DProxyDevice : public Direct3DDevice11
{
public:
	VireioD3DProxyDevice(ID3D11Device* pDevice);
	virtual ~VireioD3DProxyDevice();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);

	/**
	* Game Types.
	* We use these ProxyTypes to determine either to draw BRASSA in EndScene() or in Present().
	* Will be also used for any game- or engine-specific things.
	***/
	enum ProxyTypes
	{
		MONO = 0,                  /**<  !! */
		FIXED = 10,                /**< Default driver behavior. */
		SOURCE = 100,              /**< Source is a 3D video game engine developed by Valve Corporation. */
		SOURCE_L4D = 101,          /**<  !! */
		UNREAL = 200,              /**< The Unreal Engine is a game engine developed by Epic Games, first illustrated in the 1998 first-person shooter game Unreal. */
		UNREAL_MIRROR = 201,       /**<  !! */
		UNREAL_UT3 = 202,          /**<  !! */
		UNREAL_BIOSHOCK = 203,     /**<  !! */
		UNREAL_BORDERLANDS = 204,  /**< Borderlands(TM) */
		EGO = 300,                 /**< Ego Game Technology Engine (more commonly referred to as Ego Engine or EGO, stylised ego) is a video game engine developed by Codemasters. */
		EGO_DIRT = 301,            /**<  !! */
		REALV = 400,               /**< Real Virtuality is a proprietary computer game engine developed by Bohemia Interactive (BI), originally called Poseidon. */
		REALV_ARMA = 401,          /**<  !! */
		UNITY = 500,               /**< Unity is a cross-platform game engine with a built-in IDE developed by Unity Technologies. */
		UNITY_SLENDER = 501,       /**<  !! */
		GAMEBRYO = 600,            /**< Gamebryo 3D and LightSpeed engines are owned by Gamebase Co., Ltd. and Gamebase USA and have been used by several video game developers. */
		GAMEBRYO_SKYRIM = 601,     /**< Skyrim’s Creation Engine still has at least some Gamebryo in it. */
		LFS = 700,                 /**< Live for Speed (LFS) is a racing simulator developed by a three person team comprising Scawen Roberts, Eric Bailey, and Victor van Vlaardingen. */
		CDC = 800,                 /**< Proprietary game engine developed by Crystal Dynamics. */
		DEBUG_LOG_FILE = 99999     /**< Debug log file output game type. For development causes. Do not use since slows down game extremely. */
	};
	/**
	* Mode of the BRASSA menu.
	*
	***/
	enum BRASSA_Modes
	{
		INACTIVE = 0,
		MAINMENU = 1,
		WORLD_SCALE_CALIBRATION,
		CONVERGENCE_ADJUSTMENT,
		SHADER_ANALYZER,
		HUD_CALIBRATION,
		GUI_CALIBRATION,
		OVERALL_SETTINGS,
		VRBOOST_VALUES,
		BRASSA_SHADER_ANALYZER_SUBMENU,
		CHANGE_RULES_SCREEN,
		PICK_RULES_SCREEN,
		SHOW_SHADERS_SCREEN,
		BRASSA_ENUM_RANGE
	};
	/**
	* HUD scale enumeration.
	* ENUM_RANGE = range of the enum
	***/
	enum HUD_3D_Depth_Modes
	{
		HUD_DEFAULT = 0,
		HUD_SMALL = 1,
		HUD_LARGE = 2,
		HUD_FULL = 3,
		HUD_ENUM_RANGE = 4
	};
	/**
	* GUI scale enumeration.
	* ENUM_RANGE = range of the enum
	***/
	enum GUI_3D_Depth_Modes
	{
		GUI_DEFAULT = 0,
		GUI_SMALL = 1,
		GUI_LARGE = 2,
		GUI_FULL = 3,
		GUI_ENUM_RANGE = 4
	};

};
