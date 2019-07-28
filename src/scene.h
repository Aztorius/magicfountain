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
    QList<Block *> *getList();

    QString toHtml();
    QString toFountain();
    void toTreeWidgetItem(QTreeWidgetItem *parent);
private:
    QList<Block *> m_content;
    QString m_sceneNumber;
    Synopsis m_synopsis;
};

#endif // SCENE_H
