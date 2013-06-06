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
		explicit Solver(qint8 const dimension, qint8 const rotationSize);
		~Solver();

		//--- Accessors ---//
		inline Matrix const *	getTree() const { return _tree; }
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
		QMap<quint64, Matrix *>	_explored;
		QMutex *				_mutex;
		bool					_aborted;
};

#endif // SOLVER_H
