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
    return "<h2>" + htmlCheckBIU(m_data) + "</h2>";
}
