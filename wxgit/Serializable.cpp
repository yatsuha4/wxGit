#include "wxgit/Serializable.hpp"

namespace wxgit
{
    /**
     * @brief シリアライズ
     */
    wxXmlNode* Serializable::serialize() const
    {
        return new wxXmlNode(wxXML_ELEMENT_NODE, getSerialName());
    }

    /**
     * @brief デシリアライズ
     */
    bool Serializable::deserialize(const wxXmlNode* xml)
    {
        return xml && xml->GetName() == getSerialName();
    }

    /**
     * @brief 
     */
    void Serializable::Warning(const wxString& message, const wxXmlNode* node)
    {
        wxLogWarning("%s, '%s':%d", message, node->GetName(), 
                     node->GetLineNumber());
    }
}
