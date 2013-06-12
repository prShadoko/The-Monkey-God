#include "matrix.h"

Matrix::Matrix(qint8 const dimension, qint8 const rotationSize) :
	_level(0),
	_dimension(dimension),
	_rotationSize(rotationSize),
	_cells(new Cell[dimension*dimension]),
	_parent(NULL)
{
	for(Cell cell=0; cell<dimension*dimension; ++cell)
	{
		_cells[cell] = cell;
	}
	hash();
}

Matrix::Matrix(Matrix const * const matrix, Rotation rotation) :
	_level(matrix->getLevel() + 1),
	_dimension(matrix->getDimension()),
	_rotationSize(matrix->getRotationSize()),
	_cells(new Cell[matrix->getDimension() * matrix->getDimension()])
{
	Cell const * cells = matrix->getCells();
	for(Cell cell=0; cell<matrix->getDimension()*matrix->getDimension(); ++cell)
	{
		_cells[cell] = cells[cell];
	}
	rotate(rotation);
	hash();
}

Matrix::~Matrix()
{
	delete _cells;
}

bool Matrix::operator==(Matrix const & other) const
{
	return other.getHash() == _hash;
}

HashKey Matrix::hash(Cell const * cells, qint8 const dimension)
{
	HashKey h = 0;
	qint8 n = dimension * dimension;
	for(Cell i=0; i<n-1; ++i)
	{
		h += qPow(n, i) * cells[i];
	}
	return h;
}


void Matrix::rotate(Rotation rotation)
{
	Cell topLeftCell = rotation.first;
	Direction direction = rotation.second;
	qint8 increment[4] = {static_cast<qint8>(1), static_cast<qint8>(_dimension), static_cast<qint8>(-1), static_cast<qint8>(-_dimension)};
	Cell tmp = _cells[topLeftCell];
	Cell previousCell = topLeftCell;
	Cell cell = topLeftCell;

	switch(direction){
		case CW:
			for(qint8 i = 3; i>=0; --i)
			{
				for(qint8 j=1; j<_rotationSize; ++j)
				{
					previousCell = cell;
					cell -= increment[i];
					_cells[previousCell] = _cells[cell];
				}
			}
			_cells[previousCell] = tmp;
			break;
		case CCW:
			for(qint8 i = 0; i<4; ++i)
			{
				for(qint8 j=1; j<_rotationSize; ++j)
				{
					previousCell = cell;
					cell += increment[i];
					_cells[previousCell] = _cells[cell];
				}
			}
			_cells[previousCell] = tmp;
			break;
	}
}

void Matrix::hash()
{
	_hash = Matrix::hash(_cells, _dimension);
}

QString Matrix::toString() const
{
	QString s;
	for(qint8 i=0; i<_dimension; ++i)
	{
		for(qint8 j=0; j<_dimension; ++j)
		{
			s += QString::number(_cells[j + i * _dimension] + 1) + " ";
		}
		s.chop(1);
		s += "\n";
	}
	return s;
}
