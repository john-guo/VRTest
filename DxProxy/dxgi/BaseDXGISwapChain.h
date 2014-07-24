#pragma once

#include "dxgi.h"

class BaseDXGISwapChain : public IDXGISwapChain
{
private:
	ULONG m_ref;

protected:
	IDXGISwapChain *m_swapChain;

public:
	BaseDXGISwapChain(IDXGISwapChain *swapChain);
	virtual ~BaseDXGISwapChain();

	virtual HRESULT STDMETHODCALLTYPE Present(UINT SyncInterval, UINT Flags);

	virtual HRESULT STDMETHODCALLTYPE GetBuffer(UINT Buffer, __in REFIID riid, __out void **ppSurface);

	virtual HRESULT STDMETHODCALLTYPE SetFullscreenState(BOOL Fullscreen, __in_opt IDXGIOutput *pTarget);

	virtual HRESULT STDMETHODCALLTYPE GetFullscreenState(__out BOOL *pFullscreen, __out IDXGIOutput **ppTarget);

	virtual HRESULT STDMETHODCALLTYPE GetDesc(__out DXGI_SWAP_CHAIN_DESC *pDesc);

	virtual HRESULT STDMETHODCALLTYPE ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

	virtual HRESULT STDMETHODCALLTYPE ResizeTarget(__in const DXGI_MODE_DESC *pNewTargetParameters);

	virtual HRESULT STDMETHODCALLTYPE GetContainingOutput(__out IDXGIOutput **ppOutput);

	virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(__out DXGI_FRAME_STATISTICS *pStats);

	virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount(__out UINT *pLastPresentCount);

	virtual HRESULT STDMETHODCALLTYPE GetDevice(__in REFIID riid, __out void **ppDevice);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateData(__in REFGUID Name, UINT DataSize, __in_bcount(DataSize) const void *pData);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(__in REFGUID Name, __in const IUnknown *pUnknown);

	virtual HRESULT STDMETHODCALLTYPE GetPrivateData(__in REFGUID Name, __inout UINT *pDataSize, __out_bcount(*pDataSize) void *pData);

	virtual HRESULT STDMETHODCALLTYPE GetParent(__in REFIID riid, __out void **ppParent);

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);

};

