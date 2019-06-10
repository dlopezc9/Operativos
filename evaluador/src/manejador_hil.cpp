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

    banHilo *producto = (banHilo *)bandej;
    int num_bandeja = producto->bandeja;
    string nom_memoria = producto->nombre;

    for (;;)
    {
        registrosalida registro = man_mem.retirar_reg(num_bandeja, nom_memoria);
        man_mem.ingresarBandejaQ(registro, nom_memoria);
    }
 
    pthread_exit(NULL);
}

void Manejador_Hil::crear_hil(string n){
    
    Manejador_Mem man_mem;

    char *dir = man_mem.abrir_memoria(n);
    header *pHeader = (header *)dir;
    int i = pHeader->i; 

    // Instancia los elementos que van a hacer parte de los hilos
    // Instancia el arreglo de los hilos.
    pthread_t hiloP[i];
    banHilo bande;
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
/*
    if (pthread_join(hiloP[0], NULL)){
        fprintf(stderr, "lo que sea\n");
        return;
    }
*/
    return;
}

void *procesadorOE(void *bandej)
{
    Manejador_Mem man_mem;
    Elements element;

    banPros *producto = (banPros *)bandej;
    char tipo = producto->tipo;
    string nom_memoria2 = producto->nombre;
    int val;

    for (;;)
    {   
        registrosalida registro = man_mem.retirarRegistroDeQ(tipo, nom_memoria2);
        val = element.generar_resultado();

        if (0 < val && val < 16) registro.resultado = '-';
        else if (15 < val && val < 36) registro.resultado = 'N';
        else if (35 < val && val < 51) registro.resultado = 'P';
        sleep(5);

        man_mem.ingresarSalida(registro, nom_memoria2);
    }

    pthread_exit(NULL);
}

void Manejador_Hil::crearHiloProcesadores(string n)
{
    Manejador_Mem man_mem;
    //accede a la memoria compartida
    // posición inicial
    char *dirq = man_mem.abrir_memoriaQ(n);
    headerQ *pHeaderQ = (headerQ *)dirq;

    int q = pHeaderQ->q;
    int i = pHeaderQ->i;

    // Instancia los elementos que van a hacer parte de los hilos
    // Instancia el arreglo de los hilos.
    pthread_t hiloQ[3];
    banPros bande;
    bande.nombre = n;
    char tipoPros = 'B';
    string n_Hilo = "Hilo" + n;

    // Crea los hilos y les asigna la funcion
    for (int m = 0; m < 3; ++m)
    {
        if(m == 1) tipoPros = 'D';
        if(m == 2) tipoPros = 'S';
        bande.tipo = tipoPros;
        ostringstream namellen;
        namellen << n_Hilo << m;
        string realNameLlen(namellen.str());
        pthread_create(&hiloQ[m], NULL, procesadorOE, (void *)&bande);
        sleep(1);
    }

    return;
}
