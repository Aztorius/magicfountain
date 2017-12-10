#include "block.h"

#include <QRegularExpression>

QString htmlCheckBIU(QString text);

Block::Block(BlockType type)
{
    m_type = type;
}

Block::Block(BlockType type, QString data)
{
    m_type = type;
    m_data = data;
}

Block::Block(Block &other)
{
    m_type = other.m_type;
    m_data = other.m_data;
}

Block::~Block()
{

}

BlockType Block::getType()
{
    return m_type;
}

void Block::setType(BlockType type)
{
    m_type = type;
}

QString Block::getData()
{
    return m_data;
}

void Block::appendData(QString data)
{
    m_data.append(data);
}

QString Block::toHtml()
{
    QString html;

    switch (m_type) {
    case BlockType::Act:
        break;
    case BlockType::Action:
        html.append("<p>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Author:
        html.append("<p style=\"text-align: center;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::BlankLine:
        break;
    case BlockType::CenteredText:
        html.append("<p style='text-align: center !important; '>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Character:
        html.append("<p class='character'>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::CharacterLeft:
        html.append("<div class='dual-dialogue'><div class='dual-dialogue-left'><p class='character'>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::CharacterRight:
        html.append("</div><div class='dual-dialogue-right'><p class='character'>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Contact:
        html.append("<p style=\"text-align: left;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Credit:
        html.append("<p style=\"text-align: center;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Dialogue:
        html.append("<p class='dialogue'>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::DraftDate:
        html.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: left;\">" + htmlCheckBIU(m_data).replace("\n", "<br/>") + "</p>");
        break;
    case BlockType::DualDialogueEnd:
        html.append("</div></div>");
        break;
    case BlockType::Empty:
        break;
    case BlockType::Lyrics:
        html.append("<p>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Note:
        break;
    case BlockType::PageBreaks:
        html.append("</section><section><p class='page-break'></p>");
        break;
    case BlockType::Parentheticals:
        html.append("<p class='parenthetical'>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Scene:
        break;
    case BlockType::SceneHeading:
        html.append("<p class='scene-heading'>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Sequence:
        break;
    case BlockType::Source:
        html.append("<p style=\"text-align: center;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Synopses:
        break;
    case BlockType::Title:
        html.append("<p style=\"text-align: center;\"><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>" + htmlCheckBIU(m_data.replace("\n", "<br/>")) + "</p>");
        break;
    case BlockType::Transitions:
        html.append("<p class='transition'>" + htmlCheckBIU(m_data) + "</p>");
        break;
    default :
        html.append("<p>" + htmlCheckBIU(m_data) + "</p>");
        break;
    }

    return html;
}

QString Block::toFountain()
{
    switch (m_type) {
    case BlockType::Act:
        return QString("# ") + m_data;
    case BlockType::Action:
        return QString("\n") + m_data;
    case BlockType::Author:
        return QString("Author: ").append(m_data);
    case BlockType::BlankLine:
        return QString();
    case BlockType::CenteredText:
        return QString("\n>") + m_data + QString("<");
    case BlockType::Character:
        return QString("\n@") + m_data;
    case BlockType::CharacterLeft:
        return QString("\n@") + m_data + QString("^");
    case BlockType::CharacterRight:
        return QString("\n@") + m_data;
    case BlockType::Contact:
        return QString("Contact: ") + m_data;
    case BlockType::Credit:
        return QString("Credit: ") + m_data;
    case BlockType::Dialogue:
        return m_data;
    case BlockType::DraftDate:
        return QString("Draft date: ") + m_data;
    case BlockType::DualDialogueEnd:
        return QString();
    case BlockType::Empty:
        return QString();
    case BlockType::Lyrics:
        return QString("~") + m_data;
    case BlockType::Note:
        return QString("[[") + m_data + QString("]]");
    case BlockType::PageBreaks:
        return QString("===");
    case BlockType::Parentheticals:
        return m_data;
    case BlockType::Scene:
        return QString("### ") + m_data;
    case BlockType::SceneHeading:
        return QString(".") + m_data + QString("\n");
    case BlockType::Sequence:
        return QString("## ") + m_data;
    case BlockType::Source:
        return QString("Source: ") + m_data;
    case BlockType::Synopses:
        return QString("= ") + m_data;
    case BlockType::Title:
        return QString("Title: ") + m_data;
    case BlockType::Transitions:
        return QString("> ") + m_data;
    default :
        return m_data;
    }
}

Block& Block::operator=(const Block& other)
{
    m_type = other.m_type;
    m_data = other.m_data;
    return *this;
}

QString htmlCheckBIU(QString text)
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
