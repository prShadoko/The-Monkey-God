#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QSpinBox>
#include <QThread>

#include <model/solver.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget * parent = NULL);
		~MainWindow();

	private slots:
		void on_pushButton_buildTree_clicked();
		void buildTreeFinished();
		void on_pushButton_randomize_clicked();
		void on_pushButton_resolve_clicked();
		void on_pushButton_showStats_clicked();

	private:
		Ui::MainWindow *	_ui;
		Solver *			_solver;
		QProgressBar *		_progressBar;
		QList<QSpinBox *>	_spinBoxes;
};

#endif // MAINWINDOW_H
