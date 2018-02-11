#include "draftdate.h"

DraftDate::DraftDate(const QString &firstLine) : TitlePageElement(firstLine)
{

}

QString DraftDate::toFountain()
{
    QString result = "DraftDate:";

    foreach (QString line, getData()) {
        result.append(line + "\n");
    }

    return result;
}

QString DraftDate::toHtml()
{
    QString result = "<p class='notes'>";

    foreach (QString line, getData()) {
        result.append(htmlCheckBIU(line) + "<br/>");
    }

    result.append("</p>");
    return result;
}
