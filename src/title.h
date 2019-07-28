#ifndef TITLE_H
#define TITLE_H

#include "titlepageelement.h"

class Title : public TitlePageElement
{
public:
    Title(const QString &firstLine);

    QString toFountain();
    QString toHtml();
};

#endif // TITLE_H
