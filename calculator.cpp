/** Implements the functions in the Calculator class
 *  @file calculator.cpp
 */

#include "calculator.h"
#include "mainwindow.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QString>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <vector>

/** Creates the layout of the table for the user to input data
 * @param parent is a pointer to the object handling the calculator's memory
 * @param sets is how many data sets the user wants
 * @param entries is how many entries is in each set
 */
Calculator::Calculator(QWidget *parent, size_t sets, size_t entries)
    :m_rows(sets), m_cols(entries)
{
    data.resize(m_rows*m_cols);
    table = new QWidget;

    // making the table of QLineEdits
    tabs =  new QGridLayout(table);
    tabs->setGeometry(QRect());
    tabs->setSpacing(0);
    textboxs = new QLineEdit*[m_rows * m_cols];
    for(size_t i=0;i<m_rows;i++) {
        for(size_t j=0;j<m_cols;j++) {
            textboxs[i*m_cols+j] = new QLineEdit;
            tabs -> addWidget(textboxs[i*m_cols+j] ,i,j+1);
        }
    }

    display_objects();
}

/** Creates the calculator froma file
 * @param parent is a pointer to the object handling the calculator's memory
 * @param file_directory is the directory of the file including the data
 */
Calculator::Calculator(QWidget *parent, QString file_directory)
{
    QFile input_file(file_directory);

    // can't open file
    if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QLabel* error = new QLabel("Error, can't open this file!", this);
    }

    else
    {
        QTextStream file(&input_file);
        size_t line_number = 0, row = -1, col = -1;
        QString num;
        while (!file.atEnd())
        {
            line_number++;
            QString line = file.readLine();
            if (line_number == 1)
                m_rows = line.toInt();

            // have enough information to create tables
            else if (line_number == 2)
            {
                m_cols = line.toInt();
                // making the table of QLineEdits
                data.resize(m_rows*m_cols);
                table = new QWidget;
                tabs =  new QGridLayout(table);
                tabs->setGeometry(QRect());
                tabs->setSpacing(0);
                textboxs = new QLineEdit*[m_rows * m_cols];
                for(size_t i=0;i<m_rows;i++)
                {
                    for(size_t j=0;j<m_cols;j++)
                    {
                        textboxs[i*m_cols+j] = new QLineEdit;
                        tabs -> addWidget(textboxs[i*m_cols+j] ,i,j+1);
                    }
                }
            }

            // start getting data from file
            else
            {
                if(line == "new set")
                {
                    row++;
                    col = 0;
                }
                else
                {
                    num = QString::number(line.toDouble());
                    textboxs[row*m_cols+col]->setText(num);
                    col++;
                }
            }
        }
        input_file.close();
        display_objects();
    }
}

/** Creates the layout of the information input screen by making a row x cols table */
void Calculator::display_objects()
{
    // links the tabs to the table
    table->setLayout(tabs);

    // making the done button
    done_button = new QPushButton("Done");
    QObject::connect(done_button, SIGNAL(clicked()), this, SLOT(calculate()));

    // making the side label
    QLabel* side = new QLabel("Sets");
    side->setAlignment(Qt::AlignHCenter);

    // making the top label
    QLabel* top = new QLabel("Entries (Enter them accross in terms of real numbers)");
    top->setAlignment(Qt::AlignHCenter);
    top->setFixedHeight(20);

    // putting the labels into the table
    tabs->addWidget(side, m_rows/2, 0);

    // putting everything together
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(top);
    main_layout->addWidget(table);
    main_layout->addWidget(done_button);
    this->setLayout(main_layout);
}

/** Gets the data from the textboxes and put them in an array */
void Calculator::gather_data() {
    for(size_t i=0;i<m_rows;i++) {
        for(size_t j=0;j<m_cols;j++) {
            data[i*m_cols+j] = textboxs[i*m_cols+j]->text().toDouble();
        }
    }
}

/** Makes a new widget and displays some insights gained in the process
 *  Currently has mean, standard deviation, and percent change implemented
 */
void Calculator::calculate()
{
    // gather the data
    gather_data();

    // process data

    insights_window = new QWidget;
    QLabel* top = new QLabel("Insights:");
    QVBoxLayout* info_layout = new QVBoxLayout;
    info_layout->addWidget(top);

    // do the calculations for mean, standard deviation, and percent change
    std::vector<double> sum, sq_sum, mean, std_dev, percent_change;
    for (size_t i = 0; i < m_rows; ++i) {
        auto begin = data.begin() + i * m_cols;
        auto end = begin + m_cols;
        sum.push_back(std::accumulate(begin , end, 0.0));
        mean.push_back(sum[i]/m_cols);
        sq_sum.push_back(std::inner_product(begin, end, begin, 0.0));
        std_dev.push_back(std::sqrt(sq_sum[i] / m_cols - mean[i] * mean[i]));
        percent_change.push_back((data[i*m_cols+m_cols-1] - data[i*m_cols]) / data[i*m_cols] * 100);

    // putting the labels into the Insights window
        QLabel* result = new QLabel;
        QString a = "";
        a += "Data Set " + QString::number(i+1) + " \n";
        a += "Mean: " + QString::number(mean[i]) + '\n';
        a += "Standard Deviation: " + QString::number(std_dev[i]) + '\n';
        a += "Percent Change: " + QString::number(percent_change[i]) + '%' + '\n';
        a += '\n';
        result->setText(a);
        info_layout->addWidget(result);
    }

    insights_window->setLayout(info_layout);
    insights_window->show();
}

/** Frees memory */
Calculator::~Calculator()
{
    insights_window->setParent(nullptr);
}
