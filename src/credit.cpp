#include "credit.h"

Credit::Credit(const QString &firstLine) : TitlePageElement(firstLine)
{

}

QString Credit::toFountain()
{
    QString result = "Credit:";

    foreach (QString line, getData()) {
        result.append(line + "\n");
    }

    return result;
}

QString Credit::toHtml()
{
    QString result = "<p class='credit'>";

    foreach (QString line, getData()) {
        result.append(htmlCheckBIU(line) + "<br/>");
    }

    result.append("</p>");
    return result;
}
