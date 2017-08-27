#include "script.h"

#include <QDebug>

Script::Script()
{

}

Script::Script(QString script, ScriptType type)
{
    switch(type) {
    case ScriptType::Fountain:
        this->parseFromFountain(script);
        break;
    default:
        break;
    };
}

void Script::parseFromFountain(QString script)
{
    QStringList lines = script.split("\n");
    QString text;
    QRegExp regAlphaNumeric("[A-Z]|[a-z]|[0-9]*");
    QStringList validStartHeaders;
    validStartHeaders << "INT" << "EXT" << "EST" << "INT./EXT" << "INT/EXT" << "I/E";

    int blockcount = lines.size();
    int i = 0;

    while (i < blockcount) {
        text = lines.at(i).trimmed();

        if (text.left(1) == "!") { //Forced action
            text = lines.at(i);
            text.remove(text.indexOf("!"), 1);
            text.replace("\t", "    ");

            m_blocks.append(new Block(BlockType::Action, text));
        } else if (text.left(3) == "===") { //Page breaks
            m_blocks.append(new Block(BlockType::PageBreaks));
        } else if (text.left(2) == "= ") { //Synopses
            //Not used yet
        } else if (text.left(1) == "~") { //Lyrics
            m_blocks.append(new Block(BlockType::Lyrics, text.mid(1)));
        } else if (text.left(6) == "Title:") { //Title
            m_blocks.append(new Block(BlockType::Title, text.mid(6)));
            title.append(text.mid(6).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_blocks.last()->appendData("\n" + text.trimmed());
                title.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
        } else if (text.left(7) == "Credit:") { //Credit
            m_blocks.append(new Block(BlockType::Credit, text.mid(7)));
            credit.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_blocks.last()->appendData("\n" + text.trimmed());
                credit.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
        } else if (text.left(7) == "Author:") { //Author
            m_blocks.append(new Block(BlockType::Author, text.mid(7)));
            author.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_blocks.last()->appendData("\n" + text.trimmed());
                author.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
        } else if (text.left(7) == "Source:") { //Source
            m_blocks.append(new Block(BlockType::Source, text.mid(7)));
            source.append(text.mid(7).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_blocks.last()->appendData("\n" + text.trimmed());
                source.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
        } else if (text.left(11) == "Draft date:") { //Draft date
            m_blocks.append(new Block(BlockType::DraftDate, text.mid(11).trimmed()));
            draftDate.append(text.mid(11).trimmed());
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_blocks.last()->appendData("\n" + text.trimmed());
                draftDate.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
        } else if (text.left(8) == "Contact:") { //Contact
            m_blocks.append(new Block(BlockType::Contact, text.mid(8)));
            contact.append(text.mid(8).trimmed());

            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i);

            while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
                m_blocks.last()->appendData("\n" + text.trimmed());
                contact.append(text.trimmed());

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i);
            }
            i--;
        } else if (text.left(4) == "### ") { //Scene
            m_blocks.append(new Block(BlockType::Scene, text.mid(4)));
        } else if (text.left(3) == "## ") { //Sequence
            m_blocks.append(new Block(BlockType::Sequence, text.mid(3)));
        } else if (text.left(2) == "# ") { //Act
            m_blocks.append(new Block(BlockType::Act, text.mid(2)));
        } else if ((validStartHeaders.indexOf(text.split(".").first().toUpper()) >= 0 || validStartHeaders.indexOf(text.split(" ").first().toUpper()) >= 0) && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Scene heading
            m_blocks.append(new Block(BlockType::SceneHeading, text));
        } else if (text.left(1) == ">") {
            if (text.right(1) == "<") { //Centered text
                m_blocks.append(new Block(BlockType::CenteredText, text.mid(1, text.size()-2).trimmed()));
            } else { //Forced transition
                m_blocks.append(new Block(BlockType::Transitions, text.mid(1)));
            }
        } else if (lines.at(i).right(3) == "TO:" && text.toUpper() == text && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Transition
            m_blocks.append(new Block(BlockType::Transitions, text));
        } else if (text.left(1) == "." && regAlphaNumeric.exactMatch(text.mid(1, 1)) && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Forced scene heading
            m_blocks.append(new Block(BlockType::SceneHeading, text.mid(1)));
        } else if (((text.split("(").first().toUpper() == text.split("(").first() && !text.isEmpty() && text.split("(").first().toLong() == 0) || text.left(1) == "@") && isABlankLine(i-1, lines) && !isABlankLine(i+1, lines)) { //Dialogue and forced dialogue
            if (text.left(1) == "@") {
                text.remove(0,1);
            }

            BlockType characterType = BlockType::Character;
            qint32 cursor = m_blocks.size() - 1;

            if (text.right(1) == "^") { //Dual dialogue
                text.remove(text.size()-1, 1);

                Block *block = nullptr;

                while (cursor > 0 && (m_blocks.at(cursor)->getType() == BlockType::Dialogue || m_blocks.at(cursor)->getType() == BlockType::Parentheticals || m_blocks.at(cursor)->getType() == BlockType::BlankLine)) {
                    cursor--;
                }

                block = m_blocks.at(cursor);

                if (block->getType() == BlockType::Character) {
                    block->setType(BlockType::CharacterLeft);

                    for (qint32 i = cursor + 1; i < m_blocks.size(); i++) {
                        switch(m_blocks.at(i)->getType()) {
                        case BlockType::Dialogue:
                            m_blocks.at(i)->setType(BlockType::DualDialogueLeft);
                            break;
                        case BlockType::Parentheticals:
                            m_blocks.at(i)->setType(BlockType::LeftParentheticals);
                            break;
                        default:
                            break;
                        }
                    }
                } else {
                    //ERROR: Previous Block should be a Dialogue Block
                }

                m_blocks.append(new Block(BlockType::CharacterRight, text));
                characterType = BlockType::CharacterRight;
            } else {
                m_blocks.append(new Block(BlockType::Character, text));
            }
            i++;

            if (i >= blockcount) {
                break;
            }

            text = lines.at(i).trimmed();

            while ((!text.isEmpty() || lines.at(i) == "  ") && i < blockcount) {

                if (text.left(1) == "(" && text.right(1) == ")") { //Parenthetical : 2.6 inches from left side
                    m_blocks.append(new Block(BlockType::Parentheticals, text));
                } else if (!text.isEmpty()) { //Dialogue : 1 inche from left side
                    m_blocks.append(new Block(BlockType::Dialogue, text));
                } else {
                    m_blocks.append(new Block(BlockType::BlankLine));
                }

                i++;

                if (i >= blockcount) {
                    break;
                }

                text = lines.at(i).trimmed();
            }

            if (characterType == BlockType::CharacterRight) {
                for (qint32 i = cursor; i < m_blocks.size(); i++) {
                    switch(m_blocks.at(i)->getType()){
                    case BlockType::Character:
                        m_blocks.at(i)->setType(BlockType::CharacterRight);
                        break;
                    case BlockType::Dialogue:
                        m_blocks.at(i)->setType(BlockType::DualDialogueRight);
                        break;
                    case BlockType::Parentheticals:
                        m_blocks.at(i)->setType(BlockType::RightParentheticals);
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

            m_blocks.append(new Block(BlockType::Action, text));
        } else { //Blank action
            m_blocks.append(new Block(BlockType::BlankLine));
        }

        i++;
    }
}

Script::~Script()
{
    qDeleteAll(m_blocks);
}

QString Script::toHtml()
{
    QString content = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
    content.append("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">");
    content.append("p, li { white-space: normal; margin: 0px; padding: 0px; } body { width: 624px; letter-spacing: 0px; padding: 0px; }");
    content.append("</style></head><body>");

    foreach (Block *block, m_blocks) {
        content.append(block->toHtml());
    }

    return content;
}

bool Script::isABlankLine(int i, QStringList lines)
{
    return (i >= lines.size() || i < 0 || lines.at(i).isEmpty());
}

QList<Block *> Script::getBlocks()
{
    return m_blocks;
}

Script& Script::operator=(const Script& other)
{
    title = other.title;
    credit = other.credit;
    author = other.author;
    source = other.source;
    draftDate = other.draftDate;
    contact = other.contact;
    m_blocks = other.m_blocks;

    return *this;
}
