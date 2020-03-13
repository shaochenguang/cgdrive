#include "stdafx.h"
#include <string>
#include "log/logging.h"
#include "cgdmodule.h"
#include "cgdshellview.h"
#include "cgddef.h"
#include "cgdvirtualfolder.h"
#include "cgdhook.h"

FileLogger logging("cgnsdrive.log");
CGDModule g_CGDModule;

// {EED6379A-D755-4372-8744-4A7873B8D34B}
const CLSID CLSID_CGDVirtualFolder = { 0xeed6379a, 0xd755, 0x4372, { 0x87, 0x44, 0x4a, 0x78, 0x73, 0xb8, 0xd3, 0x4b } };
// {C0545B66-150E-4141-8B9F-24B63F4FC9BE}
const CLSID CLSID_CGDVirtualFolderCG = { 0xc0545b66, 0x150e, 0x4141, { 0x8b, 0x9f, 0x24, 0xb6, 0x3f, 0x4f, 0xc9, 0xbe } };
// {DF936597-0334-4BFE-9643-CD69CF7B8306}
const CLSID CLSID_CGDShellView = { 0xdf936597, 0x334, 0x4bfe, { 0x96, 0x43, 0xcd, 0x69, 0xcf, 0x7b, 0x83, 0x6 } };

BEGIN_OBJECT_MAP(ObjectMap)
//OBJECT_ENTRY(CLSID_CGDShellView, CGDShellView)
//OBJECT_ENTRY(CLSID_CGDVirtualFolderCG, CGDVirtualFolder)
END_OBJECT_MAP()

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(0, TEXT("DLL_PROCESS_ATTACH"), TEXT("DLL_PROCESS_ATTACH"), 0);
        g_CGDModule.Init(ObjectMap, hModule, RES_NAME_RELATIVE_DIR);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

STDAPI DllCanUnloadNow(void)
{
    LOGDEBUG << "call DllCanUnloadNow";
    return S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    LOGDEBUG << "call DllGetClassObject";
    return S_OK;
}

// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
    LOGDEBUG << "call DllRegisterServer";
    // registers object, typelib and all interfaces in typelib
    ATL::AtlSetPerUserRegistration(true);
    HRESULT hr = g_CGDModule.RegisterServer(FALSE);
    return hr;
}


STDAPI DllUnregisterServer(void)
{
    LOGDEBUG << "call DllUnregisterServer";
    ::CoFreeUnusedLibraries();

    return S_OK;
}

STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    LOGDEBUG << "call DllInstall";
    return S_OK;
}

