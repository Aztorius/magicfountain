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
    return "<p class='scene-heading'>" + htmlCheckBIU(m_data) + "</p>";
}

QString Scene::toFountain()
{
    return "." + m_data + "\n";
}

void Scene::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << m_data);

    foreach (Block *block, m_content) {
        block->toTreeWidgetItem(item);
    }

    parent->addChild(item);
}
