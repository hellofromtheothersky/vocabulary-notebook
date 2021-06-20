#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include<conio.h> //de dung duoc ham _getch doc ki tu tu ban phim
#include"screen.h"
#include"searchstring.h"
using namespace std;
typedef pair<int, int> pa_int;
typedef pair<string, pa_int> pa_spa;
typedef pair<int, pa_int> int_pa_int;
bool LOI = false;
Hash_resource Hash;
void Norming_string(string& s);
class Family_word_speech
{
    int n;
    //string* word = new string[133800];
    //string* speech = new string[133800];
    string word[133800];
    string speech[133800];
    bool s_es_suffix(string s);
    bool ing_ed_suffix(string s);
    bool Check_similar(string a, string b);
public:
    Family_word_speech()
    {
        n = 0;
        speech[0] = "?";
    }
    void Collect_data();
    int Num();
    string Baseword(int k);
    string Speech(int k);
    void Find_baseword_speech(string s, int& basew, int& sp);
};
Family_word_speech family;
class Word;
class Word_parcel;
class file_read_class
{
    string all_file[20];
    int defmode, socau, n;
public:
    int Num_of_que();
    int Num();
    void Switch_mode(int k);
    int mode();
    string name_of_file(int k);
    string deffile();
    string deffilef();
    void Collect();
    void Change_numofque(int socau);
    void Add_file(string s);
    void Unconnected_files(int* file, int sl);
    void Add_word(Word W);
    void Update_score(Word_parcel P);
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
    int c2 = -1; //end positon of word in the example
    bool Find_c1_c2(string a, string b);
    void Reform_setspeech();
    void Get_example();
    void Get_smilar_example();
    void Get_meaning();
    void Get_note();
    void Choose_word_in_example();
public:
    int vgoc; //dung de xep dung trat tu, hoac chua dia chi file khi search
    int fr = 0; //diem, file khac
    int ff = 0; //tan so xuat hien
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
    bool Analyze(string s, Word& pre);
    void Get_word();
    bool Get_word(Word pre);
    friend class Seach_solution;
    friend vector<string> Word_to_lines(Word);
    friend void Make_print_question(Word&, int);
};
class Word_parcel
{
    vector<Word> a;
    vector<int> Start;
    int n = 0;
    static bool sapxepabc_(Word u, Word v)
    {
        return u.word() < v.word();
    }
    static bool sapxepvgoc_(Word u, Word v)
    {
        return u.vgoc < v.vgoc;
    }
    static bool sapxeptanso_(Word u, const Word v)
    {
        if (u.fr*2 + u.ff == v.fr*2 + v.ff) return u.ff < v.ff;
        return u.fr*2 + u.ff < v.fr*2 + v.ff;
    }
    static bool sapxepran_(Word u, const Word v)
    {
        return u.ran < v.ran;
    }
    void range_of_this_word(file_read_class f, int k, int& u, int& v);
public:
    Word_parcel()
    {
        Start.push_back(0);
        Start.push_back(1);
        a.push_back(Word());
    }
    int start(file_read_class f);
    int end(file_read_class f);
    int findmodefrompos(int k);
    int Num(file_read_class f);
    int progress(file_read_class f);
    void Collect_data(file_read_class file_read);
    void sapxepabc(file_read_class f);
    void sapxepvgoc(file_read_class f);
    void sapxepran(file_read_class f, int v = -1);
    void sapxeptanso(file_read_class f);
    void Print_word(file_read_class f, int pos = 0, int stt = 1, int searchmode = 0);
    friend class Seach_solution;
    friend void MODE3(file_read_class, Word_parcel);
    friend void file_read_class::Update_score(Word_parcel P);
};
class Seach_solution
{
private:
    vector<pa_spa> subwords;
    int length; //length containing no space distances in whole statement
    vector<int_pa_int> result;
    void set_requi(int l, int& scch, int& dogian);
    void seperate_word(string S);
    bool search_in_string(string s, int& rate);
public:
    void Search_all(string s, file_read_class f, Word_parcel& P);
    void Show_results(file_read_class f, Word_parcel P);
};
void Add_words(file_read_class f);
void show_status(file_read_class f, Word_parcel p);
void Collect_all_files(file_read_class f, Word_parcel& p);
void MODE1(file_read_class f, Word_parcel P);
bool Collect_answers(string kq, int stt);
void MODE3(file_read_class f, Word_parcel P);
void MODE4(file_read_class f, Word_parcel P);
void MODE5(file_read_class f, Word_parcel P);
void MODE6();
int main()
{
    clock_t start;
    start = clock();
    family.Collect_data();
    gotoxy(0, 0);
    //start = clock();
    bool update = true;
    char ch;
    while (1 > 0)
    {
        if (update == true)
        {
            system("cls");
            update = false;
            file_read_class file_read;
            Word_parcel P;
            file_read.Collect();
            Collect_all_files(file_read, P);
            while (1 > 0)
            {
                show_status(file_read, P);
                cout << clock() - start << "ms\n";
                cout << "1. Tim kiem" << endl << endl;
                cout << "2. Thong ke (x)\n";
                cout << "3. Kiem tra tu vung" << endl << endl;
                cout << "4. Tat ca tu vung\n";
                cout << "5. Chinh sua\n";
                cout << "6  ?\n";
                ch = _getch();
                if (int(ch) == 27) break;
                else if (ch == '1') MODE1(file_read, P);
                //else if (ch == '2') { MODE2(); system("pause"); }
                else if (ch == '3')
                {
                    MODE3(file_read, P);
                    update = true;
                    break;

                }
                else if (ch == '4')  MODE4(file_read, P);
                else if (ch == '5')
                {
                    MODE5(file_read, P);
                    update = true;
                    break;
                }
                else if (ch == '6') MODE6();
                else if (int(ch) == 75) file_read.Switch_mode(file_read.mode() - 1);
                else if (int(ch) == 77) file_read.Switch_mode(file_read.mode() + 1);

                if (int(ch) == 75 || int(ch) == 77) gotoxy(0, 0); else system("cls");
                start = clock();
                //system("cls");
            }
        }
    }
    return 0;
}
void Norming_string(string& s)
{
    if (s == "") return;
    while (s[s.length() - 1] == ' ') s.erase(s.length() - 1, 1);
    for (int i = 0; i < s.length(); i++)
        if (s[i] == ' ' && (i == 0 || s[i - 1] == ' '))
        {
            s.erase(i, 1); i--;
        }
}

