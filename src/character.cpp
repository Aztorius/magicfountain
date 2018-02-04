#include "character.h"

Character::Character(const QString &data) : Block(data)
{

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
    if(m_isDual) {
        return "<div class='dual-dialogue'><div class='dual-dialogue-left'><p class='character'>" + htmlCheckBIU(m_data) + "</p>";
    } else {
        return "<p class='character'>" + htmlCheckBIU(m_data) + "</p>";
    }
}

QString Character::toFountain()
{
    // TODO
    return QString();
}

bool Character::isCharacterBlock()
{
    return true;
}
