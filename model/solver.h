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
		static quint32 const NB_MATRICES = 362880;

		//--- Constructor & destructor ---//
		explicit Solver(qint8 const dimension = 3, qint8 const rotationSize = 2);
		~Solver();

		//--- Accessors ---//
		inline qint8			getDimension()				const { return _tree->getDimension(); }
		inline Matrix const *	getTree()					const { return _tree; }
		inline Matrix const *	getNode(HashKey h)			const { return _findNode.value(h); }
		inline quint64			getSolvableMatricesCount()	const { return _findNode.count(); }
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
		QMap<HashKey, Matrix *>	_findNode;
		QMutex *				_mutex;
		bool					_aborted;
};

#endif // SOLVER_H
