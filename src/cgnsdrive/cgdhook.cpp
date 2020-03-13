#include "cgdhook.h"
#include "cgdshellview.h"


static bool s_bHoolExplorer;
bool CGDHookExplorer()
{
    if (!CGDShellView::isExplorer())
    {
        return false;
    }
    if (s_bHoolExplorer)
    {
        return true;
    }

    //if (!IH_Hook((PVOID*)&fnDoDragDrop, HOOK_DoDragDrop))
    //{
    //    return false;
    //}
    s_bHoolExplorer = true;
    return true;
}



bool CGDUnhookExplorer()
{
    return true;
}