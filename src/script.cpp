#include "script.h"

#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>

#include "act.h"
#include "action.h"
#include "author.h"
#include "blankline.h"
#include "boneyard.h"
#include "chapter.h"
#include "character.h"
#include "contact.h"
#include "credit.h"
#include "dialogue.h"
#include "draftdate.h"
#include "lyrics.h"
#include "note.h"
#include "pagebreak.h"
#include "parenthetical.h"
#include "scene.h"
#include "scenesection.h"
#include "sequence.h"
#include "source.h"
#include "synopsis.h"
#include "title.h"
#include "transition.h"

#define BLOCK_MAIN 1
#define BLOCK_ACT 2
#define BLOCK_SEQUENCE 4
#define BLOCK_SCENESECTION 8
#define BLOCK_SCENE 16

Script::Script()
{
    m_sourceFormat = SourceFormat::Unknown;
}

Script::Script(QString& script, SourceFormat format)
{
    this->parse(script, format);
}

Script::Script(QFile& file, SourceFormat format)
{
    this->parse(file, format);
}

void Script::parse(QString& script, SourceFormat format)
{
    m_sourceFormat = format;
    QTextStream stream(&script);
    switch(format) {
    case SourceFormat::Fountain:
        this->parseFromFountain(stream);
        break;
    case SourceFormat::River:
        this->parseFromRiver(stream);
        break;
    case SourceFormat::FinalDraft:
    case SourceFormat::Unknown:
        break;
    }
}

void Script::parse(QFile& file, SourceFormat format)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    m_sourceFormat = format;
    QTextStream in(&file);
    switch(format) {
    case SourceFormat::Fountain:
        this->parseFromFountain(in);
        break;
    case SourceFormat::FinalDraft:
        this->parseFromFinalDraft(file);
        break;
    case SourceFormat::River:
        this->parseFromRiver(in);
        break;
    case SourceFormat::Unknown:
        break;
    }

    file.close();
}

void static parseTitlePageData(QTextStream &stream, QString &rawText, QString &text, TitlePageElement *element)
{
    if (stream.atEnd()) {
        return;
    }

    rawText = stream.readLine();
    text = rawText.trimmed();

    while (rawText.left(1) == "\t" || rawText.left(3) == "   ") {
        element->addLine(text);

        if (stream.atEnd()) {
            break;
        }

        rawText = stream.readLine();
        text = rawText.trimmed();
    }
}

void Script::parseFromRiver(QTextStream& stream)
{
    QString text, rawText;

    qDeleteAll(m_content);
    m_content.clear();
    m_titlepage.clear();

    //TODO: quint8 currentBlockType = BLOCK_MAIN;
    QList<Block *> *blocklist = &m_content;

    while (!stream.atEnd()) {
        rawText = stream.readLine();
        text = text.trimmed();

        if (text.left(3) == "===") { //Page breaks
            blocklist->append(new PageBreak());
        } else if (text.left(2) == "= ") { //Synopses
            blocklist->append(new Synopsis(text.mid(2)));
        } else if (text.left(2) == "## ") { //Chapter
            blocklist->append(new Chapter(text.mid(2)));
        } else if (text.left(1) == "# ") { //Title
            //blocklist->append(new Title(text.mid(2)));
        }
    }
}

