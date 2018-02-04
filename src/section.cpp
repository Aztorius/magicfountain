#include "section.h"

Section::Section(const QString &m_data) : Block(m_data)
{

}

void Section::setSynopsis(Synopsis *synopsis)
{
    m_synopsis = synopsis;
}

void Section::addBlock(Block *block)
{
    QSharedPointer<Block> ptr(block);
    m_content.append(ptr);
}
