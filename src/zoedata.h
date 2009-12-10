#ifndef ZOEDATA_H
#define ZOEDATA_H

namespace Zoe
{
	enum {	xCells = 40,
			yCells = 30,
			cell_size = 20,
			arg_offset = 97,
		 };
	
	enum direction {	north,
						northeast,
						east,
						southeast,
						south,
						southwest,
						west,
						northwest
					};
			
	enum action {	move,
					reproduce,
					attack,
					none
				};
	
	enum neighbours {	occupied,
						vacant,
						outOfBounds
					};
}



#endif

