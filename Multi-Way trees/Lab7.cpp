/*
Boar Daniel Ioan	
Grupa 30223

Am implementat reprezentarea unui arbore multicai.
R1 reprezinta pretty-printul pentru vectorule de parinti.
R2 reprezinta pretty-printul al unui arbore multi-way format cu inserari in demo.
Pentru R2 m-am folosit de o structura in care avem key-ul inserat, copilul din arbore si urmatorul copil (daca exista).
*/

#include <iostream>

using namespace std;

typedef struct Node {
	int key;
	struct Node* child;
	struct Node* next;
};

Node* newNode(int x) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->key = x;
	p->child = NULL;
	p->next = NULL;
	return p;
}

Node* addBrother(Node* r, int key) {
	if (r == NULL)
		return NULL;
	while (r->next != NULL)
		r = r->next;
	r->next = newNode(key);
	return r->next ;
}

Node* addCopil(Node* r, int key) {
	if (r == NULL)
		return NULL;
	if (r->child != NULL)
		return addBrother(r->child, key);
	else {
		r->child = newNode(key);
		return r->child;
	}
}

void pretty_printR1(int* v, int n, int r, int space) {
	if(r == NULL)
		return;
	for (int i = 0; i < n; i++) {
		if (v[i] == r) {
			for (int j = 0; j < space; j++)
				cout << "	";
			cout  << i + 1 << "\n";
			pretty_printR1(v, n, i + 1, space + 1);
		}
	}
}

void pretty_printR2(Node* r, int space) {
	if (r == NULL)
		return;
	cout << "\n";
	for (int i = 0; i < space; i++)
		cout << "	";
	cout << r->key;
	pretty_printR2(r->child, space + 1);
	pretty_printR2(r->next, space );
}

void demo1() {
	int v[] = { 2,7,5,2,7,7,-1,5,2 };
	int n = sizeof(v) / sizeof(v[0]);
	pretty_printR1(v, n, -1, 0);
}

void demo2() {
	Node* root = newNode(7);
	Node* n1 = addCopil(root, 2);
	Node* n2 = addCopil(root, 5);
	Node* n3 = addCopil(root, 6);
	Node* n4 = addCopil(n1, 1);
	Node* n5 = addCopil(n1, 4);
	Node* n6 = addCopil(n1, 9);
	Node* n7 = addCopil(n2, 3);
	Node* n8 = addCopil(n2, 8);
	pretty_printR2(root, 0);
}

int main()
{
	cout << "Pretty-print R1\n";
	demo1();
	puts("");
	cout << "Pretty-print R2\n";
	demo2();
	return 0;
}