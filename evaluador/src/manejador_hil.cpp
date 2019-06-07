#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "elements.h"
#include "manejador_hil.h"
#include "manejador_mem.h"

using namespace std;

void* procesador(void *bandej)
{
    Manejador_Mem man_mem;
    banNam *producto = (banNam *)bandej;
    int num_bandeja = producto->bandeja;
    string nom_bandeja = producto->nombre;

    for (;;)
    {
        registrosalida registro = man_mem.retirar_reg(num_bandeja, nom_bandeja);

        // insertarRegistroSalida(registrosalida, nombre)

    }

    cout << "Sali?" << endl;
 
    pthread_exit(NULL);
}

void Manejador_Hil::crear_hil(int i, string n){
    
    // Instancia los elementos que van a hacer parte de los hilos
    // Instancia el arreglo de los hilos.
    pthread_t hiloP[i];
    banNam bande;
    bande.nombre = n;
    string n_Hilo = "Hilo" + n;

    // Crea los hilos y les asigna la funcion
    for (int m = 0; m < i; ++m)
    {
        bande.bandeja = m;
        ostringstream namellen;
        namellen << n_Hilo << m;
        string realNameLlen(namellen.str());
        pthread_create(&hiloP[m], NULL, procesador, (void *)&bande);
        sleep(0.1);
        
    }

    //ESTO SE BORRA, SE DEJA AHORA POR DEBUGGER
    if (pthread_join(hiloP[0], NULL))
    {
        fprintf(stderr, "Error joining thread\n");
        return;
    }

    return;
}