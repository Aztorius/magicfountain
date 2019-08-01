#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "dialogueblock.h"

class Dialogue : public DialogueBlock
{
public:
    Dialogue(const QString &data);

    QString toHtml();
    QString toFountain();
};

#endif // DIALOGUE_H
