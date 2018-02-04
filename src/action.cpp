#include "action.h"

Action::Action(const QString &data) : Block(data)
{

}

void Action::setCentered(bool isCentered)
{
    m_isCentered = isCentered;
}

QString Action::toHtml()
{
    return m_data;
}

QString Action::toFountain()
{
    return m_data;
}
