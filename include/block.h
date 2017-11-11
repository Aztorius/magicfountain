#ifndef BLOC_H
#define BLOC_H

#include <QString>

enum BlockType { Empty              = (1u << 0),
                 Title              = (1u << 1),
                 Credit             = (1u << 2),
                 Author             = (1u << 3),
                 Source             = (1u << 4),
                 DraftDate          = (1u << 5),
                 Contact            = (1u << 6),
                 Action             = (1u << 7),
                 CenteredText       = (1u << 8),
                 SceneHeading       = (1u << 9),
                 Character          = (1u << 10),
                 CharacterLeft      = (1u << 11),
                 CharacterRight     = (1u << 12),
                 Dialogue           = (1u << 13),
                 DualDialogueEnd    = (1u << 14),
                 Parentheticals     = (1u << 15),
                 Lyrics             = (1u << 16),
                 Transitions        = (1u << 17),
                 Note               = (1u << 18),
                 BoneyardStart      = (1u << 19),
                 BoneyardStop       = (1u << 20),
                 Scene              = (1u << 21),
                 Sequence           = (1u << 22),
                 Act                = (1u << 23),
                 Synopses           = (1u << 24),
                 PageBreaks         = (1u << 25),
                 BlankLine          = (1u << 26) };

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
