/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2012 Andres Hernandez

File <Direct3DDevice9.cpp> and
Class <BaseDirect3DDevice11> :
Copyright (C) 2012 Andres Hernandez

Vireio Perception Version History:
v1.0.0 2012 by Andres Hernandez
v1.0.X 2013 by John Hicks, Neil Schneider
v1.1.x 2013 by Primary Coding Author: Chris Drain
Team Support: John Hicks, Phil Larkson, Neil Schneider
v2.0.x 2013 by Denis Reischl, Neil Schneider, Joshua Brown

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#include "Direct3DDevice11.h"

/**
* Constructor.
* @param pDevice Imbed actual device.
* @param pCreatedBy Pointer to the object that created the device.
***/
Direct3DDevice11::Direct3DDevice11(ID3D11Device* pDevice) :
m_pDevice(pDevice),
m_nRefCount(1)
{
#ifdef _EXPORT_LOGFILE
	m_logFile.open("logD3DDevice.txt", std::ios::out);
#endif
}

/**
* Destructor.
* Releases embedded device.
***/
Direct3DDevice11::~Direct3DDevice11()
{

#ifdef _EXPORT_LOGFILE
	m_logFile.close();
#endif

	if (m_pDevice)
		m_pDevice->Release();
}

/**
* Base QueryInterface functionality.
***/
HRESULT WINAPI Direct3DDevice11::QueryInterface(REFIID riid, LPVOID* ppv)
{
#ifdef _EXPORT_LOGFILE
	m_logFile << "QueryInterface" << std::endl;
#endif

	return m_pDevice->QueryInterface(riid, ppv);
}

/**
* Base AddRef functionality.
***/
ULONG WINAPI Direct3DDevice11::AddRef()
{
#ifdef _EXPORT_LOGFILE
	m_logFile << "AddRef" << std::endl;
#endif

	return ++m_nRefCount;
}

