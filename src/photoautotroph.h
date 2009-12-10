#ifndef PHOTOAUTOTROPH_H
#define PHOTOAUTOTROPH_H

#include "icell.h"
#include "gene.h"

#include <QColor>
#include <QVector>
#include <QByteArray>

class PhotoAutotroph : public ICell
{
public:
	PhotoAutotroph(Environment *env);
	PhotoAutotroph(PhotoAutotroph *);
	~PhotoAutotroph() {};
	void mutate(){};
	void expressGenes();
	ICell * reproduce();
	Gene replicatePhotoGene();
	QColor colour();
	QColor mutateColour();
	void setColour(QColor);
	
private:
	Gene photoGene;
	
};

#endif
