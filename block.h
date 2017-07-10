#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <QStringList>

enum BlockType { Text, Dialogue, Transitions };

class Block
{
public:
    Block(BlockType type, QString data);
    Block(BlockType type, QStringList data);
private:
    BlockType m_type;
    QStringList m_data;
    QList<Block> m_blocks;
};

#endif // BLOC_H
