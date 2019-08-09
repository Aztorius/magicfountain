#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <QTreeWidget>

class Block
{
public:
    Block();
    Block(const QString &data);
    Block(const Block& other);
    virtual ~Block();

    QString getData();
    void appendData(const QString& data);

    virtual QString toHtml() = 0;
    virtual QString toFountain() = 0;
    virtual QString toRiver();

    virtual void toTreeWidgetItem(QTreeWidgetItem *parent);
    virtual bool isCharacterBlock();

    Block& operator=(const Block& block);

    static QString htmlCheckBIU(const QString &text);
protected:
    QString m_data;
};

#endif // BLOC_H
