#include "matrix.h"

Matrix::Matrix(qint8 const dimension, qint8 const rotationSize) :
	_dimension(dimension),
	_cells(new CellId[dimension*dimension]),
	_rotationSize(rotationSize)
{
	for(CellId cell=0; cell<dimension*dimension; ++cell)
	{
		_cells[cell] = cell;
	}
}

Matrix::Matrix(Matrix const * const matrix, CellId const topLeftCell, Direction const direction) :
	_dimension(matrix->dimension()),
	_cells(new CellId[dimension*dimension]),
	_rotationSize(matrix->rotationSize)
{
	CellId * cells = matrix->getCells();
	for(CellId cell=0; cell<dimension*dimension; ++cell)
	{
		_cells[cell] = cells[cell];
	}
	rotate(topLeftCell, direction);
}

Matrix::~Matrix()
{
	delete[] _cells;
	Matrix * del;
	foreach(del, _children)
	{
		delete del;
	}
}

/*
?? const Matrix::hash()
{
	TODO
}
//*/

void Matrix::rotate(CellId const topLeftCell, Direction const direction)
{
	qint8 increment[4] = {1, _dimension, -1, -_dimension};
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
