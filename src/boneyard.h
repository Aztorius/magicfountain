#ifndef BONEYARD_H
#define BONEYARD_H

#include "block.h"

class Boneyard : public Block
{
public:
    Boneyard();
    void addLine(QString line);

    virtual QString toHtml();
    virtual QString toFountain();
    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);
};

#endif // BONEYARD_H
