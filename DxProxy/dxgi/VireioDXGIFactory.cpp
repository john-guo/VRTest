#include "VireioDXGIFactory.h"


void VireioDXGIFactory::SetD3DProxy(void *device)
{
	Log("SetD3DProxy %p", device);
	m_device = (VireioD3DProxyDevice*)device;
}

VireioDXGIFactory::VireioDXGIFactory(IDXGIFactory *factory):
BaseDXGIFactory(factory)
{
	
}
