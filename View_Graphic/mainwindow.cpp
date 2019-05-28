#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Интерполяция"));
    ui->groupBox->setTitle(tr("График"));
    ui->comboBox->addItem(tr("Линейная"), 0);
    ui->comboBox->addItem(tr("Кубический сплайн"), 1);

    ui->comboBox->setCurrentIndex(0);
    index = 0;

    vector<pair<double, double>> points = {{-1, 0.756802495}, {-0.5, -0.909297427}, {0, 0}, {0.5, 0.909297427}, {1, -0.756802495}};
    inter.push_back(shared_ptr<Interpolation>(new LinearInterpolation(points)));
    inter.push_back(shared_ptr<Interpolation>(new CubicSplineInterpolation(points)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// show method
void MainWindow::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    //------------------------------------

    // Рисуем график y=x*x
    // Сгенерируем данные
    // Для этого создадим два массива точек:
    // один для созранения x координат точек,
    // а второй для y соответственно

    double a = inter[index]->getLowerBoundArgument(); // Начало интервала, где рисуем график по оси Ox
    double b = inter[index]->getUpperBoundArgument(); // Конец интервала, где рисуем график по оси Ox
    double h = 0.01; // Шаг, с которым будем пробегать по оси Ox

    int N = (b-a) / h + 2; // Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N), y(N); // Массивы координат точек

    // Вычисляем наши данные
    int i=0;
    for (double X = a; X <= b; X += h)// Пробегаем по всем точкам
    {
        x[i] = X;
        y[i] = inter[index]->getFunction(X);// Формула нашей функции
        i++;
    }
    ui->widget->clearGraphs(); // Если нужно, но очищаем все графики
    // Добавляем один график в widget
    ui->widget->addGraph();
    // Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);

    // Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    // Установим область, которая будет показываться на графике
    ui->widget->xAxis->setRange(a, b); //  Для оси Ox

    // Для показа границ по оси Oy сложнее, так как надо по правильному
    // вычислить минимальное и максимальное значение в векторах
    double minY = y[0], maxY = y[0];
    for (int i = 1; i < N; i++)
    {
        if (y[i] < minY) minY = y[i];
        if (y[i] > maxY) maxY = y[i];
    }
    ui->widget->yAxis->setRange(minY, maxY); // Для оси Oy

    // И перерисуем график на нашем widget
    ui->widget->replot();
}

void MainWindow::on_comboBox_currentIndexChanged(int i)
{
    index = i;
}
