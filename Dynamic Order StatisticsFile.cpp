/*
    Boar Daniel Ioan
    Grupa 30223

    Una dintre cerinte a fost de a implementa un algoritm care ne creeaza un arbore binar de cautare, avand ca intrare un vector crescator.
    Alta cerinta a fost sa gasim al i-lea cel mai mic element din arbore. In acest algoritm m-am folosit mult de size-ul nodurilor.
    Pentru afisarea arborelui, am folosit o afisare normal pretty_print si una care imi afiseaza in forma unui arbore binar.
*/
#include <iostream>

using namespace std;

typedef struct Node {
    int key;
    int size;
    struct Node* left;
    struct Node* right;
};

 Node* create(int key){
    Node* p = (Node*)malloc(sizeof(Node));
    p->key = key;
    p->size = 0;
    p->left = NULL;
    p->right = NULL;
    return p;
}

 Node* BUILD_TREE(int* a, int l, int r) {
     if (l > r)
         return NULL;
     int middle = (l + r) / 2;  //alegem elementrul din mijlocul vectorului pentru a face un BST 
     Node* root = create(a[middle]);
     root->left = BUILD_TREE(a, l, middle - 1); //creez arborele stang
     root->right = BUILD_TREE(a, middle + 1, r); //creez arborele drept

     //initializam size-ul in functie de cati copii sunt pe fiecare nod.
     if (root->left == NULL && root->right == NULL) //daca nu are copii
         root->size = 1;
     else if (root->left == NULL && root->right != NULL) //daca are un copil mai mare
         root->size = root->right->size + 1;
     else if (root->left != NULL && root->right == NULL) //daca are un copil mai mic
           root->size = root->left->size + 1;
     else // daca are si copil stanga si copil dreapta
         root->size = root->left->size + root->right->size + 1;
     return root;
}

void preorder(Node* root) { // RSD
    if (root != NULL) {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

Node* OS_Select(Node* x, int i) {
    int r;
    if (x->left == NULL) //daca nu avem copil stang atunci size-ul parintelui este 1
        r = 1; 
    else
         r = x->left->size + 1;
    if (i == r)                                
        return x;
    else if (i < r)
            return OS_Select(x->left, i);  // daca elementul s-a gasit, apelam recursiv pe arborele stang
        else
            return OS_Select(x->right, i - r); // daca elementul nu s-a gasit, apelam recursiv pe arborele drept
}

void pretty_print(Node* root, int space) {
    if (root == NULL)
        return;
    pretty_print(root->right, space + 4);
    puts("");
    for (int i = 0; i < space; i++)
        cout << " ";
    cout << root->key;

    pretty_print(root->left, space + 4 );
}

void pp(Node* r, int space) {
    if (r == NULL)
        return;
    cout << "\n";
    for (int i = 0; i < space; i++)
        cout << "    ";
    cout << r->key;
    pp(r->left, space + 1);
    pp(r->right, space + 1);
}

void demo() {
    int a[] = { 1,2,3,4,5,6,7,8,9,10,11 };
    int n = sizeof(a) / sizeof(a[0]);
    Node* root = BUILD_TREE(a, 0, n - 1);
    cout << "Afisare in preordine: ";
    preorder(root);
    cout << "\n";
    pretty_print(root, 0);
    cout << "\n";
    pp(root, 0);
    cout << "\n\n";
    Node* x = OS_Select(root, 4);
    cout << "Al 4 lea cel mai mic element este: " << x->key<<"\n";
}

int main()
{
    demo();
    return 0;
}


