#include "scene.h"

Scene::Scene(const QString &sceneheader) : Block(sceneheader)
{

}

void Scene::addBlock(Block *block)
{
    QSharedPointer<Block> ptr(block);
    m_content.append(ptr);
}

void Scene::setSceneNumber(QString &sceneNumber)
{
    m_sceneNumber = sceneNumber;
}

void Scene::setSynopsis(Synopsis synopsis)
{
    m_synopsis = synopsis;
}

QString Scene::toHtml()
{
    return "<p class='scene-heading'>" + htmlCheckBIU(m_data) + "</p>";
}

QString Scene::toFountain()
{
    return "." + m_data + "\n";
}
