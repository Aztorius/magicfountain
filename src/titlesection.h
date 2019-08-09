#ifndef TITLESECTION_H
#define TITLESECTION_H

#include "section.h"

class TitleSection : public Section
{
public:
    TitleSection(const QString &data);

    QString toFountain();
    QString toHtml();
    QString toRiver();
};

#endif // TITLESECTION_H
