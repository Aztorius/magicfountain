#include "parenthetical.h"

Parenthetical::Parenthetical(const QString &data) : DialogueBlock(data)
{

}

QString Parenthetical::toHtml()
{
    return "<p class='parenthetical'>" + htmlCheckBIU(m_data) + "</p>";
}

QString Parenthetical::toFountain()
{
    return m_data;
}
