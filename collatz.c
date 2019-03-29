#include <stdio.h>
#include <stdlib.h>

struct Metadata{
   int maximum;
   int number_that_generates_the_greatest_sequence;
};

void main(){
	int collatz_conjecture(int number, int counter){
		if(number == 1) return counter;
		counter++;
		int new_number = (number % 2==0) ? number/2 : number * 3 + 1;
		collatz_conjecture(new_number, counter);
	}


	struct Metadata get_maximum_sequence(int number){
		int current_number = 100000;
		int number_that_generates_the_greatest_sequence = 0;
		int maximum = -1;
		for(; current_number <= number; current_number++){
		   int counter = 0;
		   int returnn = collatz_conjecture(current_number, counter);

		   if(returnn > maximum){
			maximum = returnn;
			number_that_generates_the_greatest_sequence = current_number;
		   }
		   //printf("\ncurrent [%d] contador [%d] | maximum [%d]\n",current_number,returnn,maximum);
		}
		struct Metadata aux;
		aux.maximum = maximum;
		aux.number_that_generates_the_greatest_sequence = number_that_generates_the_greatest_sequence;
		return aux;
	}

	long test_number = 150000;
	struct Metadata metaDataQualquer = get_maximum_sequence(test_number);
	printf("\nMaior numero = {%d} - Numero que gera = {%d}\n",metaDataQualquer.maximum, metaDataQualquer.number_that_generates_the_greatest_sequence);
}
