#include "solver.h"

Solver::Solver(qint8 const dimension, qint8 const rotationSize) :
	QObject(NULL),
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
		if(!_explored.contains(matrix->getHash()))
		{
			qDebug() << "matrix";
			matrix->debug();
			_explored.insert(matrix->getHash(), matrix);
			for(qint8 i=0; i<n; ++i)
			{
				for(qint8 j=0; j<n; ++j)
				{
					CellId topLeftCell = j + i * matrix->getDimension();
					Rotation rotation(topLeftCell, CW);
					child = new Matrix(matrix, rotation);
					//				bool b1 = _explored.contains(child->getHash()), b2 = queue.contains(child);
					//				qDebug() << b1 << b2;
					if(!_explored.contains(child->getHash()) && !queue.contains(child))
					{
						matrix->addChild(rotation, child);
						queue.enqueue(child);

						qDebug() << "child CW";
						child->debug();
					}

					rotation = Rotation(topLeftCell, CCW);
					child = new Matrix(matrix, rotation);
					//				b1 = _explored.contains(child->getHash());
					//				b2 = queue.contains(child);
					//				qDebug() << b1 << b2;
					if(!_explored.contains(child->getHash()) && !queue.contains(child))
					{
						matrix->addChild(rotation, child);
						queue.enqueue(child);

						qDebug() << "child CCW";
						child->debug();
					}
				}
			}
		}
	}
}
