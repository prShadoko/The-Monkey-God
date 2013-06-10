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

	foreach(QSpinBox * sb, _spinBoxes)
	{
		connect(sb, SIGNAL(valueChanged(int)), this, SLOT(checkMatrix(int)));
	}
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
//	_ui->pushButton_buildTree->setEnabled(true);
	_ui->pushButton_resolve->setEnabled(true);
	_ui->statusbar->showMessage(tr("Building tree finished"));

	QString result;
	result += tr("Possible matrices : ") + QString::number(_solver->getPossibleMatricesCount()) + "\n";
	result += tr("Solvable matrices : ") + QString::number(_solver->getSolvableMatricesCount()) + "\n";
	result += tr("Unsolvable matrices : ") + QString::number(_solver->getPossibleMatricesCount() - _solver->getSolvableMatricesCount()) + "\n";
	result += tr("Max. step count to solve : ");//TODO
	_ui->textEdit->setText(result);
	checkMatrix(0);
}

void MainWindow::checkMatrix(int)
{
	/*
	QMap<qint8, QSpinBox *> checked;
	QList<qint8>  marked;
	foreach(QSpinBox * sb, _spinBoxes)
	{
		qint8 v = static_cast<qin8>(sb->value());
		if(checked.contains(v))
		{
			marked << v;
		}
		checked.insertMulti(v, sb);
	}
	foreach(qint8 v, marked)
	{
		QList<QSpinBox *> m = checked.values(v);
		foreach(QSpinBox * sb, m)
		{
			QPalette palette = sb->palette();
			palette.setColor(QPalette::Background, Qt::red);
			sb->setPalette();
		}
	}
	//*/
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
	qint8 stepCount = -1;
	delete[] cells;

	QString s;
	while(m != NULL)
	{
		s += m->toString() + "\n";
		m = m->getParent();
		stepCount++;
	}
	s += tr("Problem solved in %n step(s)", "", stepCount);
//	s += //TODO: sequence to solve the problem

	_ui->textEdit->setText(s);
}
