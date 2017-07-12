#include "script.h"

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
            content.append("<p>" + checkBoldItalicUnderline(text) + "</p>");
        }
        else if (text.left(3) == "===") { //Page breaks
            content.append("<p style=\"white-space:pre-warp; page-break-after: always;\" > </p>");
        }
        else if (text.left(2) == "= ") { //Synopses
            //Not used yet
        }
        else if (text.left(1) == "~") { //Lyrics
            content.append("<p>" + text.mid(1) + "</p>");
        }
        else if (text.left(6) == "Title:") { //Title
            content.append("<p style=\"text-align: center;\"><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>" + checkBoldItalicUnderline(text.mid(6).trimmed()));
            title.append(text.mid(6).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
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
        }
        else if (text.left(7) == "Credit:") { //Credit
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()));
            credit.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
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
        }
        else if (text.left(7) == "Author:") { //Author
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()));
            author.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
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
        }
        else if (text.left(7) == "Source:") { //Source
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()));
            source.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
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
        }
        else if (text.left(11) == "Draft date:") { //Draft date
            content.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: left;\">" + checkBoldItalicUnderline(text.mid(11).trimmed()));
            draftDate.append(text.mid(11).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
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
        }
        else if (text.left(8) == "Contact:") { //Contact
            content.append("<p style=\"text-align: left; page-break-after: always;\">" + checkBoldItalicUnderline(text.mid(8).trimmed()));
            contact.append(text.mid(8).trimmed());

            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
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
        }
        else if (text.left(4) == "### ") { //Scene
            //Not used yet
        }
        else if (text.left(3) == "## ") { //Sequence
            //Not used yet
        }
        else if (text.left(2) == "# ") { //Act
            //Not used yet
        }
        else if ((validStartHeaders.indexOf(text.split(".").first().toUpper()) >= 0 || validStartHeaders.indexOf(text.split(" ").first().toUpper()) >= 0) && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Scene heading
            m_blocks.append(Block(BlockType::Scene, text));
            content.append("<p style=\"margin-left: 5em\">" + checkBoldItalicUnderline(text) + "</p>");
        }
        else if (text.left(1) == ">") {
            if (text.right(1) == "<") { //Centered text
                content.append("<p style=\"text-align:center;\">" + checkBoldItalicUnderline(text.mid(1, text.size()-2).trimmed()) + "</p>");
            }
            else { //Forced transition
                content.append("<p style=\"margin-left: 480px;\">" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
            }
        }
        else if (lines.at(i).right(3) == "TO:" && text.toUpper() == text && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Transition
            content.append("<p style=\"margin-left: 480px;\">" + checkBoldItalicUnderline(text) + "</p>");
        }
        else if (text.left(1) == "." && regAlphaNumeric.exactMatch(text.mid(1, 1)) && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Forced scene heading
            content.append("<p>" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
        }
        else if (((text.split("(").first().toUpper() == text.split("(").first() && !text.isEmpty() && text.split("(").first().toLong() == 0) || text.left(1) == "@") && isABlankLine(i-1, lines) && !isABlankLine(i+1, lines)) { //Dialogue and forced dialogue
            if (text.left(1) == "@") {
                text.remove(0,1);
            }
            if (text.right(1) == "^") { //Dual dialogue
                text.remove(text.size()-1, 1);
            }

            content.append("<p style=\"margin-left: 19em;\">" + checkBoldItalicUnderline(text)); //Character name : 1.9 inches from left side
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i).trimmed();

            while ((!text.isEmpty() || lines.at(i) == "  ") && i < blockcount) {

                if (text.left(1) == "(" && text.right(1) == ")") { //Parenthetical : 2.6 inches from left side
                    content.append("<p style=\"margin-left: 15em; margin-right: 6em;\">" + checkBoldItalicUnderline(text) + "</p>");
                }
                else if (!text.isEmpty()) { //Dialogue : 1 inche from left side
                    content.append("<p style=\"margin-left: 12em; margin-right: 144px;\">" + checkBoldItalicUnderline(text) + "</p>");
                }
                else {
                    content.append("<p style=\"white-space:pre-warp;\"> </p>");
                }

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i).trimmed();
            }

            content.append("</p>");

            i--;
        }
        else if (!lines.at(i).isEmpty()) { //Default action
            text = lines.at(i);
            text.replace("\t", "    ");

            content.append("<p style=\"margin-left: 5em\">" + checkBoldItalicUnderline(text) + "</p>");
        }
        else { //Blank action
            content.append("<p style=\"white-space:pre-warp;\"> </p>"); //Add blank line
        }

        i++;
    }

    content.append("</body></html>");

    htmlScript = content;
}

QString Script::checkBoldItalicUnderline(QString text){
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

QString Script::toHtml(){
    return htmlScript;
}

bool Script::isABlankLine(int i, QStringList lines){
    if (i >= lines.size()) {
        return true;
    } else if (i < 0) {
        return true;
    } else if (i >= 0 && lines.at(i).isEmpty()) {
        return true;
    } else {
        return false;
    }
}

QList<Block> Script::getBlocks() {
    return m_blocks;
}