/**
* Base Release functionality.
***/
ULONG WINAPI Direct3DDevice11::Release()
{
#ifdef _EXPORT_LOGFILE
	m_logFile << "Release" << std::endl;
#endif

	if (--m_nRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_nRefCount;
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateVertexShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11VertexShader **ppVertexShader)
{
	return m_pDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreatePixelShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11PixelShader **ppPixelShader)
{
	return m_pDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateQuery(_In_ const D3D11_QUERY_DESC *pQueryDesc, _Out_opt_ ID3D11Query **ppQuery)
{
	return m_pDevice->CreateQuery(pQueryDesc, ppQuery);
}

/**
* Returns the actual embedded device pointer.
***/
ID3D11Device* Direct3DDevice11::getActual()
{
	return m_pDevice;
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateBuffer(_In_ const D3D11_BUFFER_DESC *pDesc, _In_opt_ const D3D11_SUBRESOURCE_DATA *pInitialData, _Out_opt_ ID3D11Buffer **ppBuffer)
{
	return m_pDevice->CreateBuffer(pDesc, pInitialData, ppBuffer);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateTexture1D(_In_ const D3D11_TEXTURE1D_DESC *pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA *pInitialData, _Out_opt_ ID3D11Texture1D **ppTexture1D)
{
	return m_pDevice->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateTexture2D(_In_ const D3D11_TEXTURE2D_DESC *pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA *pInitialData, _Out_opt_ ID3D11Texture2D **ppTexture2D)
{
	return m_pDevice->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateTexture3D(_In_ const D3D11_TEXTURE3D_DESC *pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels)) const D3D11_SUBRESOURCE_DATA *pInitialData, _Out_opt_ ID3D11Texture3D **ppTexture3D)
{
	return m_pDevice->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateShaderResourceView(_In_ ID3D11Resource *pResource, _In_opt_ const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, _Out_opt_ ID3D11ShaderResourceView **ppSRView)
{
	return m_pDevice->CreateShaderResourceView(pResource, pDesc, ppSRView);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateUnorderedAccessView(_In_ ID3D11Resource *pResource, _In_opt_ const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc, _Out_opt_ ID3D11UnorderedAccessView **ppUAView)
{
	return m_pDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateRenderTargetView(_In_ ID3D11Resource *pResource, _In_opt_ const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, _Out_opt_ ID3D11RenderTargetView **ppRTView)
{
	return m_pDevice->CreateRenderTargetView(pResource, pDesc, ppRTView);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateDepthStencilView(_In_ ID3D11Resource *pResource, _In_opt_ const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc, _Out_opt_ ID3D11DepthStencilView **ppDepthStencilView)
{
	return m_pDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateInputLayout(_In_reads_(NumElements) const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, _In_range_(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT) UINT NumElements, _In_reads_(BytecodeLength) const void *pShaderBytecodeWithInputSignature, _In_ SIZE_T BytecodeLength, _Out_opt_ ID3D11InputLayout **ppInputLayout)
{
	return m_pDevice->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateGeometryShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11GeometryShader **ppGeometryShader)
{
	return m_pDevice->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateGeometryShaderWithStreamOutput(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_reads_opt_(NumEntries) const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, _In_range_(0, D3D11_SO_STREAM_COUNT * D3D11_SO_OUTPUT_COMPONENT_COUNT) UINT NumEntries, _In_reads_opt_(NumStrides) const UINT *pBufferStrides, _In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT) UINT NumStrides, _In_ UINT RasterizedStream, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11GeometryShader **ppGeometryShader)
{
	return m_pDevice->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateHullShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11HullShader **ppHullShader)
{
	return m_pDevice->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateDomainShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11DomainShader **ppDomainShader)
{
	return m_pDevice->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateComputeShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11ComputeShader **ppComputeShader)
{
	return m_pDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateClassLinkage(_Out_ ID3D11ClassLinkage **ppLinkage)
{
	return m_pDevice->CreateClassLinkage(ppLinkage);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateBlendState(_In_ const D3D11_BLEND_DESC *pBlendStateDesc, _Out_opt_ ID3D11BlendState **ppBlendState)
{
	return m_pDevice->CreateBlendState(pBlendStateDesc, ppBlendState);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateDepthStencilState(_In_ const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc, _Out_opt_ ID3D11DepthStencilState **ppDepthStencilState)
{
	return m_pDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateRasterizerState(_In_ const D3D11_RASTERIZER_DESC *pRasterizerDesc, _Out_opt_ ID3D11RasterizerState **ppRasterizerState)
{
	return m_pDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateSamplerState(_In_ const D3D11_SAMPLER_DESC *pSamplerDesc, _Out_opt_ ID3D11SamplerState **ppSamplerState)
{
	return m_pDevice->CreateSamplerState(pSamplerDesc, ppSamplerState);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreatePredicate(_In_ const D3D11_QUERY_DESC *pPredicateDesc, _Out_opt_ ID3D11Predicate **ppPredicate)
{
	return m_pDevice->CreatePredicate(pPredicateDesc, ppPredicate);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateCounter(_In_ const D3D11_COUNTER_DESC *pCounterDesc, _Out_opt_ ID3D11Counter **ppCounter)
{
	return m_pDevice->CreateCounter(pCounterDesc, ppCounter);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CreateDeferredContext(UINT ContextFlags, _Out_opt_ ID3D11DeviceContext **ppDeferredContext)
{
	return m_pDevice->CreateDeferredContext(ContextFlags, ppDeferredContext);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::OpenSharedResource(_In_ HANDLE hResource, _In_ REFIID ReturnedInterface, _Out_opt_ void **ppResource)
{
	return m_pDevice->OpenSharedResource(hResource, ReturnedInterface, ppResource);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CheckFormatSupport(_In_ DXGI_FORMAT Format, _Out_ UINT *pFormatSupport)
{
	return m_pDevice->CheckFormatSupport(Format, pFormatSupport);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CheckMultisampleQualityLevels(_In_ DXGI_FORMAT Format, _In_ UINT SampleCount, _Out_ UINT *pNumQualityLevels)
{
	return m_pDevice->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
}

void STDMETHODCALLTYPE Direct3DDevice11::CheckCounterInfo(_Out_ D3D11_COUNTER_INFO *pCounterInfo)
{
	return m_pDevice->CheckCounterInfo(pCounterInfo);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CheckCounter(_In_ const D3D11_COUNTER_DESC *pDesc, _Out_ D3D11_COUNTER_TYPE *pType, _Out_ UINT *pActiveCounters, _Out_writes_opt_(*pNameLength) LPSTR szName, _Inout_opt_ UINT *pNameLength, _Out_writes_opt_(*pUnitsLength) LPSTR szUnits, _Inout_opt_ UINT *pUnitsLength, _Out_writes_opt_(*pDescriptionLength) LPSTR szDescription, _Inout_opt_ UINT *pDescriptionLength)
{
	return m_pDevice->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szDescription, pDescriptionLength);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::CheckFeatureSupport(D3D11_FEATURE Feature, _Out_writes_bytes_(FeatureSupportDataSize) void *pFeatureSupportData, UINT FeatureSupportDataSize)
{
	return m_pDevice->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::GetPrivateData(_In_ REFGUID guid, _Inout_ UINT *pDataSize, _Out_writes_bytes_opt_(*pDataSize) void *pData)
{
	return m_pDevice->GetPrivateData(guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::SetPrivateData(_In_ REFGUID guid, _In_ UINT DataSize, _In_reads_bytes_opt_(DataSize) const void *pData)
{
	return m_pDevice->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::SetPrivateDataInterface(_In_ REFGUID guid, _In_opt_ const IUnknown *pData)
{
	return m_pDevice->SetPrivateDataInterface(guid, pData);
}

D3D_FEATURE_LEVEL STDMETHODCALLTYPE Direct3DDevice11::GetFeatureLevel(void)
{
	return m_pDevice->GetFeatureLevel();
}

UINT STDMETHODCALLTYPE Direct3DDevice11::GetCreationFlags(void)
{
	return m_pDevice->GetCreationFlags();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::GetDeviceRemovedReason(void)
{
	return m_pDevice->GetDeviceRemovedReason();
}

void STDMETHODCALLTYPE Direct3DDevice11::GetImmediateContext(_Out_ ID3D11DeviceContext **ppImmediateContext)
{
	OutputDebugString("GetImmediateContext");

	return m_pDevice->GetImmediateContext(ppImmediateContext);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice11::SetExceptionMode(UINT RaiseFlags)
{
	return m_pDevice->SetExceptionMode(RaiseFlags);
}

UINT STDMETHODCALLTYPE Direct3DDevice11::GetExceptionMode(void)
{
	return m_pDevice->GetExceptionMode();
}
