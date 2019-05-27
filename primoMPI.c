#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    
	int n_primos = 0;
	
	int *work_size;
	work_size = calloc(0, sizeof(int));
	
	int total_primos = 0;	
	
	int inicio = 0;
	int final = 0;
	
	MPI_Init(NULL, NULL);
	
	int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    if(world_rank == 0) {
    
        printf("Até qual numero deseja calcular os primos?\n");
	    scanf("%d", &n_primos);

	    printf("Calculando numeros primos até %d...\n", n_primos);
	    
	    *work_size = ceil(n_primos / world_size);
	    
	    printf("Cada thread irá calcular %d números primos\n", *work_size);
	    
	    inicio = world_rank * *work_size;
        final = inicio + *work_size;
        
        for(int n = 1; n < world_size; n++) {
            MPI_Send(work_size, 1, MPI_INT, n, 0, MPI_COMM_WORLD);
        }   
	    
	    
    }


    while(*work_size == 0) {
        MPI_Recv(work_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        inicio = world_rank * *work_size;
        final = inicio + *work_size;
      //Espera para saber qual o tamanho do grupo de trabalho
    }
    
    printf("Thread %d - O tamanho do work size é %d\n", world_rank, *work_size);
    printf("Thread %d - Ponto incial: %d\n", world_rank, inicio);
    printf("Thread %d - Ponto final: %d\n", world_rank, final);
    
    
   

	int i = 0;
	int j = 0;

	//Para cada numero até n_primos
	for(i = inicio; i <= final; i++) {
		int atual = i;
		int divs = 0;

		//Para cada unidade até o numero
		for(j = 1; j <=  i; j ++) {
			if(atual % j == 0) {
				divs++;
			}
		}

		if(divs == 2) {
		    total_primos++;
			printf("[T%d] Número %d é primo.\n", world_rank, atual);
		}
		else{
			printf("[T%d] Número %d NÃO é primo.\n", world_rank, atual);
		}

		divs = 0;

	}
	
	MPI_Finalize();
	
	printf("[T%d] Total de numeros primos: %d\n", world_rank, total_primos);
	
	
	
	free(work_size);

	return 0;

}
