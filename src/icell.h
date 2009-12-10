#ifndef ICELL_H
#define ICELL_H

#include "environment.h"
#include "cellaction.h"
#include "kdebug.h"

#include <QColor>
#include <QVector>
#include <QByteArray>

class ICell
{
public:
	ICell(Environment *env);
	ICell();
	virtual ~ICell() {};
	virtual QColor colour();
	QColor edgeColour();
	QColor getFillColour() { return mColour; };
	QVector<int> getEdgeColour() { return mEdgeColour; };
	virtual double energy();
	virtual void expressGenes() {};
	void updateNeighbours(QVector< QVector<Zoe::neighbours> >);
	int age() { return m_age; };
	void incrementAge() { m_age++; };
	virtual CellAction act();
	virtual ICell * reproduce() { return new ICell(m_enviro); };
	void setEnvironment(Environment *env) { m_enviro = env; };
	int cellID() { return m_cellID; };
	virtual void setColour(QColor) {};
	
protected:
	int m_cellID;
	QColor mColour;
	QVector<int> mEdgeColour;
	Environment * m_enviro;
	double m_energy;
	QVector< QVector<Zoe::neighbours> > m_neighbours;
	int m_age;
	static int lastAssignedID;
	
	
};

#endif
