#include "scenesection.h"

SceneSection::SceneSection(const QString &m_data) : Section(m_data)
{

}

QString SceneSection::toHtml()
{
    //TODO Print internal blocks

    return QString();
}

QString SceneSection::toFountain()
{
    //TODO Print internal blocks

    return "### " + m_data;
}

void SceneSection::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    //TODO Add internal blocks to tree

    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}
