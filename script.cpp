#include "script.h"

#include <QDebug>

Script::Script()
{

}

Script::Script(QString script)
{
    QStringList lines = script.split("\n");
    QString text;
    QRegExp regAlphaNumeric("[A-Z]|[a-z]|[0-9]*");
    QStringList validStartHeaders;
    validStartHeaders << "INT" << "EXT" << "EST" << "INT./EXT" << "INT/EXT" << "I/E";

    QString content = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
    content.append("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">");
    content.append("p, li { white-space: normal; margin: 0px; padding: 0px; } body { width: 624px; letter-spacing: 0px; padding: 0px; }");
    content.append("</style></head><body>");

    int blockcount = lines.size();
    int i = 0;

    while (i < blockcount) {
        text = lines.at(i).trimmed();

        if (text.left(1) == "!") { //Forced action
            text = lines.at(i);
            text.remove(text.indexOf("!"), 1);
            text.replace("\t", "    ");

            m_script.append(new Block(BlockType::Action, text));

            content.append("<p>" + checkBoldItalicUnderline(text) + "</p>");
        } else if (text.left(3) == "===") { //Page breaks
            m_script.append(new Block(BlockType::PageBreaks));

            content.append("<p style=\"white-space:pre-warp; page-break-after: always;\" > </p>");
        } else if (text.left(2) == "= ") { //Synopses
            //Not used yet
        } else if (text.left(1) == "~") { //Lyrics
            m_script.append(new Block(BlockType::Lyrics, text.mid(1)));

            content.append("<p>" + text.mid(1) + "</p>");
        } else if (text.left(6) == "Title:") { //Title
            m_script.append(new Block(BlockType::Title, text.mid(6)));

            content.append("<p style=\"text-align: center;\"><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>" + checkBoldItalicUnderline(text.mid(6).trimmed()));
            title.append(text.mid(6).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_script.last()->appendData("\n" + text.trimmed());

                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));
                title.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
            content.append("<br/></p>");
        } else if (text.left(7) == "Credit:") { //Credit
            m_script.append(new Block(BlockType::Credit, text.mid(7)));

            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()));
            credit.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_script.last()->appendData("\n" + text.trimmed());

                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));
                credit.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
            content.append("<br/></p>");
        } else if (text.left(7) == "Author:") { //Author
            m_script.append(new Block(BlockType::Author, text.mid(7)));

            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()));
            author.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_script.last()->appendData("\n" + text.trimmed());

                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));
                author.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
            content.append("<br/></p>");
        } else if (text.left(7) == "Source:") { //Source
            m_script.append(new Block(BlockType::Source, text.mid(7)));

            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()));
            source.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_script.last()->appendData("\n" + text.trimmed());

                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));
                source.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
            content.append("<br/></p>");
        } else if (text.left(11) == "Draft date:") { //Draft date
            m_script.append(new Block(BlockType::DraftDate, text.mid(11).trimmed()));

            content.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: left;\">" + checkBoldItalicUnderline(text.mid(11).trimmed()));
            draftDate.append(text.mid(11).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_script.last()->appendData("\n" + text.trimmed());

                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));
                draftDate.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
            content.append("</p>");
        } else if (text.left(8) == "Contact:") { //Contact
            m_script.append(new Block(BlockType::Contact, text.mid(8)));

            content.append("<p style=\"text-align: left; page-break-after: always;\">" + checkBoldItalicUnderline(text.mid(8).trimmed()));
            contact.append(text.mid(8).trimmed());

            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_script.last()->appendData("\n" + text.trimmed());

                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));
                contact.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;

            content.append("<br/></p>");
        } else if (text.left(4) == "### ") { //Scene
            //Not used yet
        } else if (text.left(3) == "## ") { //Sequence
            //Not used yet
        } else if (text.left(2) == "# ") { //Act
            //Not used yet
        } else if ((validStartHeaders.indexOf(text.split(".").first().toUpper()) >= 0 || validStartHeaders.indexOf(text.split(" ").first().toUpper()) >= 0) && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Scene heading
            m_script.append(new Block(BlockType::SceneHeading, text));

            content.append("<p style=\"margin-left: 5em\">" + checkBoldItalicUnderline(text) + "</p>");
        } else if (text.left(1) == ">") {
            if (text.right(1) == "<") { //Centered text
                m_script.append(new Block(BlockType::CenteredText, text.mid(1, text.size()-2).trimmed()));

                content.append("<p style=\"text-align:center;\">" + checkBoldItalicUnderline(text.mid(1, text.size()-2).trimmed()) + "</p>");
            } else { //Forced transition
                m_script.append(new Block(BlockType::Transitions, text.mid(1)));

                content.append("<p style=\"margin-left: 480px;\">" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
            }
        } else if (lines.at(i).right(3) == "TO:" && text.toUpper() == text && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Transition
            m_script.append(new Block(BlockType::Transitions, text));

            content.append("<p style=\"margin-left: 480px;\">" + checkBoldItalicUnderline(text) + "</p>");
        } else if (text.left(1) == "." && regAlphaNumeric.exactMatch(text.mid(1, 1)) && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Forced scene heading
            m_script.append(new Block(BlockType::SceneHeading, text.mid(1)));

            content.append("<p>" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
        } else if (((text.split("(").first().toUpper() == text.split("(").first() && !text.isEmpty() && text.split("(").first().toLong() == 0) || text.left(1) == "@") && isABlankLine(i-1, lines) && !isABlankLine(i+1, lines)) { //Dialogue and forced dialogue
            if (text.left(1) == "@") {
                text.remove(0,1);
            }

            BlockType characterType = BlockType::Character;
            qint32 cursor = m_script.size() - 1;

            if (text.right(1) == "^") { //Dual dialogue
                text.remove(text.size()-1, 1);

                Block *block = nullptr;

                while (m_script.at(cursor)->getType() == BlockType::Dialogue || m_script.at(cursor)->getType() == BlockType::Parentheticals) {
                    if (cursor > 0) {
                        cursor--;
                    } else {
                        break;
                    }
                }

                block = m_script.at(cursor);

                if (block->getType() == BlockType::Character) {
                    block->setType(BlockType::CharacterLeft);

                    for (qint32 i = cursor + 1; i < m_script.size(); i++) {
                        switch(m_script.at(i)->getType()) {
                        case BlockType::Dialogue:
                            m_script.at(i)->setType(BlockType::DualDialogueLeft);
                            break;
                        case BlockType::Parentheticals:
                            m_script.at(i)->setType(BlockType::LeftParentheticals);
                            break;
                        default:
                            break;
                        }
                    }
                } else {
                    //ERROR: Previous Block should be a Dialogue Block
                }

                m_script.append(new Block(BlockType::CharacterRight, text));
                characterType = BlockType::CharacterRight;
            } else {
                m_script.append(new Block(BlockType::Character, text));
            }

            content.append("<p style=\"margin-left: 19em;\">" + checkBoldItalicUnderline(text)); //Character name : 1.9 inches from left side
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i).trimmed();

            while ((!text.isEmpty() || lines.at(i) == "  ") && i < blockcount) {

                if (text.left(1) == "(" && text.right(1) == ")") { //Parenthetical : 2.6 inches from left side
                    m_script.append(new Block(BlockType::Parentheticals, text));

                    content.append("<p style=\"margin-left: 15em; margin-right: 6em;\">" + checkBoldItalicUnderline(text) + "</p>");
                } else if (!text.isEmpty()) { //Dialogue : 1 inche from left side
                    m_script.append(new Block(BlockType::Dialogue, text));

                    content.append("<p style=\"margin-left: 12em; margin-right: 144px;\">" + checkBoldItalicUnderline(text) + "</p>");
                } else {
                    m_script.append(new Block(BlockType::BlankLine));

                    content.append("<p style=\"white-space:pre-warp;\"> </p>");
                }

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i).trimmed();
            }

            content.append("</p>");

            if (characterType == BlockType::CharacterRight) {
                for (qint32 i = cursor; i < m_script.size(); i++) {
                    switch(m_script.at(i)->getType()){
                    case BlockType::Dialogue:
                        m_script.at(i)->setType(BlockType::DualDialogueRight);
                        break;
                    case BlockType::Parentheticals:
                        m_script.at(i)->setType(BlockType::RightParentheticals);
                        break;
                    default:
                        break;
                    }
                }
            }

            i--;
        } else if (!lines.at(i).isEmpty()) { //Default action
            text = lines.at(i);
            text.replace("\t", "    ");

            m_script.append(new Block(BlockType::Action, text));

            content.append("<p style=\"margin-left: 5em\">" + checkBoldItalicUnderline(text) + "</p>");
        } else { //Blank action
            m_script.append(new Block(BlockType::BlankLine));

            content.append("<p style=\"white-space:pre-warp;\"> </p>"); //Add blank line
        }

        i++;
    }

    content.append("</body></html>");

    htmlScript = content;
}

Script::~Script()
{
    qDeleteAll(m_script);
}

QString Script::checkBoldItalicUnderline(QString text)
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

QString Script::toHtml()
{
    //return htmlScript;

    QString content = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
    content.append("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">");
    content.append("p, li { white-space: normal; margin: 0px; padding: 0px; } body { width: 624px; letter-spacing: 0px; padding: 0px; }");
    content.append("</style></head><body>");

    foreach (Block *block, m_script) {
        content.append(block->toHtml());
    }

    return content;
}

bool Script::isABlankLine(int i, QStringList lines)
{
    if (i >= lines.size()) {
        return true;
    } else if (i < 0) {
        return true;
    } else if (lines.at(i).isEmpty()) {
        return true;
    } else {
        return false;
    }
}

QList<Block *> Script::getBlocks()
{
    return m_script;
}

Script& Script::operator=(const Script& other)
{
    title = other.title;
    credit = other.credit;
    author = other.author;
    source = other.source;
    draftDate = other.draftDate;
    contact = other.contact;

    htmlScript = other.htmlScript;

    m_script = other.m_script;

    return *this;
}
