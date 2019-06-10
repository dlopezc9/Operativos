#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <semaphore.h>
#include "reg.h"
#include "elements.h"
#include "manejador_mem.h"

using namespace std;

int Reg::agregar(registroentrada registro, string nombre)
{
    Elements mem_el;   
    Manejador_Mem man_mem;

  //Llama los 3 semaforo requeridos, mutex, vacio lleno para el productor consumidor
  sem_t *arrayMut, *arrayVacio, *arrayLleno;
  string mutex = "Mut" + nombre + to_string(registro.bandeja);
  string vacio = "Vacio" + nombre + to_string(registro.bandeja);
  string lleno = "Lleno" + nombre + to_string(registro.bandeja);
  arrayMut = sem_open(mutex.c_str(), 0);
  arrayVacio = sem_open(vacio.c_str(), 1);
  arrayLleno = sem_open(lleno.c_str(), 0);

  //accede a la memoria compartida
  // posición inicial
  char *dir = man_mem.abrir_memoria(nombre);
  bool insertado = false;

  header *pHeader = (header *)dir;

  int i  = pHeader->i;
  int ie = pHeader->ie;
  int oe = pHeader->oe;
  int contador = pHeader->contador;
  
  // variable para recorrer la bandeja
  int recorrido = 0;

  // posición inicial de la bandeja i
  char *pos = (registro.bandeja * ie * sizeof(registroentrada)) + dir + sizeof(header);

  //hasta que no logre insertar intentar
  // Espera la semaforo para insertar, vacio para saber si hay cupo y el mutex
  //Soy consumidor
  sem_wait(arrayVacio);
  sem_wait(arrayMut);

  // ciclo que avanza dentro de una bandeja usando n, recorre bandeja
  while (recorrido < ie)
  {
    //posición en la bandeja
    char *posn = (pos + (recorrido * sizeof(registroentrada)));
    registroentrada *pRegistro = (registroentrada *)posn;

    //si logra insertar se sale
    if (pRegistro->cantidad <= 0)
    {
      pRegistro->bandeja = registro.bandeja;
      pRegistro->id = registro.id;
      pRegistro->tipo = registro.tipo;
      pRegistro->cantidad = registro.cantidad;
      pRegistro->time = rand() % ((10 - 1) + 1);
      pHeader->contador = pHeader->contador + 1;

      //Soy productor
      sem_post(arrayMut);
      sem_post(arrayLleno);
      return EXIT_SUCCESS;
      return 0;
    }
    // sino sigue avanzando
    else
    {
      recorrido++;
    }
  }

  return 1;
}