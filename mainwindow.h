#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBlock>
#include <QPrinter>
#include <QPrintDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTranslator>
#include <QSettings>

#include "script.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString filepath;
    QFont courierfont;
    Script *currentScript;
    QTranslator m_translator;
    QSettings *m_settings;

public slots:
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

private slots:
    void slot_actionFountain_Syntax();
    void slot_actionLanguage(QAction *action);
    void slot_actionReportAnIssue();
    void slot_actionAbout_Qt();
    void slot_actionAbout_Magic_Fountain();

protected:
    void changeEvent(QEvent*);
};

#endif // MAINWINDOW_H
