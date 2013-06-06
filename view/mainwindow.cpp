#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
	QMainWindow(parent),
	_ui(new Ui::MainWindow),
	_solver(NULL),
	_progressBar(new QProgressBar())
{
	_ui->setupUi(this);
	_progressBar->setMinimum(0);
	_progressBar->setMaximum(Solver::NB_MATRICES);
	_ui->statusbar->addPermanentWidget(_progressBar);
	_progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
	delete _ui;
	delete _solver;
}

void MainWindow::on_pushButton_buildTree_clicked()
{
	_ui->pushButton_buildTree->setEnabled(false);
	_solver = new Solver(3, 2);
	_progressBar->setVisible(true);
	connect(_solver, SIGNAL(progress(int)), _progressBar, SLOT(setValue(int)));
	connect(_solver, SIGNAL(finished()), this, SLOT(buildTreeFinished()));
	_solver->start();
}

void MainWindow::buildTreeFinished()
{
	_progressBar->setVisible(false);
	_ui->pushButton_buildTree->setEnabled(true);
	_ui->statusbar->showMessage(tr("Building tree finished"));
	_ui->pushButton_resolve->setEnabled(true);
}
