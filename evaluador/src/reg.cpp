#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <semaphore.h>
#include "reg.h"
#include "elements.h"
#include "manejador_mem.h"

using namespace std;

vector<int> Reg::agregar(string n, int bandeja, string tipo, int cantidad, vector<int> id_existentes)
{
    Elements mem_el;
    Manejador_Mem man_mem;

    registroentrada nuevo_reg;
    bool ciclar = true;
    bool repetido;
    int id;

    while(ciclar){        
        id = mem_el.generar_id();
        repetido = find(begin(id_existentes), end(id_existentes), id) != end(id_existentes);

            if (!repetido){
                cout << "Es unico" << endl;
                id_existentes.insert(begin(id_existentes), id);
                ciclar = false;
            }
    }
    
    nuevo_reg.id = id;
    nuevo_reg.tipo = tipo[0];
    nuevo_reg.cantidad = cantidad;
    nuevo_reg.bandeja = bandeja;

    //Llama los 3 semaforo requeridos, mutex, vacio lleno para el productor consumidor
    sem_t *arrayMut, *arrayVacio, *arrayLleno;
    string mutex = "Mut" + n + to_string(nuevo_reg.bandeja);
    string vacio = "Vacio" + n + to_string(nuevo_reg.bandeja);
    string lleno = "Lleno" + n + to_string(nuevo_reg.bandeja);
    arrayMut = sem_open(mutex.c_str(), 0);
    arrayVacio = sem_open(vacio.c_str(), 1);
    arrayLleno = sem_open(lleno.c_str(), 0);

    // accede a la memoria compartida
    // posición inicial
    char *dir = man_mem.abrir_memoria(n);
    bool insertado = false;

    header *pHeader = (header *)dir;

    int i  = pHeader->i;
    int ie = pHeader->ie;
    int oe = pHeader->oe;

    // variable para recorrer la bandeja
    int recorrido = 0;

    //Semaforos
    int posSem = i;
    string s = to_string(posSem);

    // posición inicial de la bandeja i
    char *pos = (nuevo_reg.bandeja * ie * sizeof(registroentrada)) + dir + sizeof(header);

    //hasta que no logre insertar intentar
    // Espera la semaforo para insertar, vacio para saber si hay cupo y el mutex
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
            pRegistro->bandeja = nuevo_reg.bandeja;
            pRegistro->id = nuevo_reg.id;
            pRegistro->tipo = nuevo_reg.tipo;
            pRegistro->cantidad = nuevo_reg.cantidad;
            sem_post(arrayMut);
            sem_post(arrayLleno);
            return id_existentes;

        // Si no sigue avanzando    
        } else {
            recorrido++;
        }
    }
 
    return id_existentes;
}