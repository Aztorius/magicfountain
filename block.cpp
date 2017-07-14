#include "block.h"

Block::Block(BlockType type, QString data)
{
    m_type = type;
    m_data = data;
}

Block::~Block()
{
    qDeleteAll(m_blocks.begin(), m_blocks.end());
}

void Block::addBlock(Block *block)
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

QList<Block *> Block::getBlocks()
{
    return m_blocks;
}

Block& Block::operator=(const Block& other)
{
    m_type = other.m_type;
    m_data = other.m_data;
    m_blocks = other.m_blocks;
    return *this;
}
