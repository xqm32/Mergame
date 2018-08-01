#include "mergame.h"

/*
 *	Author: xqm32	Date: 25/7/18
 *	File: ./lib/printfunc.cpp
 */

int mergame::print_table()
{
	zero=0;
	int achieve_aim=0;
	std::cout<<"Round: "<<round<<"   Score: "<<score<<std::endl;
	for (const auto &i: table)
		{for (const auto &j: i)
			{if (j==aim) achieve_aim=1;
			if (j) print(j, 1, numlen);
			else {zero=1; print(j, 2, numlen);}}
		print('\n');}
	
	return achieve_aim;
}

void mergame::rand_appear(const int &give_num)
{
	auto times=0;
	auto ry=rand()%len;
	auto rx=rand()%len;
	int num;
	if (!give_num) num=base_num*(rand()%2+1);
	for (; table[ry][rx]!=0&&times<len*len; ++times)
	{
		ry=rand()%len;
		rx=rand()%len;
	}
	if (times<len*len)
		if (!give_num) {table[ry][rx]=num; score+=num;}
		else {table[ry][rx]=give_num; score+=give_num;}
}

int mergame::menu()
{
	while(1)
	{
		if (print_table()) {print(text["win"]); return 0;}
		if (!zero) if (try_lose()) {print(text["lose"]); return 1;}
		
		print(text["menu"]);
		
		std::string ch;
		if (auto_play)
		{
			switch(rand()%4)
			{
				case 0: ch='a'; break;
				case 1: ch='s'; break;
				case 2: ch='d'; break;
				case 3: ch='w'; break;
			}
			std::cout<<ch<<std::endl;
		}
		else std::cin>>ch;
		
		if (ch == dircon["left"]) merge();
		else if (ch == dircon["down"]) {rotate_right(); merge(); rotate_right(3);}
		else if (ch == dircon["right"]) {rotate_right(2); merge(); rotate_right(2);}
		else if (ch == dircon["up"]) {rotate_right(3); merge(); rotate_right();}
		else if (ch == dircon["rotate_right"]) {rotate_right(); continue;}
		else if (ch == dircon["exit"]) return 0;
		else 
		{
			if (ch == dircon["save"]) {std::cin>>ch; save(ch);}
			else if (ch == dircon["read"]) {std::cin>>ch; read(ch);}
			else if (ch == dircon["autosave"]) {save();}
			else if (ch == dircon["autoread"]) {read();}
			else if (ch == dircon["save_option"]) {std::cin>>ch; save_option(ch);}
			else if (ch == dircon["read_option"]) {std::cin>>ch; read_option(ch);}
			else if (ch == dircon["autosave_option"]) {save_option();}
			else if (ch == dircon["autoread_option"]) {read_option();}
			else if (ch == dircon["help"]) {std::cout<<text["help"];}
			// else if (ch == dircon["change"]) {change();}
			continue;
		}
		
		if (rand_appear_mode) rand_appear();
		++round;
	}
}