/*! @mainpage Cool Calculator Documentation
 *
 * @section abt_sec About
 * @author Dien Nguyen
 * @date 12-04-15
 *
 * @section intro_sec Introduction
 * Provides a simple user interface for the user to input data
 * 		and gets back simple insights.
 *
 *
 * @section instr_sec Instructions
 *
 * @subsection instr1 Importing a file
 * Click "Select File" and choose a .txt file or type the file's directory on the line.
 * Files must satisfy the following requirements:
 * 1. The first line contains how many data sets there are
 * 2. The second line contains how many data points is in each set
 * 3. Every time you start a new data set, use the words "new set"
 * 4. Blank spaces are assumed to be 0's
 * A sample file can be found with the source code.
 * You can review and change the inputs on the next page.
 *
 * @subsection instr2 Manually entering data
 * Input the number of data sets you need and how many data points is in each set.
 * Enter your entries from left to right.
 * Each row represents a different data set.
 *
 * @subsection instr2 Analyze data
 * After making sure you have the right numbers in each
 * data set, click "Done" to get intuition from it.
 */


/** Creates a MainWindow object and gives it to a handler
  *
  * @file main.cpp
  */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
