#pragma once

#include "comm.h"
#include "BaseDXGIFactory.h"
#include "VireioD3DProxyDevice.h"

class VireioDXGIFactory : public BaseDXGIFactory,  public IProxyFactory
{
private:
	VireioD3DProxyDevice *m_device;

public:
	VireioDXGIFactory(IDXGIFactory *factory);
	
	virtual void SetD3DProxy(void *device);
};

