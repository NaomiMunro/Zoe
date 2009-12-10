#include "cell.h"
#include "zoedata.h"
#include "kdebug.h"

Cell::Cell()
{
	//photoGene = "YXMTFGOI";
	for (int i=0; i<8; i++)
	{
		photoGene += ((rand() % 26) + 65);
	}
	mEdgeColour.insert(0, rand() % 256);
	mEdgeColour.insert(1, rand() % 256);
	mEdgeColour.insert(2, rand() % 256);

}

QColor Cell::colour()
{
	int red = (((photoGene.at(0) + photoGene.at(1))-130)*10) % 256;
	int green = (((photoGene.at(2) + photoGene.at(3))-130)*10) % 256;
	int blue = (((photoGene.at(4) + photoGene.at(5))-130)*10) % 256;
	return QColor(red, green, blue);
}

// void Cell::setColour(QColor colour)
// {	//mFillColour = colour;	
// }

QColor Cell::edgeColour()
{	
	//return QColor("limegreen");
	return QColor(mEdgeColour.at(0), mEdgeColour.at(1), mEdgeColour.at(2));
}

// void Cell::setEdgeColour(QColor edge)
// {	//mEdgeColour = edge;	
// }
