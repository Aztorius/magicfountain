#ifndef SCRIPT_H
#define SCRIPT_H

#include <QStringList>
#include <QFile>

#include "block.h"
#include "titlepage.h"

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
    void parseFromFountain(const QString& script);
    void parseFromFinalDraft(const QString& script);
    QString toFountain();

    Script& operator=(const Script& other);

private:
    TitlePage m_titlepage;
    QList<Block *> m_content;
};

#endif // SCRIPT_H
