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
    QList<Block *> getBlocksOfType(BlockType type);

    Script& operator=(const Script& other);
private:
    QString title, credit, author, source, draftDate, contact;
    QList<Block *> m_blocks;

    QString m_cssStyle;

    void parseFromFountain(QString script);
};

#endif // SCRIPT_H
