#include "block.h"

Block::Block(BlockType type, QString data)
{
    m_type = type;
    m_data = data;
}

void Block::addBlock(Block block)
{
    m_blocks.append(block);
}

BlockType Block::getType()
{
    return m_type;
}

QString Block::getData()
{
    return m_data;
}
