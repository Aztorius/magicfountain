#ifndef PARENTHETICAL_H
#define PARENTHETICAL_H

#include "dialogueblock.h"

class Parenthetical : public DialogueBlock
{
public:
    Parenthetical(const QString &data);

    QString toHtml();
    QString toFountain();
};

#endif // PARENTHETICAL_H
