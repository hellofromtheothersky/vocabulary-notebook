#include"curtime.h"
void curtime::Print()
{
	textcolor(8);
	cout << d << "/" << m << "/" << y;
	textcolor(7);
}
int curtime::Day()
{
	return d;
}
int curtime::Month()
{
	return m;
}
int curtime::Year()
{
	return y;
}