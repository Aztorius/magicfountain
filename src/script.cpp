#include "script.h"

#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>

#include "act.h"
#include "action.h"
#include "author.h"
#include "blankline.h"
#include "boneyard.h"
#include "character.h"
#include "contact.h"
#include "credit.h"
#include "dialogue.h"
#include "draftdate.h"
#include "lyrics.h"
#include "pagebreak.h"
#include "parenthetical.h"
#include "scene.h"
#include "scenesection.h"
#include "sequence.h"
#include "source.h"
#include "synopsis.h"
#include "title.h"
#include "transition.h"

#define BLOCK_MAIN 0
#define BLOCK_ACT 1
#define BLOCK_SEQUENCE 2
#define BLOCK_SCENE 3
#define BLOCK_SCENEHEADER 4

Script::Script()
{

}

Script::Script(const QString &script, ScriptType type)
{
    switch(type) {
    case ScriptType::Fountain:
        this->parseFromFountain(script);
        break;
    case ScriptType::FinalDraft:
        this->parseFromFinalDraft(script);
        break;
    default:
        break;
    };
}

Script::Script(QFile file, ScriptType type)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);

    switch(type) {
    case ScriptType::Fountain:
        this->parseFromFountain(in.readAll());
        break;
    case ScriptType::FinalDraft:
        this->parseFromFinalDraft(in.readAll());
        break;
    default:
        break;
    }

    file.close();
}

bool static isABlankLine(int i, QStringList lines)
{
    return (i >= lines.size() || i < 0 || lines.at(i).isEmpty());
}

void static parseTitlePageData(quint32 &i, QStringList &lines, TitlePageElement *element)
{
    quint32 blockcount = lines.size();

    if (++i >= blockcount) {
        return;
    }

    QString text = lines.at(i);

    while ((text.left(1) == "\t" || text.left(3) == "   ") && i < blockcount) {
        element->addLine(text.trimmed());

        if (++i >= blockcount) {
            break;
        }

        text = lines.at(i);
    }
    --i;
}

void Script::parseFromFountain(const QString& script)
{
    QStringList lines = script.split("\n");
    QString text;
    QRegExp regAlphaNumeric("[A-Z]|[a-z]|[0-9]*");
    QStringList validStartHeaders;
    validStartHeaders << "INT" << "EXT" << "EST" << "INT./EXT" << "INT/EXT" << "I/E";

    quint32 blockcount = lines.size();
    quint32 i = 0;

    qDeleteAll(m_content);
    m_content.clear();

    quint8 currentBlock = BLOCK_MAIN;
    QList<Block *> *blocklist = &m_content;

    while (i < blockcount) {
        text = lines.at(i).trimmed();

        if (text.left(2) == "/*") { //Boneyard
            Boneyard *block = new Boneyard();

            while (++i < blockcount && lines.at(i).trimmed() != "*/") {
                block->addLine(lines.at(i));
            }

            blocklist->append(block);
        } else if (text.left(1) == "!") { //Forced action
            text = lines.at(i);
            text.remove(text.indexOf("!"), 1);
            text.replace("\t", "    ");

            blocklist->append(new Action(text));
        } else if (text.left(3) == "===") { //Page breaks
            blocklist->append(new PageBreak());
        } else if (text.left(2) == "= ") { //Synopses
            blocklist->append(new Synopsis(text.mid(2)));
        } else if (text.left(1) == "~") { //Lyrics
            blocklist->append(new Lyrics(text.mid(1)));
        } else if (text.left(6) == "Title:") { //Title
            TitlePageElement *title = new Title(text.mid(6).trimmed());
            parseTitlePageData(i, lines, title);
            m_titlepage.addElement(title);
        } else if (text.left(7) == "Credit:") { //Credit
            TitlePageElement *credit = new Credit(text.mid(7).trimmed());
            parseTitlePageData(i, lines, credit);
        } else if (text.left(7) == "Author:") { //Author
            TitlePageElement *author = new Author(text.mid(7).trimmed());
            parseTitlePageData(i, lines, author);
        } else if (text.left(7) == "Source:") { //Source
            TitlePageElement *source = new Source(text.mid(7).trimmed());
            parseTitlePageData(i, lines, source);
        } else if (text.left(11) == "Draft date:") { //Draft date
            TitlePageElement *draftDate = new DraftDate(text.mid(11).trimmed());
            parseTitlePageData(i, lines, draftDate);
        } else if (text.left(8) == "Contact:") { //Contact
            TitlePageElement *contact = new Contact(text.mid(8).trimmed());
            parseTitlePageData(i, lines, contact);
        } else if (text.left(4) == "### ") { //Scene
            blocklist->append(new SceneSection(text.mid(4)));
        } else if (text.left(3) == "## ") { //Sequence
            blocklist->append(new Sequence(text.mid(3)));
        } else if (text.left(2) == "# ") { //Act
            blocklist->append(new Act(text.mid(2)));
        } else if ((validStartHeaders.indexOf(text.split(".").first().toUpper()) >= 0 || validStartHeaders.indexOf(text.split(" ").first().toUpper()) >= 0) && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Scene heading
            Scene *scene = new Scene(text);
            m_content.append(scene);
            blocklist = scene->getList();
        } else if (text.left(1) == ">") {
            if (text.right(1) == "<") { //Centered text
                Action *action = new Action(text.mid(1, text.size()-2).trimmed());
                action->setCentered(true);
                blocklist->append(action);
            } else { //Forced transition
                blocklist->append(new Transition(text.mid(1)));
            }
        } else if (lines.at(i).right(3) == "TO:" && text.toUpper() == text && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Transition
            blocklist->append(new Transition(text));
        } else if (text.left(1) == "." && regAlphaNumeric.exactMatch(text.mid(1, 1)) && isABlankLine(i-1, lines) && isABlankLine(i+1, lines)) { //Forced scene heading
            blocklist->append(new Scene(text.mid(1)));
        } else if (((text.split("(").first().toUpper() == text.split("(").first() && !text.isEmpty() && text.split("(").first().toLong() == 0) || text.left(1) == "@") && isABlankLine(i-1, lines) && !isABlankLine(i+1, lines)) { //Dialogue and forced dialogue
            if (text.left(1) == "@") {
                text.remove(0, 1);
            }

            Character *character = nullptr;

            if (text.right(1) == "^") { //Dual dialogue
                text.remove(text.size() - 1, 1);

                if (m_content.size() < 2) {
                    // Treat that as a classic Dialogue
                    character = new Character(text);
                    blocklist->append(character);
                } else {
                    Block *block = m_content.at(m_content.size() - 2);

                    character = dynamic_cast<Character *>(block);

                    if (character == nullptr) {
                        // Treat that as a classic Dialogue
                        character = new Character(text);
                        blocklist->append(character);
                    } else {
                        character->setDual(true);
                        character->setRightCharacter(text);
                    }
                }
            } else {
                character = new Character(text);
                blocklist->append(character);
            }

            if (++i >= blockcount) {
                break;
            }

            text = lines.at(i).trimmed();

            while ((!text.isEmpty() || lines.at(i) == "  ") && i < blockcount) {

                if (text.left(1) == "(" && text.right(1) == ")") { //Parenthetical
                    if (character->isDual()) {
                        character->addRightDialogueBlock(new Parenthetical(text));
                    } else {
                        character->addDialogueBlock(new Parenthetical(text));
                    }
                } else if (!text.isEmpty()) { //Dialogue
                    if (character->isDual()) {
                        character->addRightDialogueBlock(new Dialogue(text));
                    } else {
                        character->addDialogueBlock(new Dialogue(text));
                    }
                } else {
                    ++i;
                    break;
                }

                if (++i >= blockcount) {
                    break;
                }

                text = lines.at(i).trimmed();
            }

            i--;
        } else if (!lines.at(i).isEmpty()) { //Default action
            text = lines.at(i);
            text.replace("\t", "    ");

            blocklist->append(new Action(text));
        } else { //Blank action
            blocklist->append(new BlankLine());
        }

        i++;
    }
}

