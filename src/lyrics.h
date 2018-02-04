#ifndef LYRICS_H
#define LYRICS_H

#include "block.h"

class Lyrics : public Block
{
public:
    Lyrics(const QString &m_data);

    virtual QString toHtml();
    virtual QString toFountain();
};

#endif // LYRICS_H
