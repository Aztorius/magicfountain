#ifndef ACTION_H
#define ACTION_H

#include "block.h"

class Action : public Block
{
public:
    Action(const QString &data);
    void setCentered(bool isCentered);

    virtual QString toHtml();
    virtual QString toFountain();
    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);
private:
    bool m_isCentered;
};

#endif // ACTION_H
