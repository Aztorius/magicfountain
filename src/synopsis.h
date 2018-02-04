#ifndef SYNOPSIS_H
#define SYNOPSIS_H

#include "block.h"

class Synopsis : public Block
{
public:
    Synopsis();
    Synopsis(const QString &m_data);

    virtual QString toHtml();
    virtual QString toFountain();

    Synopsis& operator=(const Synopsis *other);
};

#endif // SYNOPSIS_H
