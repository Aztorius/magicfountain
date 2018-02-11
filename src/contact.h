#ifndef CONTACT_H
#define CONTACT_H

#include "titlepageelement.h"

class Contact : public TitlePageElement
{
public:
    Contact(const QString &firstLine);

    virtual QString toFountain();
    virtual QString toHtml();
};

#endif // CONTACT_H
