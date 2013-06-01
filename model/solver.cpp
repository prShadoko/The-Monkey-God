#include "solver.h"

Solver::Solver(qint8 const dimension, qint8 const rotationSize) :
	_tree(new Matrix(dimension, rotationSize))
{
}

Solver::~Solver()
{
	delete _tree;
}

void Solver::buildTree()
{
	QQueue<Matrix *> queue;
	queue.enqueue(_tree);
	Matrix * matrix = NULL;
	Matrix * child = NULL;
	qint8 n = _tree->getDimension() - _tree->getRotationSize() + static_cast<qint8>(1);

	while(!queue.isEmpty())
	{
		matrix = queue.dequeue();
		for(qint8 i=0; i<n; ++i)
		{
			for(qint8 j=0; j<n; ++j)
			{
				CellId topLeftCell = j + i * matrix->getDimension();
				child = new Matrix(matrix, topLeftCell, CW);
				//TODO: check whether the matrix already exists or not
				matrix->addChild(Rotation(topLeftCell, CW), child);
				queue.enqueue(child);

				child = new Matrix(matrix, topLeftCell, CCW);
				//TODO: check whether the matrix already exists or not
				matrix->addChild(Rotation(topLeftCell, CW), child);
				queue.enqueue(child);
			}
		}
	}
}
