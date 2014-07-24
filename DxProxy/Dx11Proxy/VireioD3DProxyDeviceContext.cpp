#include "VireioD3DProxyDeviceContext.h"

VireioD3DProxyDeviceContext::VireioD3DProxyDeviceContext(ID3D11DeviceContext *pContext) :
Direct3DDeviceContext11(pContext)
{

}

VireioD3DProxyDeviceContext::~VireioD3DProxyDeviceContext()
{

}

#define IF_GUID(riid,a,b,c,d,e,f,g,h,i,j,k) if ((riid.Data1==a)&&(riid.Data2==b)&&(riid.Data3==c)&&(riid.Data4[0]==d)&&(riid.Data4[1]==e)&&(riid.Data4[2]==f)&&(riid.Data4[3]==g)&&(riid.Data4[4]==h)&&(riid.Data4[5]==i)&&(riid.Data4[6]==j)&&(riid.Data4[7]==k))
HRESULT STDMETHODCALLTYPE VireioD3DProxyDeviceContext::QueryInterface(REFIID riid, void **ppvObject)
{
	//DEFINE_GUID(IID_IDirect3DDevice9Ex, 0xb18b10ce, 0x2649, 0x405a, 0x87, 0xf, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a);
	IF_GUID(riid, 0xb18b10ce, 0x2649, 0x405a, 0x87, 0xf, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a)
	{
		if (ppvObject == NULL)
			return E_POINTER;

		this->AddRef();
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	return Direct3DDeviceContext11::QueryInterface(riid, ppvObject);
}

