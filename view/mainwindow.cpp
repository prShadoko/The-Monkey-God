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
	_ui->statusbar->addPermanentWidget(_progressBar);
	_progressBar->setVisible(false);

	_spinBoxes << _ui->spinBox_1
			   << _ui->spinBox_2
			   << _ui->spinBox_3
			   << _ui->spinBox_4
			   << _ui->spinBox_5
			   << _ui->spinBox_6
			   << _ui->spinBox_7
			   << _ui->spinBox_8
			   << _ui->spinBox_9;
}

MainWindow::~MainWindow()
{
	delete _ui;
	delete _solver;
}

void MainWindow::on_pushButton_buildTree_clicked()
{
	_ui->pushButton_buildTree->setEnabled(false);
	_solver = new Solver(_ui->spinBox_matrixSize->value(), _ui->spinBox_matrixSize->value()-1);
	_progressBar->setMaximum(_solver->getPossibleMatricesCount());
	_progressBar->setVisible(true);
	connect(_solver, SIGNAL(progress(int)), _progressBar, SLOT(setValue(int)));
	connect(_solver, SIGNAL(finished()), this, SLOT(buildTreeFinished()));
	_solver->start();
}

void MainWindow::buildTreeFinished()
{
	_progressBar->setVisible(false);
	_ui->pushButton_resolve->setEnabled(true);
	_ui->statusbar->showMessage(tr("Building tree finished"));

	QString result;
	result += tr("Possible matrices :\t\t") + QString::number(_solver->getPossibleMatricesCount()) + "\n";
	result += tr("Solvable matrices :\t\t") + QString::number(_solver->getSolvableMatricesCount()) + "\n";
	result += tr("Unsolvable matrices :\t\t") + QString::number(_solver->getPossibleMatricesCount() - _solver->getSolvableMatricesCount()) + "\n";
	result += tr("Max. step count to solve :\t") + QString::number(_solver->getMaxLevel());
	_ui->textEdit->setText(result);
}

void MainWindow::on_pushButton_resolve_clicked()
{
	qint8 dim = _solver->getDimension();
	qint8 nb_cells = dim * dim - 1;
	Cell * cells = new Cell[nb_cells];
	for(qint8 i=0; i<nb_cells; ++i)
	{
		cells[i] = _spinBoxes[i]->value() - 1;
	}
	Matrix const * m = _solver->getNode(Matrix::hash(cells));
	delete[] cells;

	QString s;
	if(m == NULL)
	{
		s += tr("The input matrix is invalid.");
	}
	else
	{
		qint8 stepCount = 0;
		s += m->toString() + "\n";
		while(m->getParent() != NULL)
		{
			s += (m->getRotation().first / dim == 0) ? tr("Top") : tr("Bottom");
			s += "-";
			s += (m->getRotation().first % dim == 0) ? tr("left") : tr("right");
			s += " ";
			s += (m->getRotation().second == CW) ? tr("Clockwise") : tr("Counter-clockwise");
			s += "\n\n";
			m = m->getParent();
			s += m->toString() + "\n";
			stepCount++;
		}
		s += tr("Problem solved in %n step(s)", "", stepCount);
	}

	_ui->textEdit->setText(s);
}
