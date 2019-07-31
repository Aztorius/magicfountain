#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QSettings>
#include <QListWidgetItem>

#include "script.h"
#include "editormode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QString filepath;
    QFont courierfont;
    Script currentScript;
    QTranslator m_qtTranslator;
    QTranslator m_translator;
    QSettings *m_settings;
    QString m_language;
    EditorMode m_editorMode;

public slots:
    void refreshTitleBar(bool modified);
    void refreshPreview();
    void refreshScenesView();
    void exportAsPDF();
    void exportAsHTML();
    void print();
    void newFile();
    void openFile();
    void quickSave();
    void saveAs();
    void setBold();
    void setItalic();
    void setUnderline();
    void import();

private slots:
    void slot_actionFountain_Syntax();
    void slot_actionLanguage(QAction *action);
    void slot_actionReportAnIssue();
    void slot_actionAbout_Qt();
    void slot_actionAbout_Magic_Fountain();

    void slot_clickScenes(QListWidgetItem *item);
    void slot_checkAndSaveScript();

    void slot_loadSystemFont();
    void slot_loadCustomFont();

private:
    void openFormatDialog();

protected:
    void changeEvent(QEvent *event);
};

#endif // MAINWINDOW_H
