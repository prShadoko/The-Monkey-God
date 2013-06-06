#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent),
	_ui(new Ui::MainWindow),
	_solver(NULL),
	_thread(new QThread(this))
{
	_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete _ui;
	delete _solver;
	delete _thread;
}

void MainWindow::on_spinBox_matrixSize_valueChanged(int value)
{
	_ui->spinBox_rotationSize->setMaximum(value - 1);
}

void MainWindow::on_pushButton_buildTree_clicked()
{
	_ui->pushButton_buildTree->setEnabled(false);
	_solver = new Solver(2, 2);
	connect(_thread, SIGNAL(started()), _solver, SLOT(buildTree()));
	connect(_thread, SIGNAL(finished()), _solver, SLOT(deleteLater()));
	connect(_thread, SIGNAL(finished()), this, SLOT(buildTreeFinished()));
	_solver->moveToThread(_thread);
	_thread->start();
}

void MainWindow::buildTreeFinished()
{
	_ui->pushButton_buildTree->setEnabled(true);
	_ui->statusbar->showMessage(tr("Building tree finished"));
}
