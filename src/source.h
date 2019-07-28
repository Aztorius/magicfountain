#ifndef SOURCE_H
#define SOURCE_H

#include "titlepageelement.h"

class Source : public TitlePageElement
{
public:
    Source(const QString &firstLine);

    QString toFountain();
    QString toHtml();
};

#endif // SOURCE_H
