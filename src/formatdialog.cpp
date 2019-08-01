#include "formatdialog.h"
#include "ui_formatdialog.h"

FormatDialog::FormatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormatDialog)
{
    ui->setupUi(this);

    m_editorMode = EditorMode::None;

    connect(ui->pushButton_fountain, SIGNAL(clicked()), this, SLOT(setFountain()));
    connect(ui->pushButton_river, SIGNAL(clicked()), this, SLOT(setRiver()));
}

FormatDialog::~FormatDialog()
{
    delete ui;
}

EditorMode FormatDialog::getEditorMode()
{
    return m_editorMode;
}

void FormatDialog::setFountain()
{
    m_editorMode = EditorMode::FountainMode;
    this->done(0);
}

void FormatDialog::setRiver()
{
    m_editorMode = EditorMode::RiverMode;
    this->done(1);
}
