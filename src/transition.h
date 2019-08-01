#ifndef TRANSITION_H
#define TRANSITION_H

#include "block.h"

class Transition : public Block
{
public:
    Transition(const QString &data);

    QString toHtml();
    QString toFountain();
};

#endif // TRANSITION_H
