/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2012 Andres Hernandez

File <Direct3DDevice9.h> and
Class <BaseDirect3DDevice9> :
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

#ifndef DIRECT3DDEVICE11_H_INCLUDED
#define DIRECT3DDEVICE11_H_INCLUDED

#include <d3d11.h>

/**
*  Direct 3D device class.
*  Overwrites IDirect3DDevice9 and imbeds the actual device pointer.
*/
class Direct3DDevice11 : public ID3D11Device
{
public:
	Direct3DDevice11(ID3D11Device* pDevice);
	virtual ~Direct3DDevice11();

	/*** IUnknown methods ***/
	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG   WINAPI AddRef();
	virtual ULONG   WINAPI Release();

	/*** BaseDirect3DDevice9 methods ***/
	ID3D11Device* getActual();

	virtual HRESULT STDMETHODCALLTYPE CreateBuffer(_In_ const D3D11_BUFFER_DESC *pDesc, _In_opt_ const D3D11_SUBRESOURCE_DATA *pInitialData, _Out_opt_ ID3D11Buffer **ppBuffer);

	virtual HRESULT STDMETHODCALLTYPE CreateTexture1D(_In_ const D3D11_TEXTURE1D_DESC *pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA *pInitialData, _Out_opt_ ID3D11Texture1D **ppTexture1D);

	virtual HRESULT STDMETHODCALLTYPE CreateTexture2D(_In_ const D3D11_TEXTURE2D_DESC *pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA *pInitialData, _Out_opt_ ID3D11Texture2D **ppTexture2D);

