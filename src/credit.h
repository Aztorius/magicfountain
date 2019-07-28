#ifndef CREDIT_H
#define CREDIT_H

#include "titlepageelement.h"

class Credit : public TitlePageElement
{
public:
    Credit(const QString &firstLine);

    QString toFountain();
    QString toHtml();
};

#endif // CREDIT_H
