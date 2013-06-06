#include <view/mainwindow.h>
#include <QApplication>

#include <model/solver.h>
//#include <model/matrix.h>
#include <iostream>

int main(int argc, char *argv[])
{
	/* Testing Matrix class
	Matrix m(3, 2);
	Matrix m2(&m, 0, CW);
	Matrix m3(&m2, 4, CCW);

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
		std::cout << " " << (int)m.getCells()[j+i*3];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
		std::cout << " " << (int)m2.getCells()[j+i*3];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
		std::cout << " " << (int)m3.getCells()[j+i*3];
		}
		std::cout << std::endl;
	}

	std::cout << m.getHash() << std::endl;
	std::cout << m2.getHash() << std::endl;
	std::cout << m3.getHash() << std::endl;
	//*/

	/* Testing Solver class
	Solver s(3, 2);
	s.buildTree();
	Matrix const * m = s.getTree();
	while((m = const_cast<Matrix *>(m->getChild(Rotation(4, CW)))) != NULL)
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
			std::cout << " " << (int)m->getCells()[j+i*3];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	//*/

	//*
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
	//*/
}
