#ifndef TITLEPAGEELEMENT_H
#define TITLEPAGEELEMENT_H

#include <QStringList>

class TitlePageElement
{
public:
    TitlePageElement(const QString &firstLine);
    void addLine(const QString &line);
private:
    QStringList m_data;
};

#endif // TITLEPAGEELEMENT_H
