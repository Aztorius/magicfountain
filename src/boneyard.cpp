#include "boneyard.h"

Boneyard::Boneyard() : Block()
{

}

void Boneyard::addLine(QString line)
{
    m_data.append(line + "\n");
}

QString Boneyard::toHtml()
{
    return QString();
}

QString Boneyard::toFountain()
{
    return "/*\n" + m_data + "*/\n";
}

void Boneyard::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    Q_UNUSED(parent)
}
