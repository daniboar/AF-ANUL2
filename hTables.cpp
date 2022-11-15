/*
    Boar Daniel-Ioan
    Grupa 30223

    Pentru aceasta saptamana am avut de implementat operatiile de inserare, cautare si stergere intr-o tabela de dispersie ce foloseste adresarea deschisa cu verificare patratica.

    Pentru inserarea unei chei, am calculat pozitia pe care trebuie inserat key-ul, apoi, daca pozitia era libera, adaugam elementul.
    Daca nu, recalculam pozitia folosint verificarea patratica si adaugam pe acea pozitie.

    Pentru search in hTables am cautat elementul prin toata tabela si returnam pozitia acestuia. Daca key-ul nu exista in tabela, atunci returneaza -1.

    Pentru delete key am implementat o metoda care imi gaseste pozitia elementului pe care vrem sa-l stergem si ii schimba valoarea in -2.

    Am folosit tabela de dispersie cu un factor de umplere de 95%. 

    95 ... 100
    x  ... M (M reprezinta lungimea tabelei)   ==> x = (95 * M) / 100  (factorul de umpplere)
*/


#include <iostream>
#define M 7
using namespace std;

typedef struct {
    int id;
    char nume[30];
}Entry;


int h1(int key) {
    if (key >= 0)
        return key % M;
    else
        return -key % M;
}

int h(int key, int i) {
    return (h1(key) + (i * i)) % M;
}

int inserare(Entry T[M], int key) {
    int i = 0;
    int j;
    while (i != M) {
        j = h(key, i);
        if (T[j].id == 0 || T[j].id == -2) {
            T[j].id = key;
            return j;
        }
        else i++;
    }
    return 0;
}

int search(Entry T[M], int key) {
    int j, i = 0;
    do {
        j = h(key, i);
        if (T[j].id == key)
            return j;
        i++;
    } while (T[j].id == 0 or i == M);
     return -1;
}

void afisare(Entry T[M]) {
    for (int i = 0; i < M; i++) {
        cout << i << ": ";
        if (T[i].id != 0)
            cout << T[i].id << "\n"; 
        else
            cout << 0 << "\n";
    }
}

void delete_key(Entry T[M], int key) {
    int j = search(T, key); //stergem elementul gasit pe pozitia j
    if(j != -1) // conditia se refera ca vrem sa stergem un element existent, daca j ar fi -1 atunci noi nu am inserat nimic pe acea pozitie
        T[j].id = -2;
}

void demo() {
    Entry T[100];
    int factor = (M * 95) / 100;
    for (int i = 0; i < M; i++)
        T[i].id = 0;
    int a[] = { 50,700,76,85,92,73, 101 };
    for (int i = 0; i < factor; i++)
        inserare(T, a[i]);
    afisare(T);
    puts("");
    if (search(T, 50) != -1)
        cout << "Elementul " << 50 << " a fost gasit pe pozitia " << search(T, 50) << "\n";
    else
        cout << "Elementul nu a fost gasit" << "\n";

    if (search(T, 100) != -1)
        cout << "Elementul " << 100 << " a fost gasit pe pozitia " << search(T, 100) << "\n";
    else
        cout << "Elementul " << 100 << " nu a fost gasit" << "\n";

    puts("");
    cout << "Tabela dupa stergerea elementului " << 76 << "\n";
    delete_key(T,76); 
    afisare(T);
}

int main()
{
    demo();
    return 0;
}


