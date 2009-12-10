#ifndef CELLACTION_H
#define CELLACTION_H

#include "zoedata.h"

class CellAction
{
public:
	CellAction(Zoe::action act, int deltaX, int deltaY) 
					: m_action(act), m_deltaX(deltaX), m_deltaY(deltaY) {};
	void set(Zoe::action act, int deltaX, int deltaY) { m_action = act; 
													m_deltaX = deltaX;
													m_deltaY = deltaY; };
	Zoe::action action() { return m_action; };
	int deltaX() { return m_deltaX; };
	int deltaY() { return m_deltaY; };
	
private:
	Zoe::action m_action;
	int m_deltaX;
	int m_deltaY;
};

#endif
