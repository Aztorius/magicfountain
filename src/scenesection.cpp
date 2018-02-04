#include "scenesection.h"

SceneSection::SceneSection(const QString &m_data) : Section(m_data)
{

}

QString SceneSection::toHtml()
{
    return QString();
}

QString SceneSection::toFountain()
{
    return "### " + m_data;
}
