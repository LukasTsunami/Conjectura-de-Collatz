#include <stdio.h>
#include <string.h>
#include "mpi.h"
main(int argc, char *argv[])
{
	#define VALOR_QUALQUER_ALEATORIO 100;
        int ret, rank, size, tag;
	double tempo_atual = 0, novo_tempo = 0;
	int variavel_transportada = 0;
        MPI_Status status;

        ret = MPI_Init(&argc, &argv);

        ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        ret = MPI_Comm_size(MPI_COMM_WORLD, &size);

	tempo_atual=MPI_Wtime();
        tag=VALOR_QUALQUER_ALEATORIO;
        if (rank == 0){
        	ret = MPI_Send(&variavel_transportada, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
		ret = MPI_Recv(&variavel_transportada, 1, MPI_INT, 3, tag, MPI_COMM_WORLD, &status);
                printf("Para circular as mensagens demorou: %f segundos - %d\n", novo_tempo, variavel_transportada);
	}
	else if (rank == 1){
		ret = MPI_Recv(&variavel_transportada, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		variavel_transportada++;
                ret = MPI_Send(&variavel_transportada, 1, MPI_INT, 2, tag, MPI_COMM_WORLD);
	}else if (rank == 2){
		ret = MPI_Recv(&variavel_transportada, 1,MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
		variavel_transportada++;
                ret = MPI_Send(&variavel_transportada, 1, MPI_INT, 3, tag, MPI_COMM_WORLD);
	}else if (rank == 3){
		ret = MPI_Recv(&variavel_transportada, 1, MPI_INT, 2, tag, MPI_COMM_WORLD, &status);
		variavel_transportada++;
                ret = MPI_Send(&variavel_transportada, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}

	novo_tempo = MPI_Wtime()-tempo_atual;
	ret = MPI_Finalize();
}

