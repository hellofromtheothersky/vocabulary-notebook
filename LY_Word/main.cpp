#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include<conio.h> //de dung duoc ham _getch doc ki tu tu ban phim
#include"screen.h"
#include"strsearch.h"
#include"dict.h"
using namespace std;
typedef pair<int, int> pa_int2;
typedef pair<int, pa_int2> pa_int3;
Hash_resource Hash;
dict Dict;
class Word;
class Word_parcel;
void Norming_string(string& s);
class File_management
{
    string all_file[20];
    int defmode, socau, n;
    void Check_files();
    void Read_words(Word_parcel &P);
public:
    File_management()
    {
        n = 0;
        defmode = 0; 
        socau = 0;
    }
    int Num_of_que()
    {
        return socau;
    }
    int Num_of_file()
    {
        return n;
    }
    void Switch_mode(int k);
    int mode();
    string name_of_file(int k);
    string deffile();
    string deffilef();
    void Collect(Word_parcel &P);
    void Update_numofque(int socau);
    void Update_score(Word_parcel P);
    void Add_file(string s);
    void Unconnected_files(int* file, int sl);
    void Add_word(Word W);
};
class Word
{
private:
    string w = "";//word
    vector<string> GC; // ghi chu
    string m = ""; //meaning
    string e = ""; //example
    int sp = 0; //speech
    int c1 = -1; //start positon of word in the example
    int c2 = -1; //to positon of word in the example
    bool Find_word_in_example();
    void Get_example();
    void Get_smilar_example();
    void Get_meaning();
    void Get_note();
    void Choose_word_in_example();
public:
    int vgoc; //dung de xep dung trat tu
    int fr = 0; //so lan tra loi dung
    int ff = 0; //so lan in
    int ran; // dung de random cau hoi
    Word(string w = "", string m = "", string e = "", vector<string> GC = {}, int c1 = -1, int c2 = -1)
    {
        fr = 0;
        ff = 0;
        sp = 0;
        ran = 0;
        this->w = w;
        this->m = m;
        this->e = e;
        this->GC = GC;
        this->c1 = c1;
        this->c2 = c2;
    }
    string word();
    void Print_this_word(bool newword = 1, int searchmode = 0);
    void Print_question();
    bool Get_word(vector<string> line, Word pre = Word()); //get from file
    void Get_word(); //get from program
    bool Get_word(Word pre); //get from program for similar word
    friend class Search_solution;
    friend vector<string> Word_to_lines(Word);
};
class Word_parcel
{
    vector<Word> a;
    vector<int> pos_area;
    int area, num_of_area;
    int n;
    static bool sapxepabc_(Word u, Word v)
    {
        return u.word() < v.word();
    }
    static bool sapxepvgoc_(Word u, Word v)
    {
        return u.vgoc < v.vgoc;
    }
    static bool sapxeptanso_(Word u, Word v)
    {
        if (u.fr*2 + u.ff == v.fr*2 + v.ff) return u.ff < v.ff;
        return u.fr*2 + u.ff < v.fr*2 + v.ff;
    }
    static bool sapxepran_(Word u, Word v)
    {
        return u.ran < v.ran;
    }
    void range_of_this_word(int k, int& u, int& v);
public:
    Word_parcel()
    {
        n = 0;
        area = 0;
        num_of_area = 0;
        pos_area.push_back(0);
        pos_area.push_back(1);
        a.push_back(Word());
    }
    void Update_area(File_management F)
    {
        this->area = F.mode();
    }
    int from();
    int to();
    int find_area_from_pos(int k);
    int Num();
    int progress();
    void new_area();
    void Add_word(Word);
    void sapxepabc();
    void sapxepvgoc();
    void sapxepran(int v);
    void sapxeptanso();
    void Print_word(int pos = 0, int stt = 1, int searchmode = 0);
    friend class Search_solution;
    friend void MODE3(File_management, Word_parcel);
    friend void File_management::Update_score(Word_parcel P);
};
class Search_solution
{
private:
    struct subword
    {
        string s;
        int scch;
        int dogian;
    };
    vector<subword> subwords;
    int len_of_keyword; //length containing no space distances in whole statement
    vector<pa_int3> result;
    void set_requi(int l, int& scch, int& dogian);
    void seperate_word(string S);
    bool search_in(string s, int& rate);
public:
    void Search_all(string s, File_management F, Word_parcel& P);
    void Show_results(File_management F, Word_parcel P);
};
void Add_words(File_management F);
void show_status(File_management F, Word_parcel p);
void MODE1(File_management F, Word_parcel P);
bool Collect_answers(string kq, int stt);
void MODE3(File_management F, Word_parcel P);
void MODE4(Word_parcel P);
void MODE5(File_management F, Word_parcel P);
void MODE6();
int main()
{
    clock_t start;
    start = clock();
    Dict.Collect_data();
    char ch;
    while (true)
    {
        system("cls");
        File_management F;
        Word_parcel P;
        F.Collect(P);
        while (true)
        {
            show_status(F, P);
            cout << clock() - start << "ms\n";
            cout << "1. Tim kiem" << endl << endl;
            cout << "2. Thong ke (x)\n";
            cout << "3. Kiem tra tu vung" << endl << endl;
            cout << "4. Tat ca tu vung\n";
            cout << "5. Chinh sua\n";
            cout << "6  ?\n";
            ch = _getch();
            switch (ch)
            {
            case '1':
                MODE1(F, P);
                break;
            case '2':
                break;
            case '3':
                MODE3(F, P);
                break;
            case '4':
                MODE4(P);
                break;
            case '5':
                MODE5(F, P);
                break;
            case '6':
                MODE6();
                break;
            case -32:
                ch = _getch(); // de lay phim mui ten
                F.Switch_mode(F.mode() + int(ch) - 76);
                P.Update_area(F);
                break;
            default:
                break;
            }
            //Switch mode, update status
            if (ch == 75 || ch == 77) gotoxy(0, 0);
            else system("cls");
            //Files change, need to read again
            if (ch == '3' || ch == '5') break;
            start = clock();
        }
    }
    return 0;
}
void Norming_string(string& s)
{
    if (s == "") return;
    //xoa dau cach cuoi cau
    while (s[s.length() - 1] == ' ') s.erase(s.length() - 1, 1);
    //xoa o giua cau, va tach ki tu ra rieng
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ' && (i == 0 || s[i - 1] == ' '))
        {
            s.erase(i, 1); i--;
        }
        else if ((s[i] >= 33 && s[i] <= 47) || (s[i] >= 58 && s[i] <= 64))
            if (s[i - 1] != ' ')
            {
                s.insert(i, " ");
                i++;
            }
    }
}
void File_management::Update_numofque(int socau)
{
    this->socau = socau;
    fstream f;
    f.open("data/LY_file2.dat", ios::trunc | ios::out);
    f << socau;
    f.close();
}
void File_management::Switch_mode(int k)
{
    if (k < 0) k = n; else if (k > n) k = 0;
    defmode = k;
}
int File_management::mode()
{
    return defmode;
}
string File_management::name_of_file(int k)
{
    return all_file[k];
}
string File_management::deffile()
{
    return ("notebook/" + all_file[defmode] + ".txt");
}
string File_management::deffilef()
{
    return ("data/" + all_file[defmode] + "_f.dat");
}
void File_management::Check_files()
{
    fstream f;
    f.open("data/LY_connected_files.dat");
    if (f.fail()) 
    { 
        cout << "LOI: Khong mo duoc file dia chi: LY_connected_files.dat\n\n"; 
        ERROR_TO_CLOSE(); 
    }
    while (1 > 0)
    {
        n++;
        getline(f, all_file[n]);
        if (all_file[n].length() == 0) { n--; break; }
    }
    f.close();

    for (int i = 1; i <= n; i++)
    {
        defmode = i;
        f.open(deffile());
        if (f.fail())
        {
            cout << "+Khong chua san: " << deffile() << "-->Tu dong tao\n";
            f.close();
            f.open(deffile(), ios::trunc | ios::out); 
        }
        f.close();

        f.open(deffilef());
        if (f.fail())
        {
            cout << "+Khong chua san: " << deffile() << "-->Tu dong tao\n";
            f.close();
            f.open(deffilef(), ios::trunc | ios::out);
        }
        f.close();
    }
    defmode = 0;

    f.open("data/LY_file2.dat");
    if (f.fail()) { cout << "LOI: Khong mo duoc file dia chi: LY_file2.dat\n"; f.close(); ERROR_TO_CLOSE(); }
    f >> socau;
    f.close();
}
void File_management::Read_words(Word_parcel &P)
{
    fstream f1, f2;
    string temp;
    vector<string> line;
    int line_int = 0, fr = 0, ff = 0;
    bool check;


    f1.open(deffile().c_str());
    f2.open(deffilef().c_str());
    P.new_area();
    Word wordp;

    while (true)
    {
        temp = "";
        getline(f1, temp);
        line_int++;
        if (line_int > 1 && (temp == "" || temp[0] != '/' || temp[1] != '/'))
        {
            if (!wordp.Get_word(line, wordp))
            {
                cout << "LOI: DONG KHONG DUNG CU PHAP: \n";
                cout << deffile() << ": \n";
                for (int i = 0; i < line.size(); i++) cout << line[i] << endl;
                ERROR_TO_CLOSE();
            }
            fr = 0; ff = 0;
            f2 >> fr >> ff;
            wordp.fr = fr;
            wordp.fr = ff;
            P.Add_word(wordp);
            line.clear();
        }
        if (temp == "") break;
        line.push_back(temp);
    }
    f1.close();
    f2.close();
}
void File_management::Collect(Word_parcel &P)
{
    Check_files();
    for (int i = 1; i <= n; i++)
    {
        defmode = i;
        Read_words(P);
    }
}
void File_management::Add_file(string s)
{
    fstream f;
    f.open("data/LY_connected_files.dat", ios::trunc | ios::out);
    for (int i = 1; i <= Num_of_file(); i++)
        f << name_of_file(i) << endl;
    f << s << endl;
    f.close();
}
void File_management::Unconnected_files(int* file, int sl)
{
    bool checkedfile[20] = { };
    for (int i = 1; i <= sl; i++)
        checkedfile[file[i]] = true;
    fstream f;
    f.open("data/LY_connected_files.dat", ios::trunc | ios::out);
    for (int i = 1; i <= Num_of_file(); i++)
        if (checkedfile[i] == false) f << name_of_file(i) << endl;
    f.close();
}
void File_management::Add_word(Word W)
{
    vector<string> line;
    line = Word_to_lines(W);
    fstream f;
    f.open(("notebook/" + name_of_file(mode()) + ".txt").c_str(), ios::app);
    for (int i = 0; i < line.size(); i++)
        f << line[i] << endl;
}
void File_management::Update_score(Word_parcel P)
{
    fstream f1;
    for (int i = 1; i <= Num_of_file(); i++)
    {
        if (mode() != 0) i = Num_of_file() + 1;
        else
        {
            Switch_mode(i); //all file mode, switch each mode to write
            P.Update_area(*this);
        }
        f1.open((deffilef()).c_str(), ios::trunc | ios::out);
        for (int i = P.from(); i <= P.to(); i++)
        {
            f1 << P.a[i].fr << " " << P.a[i].ff << endl;
        }
        f1.close();
    }
}
bool Word::Find_word_in_example()
{
    string tw = w;
    tw.erase(tw.length() - 1, 1);
    c1 = Hash.Find(tw, e);
    if (c1 == -1)
    {
        cout << "(LOI: KHONG KHOANH TIM TU VUNG DUOC!) V\n";
        return false;
    }
    c2 = c1;
    //left
    while (c1 - 1 >= 0 && 'a' <= e[c1 - 1] && e[c1 - 1] <= 'z') c1--;
    //right
    while (c2 + 1 < e.length() && 'a' <= e[c2 + 1] && e[c2 + 1] <= 'z') c2++;
    return true;
}
void Word::Get_example()
{
    do { cout << "Mau cau: "; getline(cin, e); } while (e == "");
    Norming_string(e);
}
void Word::Get_smilar_example()
{
    cout << "Mau cau tuong duong: "; getline(cin, e);
    Norming_string(e);
}
void Word::Get_meaning()
{
    do { cout << "Nghia: "; getline(cin, m); } while (m == "");
    Norming_string(m);
}
void Word::Get_note()
{
    string s;
    cout << "Ghi chu: \n";
    while (1 > 0)
    {
        cout << "//";
        s = "";
        getline(cin, s);
        if (s == "") {
            cout << "->HET\n";
            break;
        }
        else GC.push_back(s);
    }
}
void Word::Choose_word_in_example()
{
    vector<string> subwords;
    vector<int> pos_subwords;
    string s;
    int pos, l, next;
    char ch;

    //SEPERATE EXAMPLE
    cout << endl << "-> " << e << endl;
    pos = 0;
    for (int i = 0; i <= e.length(); i++)
    {
        if (e[i] == ' ' || i == e.length())
        {
            subwords.push_back(s);
            pos_subwords.push_back(pos);
            s = "";
            pos = i + 1;

        }
        else s += e[i];
    }

    //COUT A, B, C.. below each words of example
    space(3);
    textcolor(14);
    for (int i = 0; i < subwords.size(); i++)
    {
        l = subwords[i].length();
        space(l - l / 2 - 1);
        cout << char(i + int('A'));
        space(l / 2);
        space(1);
    }

    //Choose words
    textcolor(7);
    l = subwords.size();
    int numofword = 0;
    cout << "\n(Esc de chon lai)";
    do
    {
        next = 0;
        cout << "\nChon tu! : "; w = ""; numofword = 0;
        ch = _getch();
        while (((ch >= 'a') && ch <= char(l - 1 + int('a')))
            || (ch >= 'A' && ch <= char(l - 1 + int('A'))))
        {
            if (ch <= 'Z') ch = ch + ' ';
            pos = int(ch) - 'a';
            textcolor(14);
            cout << subwords[pos] << " ";
            textcolor(7);
            if (next != 0 && pos != next)
            {
                cout << "\n->TU PHAI LIEN TIEP"; next = 0; break;
            }
            w += subwords[pos] + ' '; numofword++;
            if (next == 0) c1 = pos_subwords[pos];
            next = pos + 1;
            ch = _getch();
        }
    } while (int(ch) != 13 || next == 0);
    cout << endl;
    w.erase(w.length() - 1, 1);
    c2 = c1 + w.length() - 1;
    if (numofword > 1) sp = 0;
    else
    {
        sp = Dict.Find_speech(w);
        w = Dict.Baseword(Dict.Find_baseword(sp));
    }
}
string Word::word()
{
    return w;
}
void Word::Print_this_word(bool newword, int searchmode)
{
    if (newword == 1)
    {
        if (searchmode == 1) Print_arow();
        textcolor(14);
        cout << w << endl;;
    }
    space(7); if (searchmode == 2) Print_arow();  else space(3);
    textcolor(8); cout << "+" << m << ": " << " /" << Dict.Speech(sp) << "/\n";
    space(7);  if (searchmode == 3) Print_arow(); else space(3);
    textcolor(7); cout << e; cout << endl;
    if (GC.size() > 0)
    {
        textcolor(7); space(10); cout << "................................\n";
        textcolor(7); space(10); cout << "Ghi chu: \n";
        for (int i = 0; i < GC.size(); i++)
        {
            space(10); if (searchmode == 4 + i) Print_arow(); else space(3);
            textcolor(8);  cout << GC[i] << "; \n";
        }
        textcolor(7); space(10); cout << "--------------------------------\n";
    }
    if (searchmode != 0)//o trang thai tim kiem
    {
        textcolor(3); space(10);
        cout << "%(" << fr << ", " << ff << ")\n";
    }
}
void Word::Print_question()
{
    for (int i = 0; i < c1; i++) cout << e[i];
    textcolor(14); cout << m; textcolor(7);
    for (int i = c2+1; i < e.length(); i++) cout << e[i];
    textcolor(8); cout << " %(" << fr << ", " << ff << ")";
    textcolor(7);
}
bool Word::Get_word(vector<string> line, Word pre)
{
    *this = Word();
    string s = line[0]; //sentence
    if (s[0] == '+')//bo sung cau
    {
        if (pre.w == "") return false;
        s.erase(0, 1);
        w = pre.w; m = pre.m; e = s;
        if (Find_word_in_example() == false) return false;
        sp = Dict.Find_speech(w);
    }
    else
    {
        int for_meaning = 0, count_ = 0, v = 0;
        for (int i = 0; i < s.length(); i++)
        {
            // v la vi tri bat dau tren hang
            if (s[i] == ' ' && v >= 0) v = i + 1; //cap nhat vi tri word 1 tu

            if (s[i] == '\\') v = -(i + 1); //danh dau word nhieu tu
            else if (s[i] == '<')
            {
                if (i == 0) return false;  //truong hop khong xay ra

                c1 = abs(v);
                if (v < 0) c1--; //tru vi tri dau gach \

                c2 = e.length() - 1;
                w = s.substr(abs(v), i - 1 - abs(v) + 1);
                if (v >= 0)
                {
                    sp = Dict.Find_speech(w);
                    w = Dict.Baseword(Dict.Find_baseword(sp));
                }
                else sp = 0;
                count_++; for_meaning = 1;
            }
            else if (s[i] == '>') { for_meaning = 0; count_++; v = 0; }
            else if (for_meaning == 1) m += s[i];
            else if (for_meaning == 0) e += s[i];
        }
        if (count_ != 2) return false;
    }

    for(int i=1; i<line.size(); i++)
    {
        line[i].erase(0, 2);
        GC.push_back(line[i]);
    }
    return true;
}
void Word::Get_word()
{
    Get_example();
    Choose_word_in_example();
    Get_meaning();
    Get_note();
}
bool Word::Get_word(Word pre)
{
    Get_smilar_example();
    if (e == "") return false;
    w = pre.w; 
    if (Find_word_in_example())
    {
        Get_note();
        return true;
    }
    else return false;
}
vector<string> Word_to_lines(Word W)
{
    vector<string> line;
    line.push_back("");
    for (int i = 0; i < W.e.length(); i++)
    {
        if (i == W.c1 && W.sp == 0) line[0] += '\\';
        line[0] += W.e[i];
        if (i == W.c2) line[0] += '<' + W.m + ">";
    }
    for (int i = 0; i < W.GC.size(); i++)
        line.push_back("//" + W.GC[i]);
    return line;
}
void Word_parcel::range_of_this_word(int k, int& u, int& v)
{
    u = k; v = k;
    int op = from();
    op = to();
    while (u - 1 >= from() && a[k].word() == a[u - 1].word()) u--;
    while (v + 1 <= to() && a[k].word() == a[v + 1].word()) v++;
}

