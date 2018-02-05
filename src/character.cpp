#include "character.h"

Character::Character(const QString &data) : Block(data)
{
    m_isDual = false;
}

bool Character::isDual()
{
    return m_isDual;
}

void Character::setDual(bool isDual)
{
    m_isDual = isDual;
}

void Character::addDialogueBlock(DialogueBlock *block)
{
    QSharedPointer<DialogueBlock> ptr(block);
    m_leftContent.append(ptr);
}

void Character::setRightCharacter(const QString &data)
{
    m_rightCharacter = data;
}

void Character::addRightDialogueBlock(DialogueBlock *block)
{
    QSharedPointer<DialogueBlock> ptr(block);
    m_rightContent.append(ptr);
}

QString Character::toHtml()
{
    QString result;

    if (m_isDual) {
        result = "<div class='dual-dialogue'><div class='dual-dialogue-left'><p class='character'>" + htmlCheckBIU(m_data) + "</p>";
        foreach (QSharedPointer<DialogueBlock> block, m_leftContent) {
            result.append(block.data()->toHtml());
        }

        result.append("</div><div class='dual-dialogue-right'><p class='character'>" + htmlCheckBIU(m_rightCharacter) + "</p>");

        foreach (QSharedPointer<DialogueBlock> block, m_rightContent) {
            result.append(block.data()->toHtml());
        }

        result.append("</div></div>");
    } else {
        result = "<p class='character'>" + htmlCheckBIU(m_data) + "</p>";
        foreach (QSharedPointer<DialogueBlock> block, m_leftContent) {
            result.append(block.data()->toHtml());
        }
    }

    return result;
}

QString Character::toFountain()
{
    QString result;

    if (m_isDual) {
        result = m_data + "\n";

        foreach (QSharedPointer<DialogueBlock> block, m_leftContent) {
            result.append(block.data()->toFountain());
        }

        result.append(m_rightCharacter + "\n");

        foreach (QSharedPointer<DialogueBlock> block, m_rightContent) {
            result.append(block.data()->toFountain());
        }
    } else {
        result = m_data + "\n";

        foreach (QSharedPointer<DialogueBlock> block, m_leftContent) {
            result.append(block.data()->toFountain());
        }
    }

    return result;
}

void Character::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    parent->addChild(new QTreeWidgetItem(QStringList() << m_data));
}

bool Character::isCharacterBlock()
{
    return true;
}
