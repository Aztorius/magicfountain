#ifndef ACT_H
#define ACT_H

#include "section.h"

class Act : public Section
{
public:
    Act(const QString &m_data);

    virtual QString toHtml();
    virtual QString toFountain();
};

#endif // ACT_H
