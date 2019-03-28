#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

struct Sequence{
   long maximum;
   long number_that_generates_the_greatest_sequence;
};

long collatz_conjecture(long number, long counter);
struct Sequence get_maximum_sequence(long number);	

void main(){
   int ret, rank, size, tag = 0;
	MPI_Status status;
   ret = MPI_Init(&argc, &argv);
   ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0){
			int initial = 1;
			long test_number = 111111;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			long ret1 = MPI_Recv(&variavel_transportada, 1, MPI_LONG, 1, tag, MPI_COMM_WORLD, &status);
			long ret2 = MPI_Recv(&variavel_transportada, 1, MPI_LONG, 2, tag, MPI_COMM_WORLD, &status);
			long ret3 = MPI_Recv(&variavel_transportada, 1, MPI_LONG, 3, tag, MPI_COMM_WORLD, &status);
			printf("ret0, ret1 %d ret2 %d ret3 %d",some_sequence.maximum, ret1, ret2, ret3);
	}
	else if (rank == 1){
			int initial = 111112;
			long test_number = 222222;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			long maximum = some_sequence.maximum;
        	ret = MPI_Send(&maximum, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}else if (rank == 2){
			int initial = 222223;
			long test_number = 333333;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			long maximum = some_sequence.maximum;
        	ret = MPI_Send(&maximum, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}else if (rank == 3){
			int initial = 333334;
			long test_number = 444445;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			long maximum = some_sequence.maximum;
        	ret = MPI_Send(&maximum, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}

	novo_tempo = MPI_Wtime()-tempo_atual;
	ret = MPI_Finalize();
}


long collatz_conjecture(long number, long counter){
	if(number == 1) return counter;
	counter++;
	long new_number = (number % 2==0) ? number/2 : number * 3 + 1;
	collatz_conjecture(new_number, counter);
}

struct Sequence get_maximum_sequence(long initial, long number){
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