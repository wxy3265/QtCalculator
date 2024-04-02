#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculate.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->Table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser->setFontPointSize(9);
    QTextCursor  cursor = ui->textBrowser->textCursor();
    cursor.select(QTextCursor::Document);
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignRight);
    cursor.setBlockFormat(format);
    cursor.clearSelection();
    ui->textBrowser->setTextCursor(cursor);
}

MainWindow::~MainWindow() {
    delete ui;
}
const int NORMAL = 0;
const int PER = 1;
const int COM = 2;
const int MAT = 3;

QString input = "";
QString result = "";

int mode = NORMAL;
int state = 0;
int num1 = 0, num2 = 0;
int matSize = 0;

vector<vector<double>> det;

void MainWindow:: setMode(int tar) {
    mode = tar;
    input = result = "";
    state = 0;
    num1 = num2 = 0;
    matSize = 0;
    det.clear();
    bool flag = false;
    if (tar == NORMAL) {
        ui->Table->setText("普通模式");
        flag = false;
    } else if (tar == PER) {
        ui->Table->setText("排列数模式");
        flag = true;
    } else if (tar == COM) {
        ui->Table->setText("组合数模式");
        flag = true;
    } else if (tar == MAT) {
        ui->Table->setText("行列式模式");
        flag = true;
    }
    if (flag) {
        ui->button_e->setText("OK");
        ui->button_clear->setText("普通模式");
    }
    else {
        ui->button_e->setText("=");
        ui->button_clear->setText("C");
    }
    ui->button_p->setDisabled(flag);
    ui->button_min->setDisabled(flag);
    ui->button_mul->setDisabled(flag);
    ui->button_d->setDisabled(flag);
    ui->button_left->setDisabled(flag);
    ui->button_right->setDisabled(flag);
    ui->button_pow->setDisabled(flag);
    ui->button_pow_2->setDisabled(flag);
    ui->button_square->setDisabled(flag);
    ui->button_sqrt->setDisabled(flag);
    ui->button_f->setDisabled(flag);
    ui->textBrowser->setHtml("");
}

void MainWindow::on_button_1_clicked() {
    input += "1";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_2_clicked() {
    input += "2";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_3_clicked() {
    input += "3";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_4_clicked() {
    input += "4";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_5_clicked() {
    input += "5";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_6_clicked() {
    input += "6";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_7_clicked() {
    input += "7";
    ui->textBrowser->setHtml(input);
}


void MainWindow::on_button_8_clicked() {
    input += "8";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_9_clicked() {
    input += "9";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_0_clicked() {
    if (input != "") input += "0";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_left_clicked()
{
    input += "(";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_right_clicked()
{
    input += ")";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_back_clicked()
{
    input.chop(1);
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_point_clicked()
{
    input += ".";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_p_clicked()
{
    input += "+";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_min_clicked()
{
    input += "-";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_mul_clicked()
{
    input += "*";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_d_clicked()
{
    input += "/";
    ui->textBrowser->setHtml(input);
}

void MainWindow::on_button_e_clicked()
{
    if (mode == NORMAL) {
        Calculate calculate(input);
        calculate.calculate();
        result = result.number(calculate.getResult());
        std::cout << calculate.getResult() << ' ' << result.toStdString() << endl;
        input = "";
        ui->textBrowser->setHtml(result);
    } else if (mode == PER || mode == COM) {
        if (state == 0) {
            num1 = input.toInt();
            input = "";
            ui->textBrowser->setText("");
            state++;
        } else if(state == 1) {
            num2 = input.toInt();
            input = "";
            state++;
            ui->textBrowser->setText("");
            QString res;
            Calculate cal("");
            if (mode == PER) {
                res = res.number(cal.A(num1, num2));
            } else if (mode == COM) {
                res = res.number(cal.C(num1, num2));
            }
            setMode(NORMAL);
            ui->textBrowser->setText(res);
        }
    } else if (mode == MAT) {
        cout << "!E@E\n";
        if (state == 0) {
            matSize = input.toInt();
            input.clear();
            ui->textBrowser->setText("");
            state++;
        } else if (state <= matSize * matSize) {
            det[state / matSize][state % matSize] = input.toInt();
            input.clear();
            ui->textBrowser->setText("");
            state++;
        } else {
            setMode(NORMAL);
        }
    }
}


void MainWindow::on_button_clear_clicked()
{
    setMode(NORMAL);
}


void MainWindow::on_button_pow_clicked()
{
    input += "^";
    ui->textBrowser->setHtml(input);
}


void MainWindow::on_button_square_clicked()
{
    input += "^2";
    ui->textBrowser->setHtml(input);
}


void MainWindow::on_button_pow_2_clicked()
{
    input += "!";
    ui->textBrowser->setHtml(input);
}


void MainWindow::on_button_sqrt_clicked()
{
    input += 's';
    ui->textBrowser->setHtml(input);
}


void MainWindow::on_button_A_clicked()
{
    setMode(PER);
}


void MainWindow::on_button_C_clicked()
{
    setMode(COM);
}

void MainWindow::on_pushButton_clicked() {
    ;
}
void MainWindow::on_pushButton_2_clicked() {
    ;
}


void MainWindow::on_button_m_clicked()
{
//    setMode(MAT);
    input += "|";
    ui->textBrowser->setText(input);
}


void MainWindow::on_button_f_clicked()
{
    int pos = input.length() - 1;
    if (pos == 0) {
        input.insert(0, "-");
    } else {
        while (input[pos].isDigit() && pos != 0) {
            pos--;
        }
        if (input[pos] == '-') {
            input.remove(pos, 1);
        }
        else input.insert(pos + 1, "-");
    }
    ui->textBrowser->setHtml(input);
}

