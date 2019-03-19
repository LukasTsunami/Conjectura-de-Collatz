#include <stdio.h>
#include <stdlib.h>

void main(){
	int collatz_conjecture(int number, int counter){
		if(number == 1) return counter;
		counter++;
		int new_number = (number % 2==0) ? number/2 : number * 3 + 1;
		collatz_conjecture(new_number, counter);
	}

	int number = 7;
	int counter = 0;
	int data = collatz_conjecture(number, counter);

	printf("\nfim = %d \n",data);
}
