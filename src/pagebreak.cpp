#include "pagebreak.h"

PageBreak::PageBreak()
{

}

QString PageBreak::toHtml()
{
    return "</section><section><p class='page-break'></p>";
}

QString PageBreak::toFountain()
{
    return "===";
}

void PageBreak::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    Q_UNUSED(parent)
}
