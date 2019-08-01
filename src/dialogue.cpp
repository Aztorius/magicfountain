#include "dialogue.h"

Dialogue::Dialogue(const QString &data) : DialogueBlock(data)
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
