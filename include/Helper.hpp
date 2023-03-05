// include miscellaneous functions
#include <iostream>
#include <math.h>

namespace HelperFunc
{
// randSeed is std::rand() and cannot use directly since the program assumes random seed is initialized beforehand
	inline int randNum(long randSeed, int min, int max) 
	{
		if (min >= max) 
		{
			throw std::invalid_argument("min must be smaller than max argument in HelperFunc::randNum");
		}	
		int random_num = randSeed%(max-min + 1) + min;
		return random_num; 
	}

	inline double distance(double x1, double y1, double x2, double y2) 
	{
		return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
	}
}
