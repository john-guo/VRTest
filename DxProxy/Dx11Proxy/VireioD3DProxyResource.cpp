#include "VireioD3DProxyResource.h"

VireioD3DProxyResource::VireioD3DProxyResource(ID3D11Resource* pActualSurfaceLeft, ID3D11Resource* pActualSurfaceRight, Direct3DDevice11* pOwningDevice, Direct3DDeviceContext11* pContext, IUnknown* pWrappedContainer) :
Direct3DResource11(pActualSurfaceLeft),
m_pActualSurfaceRight(pActualSurfaceRight),
m_pOwningDevice(pOwningDevice),
m_pWrappedContainer(pWrappedContainer),
m_pContext(pContext)
{
	if (!pWrappedContainer)
	{
		pOwningDevice->AddRef();
		pContext->AddRef();
	}
}

VireioD3DProxyResource::~VireioD3DProxyResource()
{
	if (!m_pWrappedContainer) {
		m_pOwningDevice->Release();
		m_pContext->Release();
	}

	if (m_pActualSurfaceRight)
		m_pActualSurfaceRight->Release();
}

ULONG STDMETHODCALLTYPE VireioD3DProxyResource::AddRef(void)
{
	if (m_pWrappedContainer) {
		return m_pWrappedContainer->AddRef();
	}
	else {
		return Direct3DResource11::AddRef();
	}
}

ULONG STDMETHODCALLTYPE VireioD3DProxyResource::Release(void)
{
	if (m_pWrappedContainer) {
		return m_pWrappedContainer->Release();
	}
	else {
		return Direct3DResource11::Release();
	}
}

void STDMETHODCALLTYPE VireioD3DProxyResource::GetDevice(__out ID3D11Device **ppDevice)
{
	*ppDevice = NULL;
	if (!m_pOwningDevice)
		return;
	else {
		*ppDevice = m_pOwningDevice;
		m_pOwningDevice->AddRef();
		return;
	}
}

HRESULT STDMETHODCALLTYPE VireioD3DProxyResource::SetPrivateData(__in REFGUID guid, __in UINT DataSize, __in_bcount_opt(DataSize) const void *pData)
{
	if (IsStereo())
		m_pActualSurfaceRight->SetPrivateData(guid, DataSize, pData);

	return m_resource->SetPrivateData(guid, DataSize, pData);
}

void STDMETHODCALLTYPE VireioD3DProxyResource::SetEvictionPriority(__in UINT EvictionPriority)
{
	if (IsStereo())
		m_pActualSurfaceRight->SetEvictionPriority(EvictionPriority);

	return m_resource->SetEvictionPriority(EvictionPriority);
}

HRESULT STDMETHODCALLTYPE VireioD3DProxyResource::SetPrivateDataInterface(__in REFGUID guid, __in_opt const IUnknown *pData)
{
	if (IsStereo())
		m_pActualSurfaceRight->SetPrivateDataInterface(guid, pData);

	return m_resource->SetPrivateDataInterface(guid, pData);
}

ID3D11Resource* VireioD3DProxyResource::getActualMono()
{
	return getActualLeft();
}

ID3D11Resource* VireioD3DProxyResource::getActualLeft()
{
	return m_resource;
}

ID3D11Resource* VireioD3DProxyResource::getActualRight()
{
	return m_pActualSurfaceRight;
}

bool VireioD3DProxyResource::IsStereo()
{
	return m_pActualSurfaceRight != NULL;
}

