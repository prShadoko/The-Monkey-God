#include "node.h"

Node::Node(qint32 const dimension, qint32 const rotationSize) :
	_dimension(dimension),
	_cells(new qint32[dimension*dimension]),
	_rotationSize(rotationSize)
{
	for(qint32 cell=0; cell<dimension*dimension; ++cell)
	{
		_cells[cell] = cell;
	}
}

Node::Node(Node const * const node, qint32 const topLeftCell, Direction const direction) :
	_dimension(node->dimension()),
	_cells(new qint32[dimension*dimension]),
	_rotationSize(node->rotationSize)
{
	qint32 * cells = node->cells();
	for(qint32 cell=0; cell<dimension*dimension; ++cell)
	{
		_cells[cell] = cells[cell];
	}
	rotate(topLeftCell, direction);
}

Node::~Node()
{
	delete[] _cells;
	delete[] _rotations;
}

void Node::rotate(qint32 const topLeftCell, Direction const direction)
{
	qint32 tmp = _cells[topLeftCell];
	switch(direction){
	case CW:
		//TODO
		break;
	case CCW:
		//TODO
		break;
	}
}
