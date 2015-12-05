/** Class mainwindow, in conjunction with mainwindow.ui, allows the user
 *  to input data. There are two ways to do this:
 *  	1) Open a file
 *  	2) Enter it manually by initially asking for the layout
 *
 *  @file mainwindow.h
 *  @brief Creates the initial window for the user to interact with.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "calculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void get_file_path();
    void start_with_entry();
    void start_with_file();
    void show_instructions();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Calculator* calc;
};

#endif // MAINWINDOW_H
