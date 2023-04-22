// Daniel Yu 501120369 daniel1.yu@torontomu.ca
#include <stdio.h>
#include <stdlib.h>
int *arr; // initialize queue
int front = 0; // front of queue
int back = 0; // back of queue
int pointer = 0;
int size = 0;

int makeArr(int w){
	size = w;
	arr = (int*)calloc(size, sizeof(int)); // make the queue of worker size
}

void enqueue(int x){
	arr[back] = x; // put the varible at front of queue
	back++; // increment front
	if (back == size){ //reset back if it exceeds max capacity
		back = 0;
	}
}

void dequeue(){// get value of back of queue
	arr[front] = -1; // reset the value of the front of queue
	front++; // add back
	if (front == size){ // reset front if it exceeds max capacity
		front = 0;
	}
}

int emptyQueue(){ //check if queue is empty
	for(int i = 0; i < size; i++){ 
		if (arr[i] != -1){ // check if each value is -1;
			return -1; // return -1 of a value is not -1
		}
	}
	return 1; // return 1 if all values are -1
}

int getValue(){
	int value = arr[pointer];
	pointer++;
	if (pointer == size){
		pointer = 0;
	}
	return value; // get valeu of 
}
