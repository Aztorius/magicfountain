#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <QStringList>

enum BlockType { Empty,
                 Global,
                 TitlePage,
                 Title,
                 Credit,
                 Author,
                 Source,
                 DraftDate,
                 Contact,
                 Action,
                 CenteredText,
                 Scene,
                 Character,
                 CharacterLeft,
                 CharacterRight,
                 Dialogue,
                 DualDialogueLeft,
                 DualDialogueRight,
                 Parentheticals,
                 LeftParentheticals,
                 RightParentheticals,
                 Lyrics,
                 Transitions,
                 PageBreaks,
                 BlankLine,
                 RawText };

class Block
{
public:
    Block(BlockType type);
    Block(BlockType type, QString data);
    ~Block();

    void addBlock(Block *block);

    BlockType getType();
    void setType(BlockType type);
    QString getData();
    QList<Block *> getBlocks();
    QString toHtml();

    Block& operator=(const Block& block);
private:
    BlockType m_type;
    QString m_data;
    QList<Block *> m_blocks;
};

#endif // BLOC_H
