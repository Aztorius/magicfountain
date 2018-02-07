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
    m_leftContent.append(block);
}

void Character::setRightCharacter(const QString &data)
{
    m_rightCharacter = data;
}

void Character::addRightDialogueBlock(DialogueBlock *block)
{
    m_rightContent.append(block);
}

QString Character::toHtml()
{
    QString result;

    if (m_isDual) {
        result = "<div class='dual-dialogue'><div class='dual-dialogue-left'><p class='character'>" + htmlCheckBIU(m_data) + "</p>";
        foreach (DialogueBlock *block, m_leftContent) {
            result.append(block->toHtml());
        }

        result.append("</div><div class='dual-dialogue-right'><p class='character'>" + htmlCheckBIU(m_rightCharacter) + "</p>");

        foreach (DialogueBlock *block, m_rightContent) {
            result.append(block->toHtml());
        }

        result.append("</div></div>");
    } else {
        result = "<p class='character'>" + htmlCheckBIU(m_data) + "</p>";
        foreach (DialogueBlock *block, m_leftContent) {
            result.append(block->toHtml());
        }
    }

    return result;
}

QString Character::toFountain()
{
    QString result;

    if (m_isDual) {
        result = m_data + "\n";

        foreach (DialogueBlock *block, m_leftContent) {
            result.append(block->toFountain());
        }

        result.append(m_rightCharacter + "\n");

        foreach (DialogueBlock *block, m_rightContent) {
            result.append(block->toFountain());
        }
    } else {
        result = m_data + "\n";

        foreach (DialogueBlock *block, m_leftContent) {
            result.append(block->toFountain());
        }
    }

    return result;
}

void Character::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << m_data);

    foreach (DialogueBlock *block, m_leftContent) {
        block->toTreeWidgetItem(item);
    }

    if (m_isDual) {
        item->addChild(new QTreeWidgetItem(QStringList() << m_rightCharacter));

        foreach (DialogueBlock *block, m_rightContent) {
            block->toTreeWidgetItem(item);
        }
    }

    parent->addChild(item);
}

bool Character::isCharacterBlock()
{
    return true;
}
