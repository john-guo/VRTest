#include "Direct3DDeviceContext11.h"
#include <stdexcept>

Direct3DDeviceContext11::Direct3DDeviceContext11(ID3D11DeviceContext *context) :
m_context(context),
m_nRefCount(1)
{

}

Direct3DDeviceContext11::~Direct3DDeviceContext11()
{
	if (m_context)
		m_context->Release();
}

HRESULT STDMETHODCALLTYPE Direct3DDeviceContext11::QueryInterface(REFIID riid, void **ppvObject)
{
	return m_context->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE Direct3DDeviceContext11::AddRef(void)
{
	return ++m_nRefCount;
}

ULONG STDMETHODCALLTYPE Direct3DDeviceContext11::Release(void)
{
	if (--m_nRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_nRefCount;
}


void STDMETHODCALLTYPE Direct3DDeviceContext11::GetDevice(_Out_ ID3D11Device **ppDevice)
{
	OutputDebugString("GetDevice");
	m_context->GetDevice(ppDevice);
}

HRESULT STDMETHODCALLTYPE Direct3DDeviceContext11::GetPrivateData(_In_ REFGUID guid, _Inout_ UINT *pDataSize, _Out_writes_bytes_opt_(*pDataSize) void *pData)
{
	return m_context->GetPrivateData(guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE Direct3DDeviceContext11::SetPrivateData(_In_ REFGUID guid, _In_ UINT DataSize, _In_reads_bytes_opt_(DataSize) const void *pData)
{
	return m_context->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE Direct3DDeviceContext11::SetPrivateDataInterface(_In_ REFGUID guid, _In_opt_ const IUnknown *pData)
{
	return m_context->SetPrivateDataInterface(guid, pData);
}


void STDMETHODCALLTYPE Direct3DDeviceContext11::VSSetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _In_reads_opt_(NumBuffers) ID3D11Buffer *const *ppConstantBuffers)
{
	m_context->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::PSSetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _In_reads_opt_(NumViews) ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	m_context->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::PSSetShader(_In_opt_ ID3D11PixelShader *pPixelShader, _In_reads_opt_(NumClassInstances) ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	m_context->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::PSSetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _In_reads_opt_(NumSamplers) ID3D11SamplerState *const *ppSamplers)
{
	m_context->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::VSSetShader(_In_opt_ ID3D11VertexShader *pVertexShader, _In_reads_opt_(NumClassInstances) ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	m_context->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DrawIndexed(_In_ UINT IndexCount, _In_ UINT StartIndexLocation, _In_ INT BaseVertexLocation)
{
	m_context->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::Draw(_In_ UINT VertexCount, _In_ UINT StartVertexLocation)
{
	m_context->Draw(VertexCount, StartVertexLocation);
}

HRESULT STDMETHODCALLTYPE Direct3DDeviceContext11::Map(_In_ ID3D11Resource *pResource, _In_ UINT Subresource, _In_ D3D11_MAP MapType, _In_ UINT MapFlags, _Out_ D3D11_MAPPED_SUBRESOURCE *pMappedResource)
{
	return m_context->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::Unmap(_In_ ID3D11Resource *pResource, _In_ UINT Subresource)
{
	m_context->Unmap(pResource, Subresource);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::PSSetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _In_reads_opt_(NumBuffers) ID3D11Buffer *const *ppConstantBuffers)
{
	m_context->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::IASetInputLayout(_In_opt_ ID3D11InputLayout *pInputLayout)
{
	m_context->IASetInputLayout(pInputLayout);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::IASetVertexBuffers(_In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumBuffers, _In_reads_opt_(NumBuffers) ID3D11Buffer *const *ppVertexBuffers, _In_reads_opt_(NumBuffers) const UINT *pStrides, _In_reads_opt_(NumBuffers) const UINT *pOffsets)
{
	m_context->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::IASetIndexBuffer(_In_opt_ ID3D11Buffer *pIndexBuffer, _In_ DXGI_FORMAT Format, _In_ UINT Offset)
{
	m_context->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DrawIndexedInstanced(_In_ UINT IndexCountPerInstance, _In_ UINT InstanceCount, _In_ UINT StartIndexLocation, _In_ INT BaseVertexLocation, _In_ UINT StartInstanceLocation)
{
	m_context->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DrawInstanced(_In_ UINT VertexCountPerInstance, _In_ UINT InstanceCount, _In_ UINT StartVertexLocation, _In_ UINT StartInstanceLocation)
{
	m_context->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GSSetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _In_reads_opt_(NumBuffers) ID3D11Buffer *const *ppConstantBuffers)
{
	m_context->GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GSSetShader(_In_opt_ ID3D11GeometryShader *pShader, _In_reads_opt_(NumClassInstances) ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	m_context->GSSetShader(pShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::IASetPrimitiveTopology(_In_ D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	m_context->IASetPrimitiveTopology(Topology);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::VSSetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _In_reads_opt_(NumViews) ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	m_context->VSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::VSSetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _In_reads_opt_(NumSamplers) ID3D11SamplerState *const *ppSamplers)
{
	m_context->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::Begin(_In_ ID3D11Asynchronous *pAsync)
{
	m_context->Begin(pAsync);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::End(_In_ ID3D11Asynchronous *pAsync)
{
	m_context->End(pAsync);
}

HRESULT STDMETHODCALLTYPE Direct3DDeviceContext11::GetData(_In_ ID3D11Asynchronous *pAsync, _Out_writes_bytes_opt_(DataSize) void *pData, _In_ UINT DataSize, _In_ UINT GetDataFlags)
{
	return m_context->GetData(pAsync, pData, DataSize, GetDataFlags);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::SetPredication(_In_opt_ ID3D11Predicate *pPredicate, _In_ BOOL PredicateValue)
{
	m_context->SetPredication(pPredicate, PredicateValue);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GSSetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _In_reads_opt_(NumViews) ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	m_context->GSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GSSetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _In_reads_opt_(NumSamplers) ID3D11SamplerState *const *ppSamplers)
{
	m_context->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::OMSetRenderTargets(_In_range_(0, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) UINT NumViews, _In_reads_opt_(NumViews) ID3D11RenderTargetView *const *ppRenderTargetViews, _In_opt_ ID3D11DepthStencilView *pDepthStencilView)
{
	m_context->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::OMSetRenderTargetsAndUnorderedAccessViews(_In_ UINT NumRTVs, _In_reads_opt_(NumRTVs) ID3D11RenderTargetView *const *ppRenderTargetViews, _In_opt_ ID3D11DepthStencilView *pDepthStencilView, _In_range_(0, D3D11_1_UAV_SLOT_COUNT - 1) UINT UAVStartSlot, _In_ UINT NumUAVs, _In_reads_opt_(NumUAVs) ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, _In_reads_opt_(NumUAVs) const UINT *pUAVInitialCounts)
{
	m_context->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, pDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::OMSetBlendState(_In_opt_ ID3D11BlendState *pBlendState, _In_opt_ const FLOAT BlendFactor[4], _In_ UINT SampleMask)
{
	m_context->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::OMSetDepthStencilState(_In_opt_ ID3D11DepthStencilState *pDepthStencilState, _In_ UINT StencilRef)
{
	m_context->OMSetDepthStencilState(pDepthStencilState, StencilRef);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::SOSetTargets(_In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT) UINT NumBuffers, _In_reads_opt_(NumBuffers) ID3D11Buffer *const *ppSOTargets, _In_reads_opt_(NumBuffers) const UINT *pOffsets)
{
	m_context->SOSetTargets(NumBuffers, ppSOTargets, pOffsets);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DrawAuto(void)
{
	m_context->DrawAuto();
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DrawIndexedInstancedIndirect(_In_ ID3D11Buffer *pBufferForArgs, _In_ UINT AlignedByteOffsetForArgs)
{
	m_context->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DrawInstancedIndirect(_In_ ID3D11Buffer *pBufferForArgs, _In_ UINT AlignedByteOffsetForArgs)
{
	m_context->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::Dispatch(_In_ UINT ThreadGroupCountX, _In_ UINT ThreadGroupCountY, _In_ UINT ThreadGroupCountZ)
{
	m_context->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DispatchIndirect(_In_ ID3D11Buffer *pBufferForArgs, _In_ UINT AlignedByteOffsetForArgs)
{
	m_context->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::RSSetState(_In_opt_ ID3D11RasterizerState *pRasterizerState)
{
	m_context->RSSetState(pRasterizerState);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::RSSetViewports(_In_range_(0, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE) UINT NumViewports, _In_reads_opt_(NumViewports) const D3D11_VIEWPORT *pViewports)
{
	m_context->RSSetViewports(NumViewports, pViewports);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::RSSetScissorRects(_In_range_(0, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE) UINT NumRects, _In_reads_opt_(NumRects) const D3D11_RECT *pRects)
{
	m_context->RSSetScissorRects(NumRects, pRects);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CopySubresourceRegion(_In_ ID3D11Resource *pDstResource, _In_ UINT DstSubresource, _In_ UINT DstX, _In_ UINT DstY, _In_ UINT DstZ, _In_ ID3D11Resource *pSrcResource, _In_ UINT SrcSubresource, _In_opt_ const D3D11_BOX *pSrcBox)
{
	m_context->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CopyResource(_In_ ID3D11Resource *pDstResource, _In_ ID3D11Resource *pSrcResource)
{
	m_context->CopyResource(pDstResource, pSrcResource);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::UpdateSubresource(_In_ ID3D11Resource *pDstResource, _In_ UINT DstSubresource, _In_opt_ const D3D11_BOX *pDstBox, _In_ const void *pSrcData, _In_ UINT SrcRowPitch, _In_ UINT SrcDepthPitch)
{
	m_context->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CopyStructureCount(_In_ ID3D11Buffer *pDstBuffer, _In_ UINT DstAlignedByteOffset, _In_ ID3D11UnorderedAccessView *pSrcView)
{
	m_context->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::ClearRenderTargetView(_In_ ID3D11RenderTargetView *pRenderTargetView, _In_ const FLOAT ColorRGBA[4])
{
	m_context->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::ClearUnorderedAccessViewUint(_In_ ID3D11UnorderedAccessView *pUnorderedAccessView, _In_ const UINT Values[4])
{
	m_context->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::ClearUnorderedAccessViewFloat(_In_ ID3D11UnorderedAccessView *pUnorderedAccessView, _In_ const FLOAT Values[4])
{
	m_context->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::ClearDepthStencilView(_In_ ID3D11DepthStencilView *pDepthStencilView, _In_ UINT ClearFlags, _In_ FLOAT Depth, _In_ UINT8 Stencil)
{
	m_context->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GenerateMips(_In_ ID3D11ShaderResourceView *pShaderResourceView)
{
	m_context->GenerateMips(pShaderResourceView);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::SetResourceMinLOD(_In_ ID3D11Resource *pResource, FLOAT MinLOD)
{
	m_context->SetResourceMinLOD(pResource, MinLOD);
}

FLOAT STDMETHODCALLTYPE Direct3DDeviceContext11::GetResourceMinLOD(_In_ ID3D11Resource *pResource)
{
	return m_context->GetResourceMinLOD(pResource);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::ResolveSubresource(_In_ ID3D11Resource *pDstResource, _In_ UINT DstSubresource, _In_ ID3D11Resource *pSrcResource, _In_ UINT SrcSubresource, _In_ DXGI_FORMAT Format)
{
	m_context->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::ExecuteCommandList(_In_ ID3D11CommandList *pCommandList, BOOL RestoreContextState)
{
	m_context->ExecuteCommandList(pCommandList, RestoreContextState);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::HSSetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _In_reads_opt_(NumViews) ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	m_context->HSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::HSSetShader(_In_opt_ ID3D11HullShader *pHullShader, _In_reads_opt_(NumClassInstances) ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	m_context->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::HSSetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _In_reads_opt_(NumSamplers) ID3D11SamplerState *const *ppSamplers)
{
	m_context->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::HSSetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _In_reads_opt_(NumBuffers) ID3D11Buffer *const *ppConstantBuffers)
{
	m_context->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DSSetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _In_reads_opt_(NumViews) ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	m_context->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DSSetShader(_In_opt_ ID3D11DomainShader *pDomainShader, _In_reads_opt_(NumClassInstances) ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	m_context->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DSSetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _In_reads_opt_(NumSamplers) ID3D11SamplerState *const *ppSamplers)
{
	m_context->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DSSetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _In_reads_opt_(NumBuffers) ID3D11Buffer *const *ppConstantBuffers)
{
	m_context->DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSSetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _In_reads_opt_(NumViews) ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	m_context->CSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSSetUnorderedAccessViews(_In_range_(0, D3D11_1_UAV_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_1_UAV_SLOT_COUNT - StartSlot) UINT NumUAVs, _In_reads_opt_(NumUAVs) ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, _In_reads_opt_(NumUAVs) const UINT *pUAVInitialCounts)
{
	m_context->CSSetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSSetShader(_In_opt_ ID3D11ComputeShader *pComputeShader, _In_reads_opt_(NumClassInstances) ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	m_context->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSSetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _In_reads_opt_(NumSamplers) ID3D11SamplerState *const *ppSamplers)
{
	m_context->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSSetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _In_reads_opt_(NumBuffers) ID3D11Buffer *const *ppConstantBuffers)
{
	m_context->CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::VSGetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _Out_writes_opt_(NumBuffers) ID3D11Buffer **ppConstantBuffers)
{
	m_context->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::PSGetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _Out_writes_opt_(NumViews) ID3D11ShaderResourceView **ppShaderResourceViews)
{
	m_context->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::PSGetShader(_Out_ ID3D11PixelShader **ppPixelShader, _Out_writes_opt_(*pNumClassInstances) ID3D11ClassInstance **ppClassInstances, _Inout_opt_ UINT *pNumClassInstances)
{
	m_context->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::PSGetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _Out_writes_opt_(NumSamplers) ID3D11SamplerState **ppSamplers)
{
	m_context->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::VSGetShader(_Out_ ID3D11VertexShader **ppVertexShader, _Out_writes_opt_(*pNumClassInstances) ID3D11ClassInstance **ppClassInstances, _Inout_opt_ UINT *pNumClassInstances)
{
	m_context->VSGetShader(ppVertexShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::PSGetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _Out_writes_opt_(NumBuffers) ID3D11Buffer **ppConstantBuffers)
{
	m_context->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::IAGetInputLayout(_Out_ ID3D11InputLayout **ppInputLayout)
{
	m_context->IAGetInputLayout(ppInputLayout);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::IAGetVertexBuffers(_In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumBuffers, _Out_writes_opt_(NumBuffers) ID3D11Buffer **ppVertexBuffers, _Out_writes_opt_(NumBuffers) UINT *pStrides, _Out_writes_opt_(NumBuffers) UINT *pOffsets)
{
	m_context->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::IAGetIndexBuffer(_Out_opt_ ID3D11Buffer **pIndexBuffer, _Out_opt_ DXGI_FORMAT *Format, _Out_opt_ UINT *Offset)
{
	m_context->IAGetIndexBuffer(pIndexBuffer, Format, Offset);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GSGetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _Out_writes_opt_(NumBuffers) ID3D11Buffer **ppConstantBuffers)
{
	m_context->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GSGetShader(_Out_ ID3D11GeometryShader **ppGeometryShader, _Out_writes_opt_(*pNumClassInstances) ID3D11ClassInstance **ppClassInstances, _Inout_opt_ UINT *pNumClassInstances)
{
	m_context->GSGetShader(ppGeometryShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::IAGetPrimitiveTopology(_Out_ D3D11_PRIMITIVE_TOPOLOGY *pTopology)
{
	m_context->IAGetPrimitiveTopology(pTopology);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::VSGetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _Out_writes_opt_(NumViews) ID3D11ShaderResourceView **ppShaderResourceViews)
{
	m_context->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::VSGetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _Out_writes_opt_(NumSamplers) ID3D11SamplerState **ppSamplers)
{
	m_context->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GetPredication(_Out_opt_ ID3D11Predicate **ppPredicate, _Out_opt_ BOOL *pPredicateValue)
{
	m_context->GetPredication(ppPredicate, pPredicateValue);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GSGetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _Out_writes_opt_(NumViews) ID3D11ShaderResourceView **ppShaderResourceViews)
{
	m_context->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::GSGetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _Out_writes_opt_(NumSamplers) ID3D11SamplerState **ppSamplers)
{
	m_context->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::OMGetRenderTargets(_In_range_(0, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) UINT NumViews, _Out_writes_opt_(NumViews) ID3D11RenderTargetView **ppRenderTargetViews, _Out_opt_ ID3D11DepthStencilView **ppDepthStencilView)
{
	m_context->OMGetRenderTargets(NumViews, ppRenderTargetViews, ppDepthStencilView);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::OMGetRenderTargetsAndUnorderedAccessViews(_In_range_(0, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) UINT NumRTVs, _Out_writes_opt_(NumRTVs) ID3D11RenderTargetView **ppRenderTargetViews, _Out_opt_ ID3D11DepthStencilView **ppDepthStencilView, _In_range_(0, D3D11_PS_CS_UAV_REGISTER_COUNT - 1) UINT UAVStartSlot, _In_range_(0, D3D11_PS_CS_UAV_REGISTER_COUNT - UAVStartSlot) UINT NumUAVs, _Out_writes_opt_(NumUAVs) ID3D11UnorderedAccessView **ppUnorderedAccessViews)
{
	m_context->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::OMGetBlendState(_Out_opt_ ID3D11BlendState **ppBlendState, _Out_opt_ FLOAT BlendFactor[4], _Out_opt_ UINT *pSampleMask)
{
	m_context->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::OMGetDepthStencilState(_Out_opt_ ID3D11DepthStencilState **ppDepthStencilState, _Out_opt_ UINT *pStencilRef)
{
	m_context->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::SOGetTargets(_In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT) UINT NumBuffers, _Out_writes_opt_(NumBuffers) ID3D11Buffer **ppSOTargets)
{
	m_context->SOGetTargets(NumBuffers, ppSOTargets);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::RSGetState(_Out_ ID3D11RasterizerState **ppRasterizerState)
{
	m_context->RSGetState(ppRasterizerState);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::RSGetViewports(_Inout_ UINT *pNumViewports, _Out_writes_opt_(*pNumViewports) D3D11_VIEWPORT *pViewports)
{
	m_context->RSGetViewports(pNumViewports, pViewports);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::RSGetScissorRects(_Inout_ UINT *pNumRects, _Out_writes_opt_(*pNumRects) D3D11_RECT *pRects)
{
	m_context->RSGetScissorRects(pNumRects, pRects);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::HSGetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _Out_writes_opt_(NumViews) ID3D11ShaderResourceView **ppShaderResourceViews)
{
	m_context->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::HSGetShader(_Out_ ID3D11HullShader **ppHullShader, _Out_writes_opt_(*pNumClassInstances) ID3D11ClassInstance **ppClassInstances, _Inout_opt_ UINT *pNumClassInstances)
{
	m_context->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::HSGetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _Out_writes_opt_(NumSamplers) ID3D11SamplerState **ppSamplers)
{
	m_context->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::HSGetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _Out_writes_opt_(NumBuffers) ID3D11Buffer **ppConstantBuffers)
{
	m_context->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DSGetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _Out_writes_opt_(NumViews) ID3D11ShaderResourceView **ppShaderResourceViews)
{
	m_context->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DSGetShader(_Out_ ID3D11DomainShader **ppDomainShader, _Out_writes_opt_(*pNumClassInstances) ID3D11ClassInstance **ppClassInstances, _Inout_opt_ UINT *pNumClassInstances)
{
	m_context->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DSGetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _Out_writes_opt_(NumSamplers) ID3D11SamplerState **ppSamplers)
{
	m_context->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::DSGetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _Out_writes_opt_(NumBuffers) ID3D11Buffer **ppConstantBuffers)
{
	m_context->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSGetShaderResources(_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot) UINT NumViews, _Out_writes_opt_(NumViews) ID3D11ShaderResourceView **ppShaderResourceViews)
{
	m_context->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSGetUnorderedAccessViews(_In_range_(0, D3D11_PS_CS_UAV_REGISTER_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_PS_CS_UAV_REGISTER_COUNT - StartSlot) UINT NumUAVs, _Out_writes_opt_(NumUAVs) ID3D11UnorderedAccessView **ppUnorderedAccessViews)
{
	m_context->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSGetShader(_Out_ ID3D11ComputeShader **ppComputeShader, _Out_writes_opt_(*pNumClassInstances) ID3D11ClassInstance **ppClassInstances, _Inout_opt_ UINT *pNumClassInstances)
{
	m_context->CSGetShader(ppComputeShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSGetSamplers(_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot) UINT NumSamplers, _Out_writes_opt_(NumSamplers) ID3D11SamplerState **ppSamplers)
{
	m_context->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::CSGetConstantBuffers(_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1) UINT StartSlot, _In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot) UINT NumBuffers, _Out_writes_opt_(NumBuffers) ID3D11Buffer **ppConstantBuffers)
{
	m_context->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::ClearState(void)
{
	m_context->ClearState();
}

void STDMETHODCALLTYPE Direct3DDeviceContext11::Flush(void)
{
	m_context->Flush();
}

D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE Direct3DDeviceContext11::GetType(void)
{
	return m_context->GetType();
}

UINT STDMETHODCALLTYPE Direct3DDeviceContext11::GetContextFlags(void)
{
	return m_context->GetContextFlags();
}

HRESULT STDMETHODCALLTYPE Direct3DDeviceContext11::FinishCommandList(BOOL RestoreDeferredContextState, _Out_opt_ ID3D11CommandList **ppCommandList)
{
	return m_context->FinishCommandList(RestoreDeferredContextState, ppCommandList);
}

