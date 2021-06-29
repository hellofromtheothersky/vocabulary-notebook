#pragma once
#include"dict.h"
bool dict::s_es_suffix(string s)
{
    if (s.length() <= 2) return false;
    int d = s.length() - 1;
    if (s[d - 1] == 'e' && s[d] == 's') return true;
    if (s[d - 1] != 's' && s[d] == 's') return true;
    return false;
}
bool dict::ing_ed_suffix(string s)
{
    if (s.length() <= 3) return false;
    int d = s.length() - 1;
    if (s[d - 2] != 'e' && s[d - 1] == 'e' && s[d] == 'd') return true;
    if (s[d - 2] == 'i' && s[d - 1] == 'n' && s[d] == 'g') return true;
    return false;
}
bool dict::Check_similar(string a, string b)
{
    int l = min(a.length(), b.length());
    for (int i = l - 2; i >= 0; i--)
        if (a[i] != b[i]) return false;
    return true;
}

void dict::Collect_data()
{
    fstream f;
    f.open("data/LY_file1.dat");
    if (f.fail()) { cout << "LOI: KHONG MO DUOC FILE LY_file1!\n"; ERROR_TO_CLOSE(); }
    string s;
    while (1 > 0)
    {
        ++n;
        s = "";
        getline(f, s);
        if (s.length() == 0) { n--; break; }
        if (n == 1 || n == 22300 || n == 44600 || n == 66900 || n == 89200 || n == 111500) cout << ".";
        word[n] = s;
        getline(f, s);
        speech[n] = s;
    }
    f.close();
}
int dict::Num()
{
    return n;
}
string dict::Baseword(int k)
{
    return word[k];
}
string dict::Speech(int k)
{
    return speech[k];
}
int dict::Find_speech(string s)
{
    int l = 1, r = Num(), mid, key = 0;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (word[mid] == s) { key = mid; break; }
        else if (word[mid] < s) l = mid + 1;
        else r = mid - 1;
    }
    return key;
}
int dict::Find_baseword(int sp)
{
    int key = sp;
    while (s_es_suffix(word[key]) == true
        || ing_ed_suffix(word[key]) == true
        || word[key].length() > word[sp].length())
        key--;
    if (Check_similar(word[sp], word[key]) == false) return sp;
    return key;
}
