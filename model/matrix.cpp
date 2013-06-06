#include "matrix.h"

Matrix::Matrix(qint8 const dimension, qint8 const rotationSize) :
	_dimension(dimension),
	_rotationSize(rotationSize),
	_cells(new CellId[dimension*dimension])
{
	for(CellId cell=0; cell<dimension*dimension; ++cell)
	{
		_cells[cell] = cell;
	}
	hash();
}

Matrix::Matrix(Matrix const * const matrix, Rotation rotation) :
	_dimension(matrix->getDimension()),
	_rotationSize(matrix->getRotationSize()),
	_cells(new CellId[matrix->getDimension() * matrix->getDimension()])
{
	CellId const * cells = matrix->getCells();
	for(CellId cell=0; cell<matrix->getDimension()*matrix->getDimension(); ++cell)
	{
		_cells[cell] = cells[cell];
	}
	rotate(rotation);
	hash();
}

Matrix::~Matrix()
{
//	delete[] _cells;
	Matrix * del;
	foreach(del, _children)
	{
		delete del;
	}
}

bool Matrix::operator==(Matrix const & other) const
{
	return other.getHash() == _hash;
}

void Matrix::rotate(Rotation rotation)
{
	CellId topLeftCell = rotation.first;
	Direction direction = rotation.second;
	qint8 increment[4] = {static_cast<qint8>(1), static_cast<qint8>(_dimension), static_cast<qint8>(-1), static_cast<qint8>(-_dimension)};
	CellId tmp = _cells[topLeftCell];
	CellId previousCell;
	CellId cell = topLeftCell;

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
{ // Max value = 50625 --> 16 bits
	_hash = 0;
	qint8 n = _dimension * _dimension;
	for(CellId i=0; i<n; ++i)
	{
		_hash += qPow(n, i) * _cells[i];
	}
}

void Matrix::debug() const
{
	qDebug() << _hash;
	for(CellId c; c<_dimension*_dimension; ++c)
	{
		qDebug() << _cells[c];
	}
}
