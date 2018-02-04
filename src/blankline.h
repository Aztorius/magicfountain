#ifndef BLANKLINE_H
#define BLANKLINE_H

#include "block.h"

class BlankLine : public Block
{
public:
    BlankLine();

    virtual QString toHtml();
    virtual QString toFountain();
};

#endif // BLANKLINE_H
