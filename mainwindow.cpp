/** Implements the functions in the mainwindow class
 *  @file mainwindow.cpp
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculator.h"
#include <QString>
#include <QObject>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

/** Allows user to brows their computer to get a file
 *  links the "Select File" button with the text line */
void MainWindow::get_file_path()
{
    QString file_directory = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), "All Files (*.*);;Text Files (*.txt)");
    ui->directory_line->setText(file_directory);
}

/** Tries to make a calculator from the file inputted by user */
void MainWindow::start_with_file()
{
   QString file_directory = ui->directory_line->text();

   // text line is empty
   if (file_directory.isEmpty())
   {
       QLabel* error_label = new QLabel("Please choose a file");
       error_label->show();
   }
   else
   {
       QWidget* current = this->centralWidget();

       calc = new Calculator(this, file_directory);
       this->setCentralWidget(calc);

       current->setParent(nullptr);
   }
}

/** Gets the numbers inputted by user and creates a calculator with it */
void MainWindow::start_with_entry()
{
   QString data_sets = ui->sets->text();
   QString data_entries = ui->entries->text();
   size_t sets = data_sets.toInt();
   size_t entries = data_entries.toInt();

   QWidget* current = this->centralWidget();

   calc = new Calculator(this, sets, entries);
   this->setCentralWidget(calc);

   current->setParent(nullptr);
}

/** Provides user with instructions on how to use Cool Calculator */
void MainWindow::show_instructions()
{
    // how to import a file
    QLabel* importing_file = new QLabel();
    QString file_entry = "How to import a file:\n";
    file_entry += "Click \"Select File\" and choose a .txt file or type the file's directory on the line.\n\n";
    file_entry += "Files must satisfy the following requirements:\n";
    file_entry += "1. The first line contains how many data sets there are\n";
    file_entry += "2. The second line contains how many data points is in each set\n";
    file_entry += "3. Every time you start a new data set, use the words \"new set\"\n";
    file_entry += "4. Blank spaces are assumed to be 0's\n";
    file_entry += "A sample file can be found with the source code.\n";
    file_entry += "You can review and change the inputs on the next page.\n\n";
    importing_file->setText(file_entry);

    // how to manually enter data
    QLabel* entering_data = new QLabel();
    QString data_entry = "How to manually enter data:\n";
    data_entry += "Input the number of data sets you need and how many data points is in each set.\n";
    data_entry += "Enter your entries from left to right.\n";
    data_entry += "Each row represents a different data set.\n\n";
    entering_data->setText(data_entry);

    // how to analyze data
    QLabel* analyzing_data = new QLabel();
    QString analyze_data = "How to analyze data:\n";
    analyze_data += "After making sure you have the right numbers in each\n";
    analyze_data += "data set, click \"Done\" to get intuition from it";
    analyzing_data->setText(analyze_data);

    // putting everything together
    QVBoxLayout* main_layout = new QVBoxLayout();
    main_layout->addWidget(importing_file);
    main_layout->addWidget(entering_data);
    main_layout->addWidget(analyzing_data);
    QWidget* instructions_window = new QWidget();
    instructions_window->setLayout(main_layout);
    instructions_window->setWindowTitle("Cool Calculator Instructions");
    instructions_window->show();
}

/** Frees memory by setting its parent to nullptr */
MainWindow::~MainWindow()
{
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    delete ui;
}