bool Family_word_speech::s_es_suffix(string s)
{
    if (s.length() <= 2) return false;
    int d = s.length() - 1;
    if (s[d - 1] == 'e' && s[d] == 's') return true;
    if (s[d - 1] != 's' && s[d] == 's') return true;
    return false;
}
bool Family_word_speech::ing_ed_suffix(string s)
{
    if (s.length() <= 3) return false;
    int d = s.length() - 1;
    if (s[d - 2] != 'e' && s[d - 1] == 'e' && s[d] == 'd') return true;
    if (s[d - 2] == 'i' && s[d - 1] == 'n' && s[d] == 'g') return true;
    return false;
}
bool Family_word_speech::Check_similar(string a, string b)
{
    int l = min(a.length(), b.length());
    for (int i = l - 2; i >= 0; i--)
        if (a[i] != b[i]) return false;
    return true;
}

void Family_word_speech::Collect_data()
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
int Family_word_speech::Num()
{
    return n;
}
string Family_word_speech::Baseword(int k)
{
    return word[k];
}
string Family_word_speech::Speech(int k)
{
    return speech[k];
}
void Family_word_speech::Find_baseword_speech(string s, int& basew, int& sp)
{
    int l = 1, r = Num(), mid, key = -1;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (word[mid] == s) { key = mid; break; }
        else if (word[mid] < s) l = mid + 1;
        else r = mid - 1;
    }
    if (key == -1) { basew = 0; sp = 0; return; }
    string tam;
    sp = key;
    tam = word[sp];
    while (s_es_suffix(word[key]) == true
        || ing_ed_suffix(word[key]) == true
        || word[key].length() > word[sp].length())
        key--;
    if (Check_similar(word[sp], word[key]) == false) basew = sp;
    else basew = key;
}

