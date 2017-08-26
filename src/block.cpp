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
    case BlockType::Action:
        html.append("<p>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Author:
        html.append("<p style=\"text-align: center;\">" + htmlCheckBIU(m_data) + "</p>");
        return html;
    case BlockType::BlankLine:
        html.append("<p style=\"white-space:pre-warp;\"> </p>");
        break;
    case BlockType::CenteredText:
        html.append("<p style=\"text-align:center;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Character:
        html.append("<p style=\"margin-left: 19em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::CharacterLeft:
        html.append("<p style=\"margin-left: 8em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::CharacterRight:
        html.append("<p style=\"margin-left: 28em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Contact:
        html.append("<p style=\"text-align: left;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Credit:
        html.append("<p style=\"text-align: center;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Dialogue:
        html.append("<p style=\"margin-left: 12em; margin-right: 9em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::DraftDate:
        html.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: left;\">" + htmlCheckBIU(m_data).replace("\n", "<br/>") + "</p>");
        break;
    case BlockType::DualDialogueLeft:
        html.append("<p style=\"margin-left: 0em; margin-right: 21em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::DualDialogueRight:
        html.append("<p style=\"margin-left: 23em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Empty:
        break;
    case BlockType::LeftParentheticals:
        html.append("<p style=\"margin-left: 3em; margin-right: 15em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Lyrics:
        html.append("<p>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::PageBreaks:
        html.append("<p style=\"white-space:pre-warp; page-break-after: always;\" > </p>");
        break;
    case BlockType::Parentheticals:
        html.append("<p style=\"margin-left: 15em; margin-right: 6em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::RightParentheticals:
        html.append("<p style=\"margin-left: 15em; margin-right: 27em;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::SceneHeading:
        html.append("<p>" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Source:
        html.append("<p style=\"text-align: center;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    case BlockType::Title:
        html.append("<p style=\"text-align: center;\"><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>" + htmlCheckBIU(m_data.replace("\n", "<br/>")) + "</p>");
        break;
    case BlockType::Transitions:
        html.append("<p style=\"margin-left: 480px;\">" + htmlCheckBIU(m_data) + "</p>");
        break;
    default :
        html.append("<p>" + htmlCheckBIU(m_data) + "</p>");
        break;
    }

    return html;
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
