#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBlock>
#include <QPrinter>
#include <QPrintDialog>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString checkBoldItalicUnderline(QString text);

private:
    Ui::MainWindow *ui;

public slots:
    void refreshPreview();
    void exportAsPDF();
    void print();
    void openFile();
    void setBold();
    void setItalic();
    void setUnderline();
};

#endif // MAINWINDOW_H
