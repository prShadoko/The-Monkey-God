#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
		void on_spinBox_matrixSize_valueChanged(int value);
		void on_pushButton_buildTree_clicked();
		void buildTreeFinished();

	private:
		Ui::MainWindow *	_ui;
		Solver *			_solver;
		QThread	*			_thread;
};

#endif // MAINWINDOW_H
