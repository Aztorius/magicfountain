#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "section.h"

class Sequence : public Section
{
public:
    Sequence(const QString &m_data);

    virtual QString toHtml();
    virtual QString toFountain();
    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);
};

#endif // SEQUENCE_H
