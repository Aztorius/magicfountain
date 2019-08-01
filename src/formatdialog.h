#ifndef FORMATDIALOG_H
#define FORMATDIALOG_H

#include <QDialog>

#include "editormode.h"

namespace Ui {
class FormatDialog;
}

class FormatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormatDialog(QWidget *parent = nullptr);
    ~FormatDialog();
    EditorMode getEditorMode();

public slots:
    void setFountain();
    void setRiver();

private:
    Ui::FormatDialog *ui;
    EditorMode m_editorMode;
};

#endif // FORMATDIALOG_H
