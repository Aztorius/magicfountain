#ifndef SCENE_H
#define SCENE_H

#include <QSharedPointer>

#include "block.h"
#include "synopsis.h"

class Scene : public Block
{
public:
    Scene(const QString &sceneheader);
    void addBlock(Block *block);
    void setSceneNumber(QString &sceneNumber);
    void setSynopsis(Synopsis synopsis);

    virtual QString toHtml();
    virtual QString toFountain();
private:
    QList<QSharedPointer<Block>> m_content;
    QString m_sceneNumber;
    Synopsis m_synopsis;
};

#endif // SCENE_H
