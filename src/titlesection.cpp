#include "titlesection.h"

TitleSection::TitleSection(const QString &data) : Section(data)
{

}

QString TitleSection::toFountain()
{
    return "# " + m_data;
}

QString TitleSection::toHtml()
{
    QString result = "<h1>" + htmlCheckBIU(m_data) + "</h1>";

    foreach (Block *block, *getList()) {
        result.append(block->toHtml());
    }

    return result;
}

QString TitleSection::toRiver()
{
    return "# " + m_data;
}
