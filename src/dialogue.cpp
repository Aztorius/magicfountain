#include "dialogue.h"

Dialogue::Dialogue(const QString &m_data) : DialogueBlock(m_data)
{

}

QString Dialogue::toHtml()
{
    return "<p class='dialogue'>" + htmlCheckBIU(m_data) + "</p>";
}

QString Dialogue::toFountain()
{
    return m_data;
}
