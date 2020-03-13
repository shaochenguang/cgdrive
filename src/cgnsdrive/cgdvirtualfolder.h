#pragma once
#include "stdafx.h"


#define DECLARE_POLY_AGGREATABLE
class ATL_NO_VTABLE CGDVirtualFolder 
    //: public CComObjectRootEx<CComSingleThreadModel>
    //, public CComCoClass<CGDVirtualFolder, &CLSID_CGDVirtualFolder>
    //, public IShellFolder
    //, public IPersistFolder
    //, public IQueryInfo
{
public:
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) {
        return S_OK;
    }
private:

};