void Script::parseFromFinalDraft(const QString& script)
{
    QXmlStreamReader reader(script);
    QString attributeName;

    qDeleteAll(m_content);
    m_content.clear();

    if (reader.readNextStartElement() && reader.name().toString() == QString("FinalDraft")) {
        if (reader.readNextStartElement() && reader.name().toString() == QString("Content")) {
            while(reader.readNextStartElement()) {
                if (reader.name().toString() == QString("Paragraph")) {
                    foreach(const QXmlStreamAttribute &attr, reader.attributes()) {
                        if (attr.name().toString() == QString("Type")) {
                            QString type = attr.value().toString();

                            if (type == QString("Action")) {
                                reader.readNextStartElement();
                                m_content.append(new Action(reader.readElementText()));
                            } else if (type == QString("Character")) {
                                reader.readNextStartElement();
                                m_content.append(new Character(reader.readElementText()));
                            } else if (type == QString("Dialogue")) {
                                reader.readNextStartElement();
                                m_content.append(new Dialogue(reader.readElementText()));
                            } else if (type == QString("Parenthetical")) {
                                reader.readNextStartElement();
                                m_content.append(new Parenthetical(reader.readElementText()));
                            } else if (type == QString("Scene Heading")) {
                                reader.readNextStartElement();
                                m_content.append(new Scene(reader.readElementText()));
                            } else if (type == QString("Transition")) {
                                reader.readNextStartElement();
                                m_content.append(new Transition(reader.readElementText()));
                            }
                        } else if (attr.name().toString() == QString("Alignment")) {
                            QString alignment = attr.value().toString();

                            if (alignment == QString("Center")) {
                                reader.readNextStartElement();
                                Action *action = new Action(reader.readElementText());
                                action->setCentered(true);
                                m_content.append(action);
                                break;
                            }
                        }
                    }
                }

                while(reader.readNextStartElement());
            }
        }
    }

    if (reader.hasError()) {
        //TODO: Raise Error
        return;
    }
}

Script::~Script()
{
    qDeleteAll(m_content);
}

QString Script::toHtml()
{
    QString cssStyle;
    QFile file(":/data/style.css");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        cssStyle = in.readAll();
        file.close();
    }

    QString content = "<!DOCTYPE HTML>";
    content.append("<html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" /><style type=\"text/css\">");
    content.append(cssStyle);
    content.append("</style></head><body><article><section>");

    foreach (Block *block, m_content) {
        content.append(block->toHtml());
    }

    content.append("</section></article></body></html>");
    return content;
}

QString Script::toFountain()
{
    QString content;

    foreach (Block* block, m_content) {
        content.append(block->toFountain().append("\n"));
    }

    return content;
}

QList<Block *> Script::getBlocks()
{
    return m_content;
}

Script& Script::operator=(const Script& other)
{
    m_titlepage = other.m_titlepage;

    qDeleteAll(m_content);
    m_content.clear();

    m_content.fromStdList(other.m_content.toStdList());

    return *this;
}
