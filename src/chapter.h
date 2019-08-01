#ifndef CHAPTER_H
#define CHAPTER_H

#include "section.h"

class Chapter : public Section
{
public:
    Chapter(const QString &data);

    QString toFountain();
    QString toHtml();
};

#endif // CHAPTER_H
