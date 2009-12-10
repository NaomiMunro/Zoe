#include "icell.h"
#include "zoedata.h"
#include "kdebug.h"

int ICell::lastAssignedID = 0;

ICell::ICell(Environment *env)
	: m_cellID(lastAssignedID + 1),
	  m_enviro(env),
	  m_energy(10),
	  m_age(1),
	  mColour(QColor(rand()%256, rand()%256, rand()%256))
{
	lastAssignedID++;
	mEdgeColour.insert(0, rand() % 256);
	mEdgeColour.insert(1, rand() % 256);
	mEdgeColour.insert(2, rand() % 256);
}

ICell::ICell()
	:	m_cellID(lastAssignedID + 1),
		m_energy(10),
		m_age(1)
{
	lastAssignedID++;
}

QColor ICell::colour()
{
	return mColour;
}

QColor ICell::edgeColour()
{	
	return QColor(mEdgeColour.at(0), mEdgeColour.at(1), mEdgeColour.at(2));
}

void ICell::updateNeighbours(QVector< QVector<Zoe::neighbours> > neighbours)
{
	m_neighbours = neighbours;
}

double ICell::energy()
{
	return m_energy;
}

CellAction ICell::act()
{
	int relativeYPos = 0;
	int relativeXPos = 0;
	if (m_energy > 60)
	{
		int position = rand() % 9;
		int iterations = 0;
		while (m_neighbours[position/3][position%3] != Zoe::occupied  &&
				m_neighbours[position/3][position%3] != Zoe::outOfBounds  &&
				iterations < 9)
		{
			position = rand() % 9;
			iterations++;
		}
		relativeYPos = (position / 3) - 1;
		relativeXPos = (position % 3) - 1;
		
		m_energy -= 30;
	}
	CellAction action(Zoe::reproduce, relativeXPos, relativeYPos);
	return action;
}
