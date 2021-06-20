#pragma once
#include"searchstring.h"
int intoint(char a)
{
    if ('a' <= a && a <= 'z') return int(a) - 'a' + 1;
    if (a == ' ') return 27;
    if ('A' <= a && a <= 'Z') return int(a) - 'A' + 28;
    if ('0' <= a && a <= '9') return int(a) - '0' + 54;
    return 65;
}
void Hash_resource::make_poww(int n)
{
    int k = poww.size();
    if (k - 1 < n)
    {
        poww.resize(n + 1);
        for (int i = k; i < poww.size(); i++)
        {
            if (i == 0) poww[0] = 1;
            else poww[i] = (base * poww[i - 1]) % MOD;
        }
    }
}
int Hash_resource::Find(string a, string b)
{
    vector <long long> hb;
    long long ha = 0;

    int m = a.length();
    int n = b.length();
    //n>m
    a = ' ' + a;
    b = ' ' + b;
    make_poww(n + 1);//n-1
    hb.resize(n + 1);

    ha = 0;
    for (int i = 1; i <= m; i++)
        ha = (ha * base + intoint(a[i])) % MOD;

    hb[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        hb[i] = (hb[i - 1] * base + intoint(b[i])) % MOD;
        if (i >= m && ha == (hb[i] - hb[i - m] * poww[m] + MOD * MOD) % MOD)
        {
            return i - m;
        }
    }
    return -1;
}
bool LCS_compare(string a, string b, int& LCS_scch, int& LCS_dogian, int& LCS_c1, int& LCS_c2)
{
    if (a.length() > b.length()) swap(a, b);
    int sn = a.length(), sm = b.length(), u, v = 0;
    a = ' ' + a;
    b = ' ' + b;
    int kq = -1, hs;
    int F[100][100], next[100][100];
    bool trace[100][100];

    for (int i = 1; i <= 65; i++) next[i][sm + 1] = sm + 1;

    for (int k = sm; k >= 1; k--)
    {
        for (int i = 1; i <= 65; i++) next[i][k] = next[i][k + 1];
        next[intoint(b[k])][k] = k;
    }
    for (int i = 0; i <= sn; i++) { F[i][0] = 0; F[0][i] = 0; }
    for (int i = 0; i <= sn; i++)
        for (int j = 0; j <= sn; j++) trace[i][j] = 0;
    int nextofj;
    for (int i = 1; i <= sn; i++)
        for (int k = 1; k <= i; k++)
        {
            //xu li
            nextofj = next[intoint(a[i])][F[i - 1][k - 1] + 1];
            if (i == k) hs = sm + 1; else hs = F[i - 1][k];
            //nextofj- F[i - 1][k - 1] >=3
            if (F[i - 1][k - 1] == sm + 1) F[i][k] = hs;
            else F[i][k] = min(hs, nextofj);
            //luu truy vet
            if (F[i][k] == nextofj) //giong nhu a[i]=b[j]
                trace[i][k] = 1;
            //luu ket qua
            if (i == sn && F[i][k] != sm + 1) { u = i; v = k; }
        }
    if (v == 0) return false;
    //-----------------------------------------------------------------------------
    //kiem tra tim delta, c1, c2 do tui tu nghi ra nhung no van con nhieu han che
    string kqs = "";
    int scch = v;
    int MINkc_giua2_kytu = 1000, kc_giua2_kytu, ikq, j;
    //truy vet tim day ki tu
    while (u >= 1 && v >= 1)
    {
        if (trace[u][v] == 1) { kqs = a[u] + kqs; u--; v--; }
        else u--;
    }
    //kqs la mang ki tu chung giua hai xau

    //tim mang rut gon nhat
    for (int i = 1; i <= sm; i++)
        if (b[i] == kqs[0])
        {
            kc_giua2_kytu = 0; ikq = 0;

            j = i;
            while (ikq != scch - 1)
            {
                hs = next[intoint(kqs[++ikq])][j + 1];
                if (hs == sm + 1 || hs - j >= 3) { kc_giua2_kytu = 1001; break; } //khong tim thay hoac vuot qua khoang cach ki tu
                kc_giua2_kytu += (hs - j);
                if (kc_giua2_kytu > MINkc_giua2_kytu) break;
                j = hs;
            }
            if (kc_giua2_kytu < MINkc_giua2_kytu) { LCS_c1 = i; LCS_c2 = j; MINkc_giua2_kytu = kc_giua2_kytu; }
        }
    if (MINkc_giua2_kytu == 1000) { LCS_c1 = -1000; LCS_c2 = 1000; return false; }
    //dong thoi cung da cap nhat vi tri c1, c2;
    LCS_c1--; LCS_c2--;
    LCS_scch = scch;
    LCS_dogian = MINkc_giua2_kytu + 1; //c2-c1+1
    return true;
}
