#include "BaseDXGIFactory.h"
#include "comm.h"
#include "BaseDXGISwapChain.h"

BaseDXGIFactory::BaseDXGIFactory(IDXGIFactory* factory):
m_factory(factory),
m_ref(1)
{
	
}

BaseDXGIFactory::~BaseDXGIFactory()
{
	m_factory->Release();
}


HRESULT STDMETHODCALLTYPE BaseDXGIFactory::QueryInterface(REFIID riid, void **ppvObject)
{
	return m_factory->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE BaseDXGIFactory::AddRef(void)
{
	//Log("BaseDXGIFactory AddRef %d", m_ref);

	return ++m_ref;
}

ULONG STDMETHODCALLTYPE BaseDXGIFactory::Release(void)
{
	//Log("BaseDXGIFactory Release %d", m_ref);

	if (--m_ref == 0)
	{
		delete this;
		return 0;
	}

	return m_ref;
}


HRESULT STDMETHODCALLTYPE BaseDXGIFactory::SetPrivateData(__in REFGUID Name, UINT DataSize, __in_bcount(DataSize) const void *pData)
{
	return m_factory->SetPrivateData(Name, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE BaseDXGIFactory::SetPrivateDataInterface(__in REFGUID Name, __in const IUnknown *pUnknown)
{
	return m_factory->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT STDMETHODCALLTYPE BaseDXGIFactory::GetPrivateData(__in REFGUID Name, __inout UINT *pDataSize, __out_bcount(*pDataSize) void *pData)
{
	return m_factory->GetPrivateData(Name, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE BaseDXGIFactory::GetParent(__in REFIID riid, __out void **ppParent)
{
	return m_factory->GetParent(riid, ppParent);
}




HRESULT STDMETHODCALLTYPE BaseDXGIFactory::EnumAdapters(UINT Adapter, __out IDXGIAdapter **ppAdapter)
{
	return m_factory->EnumAdapters(Adapter, ppAdapter);
}

HRESULT STDMETHODCALLTYPE BaseDXGIFactory::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
	return m_factory->MakeWindowAssociation(WindowHandle, Flags);
}

HRESULT STDMETHODCALLTYPE BaseDXGIFactory::GetWindowAssociation(__out HWND *pWindowHandle)
{
	return m_factory->GetWindowAssociation(pWindowHandle);
}

HRESULT STDMETHODCALLTYPE BaseDXGIFactory::CreateSwapChain(__in IUnknown *pDevice, __in DXGI_SWAP_CHAIN_DESC *pDesc, __out IDXGISwapChain **ppSwapChain)
{
	Log("CreateSwapChain %p %p", pDevice, ppSwapChain);
	HRESULT result = m_factory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
	if (result != S_OK)
	{
		Log("CreateSwapChain failed %d", result);
		return result;
	}

	*ppSwapChain = m_swapChain = new BaseDXGISwapChain(*ppSwapChain);

	return result;
}

HRESULT STDMETHODCALLTYPE BaseDXGIFactory::CreateSoftwareAdapter(HMODULE Module, __out IDXGIAdapter **ppAdapter)
{
	return m_factory->CreateSoftwareAdapter(Module, ppAdapter);
}

