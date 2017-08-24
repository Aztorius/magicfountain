#ifndef SCRIPT_H
#define SCRIPT_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>

#include "block.h"

class Script
{
public:
    Script();
    Script(QString script);
    ~Script();

    QString checkBoldItalicUnderline(QString text);
    QString toHtml();
    QList<Block *> getBlocks();

    bool isABlankLine(int i, QStringList lines);

    Script& operator=(const Script& other);
private:
    QString title, credit, author, source, draftDate, contact;
    QString htmlScript;
    Block *m_script;
};

#endif // SCRIPT_H
