#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <typeinfo>
using namespace std;

class Masina
{
protected:
    float lungime;
    int locuri;
    int pret;
    int an_fabricatie;
    int zi;
    int luna;
    int an;
public:

    Masina (int lung = -1, int loc = -1, int p = -1, int an_f = -1, int z = -1, int l = -1, int a = -1)
    {
        lungime = lung;
        locuri = loc;
        pret = p;
        an_fabricatie = an_f;
        zi = z;
        luna = l;
        an = a;
    }

    void operator= (Masina k)
    {
        lungime = k.lungime;
        locuri = k.locuri;
        pret = k.pret;
        an_fabricatie = k.an_fabricatie;
        zi = k.zi;
        luna = k.luna;
        an = k.an;
    }

    friend istream& operator>> (istream &in, Masina &k)
    {
        in >> k.lungime >> k.locuri >> k.pret >> k.an_fabricatie >> k.zi >> k.luna >> k.an;

        try
        {
            if (k.lungime >= 10 || k.lungime <= 2 || k.locuri < 2 || k.locuri > 8 || k.an_fabricatie < 1850 || k.an_fabricatie > 2020)
                throw (1);

        }
        catch(int ddd){
            cout << "Masina urmatoare nu se incadreaza in standardele unei masini normale??? \n\n";
            cout << k;
            exit(0);
        }

        return in;
    }

    void afisare_masina()
    {
        cout << "Lungime: " << lungime << '\n';
        cout << "Numar locuri: " << locuri << '\n';
        cout << "Pret: " << pret << '\n';
        cout << "An fabricatie: " << an_fabricatie << '\n';
        cout << "Data adaugarii: " << zi << "-" << luna << "-" << an;
    }

    virtual void afis()
    {
        afisare_masina();
        cout << "\n\n";
    }

    friend ostream& operator<< (ostream &out, Masina &k)
    {
        k.afis();
        return out;
    }

};

class MINI : public Masina
{
public:

    MINI(int lung = -1, int loc = -1, int p = -1, int an_f = -1, int z = -1, int l = -1, int a = -1) : Masina(lung, loc, p, an_f, z, l, a) {}

    friend istream& operator>> (istream &in, MINI &k)
    {
        in >> (Masina&) k;
        try
        {
            if (k.lungime >= 4)
                throw (1);

        }
        catch(int ddd){
            cout << "Masina urmatoare nu se incadreaza in standardele clasei 'MINI' \n\n";
            cout << k;
            exit(0);
        }
        return in;
    }

    void afis()
    {
        afisare_masina();
        cout << "\n\n";
    }
};

class MICA : public Masina
{
public:

    MICA(int lung = -1, int loc = -1, int p = -1, int an_f = -1, int z = -1, int l = -1, int a = -1) : Masina(lung, loc, p, an_f, z, l, a) {}

    friend istream& operator>> (istream &in, MICA &k)
    {
        in >> (Masina&) k;
        try
        {
            if (k.lungime > 4.1 || k.lungime < 3.85)
                throw (1);

        }
        catch(int ddd){
            cout << "Masina urmatoare nu se incadreaza in standardele clasei 'MICA' \n\n";
            cout << k;
            exit(0);
        }
        return in;
    }

    void afis()
    {
        afisare_masina();
        cout << "\n\n";
    }
};

class COMPACTA : public Masina
{
public:
    string model;

    COMPACTA(int lung = -1, int loc = -1, int p = -1, int an_f = -1, int z = -1, int l = -1, int a = -1, string mod = "?") : Masina(lung, loc, p, an_f, z, l, a)
    {
        model = mod;
    }

    friend istream& operator>> (istream &in, COMPACTA &k)
    {
        in >> (Masina&) k;
        in >> k.model;

        try
        {
            if (k.lungime > 4.5 || k.lungime < 4.2 || (k.model != "hatchback" && k.model != "sedan" && k.model != "combi"))
                throw (1);

        }
        catch(int ddd){
            cout << "Masina urmatoare nu se incadreaza in standardele clasei 'COMPACTA' \n\n";
            cout << k;
            exit(0);
        }

        return in;
    }

    void afis()
    {
        afisare_masina();
        cout << "\n" << "Model: " << model << "\n\n";
    }
};

class MONOVOLUME : public Masina
{
public:
    string tip;

    MONOVOLUME(int lung = -1, int loc = -1, int p = -1, int an_f = -1, int z = -1, int l = -1, int a = -1, string t = "?") : Masina(lung, loc, p, an_f, z, l, a)
    {
        tip = t;
        if (tip == "second-hand")///discount proportional cu anul de vechime
        {
            int v = 2019 - an_f;
            pret = pret - v * pret / 100;
        }
        if (l >= 6 && l <= 8)///discount in lunile de vara
            pret -= pret / 10;
    }


    friend istream& operator>> (istream &in, MONOVOLUME &k)
    {
        in >> (Masina&) k;
        in >> k.tip;

        try
        {
            if (k.tip != "second-hand" && k.tip != "noua")
                throw (1);

        }
        catch(int ddd){
            cout << "Masina urmatoare nu se incadreaza in standardele clasei 'COMPACTA' \n";
            cout << k;
            exit(0);
        }

        return in;
    }

