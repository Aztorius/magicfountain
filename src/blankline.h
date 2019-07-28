#ifndef BLANKLINE_H
#define BLANKLINE_H

#include "block.h"

class BlankLine : public Block
{
public:
    BlankLine();

    QString toHtml();
    QString toFountain();
    void toTreeWidgetItem(QTreeWidgetItem *parent);
};

#endif // BLANKLINE_H
