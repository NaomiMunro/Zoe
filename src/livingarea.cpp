#include "livingarea.h"
#include "kdebug.h"
#include "zoedata.h"
#include "photoautotroph.h"

#include <QTimer>

using namespace Zoe;

LivingArea::LivingArea(int xCells, int yCells)
		:	m_xCells (xCells),
			m_yCells (yCells),
		 	cellSpace(xCells, QVector<ICell *>(yCells)),
			enviroSpace(xCells, QVector<Environment *>(yCells))
{
	m_xCells = xCells;
	m_yCells = yCells;
	
	setupWorld();
	numGenerations=0;
}

void LivingArea::setupWorld()
{
 	for (int col=0; col < Zoe::xCells; col++)
	{
		for (int row=0; row < Zoe::yCells; row++)
		{
			int light;
			if (row < (m_yCells /2))
				light = 1000;
			else
				light = 1;
				
			int water;
			if (col < (m_xCells /2))
				water = 1000;
			else
				water = -50;
				
			int temperature;
			if (col < (m_xCells /2) && col > (m_xCells/2 - 5))
				temperature = 1000;
			else
				temperature = -100000;
				
			if (row < 8 && col < 8)
			{
				light = -1000000;
				temperature = -1000000;
				water = -1000000;
			}
			enviroSpace[col][row] = new Environment(light, water, temperature);
		}
	}
	
	for (int col=0; col < Zoe::xCells; col++)
	{
		for (int row=0; row < Zoe::yCells; row++)
		{
			if (rand()%100 == 0)
			{
				cellSpace[col][row] = new PhotoAutotroph(enviroSpace[col][row]);
			}
		}
	}
	
	emit redrawScreen(cellSpace);
	
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(nextGeneration()));
	timer->start(1000);
}

void LivingArea::nextGeneration()
{
	//loop
		// check energy levels, kill cells with no energy
		// express, do biochemical thingies
		// send neighbour list
		// get cell to move/eat or reproduce
		// carry out above line - reproduce includes mutation
		// update Cell location, including send new environment to cell
	// end loop
	
	for (int col=0; col < Zoe::xCells; col++)
	{
		for (int row=0; row < Zoe::yCells; row++)
		{
			if ( cellSpace[col][row] != 0 )
			{
				if ( killDeadCell(col, row) )  //kill the dead cells
					continue; // and skip this iteration;
				if ( killOldCell(col, row) )  //kill the dead cells
					continue; // and skip this iteration;
				ICell * current = cellSpace[col][row];
				
				current->expressGenes();
				current->updateNeighbours(calculateNeighbours(col,row));
				current->incrementAge();
				
				CellAction action = current->act();
				performAction(action, col, row);
			}
		}
	}
			
	emit redrawScreen(cellSpace);
	numGenerations++;
/*	if (numGenerations % 10 == 0)
		adjustEnvironment();*/
}


bool LivingArea::killDeadCell(int col, int row)
{
	if (cellSpace[col][row]->energy() < 1)
	{
		killCell(col,row);
		return true;
	}
	else return false;
}

bool LivingArea::killOldCell(int col, int row)
{
	if (cellSpace[col][row]->age() > 5)
	{
		killCell(col,row);
		return true;
	}
	else return false;
}

void LivingArea::killCell(int col, int row)
{
	ICell * temp = cellSpace[col][row];
	cellSpace[col][row] = NULL;
	delete temp;
}

QVector< QVector<Zoe::neighbours> > LivingArea::calculateNeighbours(int col, int row)
{
	QVector< QVector<Zoe::neighbours> > neighbours(3, QVector<Zoe::neighbours>(3));
	
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (inBounds(col + i, row + j))
			{
				if (cellSpace[col + i][row + j] == 0)
				{
					neighbours[i+1][j+1] == Zoe::vacant;
				}
				else neighbours[i+1][j+1] == Zoe::occupied;
			} else neighbours[i+1][j+1] = Zoe::outOfBounds;
		}
	}

	return neighbours;
}

void LivingArea::performAction(CellAction action, int col, int row)
{
	switch (action.action())
	{
		case reproduce:
					{
						ICell * daughter = cellSpace[col][row]->reproduce();
						int x = col + action.deltaX();
						int y = row + action.deltaY();
						if (inBounds(x,y))
						{
							if (cellSpace[x][y] == NULL)	
							{
								daughter->setEnvironment(enviroSpace[x][y]);
								cellSpace[x][y] = daughter;
							}
						}
						break;
					}
		case move:
		case attack:
		default:
				kDebug() << "Error, default case reached.";	
	}
}

bool LivingArea::inBounds(int x, int y)
{
	if (x >= m_xCells  ||  y >= m_yCells ||  x < 0  ||	y < 0)
		return false;
	else return true;
}
