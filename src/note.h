#ifndef NOTE_H
#define NOTE_H

#include "block.h"

enum NoteType {
    NoteInline = 0x1,
    NoteMultiline = 0x2
};

class Note : public Block
{
private:
    NoteType m_type;
public:
    Note(const QString &data, NoteType type);

    QString toHtml();
    QString toFountain();
};

#endif // NOTE_H
