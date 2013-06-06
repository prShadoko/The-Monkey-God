#ifndef SOLVER_H
#define SOLVER_H

#include <QMutex>
#include <QQueue>
#include <model/matrix.h>

#include <QtDebug>

class Solver : public QObject
{
	Q_OBJECT

	public:
		//--- Constructor & destructor ---//
		explicit Solver(qint8 const dimension, qint8 const rotationSize);
		~Solver();

		//--- Accessors ---//
		inline Matrix const * getTree() const { return _tree; }

	public slots:
		void buildTree();

	private:
		Matrix *				_tree;
		QMap<quint64, Matrix *>	_explored;
};

#endif // SOLVER_H
