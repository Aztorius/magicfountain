#include "titlepage.h"

TitlePage::TitlePage()
{

}

void TitlePage::addElement(TitlePageElement *element)
{
    m_content.append(element);
}