    void afis()
    {
        afisare_masina();
        cout << "\n" << "Tip: " << tip << "\n\n";
    }



    template<typename A>
    bool compar (A a, A b)
    {
        if (a.lungime != b.lungime)
            return 0;
        if (a.locuri != b.locuri)
            return 0;
        if (a.pret != b.pret)
            return 0;
        if (a.an_fabricatie != b.an_fabricatie)
            return 0;
        if (typeid(a) == typeid(MONOVOLUME))
            if (((MONOVOLUME&)a).tip != ((MONOVOLUME&)b).tip)
                return 0;
        if (typeid(a) == typeid(COMPACTA))
            if (((COMPACTA&)a).model != ((COMPACTA&)b).model)
                return 0;
        return 1;
    }
};


int masini_totale;

template<typename T>
class Vanzare
{

    vector<Masina*> vector_masini;
    vector<Masina*> vector_vanzare;

    char s[15];
    void nume()
    {
        strcpy(s, typeid(T).name());
        while (s[0] >= '0' && s[0] <= '9')
            strcpy(s, s + 1);
    }

public:

    static int masini_stoc;
    static int masini_vandute;

    void adaugare (T car)
    {
        vector_masini.push_back(new T(car));
        masini_stoc++;
        masini_totale++;
    }

    void sell (T car)
    {
        vector_vanzare.push_back(new T(car));
        nume();
        cout << "MASINA URMATOARE DIN CLASA '";
        cout << s;
        cout << "' A FOST VANDUTA! \n\n";
        cout << car;

        vector<Masina*>::iterator it;
        for (it = vector_masini.begin(); it != vector_masini.end(); it++)
        {
            T* q;
            q = dynamic_cast<T*>(*it);
            if (compar(*q, car))
            {
                vector_masini.erase(it);
                break;
            }
        }

        masini_stoc--;
        masini_vandute++;
        masini_totale--;
    }

    void afisare_stoc()
    {
        nume();
        int i = 1;
        cout << "Sunt " << masini_stoc << " masini in stoc din clasa '";
        cout << s;
        cout << "': \n\n";
        vector<Masina*>::iterator it;
        for (it = vector_masini.begin(); it != vector_masini.end(); it++)
        {
            cout << i++ << ". \n";
            (*it)->afis();
        }
    }

    void operator-= (T car)
    {
        sell(car);
    }
};

template<>
class Vanzare<unsigned>
{
    vector<MONOVOLUME> vm;
    vector<MONOVOLUME> sm;
public:

    static int monovolume_stoc;
    static int monovolume_vandute;

    void adaugare (MONOVOLUME car)
    {
        vm.push_back(car);
        monovolume_stoc++;
        masini_totale++;
    }

    void sell (MONOVOLUME car)
    {
        sm.push_back(car);
        cout << "MASINA URMATOARE DIN CLASA 'MONOVOLUME' A FOST VANDUTA! \n\n";
        cout << car;

        vector<MONOVOLUME>::iterator it;

        for (it = vm.begin(); it != vm.end(); it++)
        {
            if (car.compar((*it), car))
            {
                vm.erase(it);
                monovolume_stoc--;
                monovolume_vandute++;
                masini_totale--;
                break;
            }
        }
    }

    const void afisare_stoc()
    {
        int i = 1;
        cout << "Sunt " << monovolume_stoc << " masini in stoc din clasa 'MONOVOLUME': \n\n";
        vector<MONOVOLUME>::iterator it;
        for (it = vm.begin(); it != vm.end(); it++)
        {
            cout << i++ << ". \n";
            (*it).afis();
        }
    }

    void operator-= (MONOVOLUME car)
    {
        sell(car);
    }

};

int Vanzare<unsigned>::monovolume_stoc = 0;
int Vanzare<unsigned>::monovolume_vandute = 0;

template<typename T> int Vanzare<T>::masini_stoc = 0;
template<typename T> int Vanzare<T>::masini_vandute = 0;

int main()
{
    ifstream fin ("data.in");

    Vanzare<MINI> mini;
    Vanzare<MICA> mica;
    Vanzare<COMPACTA> comp;
    Vanzare<unsigned> mono;

    MINI mini1, mini2;
    MICA mica1;
    COMPACTA comp1, comp2;
    MONOVOLUME mono1, mono2, mono3;

    fin >> mini1;
    mini.adaugare(mini1);
    fin >> mini2;
    mini.adaugare(mini2);

    fin >> mica1;
    mica.adaugare(mica1);

    fin >> comp1;
    comp.adaugare(comp1);
    fin >> comp2;
    comp.adaugare(comp2);

    fin >> mono1;
    mono.adaugare(mono1);
    fin >> mono2;
    mono.adaugare(mono2);
    fin >> mono3;
    mono.adaugare(mono3);

    mono.afisare_stoc();

    return 0;
}


