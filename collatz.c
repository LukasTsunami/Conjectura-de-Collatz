#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

struct Sequence{
   long maximum;
   long number_that_generates_the_greatest_sequence;
};

long collatz_conjecture(long number, long counter);
struct Sequence get_maximum_sequence(long initial, long number);	

void main(int argc, char *argv[]){
   int ret, rank, size, tag = 0;
	long maximum = 0;
	MPI_Status status;
   ret = MPI_Init(&argc, &argv);
   ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0){
			int initial = 1;
			long test_number = 10000;
			
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			long maximumNode0 = some_sequence.maximum;
			
			ret = MPI_Recv(&maximum, 1, MPI_LONG, 1, tag, MPI_COMM_WORLD, &status);
			long maximumNode1 = maximum;
			
			ret = MPI_Recv(&maximum, 1, MPI_LONG, 2, tag, MPI_COMM_WORLD, &status);
			long maximumNode2 = maximum;
			
			ret = MPI_Recv(&maximum, 1, MPI_LONG, 3, tag, MPI_COMM_WORLD, &status);
			long maximumNode3 = maximum; 

			printf("\nmaximumNode0 %d, maximumNode1 %d maximumNode2 %d maximumNode3 %d",maximumNode0, maximumNode1, maximumNode2, maximumNode3);
			
			if((maximumNode0>maximumNode1)&&(maximumNode0>maximumNode2)&&(maximumNode0>maximumNode3)) printf("\n maximumNode0 é o maior");
			if((maximumNode1>maximumNode0)&&(maximumNode1>maximumNode2)&&(maximumNode1>maximumNode3)) printf("\n maximumNode1 é o maior");
			if((maximumNode2>maximumNode1)&&(maximumNode2>maximumNode0)&&(maximumNode2>maximumNode3)) printf("\n maximumNode2 é o maior");
			if((maximumNode3>maximumNode1)&&(maximumNode3>maximumNode2)&&(maximumNode3>maximumNode0)) printf("\n maximumNode3 é o maior");
			printf("\nend of");
	}
	else if (rank == 1){
			int initial = 10001;
			long test_number = 20000;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			maximum = some_sequence.maximum;
        	ret = MPI_Send(&maximum, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}else if (rank == 2){
			int initial = 20001;
			long test_number = 30000;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			maximum = some_sequence.maximum;
        	ret = MPI_Send(&maximum, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}else if (rank == 3){
			int initial = 30001;
			long test_number = 40000;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			maximum = some_sequence.maximum;
        	ret = MPI_Send(&maximum, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}

	ret = MPI_Finalize();
}


long collatz_conjecture(long number, long counter){
	if(number == 1) return counter;
	counter++;
	long new_number = (number % 2==0) ? number/2 : number * 3 + 1;
	collatz_conjecture(new_number, counter);
}

struct Sequence get_maximum_sequence(long initial, long number){
	long current_number = initial;
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
