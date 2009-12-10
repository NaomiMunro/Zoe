#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QVector>
#include <QByteArray>

class Cell
{
public:
	Cell();
	QColor colour();
	QColor edgeColour();
	int energy();
	int setEnergy();
	
	
private:
	QByteArray photoGene;
	QVector<int> mEdgeColour;
	int m_energy;
	
};

#endif
