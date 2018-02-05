#ifndef SCENESECTION_H
#define SCENESECTION_H

#include "section.h"

class SceneSection : public Section
{
public:
    SceneSection(const QString &m_data);

    virtual QString toHtml();
    virtual QString toFountain();
    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);
};

#endif // SCENESECTION_H
