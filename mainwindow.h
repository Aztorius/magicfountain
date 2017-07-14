#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBlock>
#include <QPrinter>
#include <QPrintDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

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
};

#endif // MAINWINDOW_H
