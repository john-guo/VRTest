#pragma once
#include "Direct3DDeviceContext11.h"

class VireioD3DProxyDeviceContext : public Direct3DDeviceContext11
{
public:
	VireioD3DProxyDeviceContext(ID3D11DeviceContext *pContext);
	virtual ~VireioD3DProxyDeviceContext();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
};