// include miscellaneous functions
#include <iostream>

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
}
