#include "section.h"

Section::Section(const QString &data) : Block(data)
{

}

void Section::setSynopsis(Synopsis *synopsis)
{
    m_synopsis = synopsis;
}

Synopsis *Section::getSynopsis()
{
    return &m_synopsis;
}

void Section::addBlock(Block *block)
{
    m_content.append(block);
}

QList<Block *> *Section::getList()
{
    return &m_content;
}

QString Section::toHtml()
{
    QString result;

    foreach (Block *block, m_content) {
        result.append(block->toHtml());
    }

    return result;
}

void Section::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << m_data);

    foreach (Block *block, m_content) {
        block->toTreeWidgetItem(item);
    }

    parent->addChild(item);
}
