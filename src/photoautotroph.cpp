#include "photoautotroph.h"
#include "kdebug.h"

#include <QColor>

PhotoAutotroph::PhotoAutotroph(Environment *env)
			:	ICell(env),
				photoGene(8,3)
{
	photoGene.printGene();
}

PhotoAutotroph::PhotoAutotroph(PhotoAutotroph *oldCell)
				:	photoGene(oldCell->replicatePhotoGene())
{
	mColour = oldCell->getFillColour();
	mEdgeColour = oldCell->getEdgeColour();
	photoGene.printGene();
}

void PhotoAutotroph::expressGenes()
{
	m_energy += photoGene.express(m_enviro->light(), m_enviro->water(), m_enviro->temperature());
	//kDebug() << "PhotoAutotroph:" << m_cellID << ", energy:" << m_energy << "\tphotoGene:" << photoGene.sequence();
}

ICell * PhotoAutotroph::reproduce()
{
	ICell * daughter = new PhotoAutotroph(this);
	daughter->setColour(mutateColour());
	return daughter;
}

QColor PhotoAutotroph::mutateColour()
{
	int red = mColour.red();
	int green = mColour.green();
	int blue = mColour.green();
	switch (rand() % 3)
	{
		case 0:	
				red += ((rand() % 21) - 10); 
				if (red > 255)
					red = 255;
				if (red < 0)
					red = 0;
				break;
		case 1:	
				green += ((rand() % 21) - 10); 
				if (green > 255)
					green = 255;
				if (green < 0)
					green = 0;
				break;
		case 2:	
				blue += ((rand() % 21) - 10);
				if (blue > 255)
					blue = 255;
				if (blue < 0)
					blue = 0;
				break;
	}
	
	return QColor(red, green, blue);
	
}

void PhotoAutotroph::setColour(QColor colour)
{
	mColour = colour;
}

Gene PhotoAutotroph::replicatePhotoGene()
{
	return photoGene.copy();
}

QColor PhotoAutotroph::colour()
{
	return mColour;
}
