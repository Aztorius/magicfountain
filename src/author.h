#ifndef AUTHOR_H
#define AUTHOR_H

#include "titlepageelement.h"

class Author : public TitlePageElement
{
public:
    Author(const QString &firstLine);
};

#endif // AUTHOR_H
