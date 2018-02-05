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

void Sequence::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}
