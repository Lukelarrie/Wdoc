#include <iostream>
#include <windows.h>
#include <vector>
#include <dxgi.h>
#include <string>

#pragma comment(lib, "dxgi.lib")

// Helper function to convert wide string to string
std::string WideToString(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

void PrintCoreHardware() {
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);

    std::cout << "--- Core Hardware ---" << std::endl;
    std::cout << "Processor Architecture: ";
    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64: std::cout << "x64 (AMD or Intel)"; break;
        case PROCESSOR_ARCHITECTURE_ARM: std::cout << "ARM"; break;
        case PROCESSOR_ARCHITECTURE_ARM64: std::cout << "ARM64"; break;
        case PROCESSOR_ARCHITECTURE_INTEL: std::cout << "x86"; break;
        default: std::cout << "Unknown"; break;
    }
    std::cout << std::endl;
    std::cout << "Number of Processors: " << sysInfo.dwNumberOfProcessors << std::endl;

    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);
    if (GlobalMemoryStatusEx(&memStatus)) {
        std::cout << "Total Physical Memory: " << memStatus.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
    }
    std::cout << std::endl;
}

void PrintGPUInfo() {
    std::cout << "--- GPU Information ---" << std::endl;
    IDXGIFactory* pFactory = NULL;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory))) {
        std::cout << "Failed to create DXGI factory." << std::endl;
        return;
    }

    IDXGIAdapter* pAdapter;
    for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        DXGI_ADAPTER_DESC desc;
        pAdapter->GetDesc(&desc);

        std::string str = WideToString(desc.Description);
        std::cout << "Adapter " << i << ": " << str << std::endl;
        std::cout << "  Dedicated Video Memory: " << desc.DedicatedVideoMemory / (1024 * 1024) << " MB" << std::endl;
        
        pAdapter->Release();
    }
    pFactory->Release();
    std::cout << std::endl;
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC /*hdcMonitor*/, LPRECT /*lprcMonitor*/, LPARAM /*dwData*/) {
    MONITORINFOEX mi;
    mi.cbSize = sizeof(mi);
    if (GetMonitorInfo(hMonitor, &mi)) {
        std::cout << "Monitor Name: " << mi.szDevice << std::endl;
        std::cout << "  Resolution: " << (mi.rcMonitor.right - mi.rcMonitor.left) << "x" << (mi.rcMonitor.bottom - mi.rcMonitor.top) << std::endl;
        if (mi.dwFlags & MONITORINFOF_PRIMARY) {
            std::cout << "  Primary: Yes" << std::endl;
        }
    }
    return TRUE;
}

void PrintMonitorInfo() {
    std::cout << "--- Monitor Information ---" << std::endl;
    if (!EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0)) {
        std::cout << "Failed to enumerate monitors." << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Windows Hardware Checker Tool" << std::endl;
    std::cout << "=============================" << std::endl << std::endl;

    PrintCoreHardware();
    PrintGPUInfo();
    PrintMonitorInfo();

    return 0;
}
