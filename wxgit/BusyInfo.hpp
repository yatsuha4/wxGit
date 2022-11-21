#pragma once

namespace wxgit
{
    /**
     *
     */
    class BusyInfo
        : public wxBusyInfo
    {
        using super = wxBusyInfo;

    private:
        wxWindowDisabler disabler_;

    public:
        BusyInfo(const wxString& message, wxWindow* parent = nullptr);
        ~BusyInfo() override = default;
    };
}
