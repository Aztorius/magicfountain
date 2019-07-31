#ifndef SCRIPT_H
#define SCRIPT_H

#include <QStringList>
#include <QFile>

#include "block.h"
#include "titlepage.h"

enum SourceFormat {
    Unknown = 0x1,
    Fountain = 0x2,
    FinalDraft = 0x4,
    River = 0x8
};

class Script
{
public:
    Script();
    Script(QString& script, SourceFormat format);
    Script(QFile& file, SourceFormat format);
    ~Script();

    void parse(QString& script, SourceFormat format);
    void parse(QFile& file, SourceFormat format);
    void parseFromFountain(QTextStream& stream);
    void parseFromRiver(QTextStream& stream);
    void parseFromFinalDraft(QIODevice &script);
    QString toFountain();
    QString toHtml();
    QList<Block *> getBlocks();

    Script& operator=(const Script& other);

private:
    SourceFormat m_sourceFormat;
    TitlePage m_titlepage;
    QList<Block *> m_content;
};

#endif // SCRIPT_H
