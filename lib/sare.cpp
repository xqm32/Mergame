#include "mergame.h"

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

inline void getnone(std::istream &is, int ch='\n')
{
	int it=is.get();
	while(it!=ch&&it!=-1) it=is.get();
}

int mergame::save(const std::string &filename)
{
	std::fstream file(filename+".msa", std::ios::in);
	if (file.is_open())
	{
		getchar();
		std::cout<<"\nThe file "<<filename<<" exists. Continue to save? [Y/n]"<<std::endl<<':'<<std::flush;
		char ch=getchar();
		if (ch=='Y'||ch=='y') getchar();
		if (ch=='N'||ch=='n') {getchar(); return 1;}
	}
	file.close();
	
	file.open("data/save.lst", std::ios::app);
	file<<filename<<std::endl;
	
	file.close();
	
	file.open(filename+".msa", std::ios::out);
	
	file<<"This file is autosave game."<<std::endl;
	
		std::cout<<"\nSaving variable."<<std::endl;
	file<<'#'<<std::endl;
	file<<round<<' '<<zero<<' '<<score<<std::endl;
		std::cout<<"Finished saving."<<std::endl;
		
		std::cout<<"Saving table."<<std::endl;
		file<<'#'<<std::endl;
	for (auto i=0; i<len; ++i)
	{
		for (auto j=0; j<len; ++j)
			file<<table[i][j]<<' ';
		file<<std::endl;
	}
		std::cout<<"Finished saving.\n"<<std::endl;
}

int mergame::read(const std::string &filename)
{
	std::ifstream file("data/"+filename+".msa");
	if (!file.is_open())
	{
		std::cout<<"The file "<<filename<<" doesn't exist."<<std::endl;
		return 1;
	}
	
	getnone(file, '#'); getnone(file);
	file>>round>>zero>>score;
	
	getnone(file, '#'); getnone(file);
		std::cout<<"Making table."<<std::endl;
	table.clear();
	table=std::vector<std::vector<int>>(len, std::vector<int>(len));
		std::cout<<"Finished reading."<<std::endl;
		std::cout<<"Reading table."<<std::endl;
	for (auto i=0; i<len; ++i)
		for (auto j=0; j<len; ++j)
			file>>table[i][j];
		std::cout<<"Finished reading."<<std::endl;
}

int mergame::save_option(const std::string &filename)
{
	std::fstream file(filename+".mso", std::ios::in);
	if (file.is_open())
	{
		getchar();
		std::cout<<"\nThe file "<<filename<<" exists, Continue to save? [Y/n]"<<std::endl<<':'<<std::flush;
		char ch=getchar();
		if (ch=='Y'||ch=='y') getchar();
		else if (ch=='N'||ch=='n') {getchar(); return 1;}
	}
	file.close();
	file.open(filename+".mso", std::ios::out);
	
	file<<"This file is autosave_option."<<std::endl;
	
		std::cout<<"\nSaving variable."<<std::endl;
	
	file<<'#'<<std::endl;
	file<<base_num<<' '<<aim<<' '<<len<<' '<<test_mode<<' '<<rand_appear_mode<<' '<<auto_play<<std::endl;
		std::cout<<"Finished saving."<<std::endl;

	file<<'#'<<std::endl;
	if (test_mode)
		file<<round<<' '<<zero<<' '<<score<<std::endl;
		
	file<<'#'<<std::endl;
		std::cout<<"Saving key option."<<std::endl;
	file<<dircon["up"]<<' '<<dircon["down"]<<' '<<dircon["right"]<<' '<<dircon["left"]<<' '<<dircon["rotate_right"]<<' '<<dircon["exit"]<<' ';
	file<<dircon["save"]<<' '<<dircon["read"]<<' '<<dircon["autosave"]<<' '<<dircon["autoread"]<<' ';
	file<<dircon["save_option"]<<' '<<dircon["read_option"]<<' '<<dircon["autosave_option"]<<' '<<dircon["autoread_option"]<<' ';
	file<<dircon["help"]<<' '<<dircon["change"]<<std::endl;
		std::cout<<"Finished saving."<<std::endl;
		
	file<<'#'<<std::endl;
	if (test_mode)
	{
			std::cout<<"Detected test mode."<<std::endl;
			std::cout<<"Saving table."<<std::endl;
		for (auto i=0; i<len; ++i)
		{
			for (auto j=0; j<len; ++j)
				file<<table[i][j]<<' ';
			file<<std::endl;
		}
			std::cout<<"Finished saving."<<std::endl;
	}
	
	file<<'#'<<std::endl;
		std::cout<<"Saving text."<<std::endl;
	file<<text["menu"]<<'#'<<std::endl;
	file<<text["help"]<<'#'<<std::endl;
	file<<text["exit"]<<'#'<<std::endl;
	file<<text["lose"]<<'#'<<std::endl;
	file<<text["win"]<<'#'<<std::endl;
		std::cout<<"Finished saving.\n"<<std::endl;
	file.close();
	
	return 0;
}

int mergame::read_option(const std::string &filename)
{
	std::ifstream file(filename+".mso");
	if (!file.is_open())
	{
		std::cout<<"The file "<<filename<<" doesn't exist."<<std::endl;
		return 1;
	}
	
	getnone(file, '#'); getnone(file);
		std::cout<<"\nReading variable."<<std::endl;
	file>>base_num>>aim>>len>>test_mode>>rand_appear_mode>>auto_play;
	numlen=log10(aim)+1;
		std::cout<<"Finished reading."<<std::endl;

	getnone(file, '#'); getnone(file);
	if (test_mode)
		file>>round>>zero>>score;
	else
	{
		round=1; zero=0; score=0;
	}
		
	getnone(file, '#'); getnone(file);
		std::cout<<"Reading key option."<<std::endl;
	file>>dircon["up"]>>dircon["down"]>>dircon["right"]>>dircon["left"]>>dircon["rotate_right"]>>dircon["exit"];
	file>>dircon["save"]>>dircon["read"]>>dircon["autosave"]>>dircon["autoread"];
	file>>dircon["save_option"]>>dircon["read_option"]>>dircon["autosave_option"]>>dircon["autoread_option"];
	file>>dircon["help"]>>dircon["change"];
		std::cout<<"Finished reading."<<std::endl;

	getnone(file, '#'); getnone(file);
		std::cout<<"Making table."<<std::endl;
	table.clear();
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
	
	getnone(file, '#'); getnone(file);
		std::cout<<"Reading text."<<std::endl;
	getline(file, text["menu"], '#'); getnone(file);
	getline(file, text["help"], '#'); getnone(file);
	getline(file, text["exit"], '#'); getnone(file);
	getline(file, text["lose"], '#'); getnone(file);
	getline(file, text["win"], '#'); getnone(file);
		std::cout<<"Finished reading.\n"<<std::endl;
	file.close();
	
	return 0;
}

void mergame::change()
{
	std::cout<<"Nothing."<<std::endl;
}