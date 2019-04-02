#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

long collatz_conjecture(long number, long counter);
long get_maximum_sequence1(long initial, long number);
long get_maximum_sequence2(long initial, long number);

void main(int argc, char *argv[]){
   int ret, rank, size, tag;
   MPI_Status status;

   ret = MPI_Init(&argc, &argv);

   ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

   long teste = get_maximum_sequence1(200000,300000);
   printf("\n\nTeste = %d\n\n",teste);
   ret = MPI_Finalize();
}

long collatz_conjecture(long number, long counter){
                if(number == 1) return counter;
                counter++;
                long new_number = (number % 2==0) ? number/2 : number * 3 + 1;
                collatz_conjecture(new_number, counter);
}

long get_maximum_sequence1(long initial, long number){
        long current_number = initial;
        long maximum = -1;
        for(; current_number <= number; current_number++){
                long counter = 0;
                long returnn = collatz_conjecture(current_number, counter);

                if(returnn > maximum){
                  maximum = returnn;
                }
        }
        return maximum;
}

long get_maximum_sequence2(long initial, long number){
        long current_number = 100000;
        long maximum = -1;
                long counter = 0;
                long returnn = collatz_conjecture(200000, counter);

                if(returnn > maximum){
                  maximum = returnn;
        }
        return maximum;
}

