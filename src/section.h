#ifndef SECTION_H
#define SECTION_H

#include "block.h"
#include "synopsis.h"

class Section : public Block
{
public:
    Section(const QString &data);

    void setSynopsis(Synopsis *synopsis);
    Synopsis *getSynopsis();
    void addBlock(Block *block);
    QList<Block *> *getList();

    QString toHtml();
    QString toFountain() = 0;
    void toTreeWidgetItem(QTreeWidgetItem *parent);
private:
    Synopsis m_synopsis;
    QList<Block *> m_content;
};

#endif // SECTION_H
