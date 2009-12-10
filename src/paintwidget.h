#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include "zoedata.h"
#include "livingarea.h"

#include <QWidget>
#include <QSize>
#include <QPixmap>
#include <QPaintEvent>
#include <QVector>

class PaintWidget : public QWidget
{

Q_OBJECT

public:
	PaintWidget (QWidget *parent = 0);
	QSize sizeHint() const;
	QSize minimumSizeHint() const;

public slots:
	void redraw(QVector< QVector<ICell *> >);

protected:
	void paintEvent(QPaintEvent *event);

private:
	QSize size;
	QVector< QVector<ICell *> > cellSpace;
	bool arrayExists;
	
  
};

#endif
