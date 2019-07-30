#include "note.h"

Note::Note(const QString &data, NoteType type) : Block(data)
{
    m_type = type;
}

QString Note::toHtml()
{
    return QString();
}

QString Note::toFountain()
{
    QString result = m_data;
    switch (m_type) {
    case NoteInline:
    case NoteMultiline:
        result = "[[" + m_data + "]]";
        break;
    }
    return result;
}

void Note::toTreeWidgetItem(QTreeWidgetItem *parent)
{
    Q_UNUSED(parent)
}
