#include "mergame.h"

#include <fstream>
#include <cstdlib>
#include <ctime>

/*
 *	Author: xqm32	Date: 25/7/18
 *	File: ./lib/mainfunc.cpp
 */

void mergame::init()
{
	read_option("data/text");
	std::ifstream file("data/.first_play");
	if (!file.is_open())
	{
		print(text["help"]);
		std::ofstream none("data/.first_play");
		none.close();
	}
	file.close();
}

mergame::mergame()
{;
	init();
	srand(time(nullptr));
	if (!test_mode)
	{
		rand_appear(base_num);
		rand_appear(base_num);
	}
}

mergame::~mergame()
{
	print(text["exit"]);
}