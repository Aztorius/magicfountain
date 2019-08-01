#ifndef PAGEBREAK_H
#define PAGEBREAK_H

#include "block.h"

class PageBreak : public Block
{
public:
    PageBreak();

    QString toHtml();
    QString toFountain();
};

#endif // PAGEBREAK_H
