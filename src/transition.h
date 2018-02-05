#ifndef TRANSITION_H
#define TRANSITION_H

#include "block.h"

class Transition : public Block
{
public:
    Transition(const QString &m_data);

    virtual QString toHtml();
    virtual QString toFountain();
    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);
};

#endif // TRANSITION_H
