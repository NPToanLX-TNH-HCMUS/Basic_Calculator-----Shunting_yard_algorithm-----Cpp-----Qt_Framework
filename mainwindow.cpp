#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream> // To cast numbers to string

using namespace std;
// cout << "\t\t***************************************************************************************" << endl;
// cout << "\t\t**   #####                                                                           **" << endl;
// cout << "\t\t**  #     #     ##    #        ####   #    #  #          ##     ###   ####   #####   **" << endl;
// cout << "\t\t**  #          #  #   #       #    #  #    #  #         #  #     #   #    #  #    #  **" << endl;
// cout << "\t\t**  #         #    #  #       #       #    #  #        #    #    #   #    #  #    #  **" << endl;
// cout << "\t\t**  #         ######  #       #       #    #  #        ######    #   #    #  #####   **" << endl;
// cout << "\t\t**  #     #  #      # #       #    #  #    #  #       #      #   #   #    #  #   #   **" << endl;
// cout << "\t\t**   #####   #      #  ######  ####    ####   ######  #      #   #    ####   #    #  **" << endl;
// cout << "\t\t***************************************************************************************" << endl;
// cout << "\t\t******************************** Ngo Phuoc Toan - HCMUS *******************************" << endl;
// cout << "\t\t***** Operations: + - * / ! ^ sin cos tan ln ------ Numbers: Just integer/long long ***" << endl;
// cout << "\t\t************************ Enter exit or quit to end the calculator *********************" << endl;
// cout << "\t\t*********************** Idea: SHUNTING YARD (Reverse Polish notation) *****************" << endl;
// cout << "\t\t********************* Special Thanks to Mr. Le Ngoc Thanh - HCMUS - VNU ***************" << endl;
// cout << "\t\t******************************** Gemini 2.5 Pro Model *********************************" << endl;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_equal->setShortcut(QKeySequence(Qt::Key_Return));
    ui->btn_clear->setShortcut(QKeySequence(Qt::Key_Escape));
    ui->btn_backspace->setShortcut(QKeySequence(Qt::Key_Backspace));
    ui->btn_0->setShortcut(QKeySequence(Qt::Key_0));
    ui->btn_1->setShortcut(QKeySequence(Qt::Key_1));
    ui->btn_2->setShortcut(QKeySequence(Qt::Key_2));
    ui->btn_3->setShortcut(QKeySequence(Qt::Key_3));
    ui->btn_4->setShortcut(QKeySequence(Qt::Key_4));
    ui->btn_5->setShortcut(QKeySequence(Qt::Key_5));
    ui->btn_6->setShortcut(QKeySequence(Qt::Key_6));
    ui->btn_7->setShortcut(QKeySequence(Qt::Key_7));
    ui->btn_8->setShortcut(QKeySequence(Qt::Key_8));
    ui->btn_9->setShortcut(QKeySequence(Qt::Key_9));
    ui->btn_plus->setShortcut(QKeySequence(Qt::Key_Plus));
    ui->btn_minus->setShortcut(QKeySequence(Qt::Key_Minus));
    ui->btn_mult->setShortcut(QKeySequence(Qt::Key_Asterisk));
    ui->btn_div->setShortcut(QKeySequence(Qt::Key_Slash));
    ui->btn_pow->setShortcut(QKeySequence("^"));
    ui->btn_fact->setShortcut(QKeySequence("!"));
    ui->btn_open->setShortcut(QKeySequence("("));
    ui->btn_close->setShortcut(QKeySequence(")"));
    ui->btn_sin->setShortcut(QKeySequence(Qt::Key_S));
    ui->btn_cos->setShortcut(QKeySequence(Qt::Key_C));
    ui->btn_tan->setShortcut(QKeySequence(Qt::Key_T));
    ui->btn_ln->setShortcut(QKeySequence(Qt::Key_L));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ------------------------------------------ Logical Function C++ ----------------------------------------
double MainWindow::factorial(double a)
{
    // Check negative cases:
    if (a < 0)
    {
        throw runtime_error("Math Error: Factorial of negative number!");
    }
    // Check whether a is an integer
    if (floor(a) != a)
    {
        throw runtime_error("Math Error: Factorial is only defined for integers!");
    }
    if (a <= 1)
    {
        return 1;
    }
    else
    {
        return a * factorial(a - 1);
    }
}

