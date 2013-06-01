#ifndef MATRIX_H
#define MATRIX_H

#include <QtGlobal>

class Matrix
{
	public:
		enum Direction {CW = 1, CCW = -1};

		//--- Constructor & destructor ---//
		Matrix(qint8 const dimension, qint8 const rotationSize = 2);
		Matrix(Matrix const * const matrix, qint8 const topLeftCell, Direction const direction);

		//--- Accessors ---//
		inline qint8 const		getDimension()		{ return _dimension; }
		inline qint8 const *	getCells()			{ return _cells; }
		inline qint8 const		getRotationSize()	{ return _rotationSize; }

	private:
		//--- Methods ---//
		void rotate(qint8 const topLeftCell, Direction const direction);

		//--- Members ---//
		qint8	_dimension;
		qint8	_rotationSize;
		qint8 *	_cells;
};

#endif // MATRIX_H
