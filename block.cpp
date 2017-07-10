#include "block.h"

Block::Block(BlockType type, QString data)
{
    m_type = type;
    m_data = QStringList(data);
}

Block::Block(BlockType type, QStringList data)
{
    m_type = type;
    m_data = data;
}
