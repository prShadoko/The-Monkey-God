#ifndef NODE_H
#define NODE_H

class Node
{
	public:
		enum Direction {CW, CCW};
		Node(qint32 const dimension, qint32 const rotationSize = 2);
		Node(Node const * const node, qint32 const topLeftCell, Direction const direction);

		inline qint32 const dimension() { return _dimension; }
		inline qint32 const * cells() { return _cells; }
		inline qint32 const rotationSize() { return _rotationSize; }
		inline void cell(qint32 const cell, qint32 const value) { _cells[cell] = value; }

	private:
		void rotate(qint32 const topLeftCell, Direction const direction);

		qint32 _dimension;
		qint32 * _cells;
		qint32 _rotationSize;
};

#endif // NODE_H
