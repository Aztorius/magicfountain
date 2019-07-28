#ifndef SYNOPSIS_H
#define SYNOPSIS_H

#include "block.h"

class Synopsis : public Block
{
public:
    Synopsis();
    Synopsis(const QString &data);

    QString toHtml();
    QString toFountain();
    void toTreeWidgetItem(QTreeWidgetItem *parent);

    Synopsis& operator=(const Synopsis *other);
};

#endif // SYNOPSIS_H
