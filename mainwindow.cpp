#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QDesktopServices>
#include <QMessageBox>

#include "block.h"

QString GLOBAL_VERSION = "1.0.0";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Magic Fountain Alpha " + GLOBAL_VERSION);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/Courier Prime.ttf");

    if (fontId == -1) {
        //Error loading the font : should use system font available
        courierfont = QFont("Courier");
    } else {
        courierfont = QFont(QFontDatabase::applicationFontFamilies(fontId).at(0));
    }

    courierfont.setPointSize(12);

    currentScript = nullptr;

    ui->plainTextEdit_fountaineditor->setFont(courierfont);
    ui->plainTextEdit_fountaineditor->setFocus();
    ui->textBrowser_preview->setFont(courierfont);

    connect(ui->plainTextEdit_fountaineditor, SIGNAL(textChanged()), this, SLOT(refreshPreview()));
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

    connect(ui->actionFountain_Syntax, SIGNAL(triggered()), this, SLOT(slot_actionFountain_Syntax()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(slot_actionAbout_Qt()));
    connect(ui->actionAbout_Magic_Fountain, SIGNAL(triggered()), this, SLOT(slot_actionAbout_Magic_Fountain()));
}

MainWindow::~MainWindow()
{
    if (currentScript != nullptr) {
        delete currentScript;
    }

    delete ui;
}

void MainWindow::refreshPreview() {
    if (currentScript != nullptr) {
        delete currentScript;
    }

    currentScript = new Script(ui->plainTextEdit_fountaineditor->toPlainText());

    ui->textBrowser_preview->setHtml(currentScript->toHtml());
    ui->textBrowser_preview->setCurrentFont(courierfont);
    ui->plainTextEdit_fountaineditor->setFocus();

    refreshScenesView();
}

void MainWindow::refreshScenesView()
{
    ui->listWidget_scenes->clear();

    foreach (Block *block, currentScript->getBlocks()) {
        if (block->getType() == BlockType::Scene) {
            ui->listWidget_scenes->insertItem(ui->listWidget_scenes->count(), block->getData());
        }
    }
}

void MainWindow::exportAsPDF() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export PDF"),
                                                    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first(),
                                                    "PDF files (*.pdf)");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()){
                 fileName.append(".pdf");
        }

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPrinter::Letter);
        printer.setColorMode(QPrinter::GrayScale);
        printer.setFullPage(true);
        printer.setResolution(96);
        printer.setPageMargins(1.0, 1.0, 1.0, 1.0, QPrinter::Inch);
        printer.setOutputFileName(fileName);

        ui->textBrowser_preview->document()->print(&printer);
    }
}

void MainWindow::exportAsHTML() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export HTML"),
                                                    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first(),
                                                    "HTML files (*.html)");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()){
             fileName.append(".html");
        }

        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
             QTextStream stream(&file);
             stream << currentScript->toHtml();
             file.close();
        }
    }
}

void MainWindow::print() {
        QPrinter printer;
        printer.setPageSize(QPrinter::Letter);
        printer.setColorMode(QPrinter::GrayScale);
        printer.setFullPage(true);
        printer.setResolution(96);
        printer.setPageMargins(1.0, 1.0, 1.0, 1.0, QPrinter::Inch);

        QPrintDialog dialog(&printer, this);
        dialog.setWindowTitle(tr("Print Document"));

        if (dialog.exec() != QDialog::Accepted) {
           return;
        }

        ui->textBrowser_preview->document()->print(&printer);
}

void MainWindow::newFile() {
    QString filename = ":/data/default.fountain";
    if(filename.isEmpty()){
        return;
    }

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->plainTextEdit_fountaineditor->clear();
        ui->plainTextEdit_fountaineditor->appendPlainText(file.readAll());
        filepath.clear();
        file.close();

        QTextCursor cursor = ui->plainTextEdit_fountaineditor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        ui->plainTextEdit_fountaineditor->setTextCursor(cursor);
    }
}

void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Fountain file"),
                                                    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first(),
                                                    "Text files (*.fountain *.txt *.markdown *.md)");
    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->plainTextEdit_fountaineditor->clear();
        ui->plainTextEdit_fountaineditor->appendPlainText(file.readAll());
        filepath = filename;
        file.close();

        QTextCursor cursor = ui->plainTextEdit_fountaineditor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        ui->plainTextEdit_fountaineditor->setTextCursor(cursor);
    }
}

void MainWindow::saveAs() {
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save Fountain file"),
                                                    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first(),
                                                    "Fountain files (*.fountain);; Text files (*.txt);; Markdown files (*.md *.markdown)");
    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << ui->plainTextEdit_fountaineditor->toPlainText();
        file.close();
        filepath = filename;
    }
}

void MainWindow::quickSave() {
    if (filepath.isEmpty()) {
        saveAs();
        return;
    }

    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << ui->plainTextEdit_fountaineditor->toPlainText();
        file.close();
    }
}

void MainWindow::setBold() {
    if (ui->plainTextEdit_fountaineditor->textCursor().selectedText().isEmpty()) {
        ui->plainTextEdit_fountaineditor->insertPlainText("****");

        QTextCursor cursor = ui->plainTextEdit_fountaineditor->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 2);
        ui->plainTextEdit_fountaineditor->setTextCursor(cursor);
    } else {
        QString selected = ui->plainTextEdit_fountaineditor->textCursor().selectedText();
        ui->plainTextEdit_fountaineditor->textCursor().clearSelection();
        ui->plainTextEdit_fountaineditor->insertPlainText("**" + selected + "**");
    }
}

void MainWindow::setItalic() {
    if (ui->plainTextEdit_fountaineditor->textCursor().selectedText().isEmpty()) {
        ui->plainTextEdit_fountaineditor->insertPlainText("**");

        QTextCursor cursor = ui->plainTextEdit_fountaineditor->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        ui->plainTextEdit_fountaineditor->setTextCursor(cursor);
    } else {
        QString selected = ui->plainTextEdit_fountaineditor->textCursor().selectedText();
        ui->plainTextEdit_fountaineditor->textCursor().clearSelection();
        ui->plainTextEdit_fountaineditor->insertPlainText("*" + selected + "*");
    }
}

void MainWindow::setUnderline() {
    if (ui->plainTextEdit_fountaineditor->textCursor().selectedText().isEmpty()) {
        ui->plainTextEdit_fountaineditor->insertPlainText("__");

        QTextCursor cursor = ui->plainTextEdit_fountaineditor->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        ui->plainTextEdit_fountaineditor->setTextCursor(cursor);
    } else {
        QString selected = ui->plainTextEdit_fountaineditor->textCursor().selectedText();
        ui->plainTextEdit_fountaineditor->textCursor().clearSelection();
        ui->plainTextEdit_fountaineditor->insertPlainText("_" + selected + "_");
    }
}

void MainWindow::slot_actionFountain_Syntax()
{
    QDesktopServices::openUrl(QUrl("https://fountain.io/syntax"));
}

void MainWindow::slot_actionAbout_Qt()
{
    QMessageBox::aboutQt(this, QString("About Qt"));
}

void MainWindow::slot_actionAbout_Magic_Fountain()
{
    QMessageBox::about(this, QString("About Magic Fountain"), QString(
                           "Magic Fountain is distributed under the GPL (General Public License) version 3.\n"\
                           "It is a free and open source software.\n"\
                           "You can contribute to the project on GitHub at https://github.com/Aztorius/magicfountain \n\n"\
                           "Magic Fountain includes the Courier Prime fonts which are licensed under the SIL Open Font License (OFL)."
                           ));
}
