#include <stdio.h>
#include <stdlib.h>

struct Sequence{
   long maximum;
   long number_that_generates_the_greatest_sequence;
};

long collatz_conjecture(long number, long counter);
struct Sequence get_maximum_sequence(long number);	

void main(){
	long test_number = 111111;
	struct Sequence some_sequence = get_maximum_sequence(test_number);
	printf("\nGreater Sequence = {%d} - Which number generate the greatest sequence = {%d}\n",some_sequence.maximum, some_sequence.number_that_generates_the_greatest_sequence);
}


long collatz_conjecture(long number, long counter){
	if(number == 1) return counter;
	counter++;
	long new_number = (number % 2==0) ? number/2 : number * 3 + 1;
	collatz_conjecture(new_number, counter);
}

struct Sequence get_maximum_sequence(long number){
	long current_number = 1;
	long number_that_generates_the_greatest_sequence = 0;
	long maximum = -1;
	for(; current_number <= number; current_number++){
		long counter = 0;
		long returnn = collatz_conjecture(current_number, counter);

		if(returnn > maximum){
		maximum = returnn;
		number_that_generates_the_greatest_sequence = current_number;
		} 
	}
	struct Sequence aux;
	aux.maximum = maximum;
	aux.number_that_generates_the_greatest_sequence = number_that_generates_the_greatest_sequence;
	return aux;
}