#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
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
    Manejador_Hil man_hil;
    banNam *producto = (banNam *)bandej;
    int num_bandeja = producto->bandeja;
    string nom_bandeja = producto->nombre;
    int ex;

    for (;;)
    {
        registrosalida registro = man_mem.retirar_reg(num_bandeja, nom_bandeja);
        ex = man_hil.ingresarBandejaQ(registro, nom_bandeja);
    }
 
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

int Manejador_Hil::ingresarBandejaQ(struct registrosalida registro, string n)
{
    Manejador_Mem man_mem;

    //accede a la memoria compartida
    // posición inicial
    char *dir = man_mem.abrir_memoria(n);
    struct header *pHeader = (struct header *)dir;
    int i = pHeader->i;

    //Llama los 3 semaforo requeridos, mutex, vacio lleno para el productor consumidor
    sem_t *arrayMut, *arrayVacio, *arrayLleno;
    int tipopipo;
    if (registro.tipo == 'B')
    {
        tipopipo = i;
    }
    if (registro.tipo == 'D')
    {
        tipopipo = i + 1;
    }
    if (registro.tipo == 'S')
    {
        tipopipo = i + 2;
    }
    string mutex = "Mut" + n + to_string(tipopipo);
    string vacio = "Vacio" + n + to_string(tipopipo);
    string lleno = "Lleno" + n + to_string(tipopipo);
    arrayMut = sem_open(mutex.c_str(), 0);
    arrayVacio = sem_open(vacio.c_str(), 1);
    arrayLleno = sem_open(lleno.c_str(), 0);

    //accede a la memoria compartida
    // posición inicial
    char *dire = man_mem.abrir_memoriaQ(n);

    headerQ *pHeaderQ = (struct headerQ *)dire;

    int q = pHeaderQ->q;

    // variable para recorrer la bandeja
    int recorrido = 0;
    //Semaforos
    int posSem = q;
    string s = to_string(posSem);

    // posición inicial de la bandeja según el tipo
    int posBandeja = tipopipo - i;
    char *pos = dire + sizeof(headerQ) + (posBandeja * sizeof(registrosalida) * q );

    //hasta que no logre insertar intentar
    // Espera la semaforo para insertar, vacio para saber si hay cupo y el mutex
    sem_wait(arrayVacio);
    sem_wait(arrayMut);
    // ciclo que avanza dentro de una bandeja usando n, recorre bandeja
    while (recorrido < q)
    {
        //posición en la bandeja
        char *posn = (pos + (recorrido * sizeof(registrosalida)));
        struct registrosalida *pRegistroSalida = (struct registrosalida *)posn;
        //si logra insertar se sale
        if (pRegistroSalida->cantidad <= 0)
        {
            pRegistroSalida->id = registro.id;
            pRegistroSalida->tipo = registro.tipo;
            pRegistroSalida->cantidad = registro.cantidad;
            sem_post(arrayMut);
            sem_post(arrayLleno);
            return EXIT_SUCCESS;
        }
        // sino sigue avanzando
        else
        {
            recorrido++;
        }
    }

    return 1;
}
