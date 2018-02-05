#ifndef PAGEBREAK_H
#define PAGEBREAK_H

#include "block.h"

class PageBreak : public Block
{
public:
    PageBreak();

    virtual QString toHtml();
    virtual QString toFountain();
    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);
};

#endif // PAGEBREAK_H
