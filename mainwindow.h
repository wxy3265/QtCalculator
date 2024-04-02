#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <cmath>
#include <iostream>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_0_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_button_left_clicked();

    void on_button_right_clicked();

    void on_button_back_clicked();

    void on_button_point_clicked();

    void on_button_p_clicked();

    void on_button_min_clicked();

    void on_button_mul_clicked();

    void on_button_d_clicked();

    void on_button_e_clicked();

    void on_button_clear_clicked();

    void on_button_pow_clicked();

    void on_button_square_clicked();

    void on_button_pow_2_clicked();

    void on_button_sqrt_clicked();

    void on_button_A_clicked();

    void on_button_C_clicked();

    void setMode(int tar);

    void on_button_m_clicked();

    void on_button_f_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
