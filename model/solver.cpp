#include "solver.h"

Solver::Solver(qint8 const dimension, qint8 const rotationSize) :
	QThread(NULL),
	_maxLevel(0),
	_tree(new Matrix(dimension, rotationSize)),
	_mutex(new QMutex()),
	_possibleMatricesCount(1)
{
	QMutexLocker locker(_mutex);
	_aborted = false;
	for(qint8 i=dimension*dimension; i>1; --i)
	{
		_possibleMatricesCount *= i;
	}
}

Solver::~Solver()
{
	abort();
	foreach(Matrix * m, _explored)
	{
		delete m;
	}
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
			_maxLevel = qMax(_maxLevel, matrix->getLevel());
			for(qint8 i=0; i<n; ++i)
			{
				for(qint8 j=0; j<n; ++j)
				{
					Cell topLeftCell = j + i * matrix->getDimension();
					Rotation rotation(topLeftCell, CW);
					child = new Matrix(matrix, rotation);
//					if(!_explored.contains(child->getHash()))
//					{
						matrix->addChild(rotation, child);
						queue.enqueue(child);

//						qDebug() << "child CW";
//						child->debug();
//					}

					rotation = Rotation(topLeftCell, CCW);
					child = new Matrix(matrix, rotation);
//					if(!_explored.contains(child->getHash()))
//					{
						matrix->addChild(rotation, child);
						queue.enqueue(child);

//						qDebug() << "child CCW";
//						child->debug();
//					}
				}
			}
		}
	}
}
