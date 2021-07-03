//SOURCE INTERNET: https://www.howkteam.vn/course/viet-chuong-trinh-so-sanh-2-thoi-gian-nhap-vao-va-in-ra-ket-qua/tim-ngay-truoc-va-sau-cua-mot-ngay-1306
#pragma once
#include"date.h"
bool LeapYear(int nYear)
{
	if ((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
	{
		return true;
	}
	return false;

	// <=> return ((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0);
}
int NumDaysInYear(int y)
{
	if (LeapYear(y)) return 366;
	return 365;
}
int NumDaysInMonth(int nMonth, int nYear)
{
	int nNumOfDays=-1;

	switch (nMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		nNumOfDays = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		nNumOfDays = 30;
		break;
	case 2:
		if (LeapYear(nYear))
		{
			nNumOfDays = 29;
		}
		else
		{
			nNumOfDays = 28;
		}
		break;
	default:
		break;
	}

	return nNumOfDays;
}
bool ExistDay(int nDay, int nMonth, int nYear)
{
	bool bResult = true; // Giả sử ngày hợp lệ

	// Kiểm tra năm
	if (!(nYear > 0 && nMonth))
	{
		bResult = false; // Ngày không còn hợp lệ nữa!
	}

	// Kiểm tra tháng
	if (!(nMonth >= 1 && nMonth <= 12))
	{
		bResult = false; // Ngày không còn hợp lệ nữa!
	}

	// Kiểm tra ngày
	if (!(nDay >= 1 && nDay <= NumDaysInMonth(nMonth, nYear)))
	{
		bResult = false; // Ngày không còn hợp lệ nữa!
	}

	return bResult; // Trả về trạng thái cuối cùng...
}
void Yesterday(int& nDay, int& nMonth, int& nYear)
{
	nDay--;
	if (nDay == 0)
	{
		nMonth--;
		if (nMonth == 0)
		{
			nMonth = 12;
			nYear--;
		}

		nDay = NumDaysInMonth(nMonth, nYear);
	}
}
void Tomorrow(int& nDay, int& nMonth, int& nYear)
{
	nDay++;
	if (nDay > NumDaysInMonth(nMonth, nYear))
	{
		nDay = 1;
		nMonth++;
		if (nMonth > 12)
		{
			nMonth = 1;
			nYear++;
		}
	}
}
int DayRank(int d, int m, int y)
{
	int ngaynam[2][12] = { {31,29,31,30,31,30,31,31,30,31,30,31},{31,28,31,30,31,30,31,31,30,31,30,31} };
	int i;
	int s = d;
	if (LeapYear(y)) i = 0;
	else i = 1;
	for (int j = 0; j < m - 1; j++)  s += ngaynam[i][j];
	return s;
}
int DayDistance(int d1, int m1, int y1, int d2, int m2, int y2)
{
	int sttngay1 = DayRank(d1, m1, y1);
	int sttngay2 = DayRank(d2, m2, y2);
	if (y1 == y2) return(abs(sttngay1 - sttngay2));
	int s = 0;
	if (y1 < y2)
	{
		sttngay1 = NumDaysInYear(y1) - sttngay1;
		for (int i = y1 + 1; i < y2; i++) s += NumDaysInYear(i);
		return(s + sttngay1 + sttngay2);
	}
	else
	{
		sttngay2 = NumDaysInYear(y2) - sttngay2;
		for (int i = y2 + 1; i < y1; i++) s += NumDaysInYear(i);
		return(s + sttngay1 + sttngay2);
	}
}
