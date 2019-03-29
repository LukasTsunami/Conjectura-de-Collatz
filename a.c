#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

long collatz_conjecture(long number, long counter){
                if(number == 1) return counter;
                counter++;
                long new_number = (number % 2==0) ? number/2 : number * 3 + 1;
                collatz_conjecture(new_number, counter);
        }


void main(int argc, char *argv[]){
   int ret, rank, size, tag;
   MPI_Status status;

   ret = MPI_Init(&argc, &argv);

   ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

   long teste = collatz_conjecture(100000000, 0);
   printf("Teste = %d",teste);
   ret = MPI_Finalize();
}
