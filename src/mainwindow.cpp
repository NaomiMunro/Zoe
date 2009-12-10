#include "mainwindow.h"
#include "kdebug.h"
#include "zoedata.h"
#include "gene.h"

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
// #include <KAction>
// #include <KLocale>
// #include <KActionCollection>


MainWindow::MainWindow(QWidget *parent)
	   : KXmlGuiWindow(parent)
{
	canvas = new PaintWidget(this);
	setCentralWidget(canvas);
	
	world = new LivingArea(Zoe::xCells, Zoe::yCells);
	
	connect(world, SIGNAL(redrawScreen(QVector< QVector<ICell *> >)),
 		  canvas, SLOT(redraw(QVector< QVector<ICell *> >)));
  
	setupGUI();
}

int main (int argc, char *argv[])
{
	KAboutData aboutData( "zoe", 0, 
					  ki18n("Zoe"), "1.0",
					  ki18n("Artificial Life"),
					  KAboutData::License_GPL,
					  ki18n("Copyright (c) Ben Munro") );
 	KCmdLineArgs::init( argc, argv, &aboutData );
	KApplication app;
	
	srand(time(NULL));
	
	Gene::setupArgNums();
	
	MainWindow * main = new MainWindow();
	main->show();
	app.exec();
	return 0;
}

// void MainWindow::setupActions()
// {
// // 	KAction* addHawkAction = new KAction(this);
// // 	addHawkAction->setText(i18n("Hawk"));
// // 	addHawkAction->setIcon(KIcon("document-new"));
// // 	actionCollection()->addAction("addHawk", addHawkAction);
// //   
// // 	connect(thread, SIGNAL(swarmMoved(QList<ICreature *>)),
// //  		  canvas, SLOT(drawSwarm(QList<ICreature *>)), Qt::DirectConnection);
// 
// }

// void MainWindow::setupWorld()
// {
// 	cellSpace = new LivingArea[Zoe::xCells * Zoe::yCells];
// 	
// 	for (int col=0; col<Zoe::xCells; col++)
// 	{
// 		for (int row=0; row<Zoe::yCells; row++)
// 		{
// 			int light;
// 			if (row < Zoe::yCells /2)
// 				light = 100;
// 			else
// 				light = 50;
// 				
// 			cellSpace[col * Zoe::yCells + row] = LivingArea(light, 0);
// 			
// 			if (rand()%100 == 0)
// 			{
// 				cellSpace[col * Zoe::yCells + row].setCell(new Cell());
// 			}
// 		}
// 	}
// 	
// 	emit redrawScreen(cellSpace);	
// 		
// 	QTimer *timer = new QTimer(this);
// 	connect(timer, SIGNAL(timeout()), this, SLOT(nextGeneration()));
// 	timer->start(1000);
// }

// void MainWindow::nextGeneration()
// {
// 	kDebug() << "new generation";
// 	emit redrawScreen(cellSpace);
// }


