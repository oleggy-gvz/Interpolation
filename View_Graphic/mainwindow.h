#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "../Types/Interpolation.h"
#include "../Types/LinearInterpolation.h"
#include "../Types/CubicSplineInterpolation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    vector<shared_ptr<Interpolation>> inter;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showEvent(QShowEvent* event);
    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
