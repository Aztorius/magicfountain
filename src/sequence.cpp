#include "sequence.h"

Sequence::Sequence(const QString &data) : Section(data)
{

}

QString Sequence::toFountain()
{
    QString result = "## " + m_data + "\n";

    if (!getSynopsis()->getData().isEmpty()) {
        result.append(getSynopsis()->toFountain());
    }

    foreach (Block *block, *getList()) {
        result.append(block->toFountain());
    }

    return result;
}
