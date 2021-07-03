#include"week.h"
int Number(int k)
{
    int number = 0;
    do
    {
        number++;
        k = k / 10;
    } while (k != 0);
    return number;
}
void Show_week_chart(int height[])
{
    int maxheight = 0, l;
    for (int i = 1; i <= 14; i++)
        maxheight = max(height[i], maxheight);

    textcolor(8);
    for (int line = maxheight + 1; line >= 1; line--)
    {
        for (int i = 1; i <= 14; i++)
        {
            if (height[i] >= line) cout << "|////|";
            else
            {
                if (height[i] + 1 == line)
                {
                    if (height[i] == 0) cout << "......";
                    else
                    {
                        l = Number(height[i]);
                        space((6 - l) / 2);
                        cout << height[i];
                        space((7 - l) / 2);
                    }
                }
                else cout << "      ";
            }
            if (i % 2 == 0)
            {
                cout << "  ";
                textcolor(8);
            }
            else textcolor(7);
        }
        cout << endl;
    }
    textcolor(7);
}

ostream& operator <<(ostream& os, day p)
{
    string out = to_string(p.d) + "/" + to_string(p.m);
    os << out;
    return os;
}
void week::Load(int curday, int curmonth, int curyear)
{
    int savedday, savedmonth, savedyear;
    fstream f;
    f.open("data/LY_file3.dat");
    if (f.fail()) { cout << "LOI: KHONG MO DUOC FILE LY_file3!\n"; ERROR_TO_CLOSE(); }

    f >> today;
    f >> savedday >> savedmonth >> savedyear;
    if (today != 0) today += DayDistance(savedday, savedmonth, savedyear, curday, curmonth, curyear);
    else today = 1;

    int n, type, nday=0;
    string s;
    if(today<=13)
    for (int i = 1; i <= 7; i++)
    {
        n = 0;
        f >> n;
        getline(f, s); 
        if (today - i < 7) nday++;
        for (int j = 1; j <= n; j++)
        {
            f >> type;
            getline(f, s);
            Day[nday].Get(s, type);
        }
    }

    today = min(7, today);
    Day[today].d = curday;
    Day[today].m = curmonth;
    Day[today].y = curyear;
    for (int i = today-1; i >= 1; i--)
    {
        Day[i].d = Day[i + 1].d;
        Day[i].m = Day[i + 1].m;
        Day[i].y = Day[i + 1].y;
        Yesterday(Day[i].d, Day[i].m, Day[i].y);
    }
    f.close();
}
void week::AddToCurrentDay(string s, int type)
{
    Day[today].Get(s, type);
    fstream f;
    f.open("data/LY_file3.dat", ios::out |ios::trunc);

    f << today << " " << Day[today].d << " " << Day[today].m << " " << Day[today].y << endl;
    for (int i = 1; i <= today; i++)
    {
        f << Day[i].n_add + Day[i].n_miss + Day[i].n_get << endl;
        for (int j = 1; j <= Day[i].NumOfWord(); j++)
            f << Day[i].ListWord[j]->Write() << endl;
    }
    f.close();
}
void week::ShowProgress()
{
    int height[15];
    for (int i = 1; i <= 7; i++)
    {
        height[i * 2 - 1] = Day[i].n_add;
        height[i * 2] = Day[i].n_miss + Day[i].n_get;
    }

    Show_week_chart(height);
    cout << "--------------------------------------------------------------------------------------------------\n";
    textcolor(14);
    for (int i = 1; i < today; i++)
        cout << setw(12) << Day[i]<<"  ";
    cout << setw(12) << "Hom nay";
    textcolor(7);
    cout << endl;

    int maxheight = 0;
    for (int i = 1; i <= 7; i++)
    {
        height[i] = Day[i].n_add + Day[i].n_miss + Day[i].n_get;
        maxheight = max(height[i], maxheight);
    }

    for (int line = 1; line <= maxheight; line++)
    {
        for (int i = 1; i <= 7; i++)
        {
            cout<<setw(12);
            if (line <= height[i]) Day[i].ListWord[line]->Print();
            else cout << "            ";
            cout << "  ";
        }
        cout << endl;
    }
    cout << endl << endl;
    system("pause");
}