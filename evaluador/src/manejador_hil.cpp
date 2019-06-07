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

    for (;;)
    // for(int k = 0; k < 5; ++k)
    {
        cout << "almenos una" << endl;
        banNam *producto = (struct banNam *)bandej;

        cout << "almenos dos?" << endl;
        //printf("%d\n", producto -> bandeja);
        //cout << producto->name << "\n" << endl;
        registrosalida registro = man_mem.retirar_reg(producto->bandeja, producto->nombre);

        cout << "tres?" << endl;
        // insertarRegistroSalida(registrosalida, nombre)

    }
 
    pthread_exit(NULL);
}

void Manejador_Hil::crear_hil(int i, string n){
    

    cout << "Mira perro, si entre" << endl;
    cout << i << endl;
    // Instancia los elementos que van a hacer parte de los hilos
    // Instancia el arreglo de los hilos.
    pthread_t hiloP[i];
    banNam bande;
    bande.bandeja = i;
    bande.nombre = n;
    string n_Hilo = "Hilo" + n;

    // Crea los hilos y les asigna la funcion
    for (int n = 0; n < i; n++)
    {
        ostringstream namellen;
        namellen << n_Hilo << n;
        string realNameLlen(namellen.str());
        pthread_create(&hiloP[n], NULL, procesador, (void *)&bande);
        
    }

    cout << "WAIT WTF" << endl; 

    if (pthread_join(hiloP[0], NULL))
    {
        cout << "Mira perro, PELIGRO" << endl;
        fprintf(stderr, "Error joining thread\n");
        return;
    }

    cout << "AHA, SALI" << endl;
    return;
}