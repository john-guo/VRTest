#pragma once

#include "dxgi.h"

class BaseDXGIFactory : public IDXGIFactory
{
private:
	ULONG m_ref;

protected:
	IDXGIFactory *m_factory;
	IDXGISwapChain *m_swapChain;

public:
	BaseDXGIFactory(IDXGIFactory* factory);
	virtual ~BaseDXGIFactory();


	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);


	virtual HRESULT STDMETHODCALLTYPE SetPrivateData(__in REFGUID Name, UINT DataSize, __in_bcount(DataSize) const void *pData);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(__in REFGUID Name, __in const IUnknown *pUnknown);

	virtual HRESULT STDMETHODCALLTYPE GetPrivateData(__in REFGUID Name, __inout UINT *pDataSize, __out_bcount(*pDataSize) void *pData);

	virtual HRESULT STDMETHODCALLTYPE GetParent(__in REFIID riid, __out void **ppParent);


	virtual HRESULT STDMETHODCALLTYPE EnumAdapters(UINT Adapter, __out IDXGIAdapter **ppAdapter);

	virtual HRESULT STDMETHODCALLTYPE MakeWindowAssociation(HWND WindowHandle, UINT Flags);

	virtual HRESULT STDMETHODCALLTYPE GetWindowAssociation(__out HWND *pWindowHandle);

	virtual HRESULT STDMETHODCALLTYPE CreateSwapChain(__in IUnknown *pDevice, __in DXGI_SWAP_CHAIN_DESC *pDesc, __out IDXGISwapChain **ppSwapChain);

	virtual HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(HMODULE Module, __out IDXGIAdapter **ppAdapter);
};
