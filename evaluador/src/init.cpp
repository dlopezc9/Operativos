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
#include <cerrno>
#include "init.h"   
#include "elements.h"
#include "manejador_mem.h"
#include "manejador_sem.h"
#include "manejador_hil.h"

using namespace std;

// Metodo init que inicia la memoria.
int Init::init(int i, int ie, int oe, string n, int b, int d, int s, int q){

    Manejador_Mem man_mem;
    Manejador_Sem man_sem;
    Manejador_Hil man_hil;

    // Se empieza el set up de todo el programa

    // Se crea la memoria
    man_mem.crear_mem(i, ie, oe, n, b, d, s, q);

    // Se mapea la memoria.
    char* aux = man_mem.abrir_memoria(n);

    cout << "La memoria se creo con exito" << endl;

    // Se crean los semaforos

    man_sem.crear_sem(i, ie, oe, n, b, d, s, q);
    
    cout << "Se crearon los semaforos con exito" << endl;

    // Inicia los hilos

    man_hil.crear_hil(i, n);

    cout << "Hilos instanciados con exito" << endl;

    //    while(true)
    //    {
            //Este ciclo se descomenta cuando sepamos que hace el init mientras bloquea la consola
    //    }    

  return EXIT_SUCCESS;

}
