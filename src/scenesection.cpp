#include "scenesection.h"

SceneSection::SceneSection(const QString &data) : Section(data)
{

}

QString SceneSection::toFountain()
{
    QString result = "### " + m_data + "\n";

    if (!getSynopsis()->getData().isEmpty()) {
        result.append(getSynopsis()->toFountain());
    }

    foreach (Block *block, *getList()) {
        result.append(block->toFountain());
    }

    return result;
}
