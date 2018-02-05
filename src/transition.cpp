#include "transition.h"

Transition::Transition(const QString &m_data) : Block(m_data)
{

}

QString Transition::toHtml()
{
    return "<p class='transition'>" + htmlCheckBIU(m_data) + "</p>";
}

QString Transition::toFountain()
{
    return "> " + m_data;
}

void Transition::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}
