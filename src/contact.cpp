#include "contact.h"

Contact::Contact(const QString &firstLine) : TitlePageElement(firstLine)
{

}

QString Contact::toFountain()
{
    QString result = "Contact:";

    foreach (QString line, getData()) {
        result.append(line + "\n");
    }

    return result;
}

QString Contact::toHtml()
{
    QString result = "<p class='notes'>";

    foreach (QString line, getData()) {
        result.append(htmlCheckBIU(line) + "<br/>");
    }

    result.append("</p>");
    return result;
}
