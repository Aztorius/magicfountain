#ifndef CREDIT_H
#define CREDIT_H

#include "titlepageelement.h"

class Credit : public TitlePageElement
{
public:
    Credit(const QString &firstLine);

    virtual QString toFountain();
    virtual QString toHtml();
};

#endif // CREDIT_H
