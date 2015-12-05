/** Class Calculator creates and displays the GUI that allow
 *  the user to input data. It also calculates the insights.
 *  These include mean, standard deviation, and percent change
 *
 *  @file calculator.h
 *  @brief Makes a calculator to analyze data
 */

#ifndef CALCULATOR
#define CALCULATOR

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <vector>
#include <QObject>
#include <QString>
#include <QDir>


namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT


public slots:
    void calculate();

public:
    explicit Calculator(QWidget *parent = 0, size_t sets = 2, size_t entries = 5);
    explicit Calculator(QWidget *parent = 0, QString file_directory = QDir::currentPath() + "sample.txt");
    ~Calculator();



private:
    void gather_data();
    void display_objects();

    QWidget* table;
    QGridLayout* tabs;
    QPushButton* done_button;
    size_t m_rows;
    size_t m_cols;
    QLineEdit** textboxs;
    QWidget* insights_window;
    QWidget* correlation_matrix_window;

    std::vector<double> data;

};


#endif // CALCULATOR
