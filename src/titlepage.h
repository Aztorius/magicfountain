#ifndef TITLEPAGE_H
#define TITLEPAGE_H

#include "titlepageelement.h"

class TitlePage
{
public:
    TitlePage();
    void addElement(TitlePageElement *element);
private:
    QList<TitlePageElement *> m_content;
};

#endif // TITLEPAGE_H
