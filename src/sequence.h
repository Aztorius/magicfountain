#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "section.h"

class Sequence : public Section
{
public:
    Sequence(const QString &m_data);

    virtual QString toFountain();
};

#endif // SEQUENCE_H