void Script::parseFromFountain(QTextStream& stream)
{
    QString text, rawText;
    QRegExp regAlphaNumeric("[A-Z]|[a-z]|[0-9]*");
    QStringList validStartHeaders;
    validStartHeaders << "INT" << "EXT" << "EST" << "INT./EXT" << "INT/EXT" << "I./E" << "I/E";

    qDeleteAll(m_content);
    m_content.clear();
    m_titlepage.clear();

    quint8 currentBlockType = BLOCK_MAIN;
    QList<Block *> *blocklist = &m_content;

    if (stream.atEnd()) {
        return;
    }

    rawText = stream.readLine();
    text = rawText.trimmed();

    while (!stream.atEnd()) {
        if (text.left(2) == "/*") { //Boneyard
            Boneyard *block = new Boneyard();

            if (text.right(2) == "*/") { //inline Boneyard
                block->addLine(text.mid(2, text.size() - 4));
            } else { //multi-line or internal Boneyard
                while (!stream.atEnd()) {
                    rawText = stream.readLine();
                    text = rawText.trimmed();
                    block->addLine(rawText);
                    if (text.right(2) == "*/") {
                        break;
                    }
                }
            }

            blocklist->append(block);
        } else if (text.left(2) == "[[") { //Note
            Note *block = nullptr;
            if (text.right(2) == "]]") { //Inline
                block = new Note(text.mid(2, text.size() - 4), NoteInline);
                blocklist->append(block);
            } else { //Multi-line
                QString string_note = text.mid(2);
                while (!stream.atEnd()) {
                    rawText = stream.readLine();
                    text = rawText.trimmed();
                    string_note.append("\n" + rawText);
                    if (text.right(2) == "]]") {
                        break;
                    }
                }
                block = new Note(string_note, NoteMultiline);
            }
        } else if (text.left(1) == "!") { //Forced action
            rawText.remove(text.indexOf("!"), 1);
            rawText.replace("\t", "    ");

            blocklist->append(new Action(rawText));
        } else if (text.left(3) == "===") { //Page breaks
            blocklist->append(new PageBreak());
        } else if (text.left(2) == "= ") { //Synopsis
            blocklist->append(new Synopsis(text.mid(2)));
        } else if (text.left(1) == "~") { //Lyrics
            blocklist->append(new Lyrics(text.mid(1)));
        } else if (text.left(6) == "Title:") { //Title
            TitlePageElement *title = new Title(text.mid(6).trimmed());
            parseTitlePageData(stream, rawText, text, title);
            m_titlepage.addElement(title);
            continue;
        } else if (text.left(7) == "Credit:") { //Credit
            TitlePageElement *credit = new Credit(text.mid(7).trimmed());
            parseTitlePageData(stream, rawText, text, credit);
            m_titlepage.addElement(credit);
            continue;
        } else if (text.left(7) == "Author:") { //Author
            TitlePageElement *author = new Author(text.mid(7).trimmed());
            parseTitlePageData(stream, rawText, text, author);
            m_titlepage.addElement(author);
            continue;
        } else if (text.left(7) == "Source:") { //Source
            TitlePageElement *source = new Source(text.mid(7).trimmed());
            parseTitlePageData(stream, rawText, text, source);
            m_titlepage.addElement(source);
            continue;
        } else if (text.left(11) == "Draft date:") { //Draft date
            TitlePageElement *draftDate = new DraftDate(text.mid(11).trimmed());
            parseTitlePageData(stream, rawText, text, draftDate);
            m_titlepage.addElement(draftDate);
            continue;
        } else if (text.left(8) == "Contact:") { //Contact
            TitlePageElement *contact = new Contact(text.mid(8).trimmed());
            parseTitlePageData(stream, rawText, text, contact);
            m_titlepage.addElement(contact);
            continue;
        } else if (text.left(4) == "### ") { //Scene Section
            SceneSection *scenesection = new SceneSection(text.mid(4));

            if (currentBlockType & (BLOCK_SCENE | BLOCK_SCENESECTION)) {
                Act *act = dynamic_cast<Act*>(m_content.last());

                if (act != nullptr) {
                    if (act->getList()->size() > 0) {
                        Sequence *sequence = dynamic_cast<Sequence*>(act->getList()->last());

                        if (sequence != nullptr) {
                            sequence->addBlock(scenesection);
                        } else {
                            act->addBlock(scenesection);
                        }
                    } else {
                        act->addBlock(scenesection);
                    }
                } else {
                    Sequence *sequence = dynamic_cast<Sequence*>(m_content.last());

                    if (sequence != nullptr) {
                        sequence->addBlock(scenesection);
                    } else {
                        m_content.append(scenesection);
                    }
                }
            } else {
                blocklist->append(scenesection);
            }

            blocklist = scenesection->getList();
            currentBlockType = BLOCK_SCENESECTION;
        } else if (text.left(3) == "## ") { //Sequence
            Sequence *sequence = new Sequence(text.mid(3));

            if (currentBlockType & (BLOCK_SEQUENCE | BLOCK_SCENE | BLOCK_SCENESECTION)) {
                Act *act = dynamic_cast<Act*>(m_content.last());
                if (act != nullptr) {
                    act->addBlock(sequence);
                } else {
                    m_content.append(sequence);
                }
            } else {
                blocklist->append(sequence);
            }

            blocklist = sequence->getList();
            currentBlockType = BLOCK_SEQUENCE;
        } else if (text.left(2) == "# ") { //Act
            Act *act = new Act(text.mid(2));
            m_content.append(act);
            blocklist = act->getList();
            currentBlockType = BLOCK_ACT;
        } else if (validStartHeaders.indexOf(text.split(".").first().toUpper()) >= 0 ||
                   validStartHeaders.indexOf(text.split(" ").first().toUpper()) >= 0) { //Scene heading
            Scene *scene = new Scene(text);

            if (currentBlockType != BLOCK_SCENE) {
                blocklist->append(scene);
            } else {
                m_content.append(scene);
            }

            blocklist = scene->getList();
            currentBlockType = BLOCK_SCENE;
        } else if (text.left(1) == ">") {
            if (text.right(1) == "<") { //Centered text
                Action *action = new Action(text.mid(1, text.size()-2).trimmed());
                action->setCentered(true);
                blocklist->append(action);
            } else { //Forced transition
                blocklist->append(new Transition(text.mid(1)));
            }
        } else if (rawText.right(3) == "TO:" && text.toUpper() == text) { //Transition
            blocklist->append(new Transition(text));
        } else if (text.left(1) == "." && regAlphaNumeric.exactMatch(text.mid(1, 1))) { //Forced scene heading
            blocklist->append(new Scene(text.mid(1)));
        } else if ((text.split("(").first().toUpper() == text.split("(").first() &&
                    !text.isEmpty() &&
                    text.split("(").first().toLong() == 0) ||
                    text.left(1) == "@") { //Dialogue and forced dialogue
            if (text.left(1) == "@") {
                text.remove(0, 1);
            }

            Character *character = nullptr;

            if (text.right(1) == "^") { //Dual dialogue
                text.remove(text.size() - 1, 1);

                if (blocklist->size() < 2) {
                    // Treat that as a classic Dialogue
                    character = new Character(text);
                    blocklist->append(character);
                } else {
                    Block *block = blocklist->at(blocklist->size() - 2);

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

            if (stream.atEnd()) {
                break;
            }

            rawText = stream.readLine();
            text = rawText.trimmed();

            while (!text.isEmpty() || rawText == "  ") {

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
                    break;
                }

                if (stream.atEnd()) {
                    break;
                }

                rawText = stream.readLine();
                text = rawText.trimmed();
            }
        } else if (!rawText.isEmpty()) { //Default action
            rawText.replace("\t", "    ");

            blocklist->append(new Action(rawText));
        } else { //Blank action
            blocklist->append(new BlankLine());
        }

        rawText = stream.readLine();
        text = rawText.trimmed();
    }
}

void Script::parseFromFinalDraft(QIODevice &script)
{
    QXmlStreamReader reader(&script);
    QString attributeName;

    qDeleteAll(m_content);
    m_content.clear();

    while (reader.readNextStartElement() && reader.name().toString() != "FinalDraft");

    Character* lastCharacterBlock = nullptr;

    if (reader.readNextStartElement() && reader.name().toString() == "Content") {
        reader.readNext();
        while(!reader.atEnd()) {
            if (reader.name().toString() == "Paragraph") {
                foreach(const QXmlStreamAttribute &attr, reader.attributes()) {
                    if (attr.name().toString() == "Type") {
                        QString type = attr.value().toString();
                        if (type == "Action") {
                            reader.readNextStartElement();
                            m_content.append(new Action(reader.readElementText()));
                        } else if (type == QString("Character")) {
                            reader.readNextStartElement();
                            lastCharacterBlock = new Character(reader.readElementText());
                            m_content.append(lastCharacterBlock);
                        } else if (type == QString("Dialogue")) {
                            reader.readNextStartElement();
                            lastCharacterBlock->addDialogueBlock(new Dialogue(reader.readElementText()));
                        } else if (type == QString("Parenthetical")) {
                            reader.readNextStartElement();
                            m_content.append(new Parenthetical(reader.readElementText()));
                        } else if (type == QString("Scene Heading")) {
                            reader.readNextStartElement();
                            while(!reader.atEnd() && reader.name().toString() != "Text") {
                                reader.readNext();
                            }
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
            reader.readNext();
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

    if (!m_titlepage.isEmpty()) {
        content.append(m_titlepage.toHtml());
        content.append("<p class='page-break'>1.</p>\n");
    }

    foreach (Block *block, m_content) {
        content.append(block->toHtml());
    }

    content.append("</section></article></body></html>");
    return content;
}

QString Script::toFountain()
{
    QString content;

    content.append(m_titlepage.toFoutain());

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
