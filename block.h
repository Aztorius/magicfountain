#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <QStringList>

enum BlockType { Action,
                 Scene,
                 Character,
                 Dialogue,
                 DualDialogue,
                 Parentheticals,
                 Transitions };

class Block
{
public:
    Block(BlockType type, QString data);
    void addBlock(Block block);
    BlockType getType();
    QString getData();
    QList<Block> getBlocks();
private:
    BlockType m_type;
    QString m_data;
    QList<Block> m_blocks;
};

#endif // BLOC_H
