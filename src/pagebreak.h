#ifndef PAGEBREAK_H
#define PAGEBREAK_H

#include "block.h"

class PageBreak : public Block
{
public:
    PageBreak();

    QString toHtml();
    QString toFountain();
    void toTreeWidgetItem(QTreeWidgetItem *parent);
};

#endif // PAGEBREAK_H
