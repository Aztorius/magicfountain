#include "titlepageelement.h"

#include <QRegularExpression>

TitlePageElement::TitlePageElement(const QString &firstLine)
{
    m_data.append(firstLine);
}

void TitlePageElement::addLine(const QString &line)
{
    m_data.append(line);
}

QStringList TitlePageElement::getData()
{
    return m_data;
}

QString TitlePageElement::htmlCheckBIU(const QString &text)
{
    QStringList result = text.split("\\*");
    int firstindex = -1, secondindex = -1;

    //Check Bold with Italic, ex: ***something***
    firstindex = result.indexOf(QRegularExpression(".*\\*\\*\\*\\S.*"));
    secondindex = result.indexOf(QRegularExpression(".*\\S\\*\\*\\*.*"));

    while(firstindex >= 0 && secondindex >=0 && (secondindex > firstindex || (firstindex == secondindex && result.at(firstindex).indexOf(QRegularExpression("\\*\\*\\*\\S.*")) != result.at(secondindex).indexOf(QRegularExpression("\\S\\*\\*\\*.*"))))){
        result[firstindex].replace(result.at(firstindex).indexOf("***"), 3, "<b><i>");
        result[secondindex].replace(result.at(secondindex).indexOf("***"), 3, "</i></b>");

        firstindex = result.indexOf(QRegularExpression(".*\\*\\*\\*\\S.*"));
        secondindex = result.indexOf(QRegularExpression(".*\\S\\*\\*\\*.*"));
    }

    //Check Bold, ex: **something**
    firstindex = result.indexOf(QRegularExpression(".*\\*\\*\\S.*"));
    secondindex = result.indexOf(QRegularExpression(".*\\S\\*\\*.*"));

    while(firstindex >= 0 && secondindex >=0 && (secondindex > firstindex || (firstindex == secondindex && result.at(firstindex).indexOf(QRegularExpression("\\*\\*\\S.*")) != result.at(secondindex).indexOf(QRegularExpression("\\S\\*\\*.*"))))){
        result[firstindex].replace(result.at(firstindex).indexOf("**"), 2, "<b>");
        result[secondindex].replace(result.at(secondindex).indexOf("**"), 2, "</b>");

        firstindex = result.indexOf(QRegularExpression(".*\\*\\*\\S.*"));
        secondindex = result.indexOf(QRegularExpression(".*\\S\\*\\*.*"));
    }

    //Check Italic, ex: *something*
    firstindex = result.indexOf(QRegularExpression(".*\\*\\S.*"));
    secondindex = result.indexOf(QRegularExpression(".*\\S\\*.*"));

    while(firstindex >= 0 && secondindex >=0 && (secondindex > firstindex || (firstindex == secondindex && result.at(firstindex).indexOf(QRegularExpression("\\*\\S.*")) != result.at(secondindex).indexOf(QRegularExpression("\\S\\*.*"))))){
        result[firstindex].replace(result.at(firstindex).indexOf("*"), 1, "<i>");
        result[secondindex].replace(result.at(secondindex).indexOf("*"), 1, "</i>");

        firstindex = result.indexOf(QRegularExpression(".*\\*\\S.*"));
        secondindex = result.indexOf(QRegularExpression(".*\\S\\*.*"));
    }

    result = result.join("*").split("\\_");

    //Check Underline, ex: _something_
    firstindex = result.indexOf(QRegularExpression(".*_\\S.*"));
    secondindex = result.indexOf(QRegularExpression(".*\\S_.*"));

    while(firstindex >= 0 && secondindex >=0 && (secondindex > firstindex || (firstindex == secondindex && result.at(firstindex).indexOf(QRegularExpression("_\\S.*")) != result.at(secondindex).indexOf(QRegularExpression("\\S_.*"))))){
        result[firstindex].replace(result.at(firstindex).indexOf("_"), 1, "<u>");
        result[secondindex].replace(result.at(secondindex).indexOf("_"), 1, "</u>");

        firstindex = result.indexOf(QRegularExpression(".*_\\S.*"));
        secondindex = result.indexOf(QRegularExpression(".*\\S_.*"));
    }

    return result.join("_");
}
