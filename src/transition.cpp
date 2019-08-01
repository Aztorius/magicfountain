#include "transition.h"

Transition::Transition(const QString &data) : Block(data)
{

}

QString Transition::toHtml()
{
    return "<p class='transition'>" + htmlCheckBIU(m_data) + "</p>";
}

QString Transition::toFountain()
{
    return "> " + m_data;
}
