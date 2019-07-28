#include "synopsis.h"

Synopsis::Synopsis()
{

}

Synopsis::Synopsis(const QString &data) : Block(data)
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

void Synopsis::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}


Synopsis& Synopsis::operator=(const Synopsis *other)
{
    m_data = other->m_data;

    return *this;
}
