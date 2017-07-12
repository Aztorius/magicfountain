#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <QStringList>

enum BlockType { Scene, Text, Dialogue, Transitions };

class Block
{
public:
    Block(BlockType type, QString data);
    void addBlock(Block block);
    BlockType getType();
    QString getData();
private:
    BlockType m_type;
    QString m_data;
    QList<Block> m_blocks;
};

#endif // BLOC_H
