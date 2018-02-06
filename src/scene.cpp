#include "scene.h"

Scene::Scene(const QString &sceneheader) : Block(sceneheader)
{

}

void Scene::addBlock(Block *block)
{
    m_content.append(block);
}

void Scene::setSceneNumber(QString &sceneNumber)
{
    m_sceneNumber = sceneNumber;
}

void Scene::setSynopsis(Synopsis synopsis)
{
    m_synopsis = synopsis;
}

QList<Block *> *Scene::getList()
{
    return &m_content;
}

QString Scene::toHtml()
{
    QString result = "<p class='scene-heading'>" + htmlCheckBIU(m_data) + "</p>";

    foreach (Block *block, m_content) {
        result.append(block->toHtml());
    }

    return result;
}

QString Scene::toFountain()
{
    QString result = "." + m_data + "\n";

    foreach (Block *block, m_content) {
        result.append(block->toFountain());
    }

    return result;
}

void Scene::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << m_data);

    foreach (Block *block, m_content) {
        block->toTreeWidgetItem(item);
    }

    parent->addChild(item);
}
