#ifndef SCRIPT_H
#define SCRIPT_H

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
    QList<Block *> getBlocksOfType(BlockType type);
    void parseFromFountain(QString script);

    Script& operator=(const Script& other);
private:
    QString title, credit, author, source, draftDate, contact;
    QList<Block *> m_blocks;
};

#endif // SCRIPT_H
