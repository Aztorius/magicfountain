#include "act.h"

Act::Act(const QString &m_data) : Section(m_data)
{

}

QString Act::toHtml()
{
    return QString();
}

QString Act::toFountain()
{
    return "# " + m_data;
}
