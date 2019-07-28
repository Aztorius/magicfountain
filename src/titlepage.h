#ifndef TITLEPAGE_H
#define TITLEPAGE_H

#include "titlepageelement.h"

class TitlePage
{
public:
    TitlePage();
    ~TitlePage();

    void clear();
    void addElement(TitlePageElement *element);
    QString toFoutain();
    QString toHtml();

private:
    QList<TitlePageElement *> m_content;
};

#endif // TITLEPAGE_H
