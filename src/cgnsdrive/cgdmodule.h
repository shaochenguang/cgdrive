#pragma once
#include <atlbase.h>

class CGDShellMalloc
{
public:
    HRESULT Init();
    void Term();
    operator LPMALLOC() const;
    LPVOID Alloc(ULONG cb);
    void Free(LPVOID p);

private:
    LPMALLOC m_pMalloc;
};

class CGDModule
    : public CComModule
{
public:
    HRESULT Init(
        __in _ATL_OBJMAP_ENTRY* p,
        __in HINSTANCE h,
        __in LPCWSTR lpszResRelativeDir,
        __in_opt const GUID* plibid = NULL);

private:
    CGDShellMalloc m_Allocator;
    //KShellImageLists m_ImageLists;
    LPITEMIDLIST m_pidlCGDROOT;

    USHORT m_usOSType;
    WCHAR m_szDN_CGDROOT[MAX_PATH];
    WCHAR m_szInstallPath[MAX_PATH];
    WCHAR m_szResPath[MAX_PATH];
    WCHAR m_szHelpDocName[MAX_PATH];

    DWORD m_dwWinMajor;
    DWORD m_dwWinMinor;
    DWORD m_dwPlatformId;

    ULONG_PTR m_upGdiplusToken;
    CRITICAL_SECTION m_csGdiplus;
    DWORD m_dwInitIconCount;

#ifndef _NO_CLIPFORMATS
    CLIPFORMAT m_CFSTR_SHELLIDLIST;
    CLIPFORMAT m_CFSTR_FILECONTENTS;
    CLIPFORMAT m_CFSTR_PASTESUCCEEDED;
    CLIPFORMAT m_CFSTR_FILEDESCRIPTOR;
    CLIPFORMAT m_CFSTR_PERFORMEDDROPEFFECT;
    CLIPFORMAT m_CFSTR_PREFERREDDROPEFFECT;
    CLIPFORMAT m_CFSTR_LOGICALPERFORMEDDROPEFFECT;
    CLIPFORMAT m_CFSTR_OLECLIPBOARDPERSISTONFLUSH;
#endif // !_NO_CLIPFORMATS
};