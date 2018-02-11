#ifndef SOURCE_H
#define SOURCE_H

#include "titlepageelement.h"

class Source : public TitlePageElement
{
public:
    Source(const QString &firstLine);

    virtual QString toFountain();
    virtual QString toHtml();
};

#endif // SOURCE_H
