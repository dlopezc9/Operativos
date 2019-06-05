#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <semaphore.h>
#include "reg.h"
#include "memory_elements.h"

using namespace std;

void Reg::agregar(string n, int bandeja, string tipo, int cantidad)
{
    Memory_Elements mem_el;
    struct registroentrada nuevo_reg;

    int id = 555; // ESTO ES SOLO MIENTRAS SE DEFINE UN IDENTIFICADOR UNICO
    nuevo_reg.id = id;
    strcpy(nuevo_reg.tipo, tipo.c_str());
    nuevo_reg.cantidad = cantidad;
    nuevo_reg.bandeja = bandeja;


    


    //AQUI AGREGAR EL REGISTRO QUE SE MANDA A LAS COLAS

    return;
}

