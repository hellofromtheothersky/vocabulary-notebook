#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int intoint(char a);
bool LCS_compare(string a, string b, int& LCS_scch, int& LCS_dogian, int& LCS_c1, int& LCS_c2);
class Hash_resource
{
    const int base = 67;
    const long long MOD = 1000000003;
    vector<long long> poww;
    void make_poww(int n);
public:
    int Find(string, string);
};