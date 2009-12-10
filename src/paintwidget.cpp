#include "paintwidget.h"
#include "kdebug.h"
#include "icell.h"

#include <QPainter>
#include <QRectF>
#include <QSizeF>
#include <QColor>


PaintWidget::PaintWidget(QWidget* parent)
		  : QWidget(parent)
{
	size.setHeight(Zoe::cell_size * Zoe::yCells);
	size.setWidth(Zoe::cell_size * Zoe::xCells);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	arrayExists = false;
}

QSize PaintWidget::sizeHint() const
{
	return size;
}

QSize PaintWidget::minimumSizeHint() const
{
	return size;
}

void PaintWidget::redraw(QVector< QVector<ICell *> > cells)
{
	cellSpace = cells;
	arrayExists = true;
	update();
}

void PaintWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.fillRect(rect(), Qt::black);
	painter.setRenderHint(QPainter::Antialiasing);
  	painter.setPen("grey");
	for (int i=0; i < Zoe::xCells; i ++)
	{
		painter.drawLine(i * Zoe::cell_size, 0, i * Zoe::cell_size, Zoe::yCells * Zoe::cell_size);
	}
	
	for (int i=0; i < Zoe::yCells; i ++)
	{
		painter.drawLine(0, i * Zoe::cell_size, Zoe::xCells * Zoe::cell_size, i * Zoe::cell_size);
	}
	
	if (arrayExists)
	{
		for (int col=0; col < Zoe::xCells; col++)
		{
			for (int row=0; row < Zoe::yCells; row++)
			{
				if (cellSpace[col][row] != 0)
				{
					
					ICell *current = cellSpace[col][row];
					painter.setBrush(current->colour());
					painter.setPen(current->edgeColour());
					
					QRectF rect(col * Zoe::cell_size +1,
								row * Zoe::cell_size +1,
								18,18);
					painter.drawRoundRect(rect, 40, 40);	
				}
			}
		}
	}
}
