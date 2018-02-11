#include "title.h"

Title::Title(const QString &firstLine) : TitlePageElement(firstLine)
{

}

QString Title::toFountain()
{
    QString result = "Title:";

    foreach (QString line, getData()) {
        result.append(line + "\n");
    }

    return result;
}

QString Title::toHtml()
{
    QString result = "<p id='script-title' class='title'>";

    foreach (QString line, getData()) {
        result.append(htmlCheckBIU(line) + "<br/>");
    }

    result.append("</p>");
    return result;
}
