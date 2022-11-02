#include "wxeditor/wxeditor.hpp"

#include "wx/artprov.h"
#include "wx/aui/auibook.h"
#include "wx/dataview.h"
#include "wx/filename.h"
#include "wx/listctrl.h"
#include "wx/memory.h"
#include "wx/stdpaths.h"
#include "wx/treectrl.h"
#include "wx/treelist.h"
#include "wx/xml/xml.h"

#include "git2.h"

namespace wxgit
{
    WXEDITOR_DECLARE_CLASS(Application);
    WXEDITOR_DECLARE_CLASS(CommitWindow);
    WXEDITOR_DECLARE_CLASS(DiffWindow);
    WXEDITOR_DECLARE_CLASS(FileList);
    WXEDITOR_DECLARE_CLASS(FileWindow);
    WXEDITOR_DECLARE_CLASS(MainFrame);
    WXEDITOR_DECLARE_CLASS(RepoBrowser);

    namespace git
    {
        WXEDITOR_DECLARE_CLASS(Blob);
        WXEDITOR_DECLARE_CLASS(Branch);
        WXEDITOR_DECLARE_CLASS(Commit);
        WXEDITOR_DECLARE_CLASS(Config);
        WXEDITOR_DECLARE_CLASS(Diff);
        WXEDITOR_DECLARE_CLASS(Index);
        WXEDITOR_DECLARE_CLASS(Reference);
        WXEDITOR_DECLARE_CLASS(Refspec);
        WXEDITOR_DECLARE_CLASS(Remote);
        WXEDITOR_DECLARE_CLASS(Repository);
        WXEDITOR_DECLARE_CLASS(Signature);
        WXEDITOR_DECLARE_CLASS(Status);
        WXEDITOR_DECLARE_CLASS(Tree);
    }
    namespace history
    {
        WXEDITOR_DECLARE_CLASS(History);
    }
    namespace outliner
    {
        WXEDITOR_DECLARE_CLASS(Branch);
        WXEDITOR_DECLARE_CLASS(Node);
        WXEDITOR_DECLARE_CLASS(Outliner);
        WXEDITOR_DECLARE_CLASS(RefspecNode);
        WXEDITOR_DECLARE_CLASS(RemoteNode);
        WXEDITOR_DECLARE_CLASS(Repository);
    }
}
