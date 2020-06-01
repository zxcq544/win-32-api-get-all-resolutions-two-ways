#pragma once
#include "stdafx.h"
#include <iostream>
#include "DXSampleHelper.h"

class DirectXDevice
{
public:
	DirectXDevice() {
		ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory)));
	}
	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);


	void CreateD3DDevice();

	~DirectXDevice() {
		if (mdxgiFactory) {
			mdxgiFactory->Release();
		}
	}
private:
	IDXGIFactory* mdxgiFactory = NULL;
	ID3D12Device* md3dDevice = NULL;
};

