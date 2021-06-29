#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include"screen.h"
using namespace std;
class dict
{
    int n;
    string word[133800];
    string speech[133800];
    bool s_es_suffix(string s);
    bool ing_ed_suffix(string s);
    bool Check_similar(string a, string b);
public:
    dict()
    {
        n = 0;
        speech[0] = "?";
    }
    void Collect_data();
    int Num();
    string Baseword(int k);
    string Speech(int k);
    int Find_speech(string s);
    int Find_baseword(int sp);
};