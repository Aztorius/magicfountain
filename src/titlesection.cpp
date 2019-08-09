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
    return "<h1>" + m_data + "</h1>";
}

QString TitleSection::toRiver()
{
    return "# " + m_data;
}
