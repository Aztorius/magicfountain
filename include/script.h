#ifndef SCRIPT_H
#define SCRIPT_H

#include <QStringList>
#include <QFile>

#include "block.h"

enum ScriptType {
    Unknown,
    Fountain,
    FinalDraft
};

class Script
{
public:
    Script();
    Script(const QString& script, ScriptType type);
    Script(QFile file, ScriptType type);
    ~Script();

    QString toHtml();
    QList<Block *> getBlocksOfType(BlockType type);
    void parseFromFountain(const QString& script);
    void parseFromFinalDraft(const QString& script);
    QString toFountain();

    Script& operator=(const Script& other);
private:
    QString title, credit, author, source, draftDate, contact;
    QList<Block *> m_blocks;
};

#endif // SCRIPT_H
