#ifndef SCENESECTION_H
#define SCENESECTION_H

#include "section.h"

class SceneSection : public Section
{
public:
    SceneSection(const QString &data);

    QString toFountain();
};

#endif // SCENESECTION_H
