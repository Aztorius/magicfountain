#include "author.h"

Author::Author(const QString &firstLine) : TitlePageElement(firstLine)
{

}

QString Author::toFountain()
{
    QString result = "Author:";

    foreach (QString line, getData()) {
        result.append(line + "\n");
    }

    return result;
}

QString Author::toHtml()
{
    QString result = "<p class='authors'>";

    foreach (QString line, getData()) {
        result.append(htmlCheckBIU(line) + "<br/>");
    }

    result.append("</p>");
    return result;
}
