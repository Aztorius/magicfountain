#include "dialogue.h"

Dialogue::Dialogue(const QString &data) : DialogueBlock(data)
{

}

QString Dialogue::toHtml()
{
    return "<p class='dialogue'>" + htmlCheckBIU(m_data) + "</p>";
}

QString Dialogue::toFountain()
{
    return m_data;
}

void Dialogue::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}
