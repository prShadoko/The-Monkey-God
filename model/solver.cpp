#include "solver.h"

Solver::Solver(qint8 const dimension, qint8 const rotationSize) :
	QThread(NULL),
	_tree(new Matrix(dimension, rotationSize)),
	_mutex(new QMutex())
{
	QMutexLocker locker(_mutex);
	_aborted = false;
}

Solver::~Solver()
{
	abort();
	delete _tree;
	delete _mutex;
}

void Solver::run()
{
	quint32 step = 0;
	QQueue<Matrix *> queue;
	queue.enqueue(_tree);
	Matrix * matrix = NULL;
	Matrix * child = NULL;
	qint8 n = _tree->getDimension() - _tree->getRotationSize() + static_cast<qint8>(1);

	while(!queue.isEmpty() && !isAborted())
	{
		matrix = queue.dequeue();
		if(!_explored.contains(matrix->getHash()))
		{
			++step;
			emit progress(step);
//			qDebug() << "matrix";
//			matrix->debug();
			_explored.insert(matrix->getHash(), matrix);
			for(qint8 i=0; i<n; ++i)
			{
				for(qint8 j=0; j<n; ++j)
				{
					CellId topLeftCell = j + i * matrix->getDimension();
					Rotation rotation(topLeftCell, CW);
					child = new Matrix(matrix, rotation);
					if(!_explored.contains(child->getHash()))
					{
						matrix->addChild(rotation, child);
						queue.enqueue(child);

//						qDebug() << "child CW";
//						child->debug();
					}

					rotation = Rotation(topLeftCell, CCW);
					child = new Matrix(matrix, rotation);
					if(!_explored.contains(child->getHash()))
					{
						matrix->addChild(rotation, child);
						queue.enqueue(child);

//						qDebug() << "child CCW";
//						child->debug();
					}
				}
			}
		}
	}
}