int file_read_class::Num_of_que()
{
    return socau;
}
int file_read_class::Num()
{
    return n;
}
void file_read_class::Change_numofque(int socau)
{
    this->socau = socau;
    fstream f;
    f.open("data/LY_file2.dat", ios::trunc | ios::out);
    f << socau;
    f.close();
}
void file_read_class::Switch_mode(int k)
{
    if (k < 0) k = n; else if (k > n) k = 0;
    defmode = k;
}
int file_read_class::mode()
{
    return defmode;
}
string file_read_class::name_of_file(int k)
{
    return all_file[k];
}
string file_read_class::deffile()
{
    return ("notebook/" + all_file[defmode] + ".txt");
}
string file_read_class::deffilef()
{
    return ("data/" + all_file[defmode] + "_f.dat");
}
void file_read_class::Collect()
{
    n = 0;

    fstream f;
    f.open("data/LY_connected_files.dat");
    if (f.fail()) { cout << "LOI: Khong mo duoc file dia chi: LY_connected_files.dat\n\n"; ERROR_TO_CLOSE(); }
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
            cout << "+Khong mo duoc file: " << deffile() << ", tu dong tao file!\n";
            f.close();
            f.open(deffile(), ios::trunc | ios::out);
            LOI = true;
        }
        f.close();

        f.open(deffilef());
        if (f.fail())
        {
            cout << "+Khong mo duoc file: " << deffilef() << ", tu dong tao file!\n";
            f.close();
            f.open(deffilef(), ios::trunc | ios::out);
        }
        f.close();
    }
    defmode = 0;

    f.open("data/LY_file2.dat");
    if (f.fail()) { cout << "Khong mo duoc file 'LY_file2.dat'\n"; f.close(); ERROR_TO_CLOSE(); }
    f >> socau;
    f.close();
}
void file_read_class::Add_file(string s)
{
    fstream f;
    f.open("data/LY_connected_files.dat", ios::trunc | ios::out);
    for (int i = 1; i <= Num(); i++)
        f << name_of_file(i) << endl;
    f << s << endl;
    f.close();
}
void file_read_class::Unconnected_files(int* file, int sl)
{
    bool checkedfile[20] = { };
    for (int i = 1; i <= sl; i++)
        checkedfile[file[i]] = true;
    fstream f;
    f.open("data/LY_connected_files.dat", ios::trunc | ios::out);
    for (int i = 1; i <= Num(); i++)
        if (checkedfile[i] == false) f << name_of_file(i) << endl;
    f.close();
}
void file_read_class::Add_word(Word W)
{
    vector<string> line;
    line = Word_to_lines(W);
    fstream f;
    f.open(("notebook/" + name_of_file(mode()) + ".txt").c_str(), ios::app);
    for (int i = 0; i < line.size(); i++)
        f << line[i] << endl;
}
void file_read_class::Update_score(Word_parcel P)
{
    fstream f1;
    for (int i = 1; i <= Num(); i++)
    {
        if (mode() != 0) i = Num() + 1;
        else Switch_mode(i); //all file mode, switch each mode to write
        f1.open((deffilef()).c_str(), ios::trunc | ios::out);
        for (int i = P.start(*this); i <= P.end(*this); i++)
        {
            f1 << P.a[i].fr << " " << P.a[i].ff << endl;
        }
        f1.close();
    }
}
bool Word::Find_c1_c2(string a, string b)
{
    c1 = Hash.Find(a, b);
    if (c1 == -1)
    {
        cout << "(LOI: KHONG KHOANH TIM TU VUNG DUOC!) V\n";
        return false;
    }
    else
    {
        c2 = c1;
        //right
        while (c1 - 1 >= 0 && 'a' <= e[c1 - 1] && e[c1 - 1] <= 'z') c1--;
        //left
        while (c2 + 1 <= e.length() && 'a' <= e[c2 + 1] && e[c2 + 1] <= 'z') c2++;
    }
}
void Word::Reform_setspeech()
{
    int basew;
    family.Find_baseword_speech(w, basew, sp);
    if (sp == 0)
    {
    }
    else
    {
        w = family.Baseword(basew);
    }
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
    cout << "\Ghi chu: \n";
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
    else Reform_setspeech();
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
    textcolor(8); cout << "+" << m << ": " << " /" << family.Speech(sp) << "/\n";
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
bool Word::Analyze(string s, Word& pre)
{
    int for_meaning, count_, v;
    if (s[0] == '/' && s[1] == '/') //ghi chu
    {
        if (pre.w == "") return false;
        s.erase(0, 2);
        pre.GC.push_back(s);
        return true;
    }
    if (s[0] == '+')//bo sung cau
    {
        if (pre.w == "") return false;
        s.erase(0, 1);
        w = pre.w; m = pre.m; e = s; sp = pre.sp;
        string tw = w;
        tw.erase(tw.length() - 1, 1);
        if (Find_c1_c2(tw, s) == false) return false;
        //Reform_setspeech();
        return true;
    }
    v = 0; for_meaning = 0; count_ = 0;
    for (int i = 0; i < s.length(); i++)
    {
        // v la vi tri bat dau word tren example
        if (s[i] == ' ' && v >= 0) v = i + 1;

        if (s[i] == '\\') v = -(i + 1); //danh dau word nhieu tu
        else if (s[i] == '<')
        {
            if (i == 0) return false;
            if (v < 0) c1 = abs(v + 1); //vi tri tren example
            else c1 = abs(v); //vi tri tren example
            c2 = e.length() - 1;
            for (int j = abs(v); j <= i - 1; j++) w += s[j];
            if (v >= 0) Reform_setspeech();
            else sp = 0;
            count_++; for_meaning = 1;
        }
        else if (s[i] == '>') { for_meaning = 0; count_++; v = 0; }
        else if (for_meaning == 1) m += s[i];
        else if (for_meaning == 0) e += s[i];
    }
    if (count_ != 2) return false;
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
    string tw;
    Get_smilar_example();
    if (e == "") {
        cout << "-HET\n"; return false;
    }
    tw = pre.w;
    c1 = Hash.Find(tw.erase(tw.length() - 1, 1), e);
    if (c1 == -1) {
        cout << "KHONG KHOANH VUNG DUOC TU VUNG\n"; return false;
    }
    m = pre.m; w = pre.w; sp = pre.sp;
    c2 = c1 + w.length() - 1;
    Get_note();
    return true;
}
vector<string> Word_to_lines(Word W)
{
    vector<string> line;
    line.push_back("");
    for (int i = 0; i < W.e.length(); i++)
    {
        if (i == W.c1 && W.sp == 0) line[0] += '/';
        line[0] += W.e[i];
        if (i == W.c2) line[0] += '<' + W.m + ">";
    }
    for (int i = 0; i < W.GC.size(); i++)
        line.push_back("//" + W.GC[i]);
    return line;
}
void Make_print_question(Word& W, int stt = 0)
{
    cout << stt << ")";
    W.w = "";
    for (int i = 0; i < W.e.length(); i++)
    {
        if (i >= W.c1 && i < W.c2) W.w += W.e[i];
        else if (i == W.c2) { textcolor(14); cout << W.m; textcolor(7); W.w += W.e[i]; }
        else  cout << W.e[i];
    }
    textcolor(8); cout << " %(" << W.fr << ", " << W.ff << ")\n";
    textcolor(7);
}

void Word_parcel::range_of_this_word(file_read_class f, int k, int& u, int& v)
{
    u = k; v = k;
    int op = start(f);
    op = end(f);
    while (u - 1 >= start(f) && a[k].word() == a[u - 1].word()) u--;
    while (v + 1 <= end(f) && a[k].word() == a[v + 1].word()) v++;
}

int Word_parcel::start(file_read_class f)
{
    if (f.mode() == 0) return 1;
    return Start[f.mode()];
}
int Word_parcel::end(file_read_class f)
{
    if (f.mode() == 0) return n;
    return Start[f.mode() + 1] - 1;
}
int Word_parcel::findmodefrompos(int k)
{
    for (int i = 1; i < Start.size() - 1; i++)
    {
        if (k >= Start[i] && k <= Start[i + 1])
            return i;
    }
    return Start.size() - 1;
}
int Word_parcel::Num(file_read_class f)
{
    if (f.mode() == 0) return n;
    return Start[f.mode() + 1] - Start[f.mode()];
}
int Word_parcel::progress(file_read_class f)
{
    int num = Num(f);
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
void Word_parcel::Collect_data(file_read_class file_read)
{
    fstream f1, f2;
    string s;
    int line = 0, fr, ff;
    bool check;

    f1.open(file_read.deffile().c_str());
    f2.open(file_read.deffilef().c_str());

    while (!f1.eof())
    {
        Word cur;
        s = "";
        getline(f1, s);
        if (s.length() == 0) break;
        line++;
        //set data for word
        if (line == 1) check = cur.Analyze(s, cur);
        else check = cur.Analyze(s, a[n]);
        if (check == false)
        {
            cout << "LOI: DONG KHONG DUNG CU PHAP: \n";
            cout << file_read.deffile() << "/line" << line << ": " << s << endl;
            ERROR_TO_CLOSE();
        }
        //save
        if (s[0] != '/' && s[1] != '/')
        {
            n++;
            fr = 0; ff = 0;
            f2 >> fr >> ff;
            //set data for question
            cur.fr = fr;
            cur.ff = ff;
            cur.vgoc = n;
            a.push_back(cur);
        }
    }

    f1.close();
    f2.close();
    Start.push_back(n + 1);
}
void Word_parcel::sapxepabc(file_read_class f)
{
    int u = start(f);
    int v = n - end(f);
    sort(a.begin() + u, a.end() - v, sapxepabc_);
}
void Word_parcel::sapxepvgoc(file_read_class f)
{
    int u = start(f);
    int v = n - end(f);
    sort(a.begin() + u, a.end() - v, sapxepvgoc_);
}
void Word_parcel::sapxepran(file_read_class f, int v)
{
    int u = start(f);
    if (v == -1) v = n - end(f);
    else v = n - v;
    sort(a.begin() + u, a.end() - v, sapxepran_);
}
void Word_parcel::sapxeptanso(file_read_class f)
{
    int u = start(f);
    int v = n - end(f);
    sort(a.begin() + u, a.end() - v, sapxeptanso_);
}
void Word_parcel::Print_word(file_read_class f, int pos, int stt, int searchmode)
{
    if (pos != 0)
    {
        textcolor(14);
        cout << stt << ")";
        if (searchmode == 0) a[pos].Print_this_word(1);
        else
        {
            int u, v, tsearchmode;
            range_of_this_word(f, pos, u, v);
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
        for (int i = start(f); i <= end(f); i++)
        {
            if (i == start(f) || a[i].word() != a[i - 1].word())
            {
                textcolor(14);
                cout << stt++ << ") ";
                a[i].Print_this_word(1);
            }
            else a[i].Print_this_word(0);
        }
    }
}
void Seach_solution::set_requi(int l, int& scch, int& dogian)
{
    if (l >= 12) { scch = l - 3; dogian = l + 3; }
    else if (l >= 9) { scch = l - 2; dogian = l + 2; }
    else if (l >= 6) { scch = l - 1; dogian = l + 1; }
    else if (l >= 5) { scch = l - 1; dogian = l; }
    else { scch = l; dogian = l; }
}
void Seach_solution::seperate_word(string S)
{
    Norming_string(S);
    int scch, dogian;
    string s = "";
    length = 0;
    for (int i = 0; i <= S.length(); i++)
    {
        if (S[i] == ' ' || i == S.length())
        {
            set_requi(s.length(), scch, dogian);
            subwords.push_back(pa_spa(s, pa_int(scch, dogian)));
            length += s.length();
            s = "";
        }
        else s += S[i];
    }
}
bool Seach_solution::search_in_string(string s, int& rate)
{
    rate = 0;
    bool check;
    int wordsfound = 0, scch, dogian, l, scch_cacau = 0;
    int LCS_scch, LCS_dogian, LCS_c1, LCS_c2;
    for (int i = 0; i < subwords.size(); i++)
    {
        l = subwords[i].first.length();
        scch = subwords[i].second.first;
        dogian = subwords[i].second.second;

        check = LCS_compare(subwords[i].first, s, LCS_scch, LCS_dogian, LCS_c1, LCS_c2);
        if (check == true && LCS_scch >= scch && LCS_dogian <= dogian)
        {
            wordsfound++; scch_cacau += LCS_scch;
            rate += scch - LCS_scch + LCS_dogian - dogian;
            s.erase(LCS_c1, LCS_c2 - LCS_c1 + 1);
        }
        else rate += (scch + dogian);
    }
    if (scch_cacau <= 2 * length / 3) return false;
    if (subwords.size() == 1 && wordsfound == 1) return true;
    else if (subwords.size() >= 2 && wordsfound >= 2 * subwords.size() / 3) return true;
    else return false;
}
void Seach_solution::Search_all(string s, file_read_class f, Word_parcel& P)
{
    int rate = 0;
    seperate_word(s);

    bool c = 0;
    for (int k = 1; k <= f.Num(); k++)
    {
        f.Switch_mode(k);
        P.sapxepabc(f);
        for (int i = P.start(f); i <= P.end(f); i++)
        {
            if (i == P.start(f) || P.a[i].w != P.a[i - 1].w || c == 0) c = 0;

            if (c == 0 && search_in_string(P.a[i].w, rate) == true) {
                result.push_back(int_pa_int(rate, pa_int(i, 1))); c = 1; //cout<<LCS_scch<<" "<<LCS_c1<<" "<<LCS_c2<<endl<<a[i].w<<endl; for(int o=LCS_c1; o<=LCS_c2; o++) cout<<a[i].w[o]; cout<<endl;
            }
            if (c == 0 && search_in_string(P.a[i].m, rate) == true) {
                result.push_back(int_pa_int(rate, pa_int(i, 2))); c = 1; //cout<<LCS_scch<<" "<<LCS_c1<<" "<<LCS_c2<<endl<<a[i].m<<endl; for(int o=LCS_c1; o<=LCS_c2; o++) cout<<a[i].m[o]; cout<<endl;
            }
            if (c == 0 && search_in_string(P.a[i].e, rate) == true) {
                result.push_back(int_pa_int(rate, pa_int(i, 3))); c = 1; //cout<<LCS_scch<<" "<<LCS_c1<<" "<<LCS_c2<<endl<<a[i].e<<endl; for(int o=LCS_c1; o<=LCS_c2; o++) cout<<a[i].e[o]; cout<<endl;
            }
            if (c == 0 && P.a[i].GC.size() > 0)
            {
                for (int j = 0; j < P.a[i].GC.size(); j++)
                    if (c == 0 && search_in_string(P.a[i].GC[j], rate) == true)
                    {
                        result.push_back(int_pa_int(rate, pa_int(i, 4 + j)));
                        c = 1;
                    }
            }
        }
    }
}
void Seach_solution::Show_results(file_read_class f, Word_parcel P)
{
    int mode;
    sort(result.begin(), result.end());
    cout << "Co " << result.size() << " ket qua tim kiem: " << endl << endl;
    for (int i = 0; i < result.size(); i++)
    {
        textcolor(8);
        mode = P.findmodefrompos(result[i].second.first);
        f.Switch_mode(mode);
        cout << ">" << f.name_of_file(mode) << endl;
        P.Print_word(f, result[i].second.first, i + 1, result[i].second.second);
    }
}
void Add_words(file_read_class f)
{
    Word added_word;
    added_word.Get_word();
    f.Add_word(added_word);
    cout << "------------------------------\n";
    cout << "Duoc them vao " << f.deffile() << endl;
    added_word.Print_this_word();

    Word added_word_2;
    bool check = added_word_2.Get_word(added_word);
    while (check == true)
    {
        added_word_2.Print_this_word();
        f.Add_word(added_word_2);
        added_word_2 = Word();
        check = added_word_2.Get_word(added_word);
    }
}
void show_status(file_read_class f, Word_parcel p)
{
    if (LOI == false) cout << "Tai du lieu thanh cong!\n";
    else
    {
        cout << "Loi khong tim duoc phat am cho vai tu!\n";
    }
    cout << "                                                           \n";
    cout << "                                                           \n";
    gotoxy(0, 1);
    if (f.mode() == 0) cout << ">TAT CA CAC FILE"; else cout << ">" << f.name_of_file(f.mode());
    textcolor(8);
    cout << " " << p.progress(f) << "%" << " (" << p.Num(f) << ")\n";
    for (int i = 0; i <= f.Num(); i++)
    {
        if (i == f.mode()) { textcolor(14); cout << "====="; textcolor(8); }
        else cout << "=====";
    }
    textcolor(7);
    cout << endl;
    cout << "                                                           ";
    gotoxy(0, 3);
}
void Collect_all_files(file_read_class f, Word_parcel& p)
{
    int save_defmode = f.mode();
    for (int i = 1; i <= f.Num(); i++)
    {
        f.Switch_mode(i);
        p.Collect_data(f);
    }
}
void MODE1(file_read_class f, Word_parcel P)
{
    cout << "====================================TIM KIEM===================================\n";
    cout << "NHAP TU KHOA: ";
    string s;
    getline(cin, s);
    cout << "--\n";
    Seach_solution S;
    clock_t start;
    start = clock();
    S.Search_all(s, f, P);
    cout << "Tim kiem trong: " << clock() - start << "ms\n";
    S.Show_results(f, P);
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
void MODE3(file_read_class f, Word_parcel P)
{
    int socau = min(P.Num(f), f.Num_of_que());
    cout << "====================================KIEM TRA TU VUNG===================================\n";
    cout << "Co " << socau << " cau hoi, nhap phim bat ky" << endl << endl;
    char ch;
    ch = _getch();

    //TAO DU LIEU CAU HOI
    srand(time(0));
    //cin>>socau;
    int begin = P.start(f);
    int pos = P.end(f);
    P.sapxeptanso(f); //main random
    // giai quyet cau chuyen nhieu cau hoi chung 1 fr va random thu tu
    for (int i = begin; i <= P.end(f); i++)
    {
        if (i - begin + 1 > socau && P.a[i].fr*2 + P.a[i].ff != P.a[i - 1].fr*2 + P.a[i - 1].ff)
        {
            pos = i - 1; break;
        }
        P.a[i].ran = (rand() % 101) + 101 * (P.a[i].fr*2 + P.a[i].ff);
    }
    P.sapxepran(f, pos); // thay doi thu thu trong pham vi
    for (int i = 1; i <= socau; i++) P.a[i].ran = (rand() % 101);
    P.sapxepran(f, begin + socau - 1);

    //IN CAU HOI
    for (int i = begin; i <= begin + socau - 1; i++)
        Make_print_question(P.a[i], i - begin + 1);

    //LAY CAU TRA LOI
    bool correct;
    bool* ans = new bool[P.end(f) + 1];
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
    P.sapxepvgoc(f);
    f.Update_score(P);
    delete[] ans;
    textcolor(7);
    cout << endl;
    system("pause");
}
void MODE4(file_read_class f, Word_parcel P)
{
    cout << "====================================TAT CA TU VUNG===================================\n";
    cout << "Tu vung duoc sap xep theo thu tu ban chu cai" << endl << endl;

    P.sapxepabc(f);
    P.Print_word(f);
    textcolor(7);
    cout << endl;
    system("pause");
}
void MODE5(file_read_class f, Word_parcel P)
{
    cout << "====================================CHINH  SUA===================================" << endl << endl;
    cout << "-So cau hoi moi bai tap: " << f.Num_of_que() << endl;
    cout << "-------------------------------\n";
    cout << "-Bo tu vung da duoc ket noi: \n";
    for (int i = 1; i <= f.Num(); i++)
    {
        space(5);  cout << "+" << i << ": " << f.name_of_file(i) << endl;
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
        if (f.mode() == 0) cout << ">TAT CA CAC FILE\n"; else cout << ">" << f.name_of_file(f.mode()) << endl;
        textcolor(7);
        if (f.mode() != 0) Add_words(f);
        else cout << "KHONG THEM DUOC!\n";
    }
    else if (ch == '2')
    {
        string s;
        cout << "THEM FILE > ";
        getline(cin, s);
        f.Add_file(s);
    }
    else if (ch == '3')
    {
        string s;
        int sl;
        do { cout << "SO LUONG >"; cin >> sl; } while (sl<1 || sl>f.Num());
        int file[20];
        int tam;
        cout << "NHAP STT FILE! \n";
        for (int i = 1; i <= sl; i++)
        {
            cout << "-" << i << ": "; cin >> tam;
            if (tam <= 0 || tam > f.Num())
            {
                cout << "LOI\n";
                i--;
                continue;
            }
            file[i] = tam;
            cout << " X " << f.name_of_file(tam) << endl;
        }
        f.Unconnected_files(file, sl);
    }
    else if (ch == '4')
    {
        int socau;
        cout << "SO CAU > ";
        cin >> socau;
        f.Change_numofque(socau);
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
