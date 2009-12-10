#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include "kdebug.h"
#include "mainwindow.h"

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
	
	MainWindow * main = new MainWindow();
	main->show();
	app.exec();
	return 0;
}


// char dna1 [] = {'a','f','G','2','3',':','x','B'};
// 	char dna2 [] = {'L','b','.','$','3','x','4','9'};
// 	
// 	int result = 0;
// 	for (int i=0; i<8; i++)
// 	{
// 		int next = 0;
// 		
// 		if (i == 7)
// 			next = dna1[3];
// 		else next = dna2[i+1];
// 		
// 		int temp = ((dna1[i] - dna2[i]) % dna2[i]) % next;
// 		kDebug() << temp;
// 		result += temp;
// 	}
// 	kDebug() << result;
