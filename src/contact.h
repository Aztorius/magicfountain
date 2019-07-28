#ifndef CONTACT_H
#define CONTACT_H

#include "titlepageelement.h"

class Contact : public TitlePageElement
{
public:
    Contact(const QString &firstLine);

    QString toFountain();
    QString toHtml();
};

#endif // CONTACT_H
