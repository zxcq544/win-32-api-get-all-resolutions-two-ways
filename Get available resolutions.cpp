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
	//normal_way();
	IDXGIAdapter* pAdapter;
	IDXGIFactory* pFactory = NULL;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	pFactory->EnumAdapters(0, &pAdapter);	
		
	//###### Prints all adapters description #######//
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	DXGI_ADAPTER_DESC desc;
	while (pFactory->EnumAdapters(i, &adapter) !=DXGI_ERROR_NOT_FOUND)	{
		
		adapter->GetDesc(&desc);
		//std::wstring text = L"***Adapter: ";
		//text += desc.Description;
		//text += L"\n";
		std::wcout << L"***Adapter: " << L"Id: "<<i << L"; Description: " << desc.Description << std::endl << std::endl;
		++i;
	}
	//####   End of adapter description print ########//


	if (pFactory)
	{
		pFactory->Release();
	}

	//######### Prints all resolutions for One adapter. For 1 Videocard it's adapter 0 #####//
	IDXGIOutput* pOutput = NULL;	
	pAdapter->EnumOutputs(0, &pOutput);
	UINT numModes = 0;
	//######## Format is tricky. Need to know monitor format.
	//######## People said this one is default for monitors.
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;	
	// Get the number of elements
	pOutput->GetDisplayModeList(format, 0, &numModes, NULL);

	pAdapter->GetDesc(&desc);
	std::wcout << L"Number of available modes for "<<desc.Description<<  L" = " << numModes << std::endl << std::endl;
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