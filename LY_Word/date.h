//SOURCE INTERNET: https://www.howkteam.vn/course/viet-chuong-trinh-so-sanh-2-thoi-gian-nhap-vao-va-in-ra-ket-qua/tim-ngay-truoc-va-sau-cua-mot-ngay-1306
#pragma once
#include<iostream>
bool LeapYear(int nYear);
int NumDaysInMonth(int nMonth, int nYear);
bool ExistDay(int nDay, int nMonth, int nYear);
void Yesterday(int& nDay, int& nMonth, int& nYear);
void Tomorrow(int& nDay, int& nMonth, int& nYear);
int DayDistance(int d1, int m1, int y1, int d2, int m2, int y2);


