#include "VireioD3DProxyDevice.h"

VireioD3DProxyDevice::VireioD3DProxyDevice(ID3D11Device* pDevice) : Direct3DDevice11(pDevice)
{

}

VireioD3DProxyDevice::~VireioD3DProxyDevice()
{

}

#define IF_GUID(riid,a,b,c,d,e,f,g,h,i,j,k) if ((riid.Data1==a)&&(riid.Data2==b)&&(riid.Data3==c)&&(riid.Data4[0]==d)&&(riid.Data4[1]==e)&&(riid.Data4[2]==f)&&(riid.Data4[3]==g)&&(riid.Data4[4]==h)&&(riid.Data4[5]==i)&&(riid.Data4[6]==j)&&(riid.Data4[7]==k))
HRESULT STDMETHODCALLTYPE VireioD3DProxyDevice::QueryInterface(REFIID riid, void **ppvObject)
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
	return Direct3DDevice11::QueryInterface(riid, ppvObject);
}

