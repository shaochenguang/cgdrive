#pragma once

#ifdef WIN32
// Windows м╥нд╪Ч
#include <windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <commctrl.h>
#include <ShlObj_core.h>
#endif
#include "cgdmodule.h"

extern CGDModule g_CGDModule;
extern const CLSID CLSID_CGDVirtualFolder;
extern const CLSID CLSID_CGDShellView;