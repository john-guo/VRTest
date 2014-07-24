#include "BaseDXGISwapChain.h"


HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::Present(UINT SyncInterval, UINT Flags)
{
	return m_swapChain->Present(SyncInterval, Flags);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetBuffer(UINT Buffer, __in REFIID riid, __out void **ppSurface)
{
	return m_swapChain->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::SetFullscreenState(BOOL Fullscreen, __in_opt IDXGIOutput *pTarget)
{
	return m_swapChain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetFullscreenState(__out BOOL *pFullscreen, __out IDXGIOutput **ppTarget)
{
	return m_swapChain->GetFullscreenState(pFullscreen, ppTarget);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetDesc(__out DXGI_SWAP_CHAIN_DESC *pDesc)
{
	return m_swapChain->GetDesc(pDesc);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	return m_swapChain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::ResizeTarget(__in const DXGI_MODE_DESC *pNewTargetParameters)
{
	return m_swapChain->ResizeTarget(pNewTargetParameters);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetContainingOutput(__out IDXGIOutput **ppOutput)
{
	return m_swapChain->GetContainingOutput(ppOutput);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetFrameStatistics(__out DXGI_FRAME_STATISTICS *pStats)
{
	return m_swapChain->GetFrameStatistics(pStats);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetLastPresentCount(__out UINT *pLastPresentCount)
{
	return m_swapChain->GetLastPresentCount(pLastPresentCount);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetDevice(__in REFIID riid, __out void **ppDevice)
{
	return m_swapChain->GetDevice(riid, ppDevice);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::SetPrivateData(__in REFGUID Name, UINT DataSize, __in_bcount(DataSize) const void *pData)
{
	return m_swapChain->SetPrivateData(Name, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::SetPrivateDataInterface(__in REFGUID Name, __in const IUnknown *pUnknown)
{
	return m_swapChain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetPrivateData(__in REFGUID Name, __inout UINT *pDataSize, __out_bcount(*pDataSize) void *pData)
{
	return m_swapChain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::GetParent(__in REFIID riid, __out void **ppParent)
{
	return m_swapChain->GetParent(riid, ppParent);
}

HRESULT STDMETHODCALLTYPE BaseDXGISwapChain::QueryInterface(REFIID riid, void **ppvObject)
{
	return m_swapChain->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE BaseDXGISwapChain::AddRef(void)
{
	return ++m_ref;
}

ULONG STDMETHODCALLTYPE BaseDXGISwapChain::Release(void)
{
	if (--m_ref == 0)
	{
		delete this;
		return 0;
	}

	return m_ref;
}

BaseDXGISwapChain::BaseDXGISwapChain(IDXGISwapChain *swapChain):
m_swapChain(swapChain),
m_ref(1)
{
	
}

BaseDXGISwapChain::~BaseDXGISwapChain()
{
	m_swapChain->Release();
}

