#pragma once
#include "stdafx.h"
#include <iostream>
class DirectXDevice
{
public:
	DirectXDevice() {
		CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	}
	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

	~DirectXDevice() {
		if (pFactory) {
			pFactory->Release();
		}
	}
private:
	IDXGIFactory* pFactory = NULL;
};

