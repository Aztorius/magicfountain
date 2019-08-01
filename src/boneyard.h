#ifndef BONEYARD_H
#define BONEYARD_H

#include "block.h"

class Boneyard : public Block
{
public:
    Boneyard();

    void addLine(QString line);

    QString toHtml();
    QString toFountain();
};

#endif // BONEYARD_H
