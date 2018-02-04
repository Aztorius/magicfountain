#include "sequence.h"

Sequence::Sequence(const QString &m_data) : Section(m_data)
{

}

QString Sequence::toHtml()
{
    return QString();
}

QString Sequence::toFountain()
{
    return "## " + m_data;
}
