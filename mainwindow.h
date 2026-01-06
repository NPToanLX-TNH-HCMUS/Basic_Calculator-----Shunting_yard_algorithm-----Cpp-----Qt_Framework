#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <stdexcept>

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
    void on_btn_equal_clicked();
    void on_btn_clear_clicked();
    void on_btn_off_clicked();
    void on_btn_backspace_clicked();

    // Input numbers
    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_00_clicked();

    // Input operators
    void on_btn_plus_clicked();
    void on_btn_minus_clicked();
    void on_btn_mult_clicked();
    void on_btn_div_clicked();
    void on_btn_pow_clicked();
    void on_btn_fact_clicked();
    void on_btn_open_clicked();
    void on_btn_close_clicked();

    // Trigonometric functions
    void on_btn_sin_clicked();
    void on_btn_cos_clicked();
    void on_btn_ln_clicked();
    void on_btn_tan_clicked();

private:
    Ui::MainWindow *ui;
    QString calculate(std::string s);
    double factorial(double a);
    long long Is_Una_or_Bina(char c);
    bool isSign(char c);
    long long precedence(char c);
};
#endif // MAINWINDOW_H
