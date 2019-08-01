#ifndef LYRICS_H
#define LYRICS_H

#include "block.h"

class Lyrics : public Block
{
public:
    Lyrics(const QString &data);

    QString toHtml();
    QString toFountain();
};

#endif // LYRICS_H
