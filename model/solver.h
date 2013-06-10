#ifndef SOLVER_H
#define SOLVER_H

#include <QMutex>
#include <QMutexLocker>
#include <QQueue>
#include <QThread>
#include <model/matrix.h>

#include <QtDebug>

class Solver : public QThread
{
	Q_OBJECT

	public:
		//--- Constructor & destructor ---//
		explicit Solver(qint8 const dimension = 3, qint8 const rotationSize = 2);
		~Solver();

		//--- Accessors ---//
		inline qint8			getDimension()				const { return _tree->getDimension(); }
		inline Matrix const *	getTree()					const { return _tree; }
		inline Matrix const *	getNode(HashKey h)			const { return _explored.value(h); }
		inline qint32			getPossibleMatricesCount()	const { return _possibleMatricesCount; }
		inline qint32			getSolvableMatricesCount()	const { return _explored.count(); }
		inline bool				isAborted() {
			QMutexLocker locker(_mutex);
			return _aborted;
		}

	public slots:
		inline void abort() {
			QMutexLocker locker(_mutex);
			_aborted = true;
		}

	signals:
		void progress(int step);

	protected:
		void run();

	private:
		Matrix *				_tree;
		QMap<HashKey, Matrix *>	_explored;
		QMutex *				_mutex;
		bool					_aborted;
		qint32					_possibleMatricesCount;
};

#endif // SOLVER_H
