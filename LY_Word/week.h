#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include"screen.h"
#include"date.h"
using namespace std;
int Number(int k);
void Show_week_chart(int height[]);
class word
{
public:
	string content;
	virtual void Print()
	{
		if (content.length() <= 12) cout << content;
		else
		{
			string out = content.substr(0, 11)+"~";
			cout << out;
		}
	}
	virtual string Write() = 0;
};
class word_add:public word
{
public:
	word_add(string content)
	{
		this->content = content;
	}
	void Print()
	{
		textcolor(8);
		word::Print();
		textcolor(7);
	}
	string Write()
	{
		return "1" + word::content;
	}
};
class word_miss :public word
{
public:
	word_miss(string content)
	{
		this->content = content;
	}
	void Print()
	{
		textcolor(12);
		word::Print();
		textcolor(7);
	}
	string Write()
	{
		return "2" + word::content;
	}
};
class word_get :public word
{
public:
	word_get(string content)
	{
		this->content = content;
	}
	void Print()
	{
		word::Print();
	}
	string Write()
	{
		return "3" + word::content;
	}
};
class day
{
public:
	vector <word*> ListWord;
	int n_add=0, n_miss=0, n_get=0;
	int d=0, m=0, y=0;
	day()
	{
		ListWord.push_back(new word_add(""));
	}
	int NumOfWord()
	{
		return n_add + n_miss + n_get;
	}
	void Get(string s, int type)
	{
		if (type == 1)
		{
			ListWord.push_back(new word_add(s));
			n_add++;
		}
		if (type == 2)
		{
			ListWord.push_back(new word_miss(s));
			n_miss++;
		}
		if (type == 3)
		{
			ListWord.push_back(new word_get(s));
			n_get++;
		}
	}
	friend ostream& operator << (ostream& os, day p);
};
class week
{
	day Day[8];
	int today=0;
public:
	void Load(int curday, int curmonth, int curyear);
	void AddToCurrentDay(string s, int type);
	void ShowProgress();
};