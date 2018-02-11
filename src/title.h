#ifndef TITLE_H
#define TITLE_H

#include "titlepageelement.h"

class Title : public TitlePageElement
{
public:
    Title(const QString &firstLine);

    virtual QString toFountain();
    virtual QString toHtml();
};

#endif // TITLE_H
