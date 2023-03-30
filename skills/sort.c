#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

#define DEBUG_INFO

#define TRUE 1
#define FALSE 0

void printArray(int const *array, int lenght) {
#ifdef DEBUG_INFO
	for (int i = 0; i < lenght; i++) {
		printf("%d ", array[i]);
	}
	printf("\n\n");
#endif
}

void randomFillArray(int *array, int size) {
	srand(time(NULL));
	//srand(1);
	for (int i = 0; i < size; i++) {
		array[i] = rand() % 100;
	}
}

#define ARRAY_SIZE 20
void test_boubble_sort() {
	srand(time(NULL));
	//srand(1);

	int arr1[ARRAY_SIZE] = { };
	randomFillArray(arr1, ARRAY_SIZE);
	printArray(arr1, ARRAY_SIZE);
	boubble_sort(arr1, ARRAY_SIZE);
	printArray(arr1, ARRAY_SIZE);

}

void test_selection_sort() {
	//srand(time(NULL));
	srand(1);

	int arr1[ARRAY_SIZE] = { };
	randomFillArray(arr1, ARRAY_SIZE);
	printArray(arr1, ARRAY_SIZE);
	selection_sort(arr1, ARRAY_SIZE);
	printArray(arr1, ARRAY_SIZE);

}

void swap_int(int *ap, int *bp) {
	int tmp = *ap;
	*ap = *bp;
	*bp = tmp;
}

void selection_sort(int *array, int length) {

	int key = 0;

	for (int j = 0; j < length; j++) {
		key = j;
		for (int i = j; i < length; i++) {
			if (array[i] < array[key])
				key = i;
		}
		swap_int(&array[j], &array[key]);
	}

}

void boubble_sort(int *array, int length) {
	short keepGoing = TRUE;

	//The last element is already in position after on for cicle
	int count = 0;
	while (keepGoing == TRUE) {
		keepGoing = FALSE;
		printArray(array, length);
		for (int i = 0; i < length - 1 - count; i++) {

			if (array[i] > array[i + 1]) {
				keepGoing = TRUE;
				swap_int(&array[i], &array[i + 1]);
			}
		}
		count++;
	}
}

