#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

/*
 *	Author: xqm32	Date: 25/7/18
 *	File: ./lib/mergame.h
 */

class mergame
{
	private:
		int	base_num, aim, len, test_mode, rand_appear_mode, auto_play;
		int numlen, round, zero, score;
		std::vector<std::vector<int>> table;
		std::map<std::string, std::string> text;
		std::map<std::string, std::string> dircon;
		void init();
	public:
		mergame(); ~mergame();
		void rotate_right(const int &times=1);
		void merge();  int try_lose() const;
		int print_table(); void rand_appear(const int &give_num=0);
		int menu(); 
		void change();
		int save(const std::string &filename="data/autosave");
		int read(const std::string &filename="data/autosave");
		int save_option(const std::string &filename="data/autosave_option");
		int read_option(const std::string &filename="data/autosave_option");
};

template<typename T>
void print(const T &str, int num_t=0, int max=0)
{
	if (!num_t) std::cout<<str<<std::flush;
	else if (num_t==1) std::cout<<'['<<std::setw(max)<<str<<']'<<std::flush;
	else if (num_t==2) std::cout<<'['<<std::setw(max)<<' '<<']'<<std::flush;
}