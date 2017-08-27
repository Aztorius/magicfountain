#ifndef SCRIPT_H
#define SCRIPT_H

#include <QString>
#include <QStringList>

#include "block.h"

enum ScriptType {
    Unknown,
    Fountain
};

class Script
{
public:
    Script();
    Script(QString script, ScriptType type);
    ~Script();

    QString toHtml();
    QList<Block *> getBlocks();

    bool isABlankLine(int i, QStringList lines);

    Script& operator=(const Script& other);
private:
    QString title, credit, author, source, draftDate, contact;
    QList<Block *> m_blocks;

    void parseFromFountain(QString script);
};

#endif // SCRIPT_H
