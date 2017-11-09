#ifndef BLOC_H
#define BLOC_H

#include <QString>

enum BlockType { Empty,
                 Title,
                 Credit,
                 Author,
                 Source,
                 DraftDate,
                 Contact,
                 Action,
                 CenteredText,
                 SceneHeading,
                 Character,
                 CharacterLeft,
                 CharacterRight,
                 Dialogue,
                 DualDialogueEnd,
                 Parentheticals,
                 Lyrics,
                 Transitions,
                 Note,
                 BoneyardStart,
                 BoneyardStop,
                 Scene,
                 Sequence,
                 Act,
                 Synopses,
                 PageBreaks,
                 BlankLine };

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
    void appendData(QString data);
    QString toHtml();

    Block& operator=(const Block& block);
private:
    BlockType m_type;
    QString m_data;
};

#endif // BLOC_H
