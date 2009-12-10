#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paintwidget.h"
#include "livingarea.h"

#include <KXmlGuiWindow>

class MainWindow : public KXmlGuiWindow
{

Q_OBJECT

public:
  	MainWindow(QWidget *parent=0);
  
private:
  	PaintWidget *canvas;
	LivingArea *world;
  
};

#endif

