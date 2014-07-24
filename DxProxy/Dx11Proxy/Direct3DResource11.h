#pragma once

#include "d3d11.h"

class Direct3DResource11 : public ID3D11Resource
{
private:
	ULONG m_nRefCount;

protected:
	ID3D11Resource *m_resource;

public:
	Direct3DResource11(ID3D11Resource *resource);
	virtual ~Direct3DResource11();

	virtual void STDMETHODCALLTYPE GetType(__out D3D11_RESOURCE_DIMENSION *pResourceDimension);

	virtual void STDMETHODCALLTYPE SetEvictionPriority(__in UINT EvictionPriority);

	virtual UINT STDMETHODCALLTYPE GetEvictionPriority(void);

	virtual void STDMETHODCALLTYPE GetDevice(__out ID3D11Device **ppDevice);

	virtual HRESULT STDMETHODCALLTYPE GetPrivateData(__in REFGUID guid, __inout UINT *pDataSize, __out_bcount_opt(*pDataSize) void *pData);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateData(__in REFGUID guid, __in UINT DataSize, __in_bcount_opt(DataSize) const void *pData);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(__in REFGUID guid, __in_opt const IUnknown *pData);

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);

};
