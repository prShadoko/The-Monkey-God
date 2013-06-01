#ifndef SOLVER_H
#define SOLVER_H

#include <QQueue>
#include <model/matrix.h>

class Solver
{
	public:
		Solver(qint8 const dimension, qint8 const rotationSize);
		~Solver();

		void buildTree();

	private:
		Matrix *	_tree;
};

#endif // SOLVER_H
