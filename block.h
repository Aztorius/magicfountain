#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <QStringList>

enum BlockType { Empty,
                 TitlePage,
                 Action,
                 Scene,
                 Character,
                 Dialogue,
                 DualDialogue,
                 Parentheticals,
                 Transitions,
                 PageBreaks };

class Block
{
public:
    Block(BlockType type, QString data);
    ~Block();

    void addBlock(Block *block);

    BlockType getType();
    QString getData();
    QList<Block *> getBlocks();

    Block& operator=(const Block& block);
private:
    BlockType m_type;
    QString m_data;
    QList<Block *> m_blocks;
};

#endif // BLOC_H
