#include "chapter.h"

Chapter::Chapter(const QString &data) : Section(data)
{

}

QString Chapter::toFountain()
{
    return "## " + m_data;
}

QString Chapter::toHtml()
{
    QString result = "<h2>" + htmlCheckBIU(m_data) + "</h2>";

    foreach (Block *block, *getList()) {
        result.append(block->toHtml());
    }

    return result;
}
