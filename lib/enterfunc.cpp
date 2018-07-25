#include "mergame.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

/*
 *	Author: xqm32	Date: 25/7/18
 *	File: ./lib/mainfunc.cpp
 */
 
inline void getnone(std::istream &is, int ch='\n')
{
	int it=is.get();
	while(it!=ch&&it!=-1) it=is.get();
}

void mergame::init()
{
	round=1; zero=0; score=0;
	
	std::ifstream file("data/text.txt", std::ios::in);
	
	getnone(file, '#'); getnone(file);
	
		std::cout<<"\nReading variable."<<std::endl;
	file>>base_num>>aim>>len>>test_mode>>rand_appear_mode>>auto_play;
	numlen=log10(aim)+1;
		std::cout<<"Finished reading."<<std::endl;
	
	getnone(file, '#'); getnone(file);
	
		std::cout<<"Making table."<<std::endl;
	table=std::vector<std::vector<int>>(len, std::vector<int>(len));
		std::cout<<"Finished making."<<std::endl;
		
	if (test_mode)
	{
			std::cout<<"Detected test mode."<<std::endl;
			std::cout<<"Reading table."<<std::endl;
		for (auto i=0; i<len; ++i)
			for (auto j=0; j<len; ++j)
				file>>table[i][j];
			std::cout<<"Finished reading."<<std::endl;
	}
	
		std::cout<<"Reading text."<<std::endl;
	getnone(file, '#'); getnone(file);
	getline(file, text["menu"], '#'); getnone(file);
	getline(file, text["help"], '#'); getnone(file);
	getline(file, text["exit"], '#'); getnone(file);
	getline(file, text["lose"], '#'); getnone(file);
	getline(file, text["win"], '#'); getnone(file);
		std::cout<<"Finished reading.\n"<<std::endl;
	
	file.close();
	file.open("data/.first_play", std::ios::in);
	if (!file.is_open())
	{
		print(text["help"]);
		std::ofstream none("data/.first_play");
		none.close();
	}
	file.close();
}

mergame::mergame()
{
	srand(time(nullptr));
	init();
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