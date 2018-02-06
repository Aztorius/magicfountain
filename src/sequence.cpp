#include "sequence.h"

Sequence::Sequence(const QString &m_data) : Section(m_data)
{

}

QString Sequence::toHtml()
{
    //TODO Print internal blocks

    return QString();
}

QString Sequence::toFountain()
{
    //TODO Print internal blocks

    return "## " + m_data;
}

void Sequence::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    //TODO Add internal blocks to tree

    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}
