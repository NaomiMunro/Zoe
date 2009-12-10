#ifndef LIVINGAREA_H
#define LIVINGAREA_H

#include "icell.h"
#include "environment.h"
#include "cellaction.h"

#include <QObject>
#include <QVector>

class LivingArea : public QObject
{

Q_OBJECT

public:
	LivingArea(int, int);

signals:
	void redrawScreen(QVector< QVector<ICell *> >);

public slots:
	void nextGeneration();
	
private:
	void setupWorld();
	bool killDeadCell(int, int);
	bool killOldCell(int, int);
	void killCell(int col, int row);
	QVector< QVector<Zoe::neighbours> > calculateNeighbours(int col, int row);
	void performAction(CellAction, int col, int row);
	bool inBounds(int x, int y);
	//void adjustEnvironment();
	
	int m_xCells;
	int m_yCells;
	QVector< QVector<ICell *> > cellSpace;
	QVector< QVector<Environment *> > enviroSpace;
	int numGenerations;
};

#endif
