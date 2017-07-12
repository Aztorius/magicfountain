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
    QString checkBoldItalicUnderline(QString text);
    QString toHtml();
    QList<Block> getBlocks();

    bool isABlankLine(int i, QStringList lines);

private:
    QString title, credit, author, source, draftDate, contact;
    QString htmlScript;
    QList<Block> m_blocks;
};

#endif // SCRIPT_H
