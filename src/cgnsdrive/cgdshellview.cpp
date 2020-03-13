#include "cgdshellview.h"
#include "cgddef.h"

BOOL CGDShellView::IsProcess(__in LPCWSTR lpszProcessName)
{
    if (lpszProcessName == NULL)
    {
        return FALSE;
    }
    WCHAR szPath[MAX_PATH] = { 0 };
    ::GetModuleFileName(NULL, szPath, sizeof(szPath) / sizeof(WCHAR));
    ::PathStripPath(szPath);

    return wcsicmp(szPath, lpszProcessName) == 0;
}

BOOL CGDShellView::isExplorer()
{
    return IsProcess(CGD_EXPLORER_NAME);
}
