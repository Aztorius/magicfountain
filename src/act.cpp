#include "act.h"

Act::Act(const QString &m_data) : Section(m_data)
{

}

QString Act::toFountain()
{
    QString result = "# " + m_data + "\n";

    if (!getSynopsis()->getData().isEmpty()) {
        result.append(getSynopsis()->toFountain());
    }

    foreach (Block *block, *getList()) {
        result.append(block->toFountain());
    }

    return result;
}
