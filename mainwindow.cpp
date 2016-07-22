#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Magic Fountain Alpha 1.0.0");

    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(refreshPreview()));
    connect(ui->actionExport_as_PDF, SIGNAL(triggered()), this, SLOT(exportAsPDF()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshPreview()
{
    QTextDocument* document = ui->plainTextEdit->document();
    QTextBlock block;
    QString text;
    QString content = "";
    int blockcount = ui->plainTextEdit->blockCount();
    int i = 0;

    while(i < blockcount){
        block = document->findBlockByNumber(i);
        text = block.text();

        if(text.left(2) == "# "){
            content.append("<h1>" + text.mid(2) + "</h1>");
        }
        else if(text.left(3) == "## "){
            content.append("<h2>" + text.mid(3) + "</h2>");
        }
        else if(text.left(4) == "### "){
            content.append("<h3>" + text.mid(4) + "</h3>");
        }
        else if(text.left(3).toLower() == "int" || text.left(3).toLower() == "ext"){
            content.append("<p><b>" + text + "</b></p>");
        }
        else if(text.left(1) == "."){
            content.append("<p><b>" + text.mid(1) + "</b></p>");
        }
        else{
            content.append("<p>" + checkBoldItalicUnderline(text) + "</p>");
        }

        i++;
    }

    ui->textBrowser->setHtml(content);
}

void MainWindow::exportAsPDF(){
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()){
                 fileName.append(".pdf");
        }
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textBrowser->document()->print(&printer);
    }
}

void MainWindow::openFile(){
    QString filename = QFileDialog::getOpenFileName(this, "Open Fountain file", QString(), "Text files (*.txt *.fountain *.markdown *.md)");
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(file.readAll());
    }
}

QString MainWindow::checkBoldItalicUnderline(QString text){
    QString temp, result = text;

    //Check Bold with Italic, ex: ***something***
    while(result.contains("***") && result.mid(result.indexOf("***") + 3).contains("***")){
        temp = result.left(result.indexOf("***")) + "<b><i>";
        result = result.mid(result.indexOf("***") + 3);
        temp += result.left(result.indexOf("***")) + "</i></b>";
        result = result.mid(result.indexOf("***") + 3);
        temp += result;
        result = temp;
    }

    //Check Bold, ex: **something**
    while(result.contains("**") && result.mid(result.indexOf("**") + 2).contains("**")){
        temp = result.left(result.indexOf("**")) + "<b>";
        result = result.mid(result.indexOf("**") + 2);
        temp += result.left(result.indexOf("**")) + "</b>";
        result = result.mid(result.indexOf("**") + 2);
        temp += result;
        result = temp;
    }

    //Check Italic, ex: *something*
    while(result.contains("*") && result.mid(result.indexOf("*") + 1).contains("*")){
        temp = result.left(result.indexOf("*")) + "<i>";
        result = result.mid(result.indexOf("*") + 1);
        temp += result.left(result.indexOf("*")) + "</i>";
        result = result.mid(result.indexOf("*") + 1);
        temp += result;
        result = temp;
    }

    //Check Underline, ex: _something_
    while(result.contains("_") && result.mid(result.indexOf("_") + 1).contains("_")){
        temp = result.left(result.indexOf("_")) + "<u>";
        result = result.mid(result.indexOf("_") + 1);
        temp += result.left(result.indexOf("_")) + "</u>";
        result = result.mid(result.indexOf("_") + 1);
        temp += result;
        result = temp;
    }

    return result;
}
