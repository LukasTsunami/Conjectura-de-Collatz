#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

struct Metadata{
   int maximum;
   int number_that_generates_the_greatest_sequence;
};

void main(int argc, char *argv[]){
   int ret, rank, size, tag;
   MPI_Status status;

   ret = MPI_Init(&argc, &argv);

   ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

   double tempo_inicial = MPI_Wtime();

	int collatz_conjecture(int number, int counter){
		if(number == 1) return counter;
		counter++;
		int new_number = (number % 2==0) ? number/2 : number * 3 + 1;
		collatz_conjecture(new_number, counter);
	}


	struct Metadata get_maximum_sequence(int number){
		int current_number = 1;
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

	long test_number = 40000;
	struct Metadata metaDataQualquer = get_maximum_sequence(test_number);
	printf("\nMaior numero = {%d} - Numero que gera = {%d}\n",metaDataQualquer.maximum, metaDataQualquer.number_that_generates_the_greatest_sequence);
	double novo_tempo = MPI_Wtime()-tempo_inicial;
	printf("\n\nTempo de execucao: %f \n\n",novo_tempo);
	ret = MPI_Finalize();
}
