#include "matrix.h"

Matrix::Matrix(qint8 const dimension, qint8 const rotationSize) :
	_dimension(dimension),
	_cells(new qint8[dimension*dimension]),
	_rotationSize(rotationSize)
{
	for(qint32 cell=0; cell<dimension*dimension; ++cell)
	{
		_cells[cell] = cell;
	}
}

Matrix::Matrix(Matrix const * const matrix, qint8 const topLeftCell, Direction const direction) :
	_dimension(matrix->dimension()),
	_cells(new qint8[dimension*dimension]),
	_rotationSize(matrix->rotationSize)
{
	qint8 * cells = matrix->cells();
	for(qint8 cell=0; cell<dimension*dimension; ++cell)
	{
		_cells[cell] = cells[cell];
	}
	rotate(topLeftCell, direction);
}

Matrix::~Matrix()
{
	delete[] _cells;
	delete[] _rotations;
}

void Matrix::rotate(qint8 const topLeftCell, Direction const direction)
{
	qint8 increment[4] = {1, _dimension, -1, -_dimension};
	qint8 tmp = _cells[topLeftCell];
	qint8 previousCell;
	qint8 cell = topLeftCell;

	switch(direction){
		case CW:
			for(qint8 i = 3; i>=0; --i)
			{
				for(qint8 j=1; j<_rotationSize; ++j)
				{
					previousCell = cell;
					cell += increment[i];
					_cells[previousCell] = cell;
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
					_cells[previousCell] = cell;
				}
			}
			_cells[previousCell] = tmp;
			break;
	}


}
