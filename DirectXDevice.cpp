#include "DirectXDevice.h"
using namespace Microsoft::WRL;
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
//Prints out each video card(including Microsoft software render)
// And prints out all connected display names and their available resolutions and refresh rates
void DirectXDevice::LogAdapters(){
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	DXGI_ADAPTER_DESC desc;
	while (mdxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)	{		
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
	CreateD3DDevice();
}

//Prints all connected displays for each video card
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

//Prints out available Resolutions and Refresh rates for each connected display
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

void DirectXDevice::CreateD3DDevice(){
#if defined(DEBUG) || defined(_DEBUG)
	// Enable the D3D12 debug layer.
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif
	// Try to create hardware device.
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr, // default adapter
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&md3dDevice));	
	if (md3dDevice) {
		std::wcout << "Device Created Succeffully" << std::endl;
	}
	else {
		std::wcout << "Failed to Create Device " << std::endl;
	}
}

