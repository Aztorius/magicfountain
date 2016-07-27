#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Magic Fountain Alpha 1.0.0");

    courierfont = QFont("Courier");
    courierfont.setPointSize(12);

    ui->plainTextEdit->setFont(courierfont);
    ui->plainTextEdit->setFocus();

    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(refreshPreview()));
    connect(ui->actionExport_as_PDF, SIGNAL(triggered()), this, SLOT(exportAsPDF()));
    connect(ui->actionExport_as_HTML, SIGNAL(triggered()), this, SLOT(exportAsHTML()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(quickSave()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionPrint, SIGNAL(triggered()), this, SLOT(print()));

    connect(ui->actionBold, SIGNAL(triggered()), this, SLOT(setBold()));
    connect(ui->actionItalic, SIGNAL(triggered()), this, SLOT(setItalic()));
    connect(ui->actionUnderline, SIGNAL(triggered()), this, SLOT(setUnderline()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshPreview(){
    currentScript = Script(ui->plainTextEdit->toPlainText());

    ui->textBrowser->setHtml(currentScript.toHtml());

    ui->textBrowser->setCurrentFont(courierfont);

    ui->plainTextEdit->setFocus();
}

void MainWindow::exportAsPDF(){
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "PDF files (*.pdf)");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()){
                 fileName.append(".pdf");
        }

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setFullPage(true);
        printer.setResolution(96);
        printer.setPageMargins(1.5, 1.0, 1.0, 1.0, QPrinter::Inch);
        printer.setOutputFileName(fileName);

        ui->textBrowser->document()->print(&printer);
    }
}

void MainWindow::exportAsHTML(){
    QString fileName = QFileDialog::getSaveFileName(this, "Export HTML", QString(), "HTML files (*.html)");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()){
             fileName.append(".html");
        }

        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
             QTextStream stream(&file);
             stream << currentScript.toHtml();
             file.close();
        }
    }
}

void MainWindow::print(){
        QPrinter printer;
        printer.setFullPage(true);
        printer.setResolution(96);
        printer.setPageMargins(1.5, 1.0, 1.0, 1.0, QPrinter::Inch);

        QPrintDialog dialog(&printer, this);
        dialog.setWindowTitle(tr("Print Document"));

        if (dialog.exec() != QDialog::Accepted) {
           return;
        }

        ui->textBrowser->document()->print(&printer);
}

void MainWindow::newFile(){
    QString filename = ":/data/default.fountain";
    if(filename.isEmpty()){
        return;
    }

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(file.readAll());
        filepath.clear();
        file.close();

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        ui->plainTextEdit->setTextCursor(cursor);
    }
}

void MainWindow::openFile(){
    QString filename = QFileDialog::getOpenFileName(this, "Open Fountain file", QString(), "Text files (*.fountain *.txt *.markdown *.md)");
    if(filename.isEmpty()){
        return;
    }

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(file.readAll());
        filepath = filename;
        file.close();

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        ui->plainTextEdit->setTextCursor(cursor);
    }
}

void MainWindow::saveAs(){
    QString filename = QFileDialog::getSaveFileName(this, "Save Fountain file", QString(), "Fountain files (*.fountain);; Text files (*.txt);; Markdown files (*.md *.markdown)");
    if (filename.isEmpty()){
        return;
    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << ui->plainTextEdit->toPlainText();
        file.close();
        filepath = filename;
    }
}

void MainWindow::quickSave(){
    if(filepath.isEmpty()){
        saveAs();
        return;
    }

    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << ui->plainTextEdit->toPlainText();
        file.close();
    }
}

void MainWindow::setBold(){
    if(ui->plainTextEdit->textCursor().selectedText().isEmpty()){
        ui->plainTextEdit->insertPlainText("****");

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 2);
        ui->plainTextEdit->setTextCursor(cursor);
    }
    else{
        QString selected = ui->plainTextEdit->textCursor().selectedText();
        ui->plainTextEdit->textCursor().clearSelection();
        ui->plainTextEdit->insertPlainText("**" + selected + "**");
    }
}

void MainWindow::setItalic(){
    if(ui->plainTextEdit->textCursor().selectedText().isEmpty()){
        ui->plainTextEdit->insertPlainText("**");

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        ui->plainTextEdit->setTextCursor(cursor);
    }
    else{
        QString selected = ui->plainTextEdit->textCursor().selectedText();
        ui->plainTextEdit->textCursor().clearSelection();
        ui->plainTextEdit->insertPlainText("*" + selected + "*");
    }
}

void MainWindow::setUnderline(){
    if(ui->plainTextEdit->textCursor().selectedText().isEmpty()){
        ui->plainTextEdit->insertPlainText("__");

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        ui->plainTextEdit->setTextCursor(cursor);
    }
    else{
        QString selected = ui->plainTextEdit->textCursor().selectedText();
        ui->plainTextEdit->textCursor().clearSelection();
        ui->plainTextEdit->insertPlainText("_" + selected + "_");
    }
}

