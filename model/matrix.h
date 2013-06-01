#ifndef MATRIX_H
#define MATRIX_H

#include <QMap>
#include <QPair>

typedef qint8 CellId; // For semantic
typedef QPair<CellId, Matrix::Direction> Rotation; // For shortness

class Matrix
{
	public:
		enum Direction {CW = 1, CCW = -1};

		//--- Constructor & destructor ---//
		Matrix(qint8 const dimension, qint8 const rotationSize = 2);
		Matrix(Matrix const * const matrix, CellId const topLeftCell, Direction const direction);

		//--- Accessors ---//
		inline qint8 const						getDimension()				{ return _dimension; }
		inline qint8 const						getRotationSize()			{ return _rotationSize; }
		inline CellId const *					getCells()					{ return _cells; }
		inline Matrix const *					getParent()					{ return _parent; }
		inline QMap<Rotation, Matrix *> const	getChildren()				{ return _children; }

		inline void								setParent(Matrix * parent)	{ _parent = parent; }
		inline void								addChild(Rotation r, Matrix * child)	{
			_children.insert(r, child);
			child->setParent(this);
		}

		//--- Methods ---//

//		?? const hash();

	private:
		//--- Methods ---//
		void rotate(CellId const topLeftCell, Direction const direction);

		//--- Members ---//
		qint8		_dimension;
		qint8		_rotationSize;
		CellId *	_cells;
		Matrix *	_parent;
		QMap<Rotation, Matrix *>	_children;
};

#endif // MATRIX_H
