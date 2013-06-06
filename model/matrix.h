#ifndef MATRIX_H
#define MATRIX_H

#include <QMap>
#include <QPair>
#include <QtCore/qmath.h>

#include <QtDebug>

enum Direction {CW = 1, CCW = -1};

typedef qint8 CellId; // Allows 15x15 matrix (225 cells)
typedef QPair<CellId, Direction> Rotation; // For shortness

class Matrix
{
	public:
		//--- Constructor & destructor ---//
		explicit Matrix(qint8 const dimension, qint8 const rotationSize = 2);
		explicit Matrix(Matrix const * const matrix, Rotation rotation);
		~Matrix();

		//--- Accessors ---//
		inline qint8					getDimension()							const { return _dimension; }
		inline qint8					getRotationSize()						const { return _rotationSize; }
		inline CellId const *			getCells()								const { return _cells; }
		inline Matrix const *			getParent()								const { return _parent; }
		inline QMap<Rotation, Matrix *>	getChildren()							const { return _children; }
		inline Matrix const *			getChild(Rotation r)					const { return _children.value(r, NULL); }
		inline quint64					getHash()								const { return _hash; }

		inline void						setParent(Matrix * parent)				{ _parent = parent; }
		inline void						addChild(Rotation r, Matrix * child)	{
			_children.insert(r, child);
			child->setParent(this);
		}

		//--- Methods ---//
		bool							operator==(Matrix const & other)		const;
		void debug() const;

	private:
		void rotate(Rotation rotation);
		void hash();

		//--- Members ---//
		qint8						_dimension;
		qint8						_rotationSize;
		CellId *					_cells;
		Matrix *					_parent;
		QMap<Rotation, Matrix *>	_children;
		quint64						_hash;
};

#endif // MATRIX_H
