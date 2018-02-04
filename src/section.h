#ifndef SECTION_H
#define SECTION_H

#include <QSharedPointer>

#include "block.h"
#include "synopsis.h"

class Section : public Block
{
public:
    Section(const QString &m_data);
    void setSynopsis(Synopsis *synopsis);
    void addBlock(Block *block);

    virtual QString toHtml() = 0;
    virtual QString toFountain() = 0;
private:
    Synopsis m_synopsis;
    QList<QSharedPointer<Block>> m_content;
};

#endif // SECTION_H
