#include "mergame.h"

/*
 *	Author: xqm32	Date: 25/7/18
 *	File: ./lib/mainfunc.cpp
 */

void mergame::rotate_right(const int &times)
{
	std::vector<std::vector<int>> medium=table;
	for (auto c=0; c<times; ++c)
	{
		for (auto i=0; i<len; ++i)
			for (auto j=0; j<len; ++j)
				medium[i][j]=table[len-1-j][i];
		for (auto i=0; i<len; ++i)
			for (auto j=0; j<len; ++j)
				table[i][j]=medium[i][j];
	}
}

void mergame::merge()
{
	for (auto &i: table)
		for (auto j=0, k=1; k<len; ++k)
		{
			if (j!=k && i[j] && i[k])
				if (i[j]==i[k]) {i[j]*=2; i[k]=0; j=k;}
				else {j=k;}
			if (!i[j]) ++j;
		}
	for (auto &i: table)
		for (auto j=0, k=1; k<len; ++k)
		{
			if (j<k && !i[j] && i[k]) std::swap(i[j], i[k]);
			while(i[j]) ++j;
		}
}

int mergame::try_lose() const
{
	for (auto i=0; i<len-1; ++i)
		for (auto j=0; j<len-1; ++j)
			if (table[i][j]==table[i+1][j]||
				table[i][j]==table[i][j+1]) return 0;
	for (auto i=0; i<len-1; ++i)
		if (table[i][len-1]==table[i+1][len-1]) return 0;
	for (auto j=0; j<len-1; ++j)
		if (table[len-1][j]==table[len-1][j+1]) return 0;
	return 1;
}