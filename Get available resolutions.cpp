#include "stdafx.h"
#include <iostream>
#include <vector>

void normal_way() {
	DEVMODE dm = { 0 };
	int num = 0;
	dm.dmSize = sizeof(dm);
	for (int iModeNum = 0; EnumDisplaySettings(NULL, iModeNum, &dm) != 0; iModeNum++) {
		std::cout << "Mode #" << iModeNum << " = " << dm.dmPelsWidth << "x" << dm.dmPelsHeight << " Hz " << dm.dmDisplayFrequency << std::endl;
		num++;
	}
	std::cout <<"NORMAL WAY NUM RESOLUTIONS = " << num << std::endl;
}


int main() {
	normal_way();
	IDXGIAdapter* pAdapter;
	IDXGIFactory* pFactory = NULL;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	pFactory->EnumAdapters(0, &pAdapter);
	if (pFactory)
	{
		pFactory->Release();
	}	
	IDXGIOutput* pOutput = NULL;	
	pAdapter->EnumOutputs(0, &pOutput);
	UINT numModes = 0;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;	
	// Get the number of elements
	pOutput->GetDisplayModeList(format, 0, &numModes, NULL);
	std::cout <<" Number of available modes = "<< numModes<<std::endl;
	std::vector<DXGI_MODE_DESC> modeList(numModes);
	// Get the list
	pOutput->GetDisplayModeList(format, 0, &numModes, &modeList[0]);	
	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;		
		std::cout <<"Width = "<< x.Width<< "	Height =" << x.Height << "	Refresh = "<< n/d <<" Hz" <<std::endl;
	}
}