	virtual HRESULT STDMETHODCALLTYPE CreateTexture3D(_In_ const D3D11_TEXTURE3D_DESC *pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels)) const D3D11_SUBRESOURCE_DATA *pInitialData, _Out_opt_ ID3D11Texture3D **ppTexture3D);

	virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView(_In_ ID3D11Resource *pResource, _In_opt_ const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, _Out_opt_ ID3D11ShaderResourceView **ppSRView);

	virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView(_In_ ID3D11Resource *pResource, _In_opt_ const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc, _Out_opt_ ID3D11UnorderedAccessView **ppUAView);

	virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView(_In_ ID3D11Resource *pResource, _In_opt_ const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, _Out_opt_ ID3D11RenderTargetView **ppRTView);

	virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilView(_In_ ID3D11Resource *pResource, _In_opt_ const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc, _Out_opt_ ID3D11DepthStencilView **ppDepthStencilView);

	virtual HRESULT STDMETHODCALLTYPE CreateInputLayout(_In_reads_(NumElements) const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, _In_range_(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT) UINT NumElements, _In_reads_(BytecodeLength) const void *pShaderBytecodeWithInputSignature, _In_ SIZE_T BytecodeLength, _Out_opt_ ID3D11InputLayout **ppInputLayout);

	virtual HRESULT STDMETHODCALLTYPE CreateVertexShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11VertexShader **ppVertexShader);

	virtual HRESULT STDMETHODCALLTYPE CreateGeometryShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11GeometryShader **ppGeometryShader);

	virtual HRESULT STDMETHODCALLTYPE CreateGeometryShaderWithStreamOutput(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_reads_opt_(NumEntries) const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, _In_range_(0, D3D11_SO_STREAM_COUNT * D3D11_SO_OUTPUT_COMPONENT_COUNT) UINT NumEntries, _In_reads_opt_(NumStrides) const UINT *pBufferStrides, _In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT) UINT NumStrides, _In_ UINT RasterizedStream, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11GeometryShader **ppGeometryShader);

	virtual HRESULT STDMETHODCALLTYPE CreatePixelShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11PixelShader **ppPixelShader);

	virtual HRESULT STDMETHODCALLTYPE CreateHullShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11HullShader **ppHullShader);

	virtual HRESULT STDMETHODCALLTYPE CreateDomainShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11DomainShader **ppDomainShader);

	virtual HRESULT STDMETHODCALLTYPE CreateComputeShader(_In_reads_(BytecodeLength) const void *pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage *pClassLinkage, _Out_opt_ ID3D11ComputeShader **ppComputeShader);

	virtual HRESULT STDMETHODCALLTYPE CreateClassLinkage(_Out_ ID3D11ClassLinkage **ppLinkage);

	virtual HRESULT STDMETHODCALLTYPE CreateBlendState(_In_ const D3D11_BLEND_DESC *pBlendStateDesc, _Out_opt_ ID3D11BlendState **ppBlendState);

	virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilState(_In_ const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc, _Out_opt_ ID3D11DepthStencilState **ppDepthStencilState);

	virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState(_In_ const D3D11_RASTERIZER_DESC *pRasterizerDesc, _Out_opt_ ID3D11RasterizerState **ppRasterizerState);

	virtual HRESULT STDMETHODCALLTYPE CreateSamplerState(_In_ const D3D11_SAMPLER_DESC *pSamplerDesc, _Out_opt_ ID3D11SamplerState **ppSamplerState);

	virtual HRESULT STDMETHODCALLTYPE CreateQuery(_In_ const D3D11_QUERY_DESC *pQueryDesc, _Out_opt_ ID3D11Query **ppQuery);

	virtual HRESULT STDMETHODCALLTYPE CreatePredicate(_In_ const D3D11_QUERY_DESC *pPredicateDesc, _Out_opt_ ID3D11Predicate **ppPredicate);

	virtual HRESULT STDMETHODCALLTYPE CreateCounter(_In_ const D3D11_COUNTER_DESC *pCounterDesc, _Out_opt_ ID3D11Counter **ppCounter);

	virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext(UINT ContextFlags, _Out_opt_ ID3D11DeviceContext **ppDeferredContext);

	virtual HRESULT STDMETHODCALLTYPE OpenSharedResource(_In_ HANDLE hResource, _In_ REFIID ReturnedInterface, _Out_opt_ void **ppResource);

	virtual HRESULT STDMETHODCALLTYPE CheckFormatSupport(_In_ DXGI_FORMAT Format, _Out_ UINT *pFormatSupport);

	virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels(_In_ DXGI_FORMAT Format, _In_ UINT SampleCount, _Out_ UINT *pNumQualityLevels);

	virtual void STDMETHODCALLTYPE CheckCounterInfo(_Out_ D3D11_COUNTER_INFO *pCounterInfo);

	virtual HRESULT STDMETHODCALLTYPE CheckCounter(_In_ const D3D11_COUNTER_DESC *pDesc, _Out_ D3D11_COUNTER_TYPE *pType, _Out_ UINT *pActiveCounters, _Out_writes_opt_(*pNameLength) LPSTR szName, _Inout_opt_ UINT *pNameLength, _Out_writes_opt_(*pUnitsLength) LPSTR szUnits, _Inout_opt_ UINT *pUnitsLength, _Out_writes_opt_(*pDescriptionLength) LPSTR szDescription, _Inout_opt_ UINT *pDescriptionLength);

	virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(D3D11_FEATURE Feature, _Out_writes_bytes_(FeatureSupportDataSize) void *pFeatureSupportData, UINT FeatureSupportDataSize);

	virtual HRESULT STDMETHODCALLTYPE GetPrivateData(_In_ REFGUID guid, _Inout_ UINT *pDataSize, _Out_writes_bytes_opt_(*pDataSize) void *pData);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateData(_In_ REFGUID guid, _In_ UINT DataSize, _In_reads_bytes_opt_(DataSize) const void *pData);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(_In_ REFGUID guid, _In_opt_ const IUnknown *pData);

	virtual D3D_FEATURE_LEVEL STDMETHODCALLTYPE GetFeatureLevel(void);

	virtual UINT STDMETHODCALLTYPE GetCreationFlags(void);

	virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason(void);

	virtual void STDMETHODCALLTYPE GetImmediateContext(_Out_ ID3D11DeviceContext **ppImmediateContext);

	virtual HRESULT STDMETHODCALLTYPE SetExceptionMode(UINT RaiseFlags);

	virtual UINT STDMETHODCALLTYPE GetExceptionMode(void);


private:
	/**
	* Actual Direct3D Device pointer embedded.
	* Private to force you to think about whether you really need direct
	* access to the actual device. Can be accessed via getActual().
	***/
	ID3D11Device* m_pDevice;

	/**
	* Internal reference counter.
	***/
	ULONG m_nRefCount;
#ifdef _EXPORT_LOGFILE
	/**
	* The log file (.txt format).
	* Outputs D3D device history.
	* (define _EXPORT_LOGFILE to use this)
	***/
	std::ofstream m_logFile;
#endif
};

#endif