int Word_parcel::from()
{
    if (area == 0) return 1;
    return pos_area[area];
}
int Word_parcel::to()
{
    if (area == 0) return n;
    return pos_area[area + 1] - 1;
}
int Word_parcel::find_area_from_pos(int k)
{
    for (int i = 1; i < pos_area.size() - 1; i++)
    {
        if (k >= pos_area[i] && k <= pos_area[i + 1]-1)
            return i;
    }
    return pos_area.size() - 1;
}
int Word_parcel::Num()
{
    if (area == 0) return n;
    return pos_area[area + 1] - pos_area[area];
}
int Word_parcel::progress()
{
    int num = Num();
    if (num == 0) return 0;
    int dem0 = 0, dem1 = 0, dem2 = 0, dem3 = 0, dem = 0;
    for (int i = 1; i <= num; i++)
    {
        if (a[i].fr == 0) dem0++;
        if (a[i].fr == 1) dem1++;
        if (a[i].fr == 2) dem2++;
        if (a[i].fr >= 3) dem3++;
    }
    return int((dem1 + dem2 + dem3) * (float)35 / num + (dem2 + dem3) * (float)30 / num + (dem3 + 0) * (float)35 / num);
}
void Word_parcel::new_area()
{
    int k = pos_area[pos_area.size() - 1];
    pos_area.push_back(k);
}
void Word_parcel::Add_word(Word wordp)
{
    wordp.vgoc = ++n;
    a.push_back(wordp);
    pos_area[pos_area.size() - 1]++;
}
void Word_parcel::sapxepabc()
{
    int u = from();
    int v = n - to();
    sort(a.begin() + u, a.end() - v, sapxepabc_);
}
void Word_parcel::sapxepvgoc()
{
    int u = from();
    int v = n - to();
    sort(a.begin() + u, a.end() - v, sapxepvgoc_);
}
void Word_parcel::sapxepran(int v)
{
    int u = from();
    if (v == -1) v = n - to();
    else v = n - v;
    sort(a.begin() + u, a.end() - v, sapxepran_);
}
void Word_parcel::sapxeptanso()
{
    int u = from();
    int v = n - to();
    sort(a.begin() + u, a.end() - v, sapxeptanso_);
}
void Word_parcel::Print_word(int pos, int stt, int searchmode)
{
    if (pos != 0)
    {
        textcolor(14);
        cout << stt << ")";
        if (searchmode == 0) a[pos].Print_this_word(1);
        else
        {
            int u, v, tsearchmode;
            range_of_this_word(pos, u, v);
            if (searchmode == 1) pos = u;
            for (int i = u; i <= v; i++)
            {
                if (i == pos) tsearchmode = searchmode; else tsearchmode = -1;
                if (i == u) a[i].Print_this_word(1, tsearchmode);
                else a[i].Print_this_word(0, tsearchmode);
            }
        }
    }
    else
    {
        for (int i = from(); i <= to(); i++)
        {
            if (i == from() || a[i].word() != a[i - 1].word())
            {
                textcolor(14);
                cout << stt++ << ") ";
                a[i].Print_this_word(1);
            }
            else a[i].Print_this_word(0);
        }
    }
}
void Search_solution::set_requi(int l, int& scch, int& dogian)
{
    if (l >= 12) { scch = l - 3; dogian = l + 3; }
    else if (l >= 9) { scch = l - 2; dogian = l + 2; }
    else if (l >= 6) { scch = l - 1; dogian = l + 1; }
    else if (l >= 5) { scch = l - 1; dogian = l; }
    else { scch = l; dogian = l; }
}
void Search_solution::seperate_word(string S)
{
    Norming_string(S);
    int scch, dogian;
    string s = "";
    len_of_keyword = 0;
    for (int i = 0; i <= S.length(); i++)
    {
        if (S[i] == ' ' || i == S.length())
        {
            set_requi(s.length(), scch, dogian);
            subwords.push_back({s, scch, dogian});
            len_of_keyword += s.length();
            s = "";
        }
        else s += S[i];
    }
}
bool Search_solution::search_in(string s, int& rate)
{
    rate = 0;
    bool check;
    int wordsfound = 0, scch, dogian, l, scch_cacau = 0;
    int LCS_scch, LCS_dogian, LCS_c1, LCS_c2;
    for (int i = 0; i < subwords.size(); i++)
    {
        l = subwords[i].s.length();
        scch = subwords[i].scch;
        dogian = subwords[i].dogian;

        check = LCS_compare(subwords[i].s, s, LCS_scch, LCS_dogian, LCS_c1, LCS_c2);
        if (check == true && LCS_scch >= scch && LCS_dogian <= dogian)
        {
            wordsfound++; scch_cacau += LCS_scch;
            rate += scch - LCS_scch + LCS_dogian - dogian;
            s.erase(LCS_c1, LCS_c2 - LCS_c1 + 1);
        }
        else rate += (scch + dogian);
    }
    if (scch_cacau <= 2 * len_of_keyword / 3) return false;
    if (subwords.size() == 1 && wordsfound == 1) return true;
    else if (subwords.size() >= 2 && wordsfound >= 2 * subwords.size() / 3) return true;
    else return false;
}
void Search_solution::Search_all(string s, File_management F, Word_parcel& P)
{
    int rate = 0;
    seperate_word(s);

    bool c = 0;
    for (int k = 1; k <= F.Num_of_file(); k++)
    {
        F.Switch_mode(k);
        P.Update_area(F);
        P.sapxepabc();
        for (int i = P.from(); i <= P.to(); i++)
        {
            if (i == P.from() || P.a[i].w != P.a[i - 1].w || c == 0) c = 0;

            if (c == 0 && search_in(P.a[i].w, rate) == true) 
            {
                result.push_back(pa_int3(rate, pa_int2(i, 1))); 
                c = 1; 
            }
            if (c == 0 && search_in(P.a[i].m, rate)) 
            {
                result.push_back(pa_int3(rate, pa_int2(i, 2))); 
                c = 1; 
            }
            if (c == 0 && search_in(P.a[i].e, rate) == true) 
            {
                result.push_back(pa_int3(rate, pa_int2(i, 3))); 
                c = 1; 
            }
            if (c == 0 && P.a[i].GC.size() > 0)
            {
                for (int j = 0; j < P.a[i].GC.size(); j++)
                    if (c == 0 && search_in(P.a[i].GC[j], rate) == true)
                    {
                        result.push_back(pa_int3(rate, pa_int2(i, 4 + j)));
                        c = 1;
                    }
            }
        }
    }
}
void Search_solution::Show_results(File_management F, Word_parcel P)
{
    int mode;
    sort(result.begin(), result.end());
    cout << "Co " << result.size() << " ket qua tim kiem: " << endl << endl;
    for (int i = 0; i < result.size(); i++)
    {
        textcolor(8);
        mode = P.find_area_from_pos(result[i].second.first);
        F.Switch_mode(mode);
        cout << ">" << F.name_of_file(mode) << endl;
        P.Print_word(result[i].second.first, i + 1, result[i].second.second);
    }
}
void Add_words(File_management F)
{
    Word added_word;
    added_word.Get_word();
    F.Add_word(added_word);
    cout << "------------------------------\n";
    cout << "Duoc them vao " << F.deffile() << endl;
    added_word.Print_this_word();

    Word added_word_2;
    while (added_word_2.Get_word(added_word))
    {
        added_word_2.Print_this_word();
        F.Add_word(added_word_2);
        added_word_2 = Word();
    }
}
void show_status(File_management F, Word_parcel p)
{
    cout << "Tai du lieu thanh cong!\n";
    cout << "                                                           \n";
    cout << "                                                           \n";
    gotoxy(0, 1);
    if (F.mode() == 0) cout << ">TAT CA CAC FILE"; else cout << ">" << F.name_of_file(F.mode());
    textcolor(8);
    cout << " " << p.progress() << "%" << " (" << p.Num() << ")\n";
    for (int i = 0; i <= F.Num_of_file(); i++)
    {
        if (i == F.mode()) { textcolor(14); cout << "====="; textcolor(8); }
        else cout << "=====";
    }
    textcolor(7);
    cout << endl;
    cout << "                                                           ";
    gotoxy(0, 3);
}
void MODE1(File_management F, Word_parcel P)
{
    cout << "====================================TIM KIEM===================================\n";
    cout << "NHAP TU KHOA: ";
    string s;
    getline(cin, s);
    cout << "--\n";
    Search_solution S;
    clock_t from;
    from = clock();
    S.Search_all(s, F, P);
    cout << "Tim kiem trong: " << clock() - from << "ms\n";
    S.Show_results(F, P);
    textcolor(7);
    cout << endl;
    system("pause");
}
bool Collect_answers(string kq, int stt)
{
    string traloi;
    int k;
    k = -2; //coi nhu chua chup
    do
    {
        k++; //ban dau k se la -1
        if (k != -1 && k + 1 <= kq.length() / 3)
        {
            cout << "[?] ";
            for (int j = 0; j <= k; j++) cout << kq[j];
            for (int j = k + 1; j < kq.length(); j++) cout << "*";
            cout << endl;
        }
        else if (k + 2 > kq.length() / 3) cout << "(Khong the hien thi them)\n";
        cout << stt << ") ";
        getline(cin, traloi);
    } while (traloi == "?");
    if (traloi == kq) return true;
    return false;
}
void MODE3(File_management F, Word_parcel P)
{
    int socau = min(P.Num(), F.Num_of_que());
    cout << "====================================KIEM TRA TU VUNG===================================\n";
    cout << "Co " << socau << " cau hoi, nhap phim bat ky" << endl << endl;
    char ch;
    ch = _getch();

    //TAO DU LIEU CAU HOI
    srand(time(0));
    //cin>>socau;
    int begin = P.from();
    int pos = P.to();
    P.sapxeptanso(); //main random
    // giai quyet cau chuyen nhieu cau hoi chung 1 fr va random thu tu
    for (int i = begin; i <= P.to(); i++)
    {
        if (i - begin + 1 > socau && P.a[i].fr*2 + P.a[i].ff != P.a[i - 1].fr*2 + P.a[i - 1].ff)
        {
            pos = i - 1; break;
        }
        P.a[i].ran = (rand() % 101) + 101 * (P.a[i].fr*2 + P.a[i].ff);
    }
    P.sapxepran(pos); // thay doi thu thu trong pham vi
    for (int i = 1; i <= socau; i++) P.a[i].ran = (rand() % 101);
    P.sapxepran(begin + socau - 1);

    //IN CAU HOI
    for (int i = begin; i <= begin + socau - 1; i++)
    {
        cout << i << ") ";
        P.a[i].Print_question();
        cout << "\n\n";
    }

    //LAY CAU TRA LOI
    bool correct;
    bool* ans = new bool[P.to() + 1];
    cout << endl << "Nhap dap an (go ? de hien goi y): \n";
    for (int i = begin; i <= begin + socau - 1; i++)
    {
        correct = Collect_answers(P.a[i].word(), i - begin + 1);
        if (correct == true)
        {
            cout << "-O\n";
            P.a[i].fr ++; ans[i] = 1;
        }
        else {
            cout << "-X\n";
            P.a[i].fr = min(1, P.a[i].fr);
            ans[i] = 0;
        }
    }

    //LUU KET QUA & IN DAP AN
    cout << endl << "====KET QUA & TU VUNG====\n";
    for (int i = begin; i <= begin + socau - 1; i++)
    {
        P.a[i].ff++;
        if (ans[i] == false)
        {
            textcolor(14);
            cout << i - begin + 1 << ")";
            P.a[i].Print_this_word(1, -1);
        }
    }
    P.sapxepvgoc();
    F.Update_score(P);
    delete[] ans;
    textcolor(7);
    cout << endl;
    system("pause");
}
void MODE4(Word_parcel P)
{
    cout << "====================================TAT CA TU VUNG===================================\n";
    cout << "Tu vung duoc sap xep theo thu tu ban chu cai" << endl << endl;

    P.sapxepabc();
    P.Print_word();
    textcolor(7);
    cout << endl;
    system("pause");
}
void MODE5(File_management F, Word_parcel P)
{
    cout << "====================================CHINH  SUA===================================" << endl << endl;
    cout << "-So cau hoi moi bai tap: " << F.Num_of_que() << endl;
    cout << "-------------------------------\n";
    cout << "-Bo tu vung da duoc ket noi: \n";
    for (int i = 1; i <= F.Num_of_file(); i++)
    {
        space(5);  cout << "+" << i << ": " << F.name_of_file(i) << endl;
    }

    cout << "-------------------------------\n";
    string lenh;
    cout << "5. Them tu vung\n" << "2. Ket noi bo tu vung\n" << "3. Huy ket noi bo tu vung\n" << "4. Sua so cau hoi\n";
    cout << "-------\n";
    char ch;
    ch = _getch();
    if (ch == '5')
    {
        cout << "====================================THEM TU VUNG===================================\n";
        textcolor(8);
        if (F.mode() == 0) cout << ">TAT CA CAC FILE\n"; else cout << ">" << F.name_of_file(F.mode()) << endl;
        textcolor(7);
        if (F.mode() != 0) Add_words(F);
        else cout << "KHONG THEM DUOC!\n";
    }
    else if (ch == '2')
    {
        string s;
        cout << "THEM FILE > ";
        getline(cin, s);
        F.Add_file(s);
    }
    else if (ch == '3')
    {
        string s;
        int sl;
        do { cout << "SO LUONG >"; cin >> sl; } while (sl<1 || sl>F.Num_of_file());
        int file[20];
        int tam;
        cout << "NHAP STT FILE! \n";
        for (int i = 1; i <= sl; i++)
        {
            cout << "-" << i << ": "; cin >> tam;
            if (tam <= 0 || tam > F.Num_of_file())
            {
                cout << "LOI\n";
                i--;
                continue;
            }
            file[i] = tam;
            cout << " X " << F.name_of_file(tam) << endl;
        }
        F.Unconnected_files(file, sl);
    }
    else if (ch == '4')
    {
        int socau;
        cout << "SO CAU > ";
        cin >> socau;
        F.Update_numofque(socau);
    }
    textcolor(7);
    cout << endl;
    system("pause");
}
void MODE6()
{
    cout << "====================================THONG TIN===================================" << endl << endl;
    cout << "--------------------------------------------\n";
    textcolor(15);
    cout << "LY_WORD (Update Version 10/6/2021)\n";
    textcolor(9);
    cout << "->LY Words-->\n\n";
    textcolor(7);
    cout << endl;
    system("pause");
}
