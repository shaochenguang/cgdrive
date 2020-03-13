#pragma once
#include "stdafx.h"



class ATL_NO_VTABLE CGDShellView
    : public CComObjectRootEx<CComSingleThreadModel>
    , public CComCoClass<CGDShellView, &CLSID_CGDShellView>
    , public IShellView
{
public:

    DECLARE_PROTECT_FINAL_CONSTRUCT()
    BEGIN_COM_MAP(CGDShellView)
        COM_INTERFACE_ENTRY_IID(IID_IShellView, IShellView)
        COM_INTERFACE_ENTRY(IOleWindow)
    END_COM_MAP()

public:
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
    {
        return S_OK;
    }


    static BOOL IsProcess(__in LPCWSTR lpszProcessName);

    static BOOL isExplorer();
};