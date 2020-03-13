#include "cgnsmodule.h"
#include <commctrl.h>
#include <ShlObj_core.h>

#pragma comment(lib, "comctl32.lib")

HRESULT CGShellMalloc::Init()
{
    m_pMalloc = NULL;
    if (FAILED(::SHGetMalloc(&m_pMalloc)))
    {
        return E_FAIL;
    }
    return S_OK;
}

void CGShellMalloc::Term()
{
    if (m_pMalloc != NULL)
    {
        m_pMalloc->Release();
    }
}

CGShellMalloc::operator LPMALLOC() const
{
    return m_pMalloc;
}

LPVOID CGShellMalloc::Alloc(ULONG cb)
{
    return m_pMalloc->Alloc(cb);
}
void CGShellMalloc::Free(LPVOID p)
{
    m_pMalloc->Free(p);
}

HRESULT CGnsModule::Init(__in _ATL_OBJMAP_ENTRY* p, __in HINSTANCE h, 
    __in LPCWSTR lpszResRelativeDir, __in_opt const GUID* plibid /*= NULL*/)
{
    ::OleInitialize(NULL);
    ::InitCommonControls();

#ifndef _NO_CLIPFORMATS
    #define	CFSTR_OLECLIPBOARDPERSISTONFLUSH TEXT("OleClipboardPersistOnFlush")

    m_CFSTR_SHELLIDLIST = (CLIPFORMAT)::RegisterClipboardFormat(CFSTR_SHELLIDLIST);
    m_CFSTR_FILECONTENTS = (CLIPFORMAT)::RegisterClipboardFormat(CFSTR_FILECONTENTS);
    m_CFSTR_FILEDESCRIPTOR = (CLIPFORMAT)::RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR);
    m_CFSTR_PASTESUCCEEDED = (CLIPFORMAT)::RegisterClipboardFormat(CFSTR_PASTESUCCEEDED);
    m_CFSTR_LOGICALPERFORMEDDROPEFFECT = (CLIPFORMAT)::RegisterClipboardFormat(CFSTR_LOGICALPERFORMEDDROPEFFECT);
    m_CFSTR_PERFORMEDDROPEFFECT = (CLIPFORMAT)::RegisterClipboardFormat(CFSTR_PERFORMEDDROPEFFECT);
    m_CFSTR_PREFERREDDROPEFFECT = (CLIPFORMAT)::RegisterClipboardFormat(CFSTR_PREFERREDDROPEFFECT);
    m_CFSTR_OLECLIPBOARDPERSISTONFLUSH = (CLIPFORMAT)::RegisterClipboardFormat(CFSTR_OLECLIPBOARDPERSISTONFLUSH);
#endif // !_NO_CLIPFORMATS

    HRESULT hr = m_Allocator.Init();
    if (FAILED(hr))
    {
        return hr;
    }

    OSVERSIONINFO osVersion = { 0 };
    osVersion.dwOSVersionInfoSize = sizeof(osVersion);
    ::GetVersionEx(&osVersion);

    m_dwWinMajor = osVersion.dwMajorVersion;
    m_dwWinMinor = osVersion.dwMinorVersion;
    m_dwPlatformId = osVersion.dwPlatformId;

    m_dwInitIconCount = 0;
    m_upGdiplusToken = NULL;
    ::InitializeCriticalSection(&m_csGdiplus);
    memset(m_szHelpDocName, 0, sizeof(m_szHelpDocName));

    ::GetModuleFileName(h, m_szInstallPath, sizeof(m_szInstallPath) / sizeof(WCHAR));
    ::PathRemoveFileSpec(m_szInstallPath);

    wcscpy_s(m_szResPath, sizeof(m_szResPath) / sizeof(WCHAR), m_szInstallPath);
    ::PathAppend(m_szResPath, lpszResRelativeDir);

    return CComModule::Init(p, h, plibid);
}

