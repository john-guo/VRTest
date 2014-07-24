#include "Direct3DResource11.h"

Direct3DResource11::Direct3DResource11(ID3D11Resource *resource) :
m_resource(resource),
m_nRefCount(1)
{

}

Direct3DResource11::~Direct3DResource11()
{
	if (m_resource)
		m_resource->Release();
}


HRESULT STDMETHODCALLTYPE Direct3DResource11::QueryInterface(REFIID riid, void **ppvObject)
{
	return m_resource->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE Direct3DResource11::AddRef(void)
{
	return ++m_nRefCount;
}

ULONG STDMETHODCALLTYPE Direct3DResource11::Release(void)
{
	if (--m_nRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_nRefCount;
}


void STDMETHODCALLTYPE Direct3DResource11::GetDevice(_Out_ ID3D11Device **ppDevice)
{
	OutputDebugString("GetDevice");
	m_resource->GetDevice(ppDevice);
}

HRESULT STDMETHODCALLTYPE Direct3DResource11::GetPrivateData(_In_ REFGUID guid, _Inout_ UINT *pDataSize, _Out_writes_bytes_opt_(*pDataSize) void *pData)
{
	return m_resource->GetPrivateData(guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE Direct3DResource11::SetPrivateData(_In_ REFGUID guid, _In_ UINT DataSize, _In_reads_bytes_opt_(DataSize) const void *pData)
{
	return m_resource->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE Direct3DResource11::SetPrivateDataInterface(_In_ REFGUID guid, _In_opt_ const IUnknown *pData)
{
	return m_resource->SetPrivateDataInterface(guid, pData);
}


void STDMETHODCALLTYPE Direct3DResource11::GetType(__out D3D11_RESOURCE_DIMENSION *pResourceDimension)
{
	m_resource->GetType(pResourceDimension);
}

void STDMETHODCALLTYPE Direct3DResource11::SetEvictionPriority(__in UINT EvictionPriority)
{
	m_resource->SetEvictionPriority(EvictionPriority);
}

UINT STDMETHODCALLTYPE Direct3DResource11::GetEvictionPriority(void)
{
	return m_resource->GetEvictionPriority();
}
