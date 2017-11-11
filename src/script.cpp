#include "script.h"

#include <QFile>
#include <QTextStream>

Script::Script()
{

}

Script::Script(QString script, ScriptType type)
{
    QFile file(":/data/style.css");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    m_cssStyle = in.readAll();

    file.close();

    switch(type) {
    case ScriptType::Fountain:
        this->parseFromFountain(script);
        break;
    default:
        break;
    };
}

bool static isABlankLine(int i, QStringList lines)
{
    return (i >= lines.size() || i < 0 || lines.at(i).isEmpty());
}

void static parseTitlePageData(quint32 *i, QStringList *lines, QList<Block *> *m_blocks, QString *destination)
{
    quint32 blockcount = lines->size();

    if (++(*i) >= blockcount) {
        return;
    }

    QString text = lines->at(*i);

    while ((text.left(1) == "\t" || text.left(3) == "   ") && (*i) < blockcount) {
        m_blocks->last()->appendData("\n" + text.trimmed());
        (*destination).append(text.trimmed());

        if (++(*i) >= blockcount) {
            break;
        }

        text = lines->at(*i);
    }
    --(*i);
}

void Script::parseFromFountain(QString script)
{
    QStringList lines = script.split("\n");
    QString text;
    QRegExp regAlphaNumeric("[A-Z]|[a-z]|[0-9]*");
    QStringList validStartHeaders;
    validStartHeaders << "INT" << "EXT" << "EST" << "INT./EXT" << "INT/EXT" << "I/E";

    quint32 blockcount = lines.size();
    quint32 i = 0;

    while (i < blockcount) {
        text = lines.at(i).trimmed();

        if (text.left(2) == "/*") { //Boneyard Start
            m_blocks.append(new Block(BlockType::BoneyardStart));
        } else if (text.left(2) == "*/") { //Boneyard Stop
            m_blocks.append(new Block(BlockType::BoneyardStop));
        } else if (text.left(1) == "!") { //Forced action
            text = lines.at(i);
            text.remove(text.indexOf("!"), 1);
            text.replace("\t", "    ");

            m_blocks.append(new Block(BlockType::Action, text));
        } else if (text.left(3) == "===") { //Page breaks
            m_blocks.append(new Block(BlockType::PageBreaks));
        } else if (text.left(2) == "= ") { //Synopses
            m_blocks.append(new Block(BlockType::Synopses, text.mid(2)));
        } else if (text.left(1) == "~") { //Lyrics
            m_blocks.append(new Block(BlockType::Lyrics, text.mid(1)));
        } else if (text.left(6) == "Title:") { //Title
            m_blocks.append(new Block(BlockType::Title, text.mid(6)));
            title.append(text.mid(6).trimmed());
            parseTitlePageData(&i, &lines, &m_blocks, &title);
        } else if (text.left(7) == "Credit:") { //Credit
            m_blocks.append(new Block(BlockType::Credit, text.mid(7)));
            credit.append(text.mid(7).trimmed());
            parseTitlePageData(&i, &lines, &m_blocks, &credit);
        } else if (text.left(7) == "Author:") { //Author
            m_blocks.append(new Block(BlockType::Author, text.mid(7)));
            author.append(text.mid(7).trimmed());
            parseTitlePageData(&i, &lines, &m_blocks, &author);
        } else if (text.left(7) == "Source:") { //Source
            m_blocks.append(new Block(BlockType::Source, text.mid(7)));
            source.append(text.mid(7).trimmed());
            parseTitlePageData(&i, &lines, &m_blocks, &source);
        } else if (text.left(11) == "Draft date:") { //Draft date
            m_blocks.append(new Block(BlockType::DraftDate, text.mid(11).trimmed()));
            draftDate.append(text.mid(11).trimmed());
            parseTitlePageData(&i, &lines, &m_blocks, &draftDate);
        } else if (text.left(8) == "Contact:") { //Contact
            m_blocks.append(new Block(BlockType::Contact, text.mid(8)));
            contact.append(text.mid(8).trimmed());
            parseTitlePageData(&i, &lines, &m_blocks, &contact);
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
                text.remove(0, 1);
            }

            BlockType characterType = BlockType::Character;
            qint32 cursor = m_blocks.size() - 1;

            if (text.right(1) == "^") { //Dual dialogue
                text.remove(text.size() - 1, 1);

                Block *block = nullptr;

                while (cursor > 0 && (m_blocks.at(cursor)->getType() & (BlockType::Dialogue | BlockType::Parentheticals | BlockType::BlankLine))) {
                    cursor--;
                }

                block = m_blocks.at(cursor);

                if (block->getType() == BlockType::Character) {
                    block->setType(BlockType::CharacterLeft);
                } else {
                    //ERROR: Previous Block should be a Dialogue Block
                }

                m_blocks.append(new Block(BlockType::CharacterRight, text));
                characterType = BlockType::CharacterRight;
            } else {
                m_blocks.append(new Block(BlockType::Character, text));
            }

            if (++i >= blockcount) {
                break;
            }

            text = lines.at(i).trimmed();

            while ((!text.isEmpty() || lines.at(i) == "  ") && i < blockcount) {

                if (text.left(1) == "(" && text.right(1) == ")") { //Parenthetical
                    m_blocks.append(new Block(BlockType::Parentheticals, text));
                } else if (!text.isEmpty()) { //Dialogue
                    m_blocks.append(new Block(BlockType::Dialogue, text));
                } else {
                    m_blocks.append(new Block(BlockType::BlankLine));
                }

                if (++i >= blockcount) {
                    break;
                }

                text = lines.at(i).trimmed();
            }

            if (characterType == BlockType::CharacterRight) {
                m_blocks.append(new Block(BlockType::DualDialogueEnd));
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
    QString content = "<!DOCTYPE HTML>";
    content.append("<html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" /><style type=\"text/css\">");
    content.append(m_cssStyle);
    content.append("</style></head><body><article><section>");

    Block *block;
    for (qint64 i = 0; i < m_blocks.size(); ++i) {
        block = m_blocks.at(i);

        if (block->getType() == BlockType::BoneyardStart) {
            while(block->getType() != BlockType::BoneyardStop) {
                if (++i == m_blocks.size()) {
                    break;
                }
                block = m_blocks.at(i);
            }
        } else {
            content.append(block->toHtml());
        }
    }

    content.append("</section></article></body></html>");
    return content;
}

QList<Block *> Script::getBlocksOfType(BlockType type)
{
    QList<Block *> list;

    foreach (Block *block, m_blocks) {
        if (block->getType() == type) {
            list.append(block);
        }
    }

    return list;
}

Script& Script::operator=(const Script& other)
{
    title = other.title;
    credit = other.credit;
    author = other.author;
    source = other.source;
    draftDate = other.draftDate;
    contact = other.contact;
    m_cssStyle = other.m_cssStyle;

    qDeleteAll(m_blocks);
    m_blocks = other.m_blocks;

    return *this;
}
