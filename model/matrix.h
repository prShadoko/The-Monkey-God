#ifndef MATRIX_H
#define MATRIX_H

#include <QMap>
#include <QPair>
#include <QtCore/qmath.h>

#include <QtDebug>

enum Direction {CW = 1, CCW = -1};

typedef quint64 HashKey; // Allows 3x3 and 4x4 matrices
typedef qint8 Cell;
typedef QPair<Cell, Direction> Rotation; // For shortness

class Matrix
{
	public:
		//--- Constructor & destructor ---//
		explicit Matrix(qint8 const dimension = 3, qint8 const rotationSize = 2);
		explicit Matrix(Matrix const * const matrix, Rotation rotation);
		~Matrix();

		//--- Accessors ---//
		inline qint8					getDimension()							const { return _dimension; }
		inline qint8					getRotationSize()						const { return _rotationSize; }
		inline Cell const *				getCells()								const { return _cells; }
		inline Matrix const *			getParent()								const { return _parent; }
		inline Rotation					getRotation()							const { return _rotation; }
//		inline QMap<Rotation, Matrix *>	getChildren()							const { return _children; }
//		inline Matrix const *			getChild(Rotation r)					const { return _children.value(r, NULL); }
		inline HashKey					getHash()								const { return _hash; }

		inline void						setParent(Matrix * parent)				{ _parent = parent; }
		inline void						setRotation(Rotation rotation)			{ _rotation = rotation; }
		inline void						addChild(Rotation r, Matrix * child)	{
//			_children.insert(r, child);
			child->setParent(this);
			child->setRotation(Rotation(r.first, static_cast<Direction>(-r.second)));
		}

		//--- Methods ---//
		bool							operator==(Matrix const & other)		const;
		QString							toString() const;
		static HashKey					hash(Cell const * cells, qint8 const dimension = 3);

	private:
		void rotate(Rotation rotation);
		void hash();

		//--- Members ---//
		qint8						_dimension;
		qint8						_rotationSize;
		Cell *						_cells;
		Matrix *					_parent;
		Rotation					_rotation;
//		QMap<Rotation, Matrix *>	_children;
		HashKey						_hash;
};

#endif // MATRIX_H
