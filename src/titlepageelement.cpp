#include "titlepageelement.h"

TitlePageElement::TitlePageElement(const QString &firstLine)
{
    m_data.append(firstLine);
}

void TitlePageElement::addLine(const QString &line)
{
    m_data.append(line);
}
