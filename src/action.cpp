#include "action.h"

Action::Action(const QString &data) : Block(data)
{
    m_isCentered = false;
}

void Action::setCentered(bool isCentered)
{
    m_isCentered = isCentered;
}

QString Action::toHtml()
{
    QString result = "<p>" + htmlCheckBIU(m_data) + "</p>";

    if (m_isCentered) {
        result = "<p style='text-align: center !important; '>" + htmlCheckBIU(m_data) + "</p>";
    }

    return result;
}

QString Action::toFountain()
{
    QString result = m_data;

    if (m_isCentered) {
        result = "> " + m_data + " <";
    }

    return result;
}

void Action::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}
