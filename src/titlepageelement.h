#ifndef TITLEPAGEELEMENT_H
#define TITLEPAGEELEMENT_H

#include <QStringList>

class TitlePageElement
{
public:
    TitlePageElement(const QString &firstLine);
    void addLine(const QString &line);
    QStringList getData();

    virtual QString toFountain() = 0;
    virtual QString toHtml() = 0;

    static QString htmlCheckBIU(const QString &text);

private:
    QStringList m_data;
};

#endif // TITLEPAGEELEMENT_H
