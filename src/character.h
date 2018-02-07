#ifndef CHARACTER_H
#define CHARACTER_H

#include "block.h"
#include "dialogueblock.h"

class Character : public Block
{
public:
    Character(const QString &data);

    bool isDual();
    void setDual(bool isDual);
    void addDialogueBlock(DialogueBlock *block);
    void setRightCharacter(const QString &data);
    void addRightDialogueBlock(DialogueBlock *block);

    virtual QString toHtml();
    virtual QString toFountain();
    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);

    virtual bool isCharacterBlock();
private:
    bool m_isDual;
    QList<DialogueBlock *> m_leftContent;
    QString m_rightCharacter;
    QList<DialogueBlock *> m_rightContent;
};

#endif // CHARACTER_H
