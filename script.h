#ifndef SCRIPT_H
#define SCRIPT_H

#include <QString>
#include <QStringList>

class Script
{
public:
    Script(QString script);
    QString checkBoldItalicUnderline(QString text);
    QString toHtml();

private:
    QString title, credit, author, source, draftDate, contact;
    QString htmlScript;

};

#endif // SCRIPT_H
