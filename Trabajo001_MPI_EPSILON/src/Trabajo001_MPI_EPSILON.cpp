/*
 ============================================================================
 Name        : Trabajo001_MPI_EPSILON.c
 Author      : Napoleon
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
// Incluimos las librerias:

#include <math.h>
#include "mpi.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sys/time.h>

using namespace std;

int main(int argc, char *argv[])
{
	/*
	 * Declaramos las variables
	 */
    int n,    // Numero de iteraciones
		rank, // Identificador de proceso
		size; // Numero de procesos con el se trabaja

    double EPSILON = 2.718281828459045235360;
    double startval, endval;
    double ValEpsilon = 0.0;
    double factorial;
    double sum = 0.0;
    double epsilon;
    double error = 0.0;

    //inicializamos y configuramos el rango y el tama del proceso
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Solo el proceso 0 va a conocer el numero de iteraciones que vamos a
    // ejecutar para la aproximacion de Epsilon
	if (rank == 0) {
		cout<<"Ingrese la precision del calculo (n > 0): ";
		cin>>n;
	}

	startval = 4*n*rank/size+1;
	endval = 4*n*(rank+1)/size;

	factorial = 1;



	// El proceso 0 reparte al resto de procesos el numero de iteraciones
	// que calcularemos para la aproximacion de EPSILON

	MPI_Bcast(&n, // Puntero al dato que vamos a enviar
			  1,  // Numero de datos a los que apunta el puntero
			  MPI_INT, // Tipo del dato a enviar
			  0, // Identificacion del proceso que envia el dato
			  MPI_COMM_WORLD);

	if (n <= 0){
		MPI_Finalize();
		exit(0);

	}else {
		for(int i = startval; i <= endval; i = i+1){

			factorial=(factorial*i); // factorial de un numero
			sum+= (1/factorial);     // suma de 1/factorial obtenido


		}


		//printf("rank %d s = %f \n",rank,sum);


		MPI_Reduce(&sum, 	// Valor local de Epsilon obtenido
					&epsilon,  	// Dato sobre el que vamos a empaquetar
					1,	    	// Numero de datos que vamos a reducir
					MPI_DOUBLE,  // Tipo de dato que vamos a reducir
					MPI_SUM,  	// Operacion que aplicaremos
					0, 			// proceso que va a recibir el dato reducido
					MPI_COMM_WORLD);



		ValEpsilon = epsilon+1;
		error= EPSILON - ValEpsilon;

		if (rank == 0){

			cout<<"Valor Aproximado de Epsilon es: "<<ValEpsilon<<", con un error de"<<error<<endl;

		}
		}
    MPI_Finalize();
    return 0;
}