long long MainWindow::Is_Una_or_Bina(char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

bool MainWindow::isSign(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!' || c == 's' || c == 'l' || c == 'c' || c == 't');
}

long long MainWindow::precedence(char c)
{
    // u = unary '-' (negative number)
    // s = sin; c = cos; t = tan; l = ln
    if (c == 'u' || c == '!' || c == 's' || c == 'c' || c == 't' || c == 'l')
        return 10;
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

QString MainWindow::calculate(string s)
{
    queue<char> Postfix;
    stack<char> Sign;
    bool maybeUnary = true;
    // bool Unaryopen = false;
    try
    {
        // ------------------------------------------ STEP 1: INFIX TO POSTFIX -----------------------------------
        for (int i = 0; i < s.length(); i++)
        {
            char ch = s[i];

            if (ch == ' ')
                continue;

            // If it is a digit
            if (isdigit(ch))
            {
                maybeUnary = false; // After a digit, must be a binary operation
                Postfix.push(ch);
                // Check if the next char is a digit. If NOT, push a space to separate numbers.
                // E.g., for number "12":
                // When i is at '1', i+1 is '2' -> do not push space.
                // When i is at '2', i+1 is '+' (or end) -> push space.
                if (i + 1 >= s.length() || !isdigit(s[i + 1]))
                {
                    Postfix.push(' ');
                }
            }

            // If it is a sign?
            else if (isSign(ch))
            {
                //'('
                if (ch == '(')
                {
                    Sign.push(ch);
                    maybeUnary = true; // After a '(', must be a unary operation
                }

                //')'
                else if (ch == ')')
                {
                    bool foundOpen = false;
                    while (!Sign.empty())
                    {
                        if (Sign.top() == '(')
                        {
                            foundOpen = true;
                            Sign.pop();
                            break;
                        }
                        Postfix.push(Sign.top());
                        Postfix.push(' ');
                        Sign.pop(); // Pop '(' out of Sign stack
                    }
                    if (!foundOpen)
                    {
                        throw runtime_error("Syntax Error: Mismatched parentheses !");
                    }
                    maybeUnary = false;
                }

                // Unary '-' and '+'
                else if (maybeUnary && (ch == '+' || ch == '-'))
                {
                    if (ch == '-')
                    {
                        Sign.push('u');
                    }
                    // Unary '+' is skipped as being nonsense
                }

                // Binary Operators:
                // Binary Operators handling:
                else
                {
                    while (!Sign.empty() && Sign.top() != '(')
                    {
                        char top = Sign.top();
                        long long topPrec = precedence(top);
                        long long currPrec = precedence(ch);

                        // Special handling for the Exponentiation operator '^'
                        // Power operator is Right-Associative (e.g., 5^3^2 = 5^(3^2))
                        if (ch == '^')
                        {
                            /* For Right-Associative operators:
               Only pop from stack if the operator on top has STRICTLY HIGHER precedence.
               If top is also '^', we do NOT pop it because the new '^' must be evaluated first.
            */
                            if (topPrec > currPrec)
                            {
                                Postfix.push(top);
                                Postfix.push(' ');
                                Sign.pop();
                            }
                            else
                            {
                                break;
                            }
                        }
                        // Handling for Left-Associative operators (+, -, *, /)
                        else
                        {
                            /* For Left-Associative operators:
               Pop from stack if the operator on top has HIGHER or EQUAL precedence.
               This ensures left-to-right evaluation (e.g., 5-3-1 = (5-3)-1).
            */
                            if (topPrec >= currPrec)
                            {
                                Postfix.push(top);
                                Postfix.push(' ');
                                Sign.pop();
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    // Push the current operator onto the stack
                    Sign.push(ch);
                    maybeUnary = true;
                }
            }
        }

        // Push remaining operators from stack to Postfix queue
        while (!Sign.empty())
        {
            if (Sign.top() == '(')
            {
                throw runtime_error("Syntax Error: Mismatched parentheses !");
            }
            Postfix.push(Sign.top());
            Postfix.push(' ');
            Sign.pop();
        }

        // -----------  Print Postfix expression (Use a temp queue to preserve data) -------------
        // cout << "Postfix: ";
        // queue<char> tempQ = Postfix;
        // while (!tempQ.empty())
        // {
        //     cout << tempQ.front();
        //     tempQ.pop();
        // }
        // cout << endl;
        stack<double> answer;

        // --------------------------------------- STEP 2: EVALUATION -----------------------------------------
        while (!Postfix.empty())
        {
            char current = Postfix.front();
            Postfix.pop();

            if (current == ' ')
                continue;

            // If it's a number:
            if (isdigit(current))
            {
                double num = current - '0';
                // Number parsing logic: Since operators are separated numbers with ' ', read digits until ' ' is found
                while (!Postfix.empty() && isdigit(Postfix.front()))
                {
                    num = num * 10 + (Postfix.front() - '0');
                    Postfix.pop();
                }
                answer.push(num);
            }

            // If it's a sign:
            else if (isSign(current) && Is_Una_or_Bina(current) == 2)
            {
                // Check whether already had enough 2 operand ?
                if (answer.size() < 2)
                {
                    throw runtime_error("Syntax Error: Invalid expression (missing operand)!");
                }
                // If it's enough:
                double val2 = answer.top();
                answer.pop();
                double val1 = answer.top();
                answer.pop();
                double result = 0;
                if (current == '+')
                    result = val1 + val2;
                else if (current == '-')
                    result = val1 - val2;
                else if (current == '*')
                    result = val1 * val2;
                else if (current == '/')
                {
                    // Check divided by 0 !!:
                    if (val2 == 0)
                        throw runtime_error("Math Error: Division by zero!");
                    result = val1 / val2;
                }
                else if (current == '^')
                    result = pow(val1, val2);
                answer.push(result);
            }
            else
            {
                // Check whether already had enough 1 operand ? For example: The expression: *5 - 3 ? ?? ?
                if (answer.empty())
                {
                    throw runtime_error("Syntax Error: Invalid expression (missing operand for unary op)!");
                }
                double val = answer.top();
                answer.pop();
                double result = 0;
                if (current == 'u')
                    result = -val;
                else if (current == '!')
                    result = factorial(val);
                else if (current == 's')
                    result = sin(val);
                else if (current == 'c')
                    result = cos(val);
                else if (current == 't')
                {
                    // Check cos ~ 0 ==> not in the Domain of tan(x)
                    if (abs(cos(val)) < 1e-9)
                        throw runtime_error("Math Error: Tan is undefined !");
                    result = tan(val);
                }
                else if (current == 'l')
                {
                    // Check ln(x) x<=0 ?
                    if (val <= 0)
                        throw runtime_error("Math Error: Logarithm of non-positive number!");
                    result = log(val);
                }
                answer.push(result);
            }
        }
        //------------------------------------------Return answer/Errors (Maybe)----------------------------
        if (answer.empty())
            return "Error";
        double result = answer.top();
        return QString::number(result);
    }
    catch (const std::exception &e)
    {
        return QString("Error: ") + e.what();
    }
    catch (...)
    {
        return "Unknown Error";
    }
}

// ==================== NUMBER GROUP (0-9) ====================
void MainWindow::on_btn_0_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "0"); }
void MainWindow::on_btn_1_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "1"); }
void MainWindow::on_btn_2_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "2"); }
void MainWindow::on_btn_3_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "3"); }
void MainWindow::on_btn_4_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "4"); }
void MainWindow::on_btn_5_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "5"); }
void MainWindow::on_btn_6_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "6"); }
void MainWindow::on_btn_7_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "7"); }
void MainWindow::on_btn_8_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "8"); }
void MainWindow::on_btn_9_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "9"); }
void MainWindow::on_btn_00_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "00"); }

