#include "source.h"

Source::Source(const QString &firstLine) : TitlePageElement(firstLine)
{

}

QString Source::toFountain()
{
    QString result = "Source:";

    foreach (QString line, getData()) {
        result.append(line + "\n");
    }

    return result;
}

QString Source::toHtml()
{
    QString result = "<p class='source'>";

    foreach (QString line, getData()) {
        result.append(htmlCheckBIU(line) + "<br/>");
    }

    result.append("</p>");
    return result;
}
