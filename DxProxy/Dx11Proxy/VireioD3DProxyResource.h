#pragma once
#include "Direct3DResource11.h"
#include "Direct3DDevice11.h"
#include "Direct3DDeviceContext11.h"

class VireioD3DProxyResource : public Direct3DResource11
{
protected:
	IUnknown* const m_pWrappedContainer;
	Direct3DDevice11* const m_pOwningDevice;
	Direct3DDeviceContext11* const m_pContext;
	ID3D11Resource* const m_pActualSurfaceRight;


public:
	VireioD3DProxyResource(ID3D11Resource* pActualSurfaceLeft, ID3D11Resource* pActualSurfaceRight, Direct3DDevice11* pOwningDevice, Direct3DDeviceContext11 *pContext, IUnknown* pWrappedContainer);
	virtual ~VireioD3DProxyResource();
	
	virtual ID3D11Resource* getActualMono();
	virtual ID3D11Resource* getActualLeft();
	virtual ID3D11Resource* getActualRight();
	virtual bool            IsStereo();

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual void STDMETHODCALLTYPE GetDevice(__out ID3D11Device **ppDevice);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateData(__in REFGUID guid, __in UINT DataSize, __in_bcount_opt(DataSize) const void *pData);

	virtual void STDMETHODCALLTYPE SetEvictionPriority(__in UINT EvictionPriority);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(__in REFGUID guid, __in_opt const IUnknown *pData);

};
