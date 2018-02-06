#include "blankline.h"

BlankLine::BlankLine()
{

}

QString BlankLine::toHtml()
{
    return QString();
}

QString BlankLine::toFountain()
{
    return "\n";
}

void BlankLine::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    Q_UNUSED(parent);
}
