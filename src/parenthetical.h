#ifndef PARENTHETICAL_H
#define PARENTHETICAL_H

#include "dialogueblock.h"

class Parenthetical : public DialogueBlock
{
public:
    Parenthetical(const QString &m_data);

    virtual QString toHtml();
    virtual QString toFountain();
};

#endif // PARENTHETICAL_H