// ==================== BASIC OPERATORS GROUP ====================
void MainWindow::on_btn_plus_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "+"); }
void MainWindow::on_btn_minus_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "-"); }
void MainWindow::on_btn_mult_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "*"); }
void MainWindow::on_btn_div_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "/"); }
void MainWindow::on_btn_pow_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "^"); }
void MainWindow::on_btn_fact_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "!"); }
void MainWindow::on_btn_open_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + "("); }
void MainWindow::on_btn_close_clicked() { ui->displayScreen->setText(ui->displayScreen->text() + ")"); }

// ==================== TRIGONOMETRY & LOGIC GROUP ====================
// Note: s=sin, c=cos, l=ln, t=tan
void MainWindow::on_btn_sin_clicked()
{
    ui->displayScreen->setText(ui->displayScreen->text() + "s(");
}
void MainWindow::on_btn_cos_clicked()
{
    ui->displayScreen->setText(ui->displayScreen->text() + "c(");
}
void MainWindow::on_btn_ln_clicked()
{
    ui->displayScreen->setText(ui->displayScreen->text() + "l(");
}
void MainWindow::on_btn_tan_clicked()
{
    ui->displayScreen->setText(ui->displayScreen->text() + "t(");
}

// ==================== CONTROL GROUP ====================
void MainWindow::on_btn_clear_clicked()
{
    ui->displayScreen->clear();
}
void MainWindow::on_btn_off_clicked()
{
    QApplication::quit();
}
void MainWindow::on_btn_equal_clicked()
{
    QString inputQt = ui->displayScreen->text();
    if (inputQt.isEmpty())
        return;
    std::string inputStd = inputQt.toStdString();
    QString result = calculate(inputStd);
    ui->displayScreen->setText(result);
}
void MainWindow::on_btn_backspace_clicked()
{
    QString text = ui->displayScreen->text();
    if (text.isEmpty())
        return;
    text.chop(1);
    ui->displayScreen->setText(text);
}

//======================================== THE END =====================================
//========================================== NPT =========================================
