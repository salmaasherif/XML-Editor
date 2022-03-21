#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QtDebug>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <QDir>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Browse button
void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit_2->clear();
    QString s1 = QFileDialog::getOpenFileName(this, "Open the file", "directoryToOpen",
            "XML files (*.xml)");
    QFile file(s1);
    input = s1;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file:" + file.errorString());
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textBrowser->setText(text);
    ui->textBrowser->setReadOnly(true);
    file.close();
}

//Compress button
void MainWindow::on_pushButton_5_clicked()
{
    ui->plainTextEdit_2->clear();
    QString s2 = ui->textBrowser->toPlainText();
    std::string input1 = s2.toLocal8Bit().constData();
    std::string output = Compress(input1);
    QString s3 = QString::fromLocal8Bit(output);
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setPlainText(s3.toLocal8Bit());
    QMessageBox::information(this, "Compression Info" ,"Original File Size: "+QString::number(size_of_file(input1))+" Byte\n"+
                                 "Compressed File Size: "+QString::number(size_of_file(output))+" Byte\n");
}

//Decompress button
void MainWindow::on_pushButton_8_clicked()
{
    ui->plainTextEdit_2->clear();
    std::string output=Decompress();
    QString s3 = QString::fromLocal8Bit(output.c_str());
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setPlainText(s3);
}

//Minify button
void MainWindow::on_pushButton_4_clicked()
{
    ui->plainTextEdit_2->clear();
    QString s2 = ui->textBrowser->toPlainText();
    std::string input1 = s2.toLocal8Bit().constData();
    std::ofstream temp("temp.xml");
    temp << input1;
    temp.close();
    std::ifstream temp1("temp.xml");
    std::string output = Minify(temp1);
    QString s3 = QString::fromLocal8Bit(output.c_str());
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setPlainText(s3);
}

//Format button
void MainWindow::on_pushButton_3_clicked()
{
    ui->plainTextEdit_2->clear();
    QString s2 = ui->textBrowser->toPlainText();
    std::string input1 = s2.toLocal8Bit().constData();
    std::ofstream temp("temp1.xml");
    temp << input1;
    temp.close();
    std::ifstream inputFile("temp1.xml");
    std::ofstream temp3("middle.xml");
    std::ofstream outputFile("output.xml");
    temp3 << Minify2(inputFile, outputFile);
    temp3.close();
    std::ifstream temp2("middle.xml");
    XML_tree* t1 = new XML_tree();
    outputFile << Parser(temp2, outputFile);
    temp2.close();
    std::ifstream in2("output.xml");
    std::string output = Format(t1, in2, outputFile);
    QString s3 = QString::fromLocal8Bit(output.c_str());
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(12);
    ui->plainTextEdit_2->setFont(font);
    QFontMetrics metrics(font);
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setTabStopDistance(15);
    ui->plainTextEdit_2->setPlainText(s3);
}

//XML to JSON button
void MainWindow::on_pushButton_6_clicked()
{
    ui->plainTextEdit_2->clear();
    QString s2 = ui->textBrowser->toPlainText();
    std::string input1 = s2.toLocal8Bit().constData();
    std::ofstream temp("temp1.xml");
    temp << input1;
    temp.close();
    std::ifstream inputFile("temp1.xml");
    std::ofstream temp3("middle.xml");
    std::ofstream outputFile("output2.xml");
    temp3 << Minify2(inputFile, outputFile);
    temp3.close();
    std::ifstream temp2("middle.xml");
    outputFile << Parser(temp2, outputFile);
    temp2.close();
    XML_tree* T1 = new XML_tree();
    std::ifstream input("output2.xml");
    std::string output2="";
    output2+= "{" ;
    output2 += "\r\n";
    //output5 += "{" + '\n';
    tree(T1, input);
    Node* root = T1->get_root();
    Node* parent_of_root = new Node("dummy Node");
    root->parent = parent_of_root;
    output2+=XML_to_json(root);
    output2 += "\r\n";
    output2 +="}" ;
    output2 += "\r\n";
    QString s3 = QString::fromLocal8Bit(output2);
    /*ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setPlainText(s3.toLocal8Bit());*/
    output2="";
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(12);
    ui->plainTextEdit_2->setFont(font);
    QFontMetrics metrics(font);
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setTabStopDistance(15);
    ui->plainTextEdit_2->setPlainText(s3);
}


//Correct Errors button
void MainWindow::on_pushButton_2_clicked()
{
    ui->plainTextEdit_2->clear();
    QString s2 = ui->textBrowser->toPlainText();
    std::string input1 = s2.toLocal8Bit().constData();
    std::vector<std::string> xmlfile ;
    xmlfile.push_back(input1);
    xml_corrector(xmlfile);
    std::stringstream strrr;
    for (std::vector<std::string>::const_iterator i = xmlfile.begin(); i != xmlfile.end(); ++i)
        strrr<< *i;
    QString s3 = QString::fromLocal8Bit(strrr.str());
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setPlainText(s3.toLocal8Bit());
}

//Check Consistency button
void MainWindow::on_pushButton_7_clicked()
{
    ui->plainTextEdit_2->clear();
    QString s2 = ui->textBrowser->toPlainText();
    std::string input1 = s2.toLocal8Bit().constData();
    std::vector<std::string> xmlfile ;
    xmlfile.push_back(input1);
    std::vector<std::string> corrections = xml_corrector(xmlfile);
    std::string strrr;
    for (std::vector<std::string>::const_iterator i = corrections.begin(); i != corrections.end(); ++i)
        strrr+= *i;
    QString s3 = QString::fromLocal8Bit(strrr);
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setPlainText(s3.toLocal8Bit());
}

//graph button
void MainWindow::on_pushButton_9_clicked(){
    std:: ofstream dotinput("test.dot");
    QString s2 = ui->textBrowser->toPlainText();
    std::string input1 = s2.toLocal8Bit().constData();
    std::ofstream temp("temp1.xml");
    temp << input1;
    temp.close();
    std::ifstream inputFile("temp1.xml");
    std:: ofstream temp3("middle.xml");
    std:: ofstream outputFile("output2.xml");
    temp3 << Minify2(inputFile, outputFile);
    temp3.close();
    std:: ifstream temp2("middle.xml");
    outputFile << Parser(temp2, outputFile);
    temp2.close();
    XML_tree* T1 = new XML_tree();
    std:: ifstream input("output2.xml");
    tree(T1, input);
    Node* root = T1->get_root();
    Graph(dotinput,root);
    dotinput.close();
    QDir::setCurrent("C:\\Users\\20112\\Downloads\\XML3");
    system("dot -Tpng -O test.dot");
    QPixmap p("C:\\Users\\20112\\Downloads\\XML3\\test.dot.png");
    ui->label_2->setPixmap(p);
}
