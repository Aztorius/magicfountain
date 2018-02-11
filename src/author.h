#ifndef AUTHOR_H
#define AUTHOR_H

#include "titlepageelement.h"

class Author : public TitlePageElement
{
public:
    Author(const QString &firstLine);

    virtual QString toFountain();
    virtual QString toHtml();
};

#endif // AUTHOR_H
