#include "DirectXDevice.h"
void DirectXDevice::LogAdapters(){
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	DXGI_ADAPTER_DESC desc;
	while (pFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)	{		
		adapter->GetDesc(&desc);
		std::wstring text = L"***Adapter: ";
		text += desc.Description;
		text += L"\n";
		std::wcout<< text.c_str() << std::endl;
		adapterList.push_back(adapter);
		++i;
	}
	for (size_t i = 0; i < adapterList.size(); ++i)	{
		LogAdapterOutputs(adapterList[i]);
		adapterList[i]->Release();
	}	
}
void DirectXDevice::LogAdapterOutputs(IDXGIAdapter* adapter) {
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	DXGI_OUTPUT_DESC desc;
	while (adapter->EnumOutputs(i, &output) !=DXGI_ERROR_NOT_FOUND)	{		
		output->GetDesc(&desc);
		std::wstring text = L"***Output: ";
		text += desc.DeviceName;
		text += L"\n";
		std::wcout << text.c_str() << std::endl;
		//Format for monitor
		LogOutputDisplayModes(output,DXGI_FORMAT_B8G8R8A8_UNORM);
		output->Release();
		++i;
	}
}

void DirectXDevice::LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format){
	UINT count = 0;
	UINT flags = 0;
	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);
	std::vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);
	for (auto& x : modeList){
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		std::wstring text =
			L"Width = " + std::to_wstring(x.Width) + L"\t"+
			L"Height = " + std::to_wstring(x.Height) + L"\t" +
			L"Refresh = " + std::to_wstring(n/d) + L" Hz\n";
		std::wcout<<text.c_str();
	}
}

