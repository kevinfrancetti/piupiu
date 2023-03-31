#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

typedef struct node Node;
struct node{
	int data;
	Node* next_p;
};



int a = 3;
//dd

void printNode(Node *n){
	printf("::PRINT NODE %d\n", (*n).data);
}

Node* createNode(int data){
	Node* node_address = (Node*) malloc(sizeof(Node));
	(*node_address).data = data;
	(*node_address).next_p = NULL;
	return node_address;
}

void setNextNode(Node* n1, Node* n2){
	(*n1).next_p = n2;
}

void testNode(){
	Node* p_head = NULL;
	Node* n2 = createNode(2);
	p_head = createNode(34);
	setNextNode(p_head, n2);
	printNode(p_head);
	printNode((*p_head).next_p);
	free(p_head);

}


int lsearch_int(int key, int array[], int size) {
	for (int i = 0; i < size; i++) {
		if (array[i] == key)
			return i;
	}
	return -1;
}

void* lsearch_generik(void *key, void *base, int quantity, int elmSize, int (*cmpFun)(void*, void*)) {

	for (int i = 0; i < quantity; i++) {
		void *elmAddr = (char*) base + i * elmSize;

	}

	return NULL;
}


void swap_generik(void *vp1, void *vp2, int size) {
	char buffer[size];
	memcpy(buffer, vp1, size);
	memcpy(vp1, vp2, size);
	memcpy(vp2, buffer, size);
}

void test_generik_swap() {
	printf("::TEST GENERIC SWAP::\n");
	int a = 4;
	int b = 5;
	float fa = 4.247;
	float fb = 9.342;

	printf("a=%d , b=%d\n", a, b);
	printf("fa=%f , fb=%f\n", fa, fb);
	swap_generik(&a, &b, sizeof(int));
	swap_generik(&fa, &fb, sizeof(float));
	printf("a=%d , b=%d\n", a, b);
	printf("fa=%f , fb=%f\n", fa, fb);

}

void test_swap_int() {
	int a = 10;
	int b = 5;
	printf("a=%d , b=%d\n", a, b);
	swap_int(&a, &b);
	printf("a=%d , b=%d\n", a, b);
}

void testDoublePointers(){
	char *str1 = "cciiiao";
	char *str2 = "di cane";

	char str3[] = "bella";
	*(str3 + 1) = 'q';
	char *text[2];
	text[0] = str1;
	text[1] = str2;

	printf("%s\n", text[0]);
	printf("%s\n", text[1]);
	printf("%s\n", str3);



}


int main() {


	//testNode();
	//testDoublePointers();
	//test_boubble_sort();
	test_selection_sort();
	test_selection_sort();
	test_selection_sort();

	//boubbleSort(NULL, 0);
	/*
	const char *notes1[] = { "AA", "AA", "AA", "AB", "AA" };
	char *notes2[] = { "AB", "AC", "AD", "AE", "AF" };
	char str2[5] = "Hello";
	char *str3 = "Hello";
	char *str4 = str3;
	char *str5 = str2 + 1;
	*str5 = 'R';

	printf("Carattere1=%s \n", notes1[1]);
	printf("Carattere1=%s \n", notes1[3]);
	printf("Carattere2=%s \n", notes1[0]);
	notes1[3] = "Dio cane";
	printf("Carattere1=%s \n", notes1[3]);
	printf("Carattere2=%s \n", notes2[0]);

	printf("Carattere=%c \n", *notes1[1]);
	//printf("Carattere=%s \n", (char*) (*notes1[1]) + 1);
	//printf("Carattere=%s \n", (char*) (notes1[1]) + 1);

	//printf("Carattere=%p \n", *notes1[1]);

	int array1[5] = { 1, 2, 3, 4 };
	char array2[] = { 5, 66, 7, 8 };
	int a = 0;
	int b = 1;
	int c = -1;

	printf("%p\n", array1);
	printf("%p\n", array1 + 1);
	printf("%p\n", (char*) array1 + 1);
	printf("%c", array2[1]);
	printf("Hohhhla\n");
//test_swap_int();
	printf("sizeof(int) = %ld\n", sizeof(int));
	printf("sizeof(int*) = %ld\n", sizeof(int*));
	printf("sizeof(void) = %ld\n", sizeof(void));
	printf("sizeof(void*) = %ld\n", sizeof(void*));
	testBox();

	test_generik_swap();
	*/
	return 0;

}
