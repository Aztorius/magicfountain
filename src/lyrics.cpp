#include "lyrics.h"

Lyrics::Lyrics(const QString &data) : Block(data)
{

}

QString Lyrics::toHtml()
{
    return "<p>" + htmlCheckBIU(m_data) + "</p>";
}

QString Lyrics::toFountain()
{
    return "~" + m_data;
}

void Lyrics::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}
