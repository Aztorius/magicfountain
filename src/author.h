#ifndef AUTHOR_H
#define AUTHOR_H

#include "titlepageelement.h"

class Author : public TitlePageElement
{
public:
    Author(const QString &firstLine);

    QString toFountain();
    QString toHtml();
};

#endif // AUTHOR_H
