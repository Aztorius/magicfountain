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
};

#endif // BONEYARD_H
