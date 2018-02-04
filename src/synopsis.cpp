#include "synopsis.h"

Synopsis::Synopsis()
{

}

Synopsis::Synopsis(const QString &m_data) : Block(m_data)
{

}

QString Synopsis::toHtml()
{
    return QString();
}

QString Synopsis::toFountain()
{
    return "= " + m_data;
}

Synopsis& Synopsis::operator=(const Synopsis *other)
{
    m_data = other->m_data;

    return *this;
}
