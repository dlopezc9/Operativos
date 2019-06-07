#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "elements.h"
#include "manejador_mem.h"
#include "manejador_sem.h"
#include "manejador_hil.h"

using namespace std;

int Manejador_Mem::crear_mem(int i, int ie, int oe, string n, int b, int d, int s, int q)
{
    Elements mem_el;

    // Crea la memoria compartida.
    int fd = shm_open( n.c_str(), O_RDWR | O_CREAT | O_EXCL, 0660);

    // Atrapa los errores de la memoria compartida.
    if (fd < 0) 
    {
        cerr << "Error creando la memoria compartida: 1"
	    << errno << strerror(errno) << endl;
        exit(1);
    }

    if (ftruncate(fd, sizeof(header) != 0) ) 
    {
        cerr << "Error creando la memoria compartida: 2"
	    << errno << strerror(errno) << endl;
        exit(1);
    }

    // Mapea la memoria compartida.
    char *dir;
    if ((dir = (char*) mmap(NULL, sizeof(header) , PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) 
    {
        cerr << "Error mapeando la memoria compartida: 3"
	    << errno << strerror(errno) << endl;
        exit(1);
    }
  
    // Se crea el header y se asignan sus variables.
    header *pHeader = (header *) dir;
  
    pHeader->i = i;
    pHeader->ie = ie;
    pHeader->oe = oe;
    pHeader->q = q;
    pHeader->b = b;
    pHeader->d = d;
    pHeader->s = s;
    strcpy(pHeader->n , n.c_str());

    close(fd);

    return EXIT_SUCCESS;
}

char* Manejador_Mem::abrir_memoria(string n) 
{
    // Hace el ajuste en el string para poder acceder al espacio de memoria y abre la memoria.
    n = "/" + n;
    int fd = shm_open(n.c_str(), O_RDWR, 0660);

    // Localiza error.
    if (fd < 0) 
    {
        cerr << "Error abriendo la memoria compartida: 4" << errno << strerror(errno) << endl;
        exit(1);
    }

    char *dir;
  
    if ((dir = (char *)(mmap(NULL, sizeof(header), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) == MAP_FAILED)
    {
      cerr << "Error mapeando la memoria compartida: 5"
	         << errno << strerror(errno) << endl;
           exit(1);
    }

    // Toma los elementos del header.
    header *pHeader = (header *) dir;
  
    int i  = pHeader->i;
    int ie = pHeader->ie;
    int oe = pHeader->oe;
    int q  = pHeader->q;

    // Hace remapeo a toda la memoria.
    munmap((void *) pHeader, sizeof(header));
    size_t memorysize = sizeof(header) + (sizeof(registroentrada)* i * ie) + (sizeof(registrosalida) * oe);

    if ((dir = (char *)(mmap(NULL, memorysize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) == MAP_FAILED) 
    {
        cerr << "Error mapeando la memoria compartida: 6" << errno << strerror(errno) << endl;
        exit(1);
    }

    // Retorna la posicion inicial de la memoria.
    return dir;
}

registrosalida Manejador_Mem::retirar_reg(int bandeja, string n)
{

    char basura = 'a';
    char aux;

    //Llama los 3 semaforo requeridos, mutex, vacio lleno para el productor consumidor de las bandejas
    sem_t *arrayMut, *arrayVacio, *arrayLleno;
    string mutex = "Mut" + n + to_string(bandeja);
    string vacio = "Vacio" + n + to_string(bandeja);
    string lleno = "Lleno" + n + to_string(bandeja);
    arrayMut = sem_open(mutex.c_str(), 0);
    arrayVacio = sem_open(vacio.c_str(), 1);
    arrayLleno = sem_open(lleno.c_str(), 0);

    //accede a la memoria compartida
    // posición inicial
    char *dir = abrir_memoria(n);
    bool insertado = false;

    header *pHeader = (header *)dir;

    int i = pHeader->i;
    int ie = pHeader->ie;
    int oe = pHeader->oe;

    // variable para recorrer la bandeja
    int recorrido = 0;
    //Semaforos
    int posSem = i;
    string s = to_string(posSem);

    // posición inicial de la bandeja i
    char *pos = (bandeja * ie * sizeof(registroentrada)) + dir + sizeof(header);

    //Crear el registro de salida que devolver
    registrosalida registro;

    //hasta que no logre insertar intentar
    // Espera la semaforo para insertar, vacio para saber si hay cupo y el mutex
    sem_wait(arrayLleno);
    sem_wait(arrayMut);

    // ciclo que avanza dentro de una bandeja usando n, recorre bandeja
    while (recorrido < ie)
    {
        //posición en la bandeja
        char *posn = (pos + (recorrido * sizeof(registroentrada)));
        registroentrada *pRegistro = (registroentrada *)posn;

        //si encuentro elemento a retirar
        if (pRegistro->cantidad > 0)
        {
            //asigno los valores a devolver
            registro.cantidad = pRegistro->cantidad;
            registro.id = pRegistro->id;
            aux = registro.tipo;
            pRegistro->tipo = aux;
      
            //Pongo basura donde estaba
            pRegistro->bandeja = bandeja;
            pRegistro->id = -1;
            pRegistro->tipo = 'a';
            pRegistro->cantidad = -1;

            //soy consumidor
            sem_post(arrayMut);
            sem_post(arrayVacio);

            return registro;

        // Sigo avanzando
        } else {

            recorrido++;
        }
    }

  return registro;
}


int Manejador_Mem::recorrer_mem(string n)
{
  int temp1 = 0;
  int temp2 = 0;
  Manejador_Mem man_mem;

  // posición inicial
  char *dir = man_mem.abrir_memoria(n);
  header *pHeader = (header *)dir;

  int i = pHeader->i;
  int ie = pHeader->ie;
  int oe = pHeader->oe;

  while (temp1 < i)
  {
    char *pos = (temp1 * ie * sizeof(registroentrada)) + dir + sizeof(struct header);
    while (temp2 < ie)
    {
      char *posn = (pos + (temp2 * sizeof(registroentrada)));
      struct registroentrada *pRegistro = (struct registroentrada *)posn;
      cout << pRegistro->id << pRegistro->tipo << pRegistro->cantidad << endl;
      temp2++;
    }
    temp1++;
    temp2 = 0;
  }
  return 0;
}

int Manejador_Mem::crear_memQ(string n)
{
    Manejador_Mem man_mem;

    //accede a la memoria compartida
    // posición inicial
    char *dir = man_mem.abrir_memoria(n);
    header *pHeader = (header *)dir;
    int q = pHeader->q;

    // Abrir espacio de memoria para usar, usando el nombre n
    n = n + "Q";

    int fd = shm_open(n.c_str(), O_RDWR | O_CREAT | O_EXCL, 0660);
    if (fd < 0)
    {
        cerr << "Error creando la memoria compartida: Q1"
             << errno << strerror(errno) << endl;
        exit(1);
    }

    if (ftruncate(fd, sizeof(headerQ) != 0))
    {
        cerr << "Error creando la memoria compartida: Q2"
             << errno << strerror(errno) << endl;
        exit(1);
    }
    char *dirQ;

    if ((dirQ = (char *)mmap(NULL, sizeof(headerQ), PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0)) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: Q3"
             << errno << strerror(errno) << endl;
        exit(1);
    }

    headerQ *pHeaderQ = (headerQ *)dirQ;
    pHeaderQ->q = q;

    close(fd);
    return EXIT_SUCCESS;
}


char * Manejador_Mem::abrir_memoriaQ(string n)
{
    n = "/" + n + "Q";
    int fd = shm_open(n.c_str(), O_RDWR, 0660);
    if (fd < 0)
    {
        cerr << "Error abriendo la memoria compartida: Q4"
             << errno << strerror(errno) << endl;
        exit(1);
    }

    char *dir;

    if ((dir = (char *)(mmap(NULL, sizeof(headerQ), PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0))) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: Q5"
             << errno << strerror(errno) << endl;
        exit(1);
    }

    headerQ *pHeaderQ = (headerQ *)dir;
    int q = pHeaderQ->q;

    munmap((void *)pHeaderQ, sizeof(headerQ));
    size_t memorysize = sizeof(headerQ) + (sizeof(registrosalida) * q * 3);

    if ((dir = (char *)(mmap(NULL, memorysize, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0))) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: Q6"
             << errno << strerror(errno) << endl;
        exit(1);
    }
    return dir;
}


int Manejador_Mem::recorrerQ(string n)
{   

    int temp1 = 0;
    int temp2 = 0;
    int recorrido = 0;

    // posición inicial
    char *dire = abrir_memoriaQ(n);
    headerQ *pHeaderQ = (headerQ *)dire;
    int q = pHeaderQ->q;

    while (recorrido < 3)
    {
        char *pos = dire + sizeof(struct headerQ) + (recorrido * sizeof(registrosalida) * q);
        
        while(temp2 < q ){
        char *posn = pos + (temp2 * sizeof(registrosalida));
        registrosalida *pRegistroSalida = (registrosalida *)posn;
        cout << pRegistroSalida->id << pRegistroSalida->tipo << pRegistroSalida->cantidad << endl;
        temp2++;
        }
        
        recorrido++;
        temp2 = 0;
    }
    return 0;
}

