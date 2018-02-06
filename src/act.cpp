#include "act.h"

Act::Act(const QString &m_data) : Section(m_data)
{

}

QString Act::toHtml()
{
    //TODO Print internal blocks

    return QString();
}

QString Act::toFountain()
{
    //TODO Print internal blocks

    return "# " + m_data;
}

void Act::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << m_data);

    //TODO Add internal blocks to tree

    parent->addChild(item);
}
