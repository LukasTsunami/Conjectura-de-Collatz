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
			long test_number = 111111;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			long ret0 = some_sequence.maximum;
			printf("\n maximum a %d",maximum);
			long ret1 = MPI_Recv(&maximum, 1, MPI_LONG, 1, tag, MPI_COMM_WORLD, &status);
			printf("\n maximum a %d",maximum);
			long ret2 = MPI_Recv(&maximum, 1, MPI_LONG, 2, tag, MPI_COMM_WORLD, &status);
			printf("\n maximum a %d",maximum);
			long ret3 = MPI_Recv(&maximum, 1, MPI_LONG, 3, tag, MPI_COMM_WORLD, &status);
			printf("\n maximum a %d",maximum);

			printf("ret0 %d, ret1 %d ret2 %d ret3 %d",ret0, ret1, ret2, ret3);
			
			if((ret0>ret1)&&(ret0>ret2)&&(ret0>ret3)) printf("\n ret0 é o maior");
			if((ret1>ret0)&&(ret1>ret2)&&(ret1>ret3)) printf("\n ret1 é o maior");
			if((ret2>ret1)&&(ret2>ret0)&&(ret2>ret3)) printf("\n ret2 é o maior");
			if((ret3>ret1)&&(ret3>ret2)&&(ret3>ret0)) printf("\n ret3 é o maior");
			printf("\nend of");
	}
	else if (rank == 1){
			int initial = 1;
			long test_number = 111111;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			maximum = some_sequence.maximum;
        	ret = MPI_Send(&maximum, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}else if (rank == 2){
			int initial = 1;
			long test_number = 111111;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			maximum = 800;
        	ret = MPI_Send(&maximum, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}else if (rank == 3){
			int initial = 1;
			long test_number = 111111;
			struct Sequence some_sequence = get_maximum_sequence(initial, test_number);
			maximum = 900;
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