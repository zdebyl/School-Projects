/*
Name: Zoe Debyl
Date: November 26th 2022
Assignment: Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int sum_key;
	int key[3];
	int content[7];
} node;

int main() {
	int numbers[20][10];
	node objects[20];
	int parent, leftChild, rightChild;
	node temp;

	//open file for reading
	FILE* fp = fopen("f.dat", "r");

	//read file into an array
	for (int i=0; i<20; i++) {
		for (int j=0; j<10; j++) {
			fscanf(fp, "%d", &numbers[i][j]);
		}
	}
	
	//initialize sum_key
	for (int i=0; i<20; i++) {
		objects[i].sum_key = 0;
	}

	//change each row into an object
	for (int i=0; i<20; i++) {
		for (int j=0; j<10; j++) {
			if (j<3) {
				objects[i].key[j] = numbers[i][j];
				objects[i].sum_key = objects[i].sum_key + numbers[i][j];
			} else {
				objects[i].content[j-3] = numbers[i][j];
			}
		}
	}

	//downheap
	//max number of swaps
	for (int i=0; i<4; i++) {
		//number of parents
		for (int j=9; j>=0; j--) {
			//get each value
			parent = objects[j].sum_key;
			if ((2*j+1)<20) {
				leftChild = objects[2*j+1].sum_key;
			} else {
				leftChild = 1000;
			}
			if ((2*j+2)<20) {
				rightChild = objects[2*j+2].sum_key;
			} else {
				rightChild = 1000;
			}
			
			//check if children are smaller value than parent
			if (parent>leftChild && rightChild>=leftChild) {
				//swap leftChild and parent
				temp = objects[j];
				objects[j] = objects[2*j+1];
				objects[2*j+1] = temp;
			} else if (parent>rightChild && leftChild>=rightChild) {
				//swap rightChild and parent
				temp = objects[j];
				objects[j] = objects[2*j+2];
				objects[2*j+2] = temp;
			}
		}
	}

	//print
	for (int i=0; i<20; i++) {
		for (int j=0; j<3; j++) {
			printf("%d ", objects[i].key[j]);
		}
		
		for (int k=0; k<7; k++) {
			printf("%d ", objects[i].content[k]);
		}
		
		printf("\n");
	}

	return 0;
}
