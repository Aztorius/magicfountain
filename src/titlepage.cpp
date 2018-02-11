#include "titlepage.h"

TitlePage::TitlePage()
{

}

TitlePage::~TitlePage()
{
    qDeleteAll(m_content);
    m_content.clear();
}

void TitlePage::clear()
{
    qDeleteAll(m_content);
    m_content.clear();
}

void TitlePage::addElement(TitlePageElement *element)
{
    m_content.append(element);
}

QString TitlePage::toFoutain()
{
    QString result;

    foreach (TitlePageElement *element, m_content) {
        result.append(element->toFountain());
    }

    return result;
}

QString TitlePage::toHtml()
{
    QString result = "<p id='script-title'>";

    foreach (TitlePageElement *element, m_content) {
        result.append(element->toHtml());
    }

    result.append("</p>");
    return result;
}
