#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "dialogueblock.h"

class Dialogue : public DialogueBlock
{
public:
    Dialogue(const QString &m_data);

    virtual QString toHtml();
    virtual QString toFountain();
    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);
};

#endif // DIALOGUE_H
