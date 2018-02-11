#ifndef DRAFTDATE_H
#define DRAFTDATE_H

#include "titlepageelement.h"

class DraftDate : public TitlePageElement
{
public:
    DraftDate(const QString &firstLine);

    virtual QString toFountain();
    virtual QString toHtml();
};

#endif // DRAFTDATE_H
