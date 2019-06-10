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
    pHeader->contador = 0;
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
    int contador = pHeader->contador;

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

    //Llama los 3 semaforo requeridos, mutex, vacio lleno para el productor consumidor de las bandejas
    sem_t *arrayMut, *arrayVacio, *arrayLleno;
    string mutex = "Mut" + n + to_string(bandeja);
    string vacio = "Vacio" + n + to_string(bandeja);
    string lleno = "Lleno" + n + to_string(bandeja);
    arrayMut = sem_open(mutex.c_str(), 0);
    arrayVacio = sem_open(vacio.c_str(), 1);
    arrayLleno = sem_open(lleno.c_str(), 0);

    // accede a la memoria compartida
    // posición inicial
    char *dir = abrir_memoria(n);

    header *pHeader = (header *)dir;

    int i = pHeader->i;
    int ie = pHeader->ie;
    int oe = pHeader->oe;
    int contador = pHeader->contador;

    // variable para recorrer la bandeja
    int recorrido = 0;

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
            registro.tipo = pRegistro->tipo;
            registro.time = pRegistro->time;
            registro.bandeja = pRegistro->bandeja; 

            //Pongo basura donde estaba
            pRegistro->bandeja = bandeja;
            pRegistro->id = 0;
            pRegistro->tipo = '0';
            pRegistro->cantidad = 0;
            pRegistro->time = 0;

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
    int contador = pHeader->contador;

    while (temp1 < i)
    {
        char *pos = (temp1 * ie * sizeof(registroentrada)) + dir + sizeof(struct header);
        while (temp2 < ie)
        {
            char *posn = (pos + (temp2 * sizeof(registroentrada)));
            struct registroentrada *pRegistro = (struct registroentrada *)posn;

            if(pRegistro->id != 0){
                cout <<"[" << pRegistro->id << " "
                    << pRegistro->bandeja << " "
                    << pRegistro->tipo << " "
                    << pRegistro->cantidad << "]" << endl;
            }

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
    int i = pHeader->i;
    int b = pHeader->b;
    int d = pHeader->d;
    int s = pHeader->s;

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
    pHeaderQ->i = i;
    pHeaderQ->b = b;
    pHeaderQ->d = d;
    pHeaderQ->s = s;

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

    char *dirQ;

    if ((dirQ = (char *)(mmap(NULL, sizeof(headerQ), PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0))) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: Q5"
             << errno << strerror(errno) << endl;
        exit(1);
    }

    headerQ *pHeaderQ = (headerQ *)dirQ;
    int q = pHeaderQ->q;
    int i = pHeaderQ->i;
    int b = pHeaderQ->b;
    int d = pHeaderQ->d;
    int s = pHeaderQ->s;


    munmap((void *)pHeaderQ, sizeof(headerQ));
    size_t memorysize = sizeof(headerQ) + (sizeof(registrosalida) * q * 3);

    if ((dirQ = (char *)(mmap(NULL, memorysize, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0))) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: Q6"
             << errno << strerror(errno) << endl;
        exit(1);
    }
    return dirQ;
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
    int b = pHeaderQ->b;
    int d = pHeaderQ->d;
    int s = pHeaderQ->s;

 
    while (recorrido < 3)
    {
        char *pos = dire + sizeof(struct headerQ) + (recorrido * sizeof(registrosalida) * q);
        
        while(temp2 < q ){
        char *posn = pos + (temp2 * sizeof(registrosalida));
        registrosalida *pRegistroSalida = (registrosalida *)posn;

        if (pRegistroSalida->id !=  0){
            cout << "[" << pRegistroSalida->id << " "
                << pRegistroSalida->bandeja << " " 
                << pRegistroSalida->tipo  << " " 
                << pRegistroSalida->cantidad << " "
                << pRegistroSalida->time << "]" << endl;
        }

        temp2++;
        }
        
        recorrido++;
        temp2 = 0;
    }
    return 0;
}

int Manejador_Mem::ingresarBandejaQ(registrosalida registro, string n)
{
    Manejador_Mem man_mem;

    // Accede a la memoria compartida
    // posición inicial
    char *dire = man_mem.abrir_memoriaQ(n);

    headerQ *pHeaderQ = (struct headerQ *)dire;

    int q = pHeaderQ->q;
    int i = pHeaderQ->i;
    int b = pHeaderQ->b;
    int d = pHeaderQ->d;
    int s = pHeaderQ->s;

    //Llama los 3 semaforo requeridos, mutex, vacio lleno para el productor consumidor
    sem_t *arrayMut, *arrayVacio, *arrayLleno;
    int tipopipo;

    if (registro.tipo == 'B') tipopipo = i;
    if (registro.tipo == 'D') tipopipo = i + 1;
    if (registro.tipo == 'S') tipopipo = i + 2;

    string mutex = "Mut" + n + to_string(tipopipo);
    string vacio = "Vacio" + n + to_string(tipopipo);
    string lleno = "Lleno" + n + to_string(tipopipo);
    arrayMut = sem_open(mutex.c_str(), 0);
    arrayVacio = sem_open(vacio.c_str(), 0);
    arrayLleno = sem_open(lleno.c_str(), 0);


    // variable para recorrer la bandeja
    int recorrido = 0;

    // posición inicial de la bandeja según el tipo
    int posBandeja = tipopipo - i;
    char *pos = dire + sizeof(headerQ) + (posBandeja * sizeof(registrosalida) * q);

    //hasta que no logre insertar intentar
    // Espera la semaforo para insertar, vacio para saber si hay cupo y el mutex
    sem_wait(arrayVacio);
    sem_wait(arrayMut);

    // ciclo que avanza dentro de una bandeja usando n, recorre bandeja
    while (recorrido < q)
    {
        //posición en la bandeja
        char *posn = (pos + (recorrido * sizeof(registrosalida)));
        registrosalida *pRegistroSalida = (registrosalida *)posn;
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

registrosalida Manejador_Mem::retirarRegistroDeQ(char tipo, string n)
{
    Manejador_Mem man_mem;

    //accede a la memoria compartida
    // posición inicial
    char *dirQ = man_mem.abrir_memoriaQ(n);
    headerQ *pHeaderQ = (headerQ *)dirQ;

    int q = pHeaderQ->q;
    int i = pHeaderQ->i;
    int b = pHeaderQ->b;
    int d = pHeaderQ->d;
    int s = pHeaderQ->s;


    //Llama los 3 semaforo requeridos, mutex, vacio lleno para el productor consumidor de las bandejas
    sem_t *arrayMut, *arrayVacio, *arrayLleno, *arrayReact;
    int pos_tipo;
    int pos_bandejaQ;
    if (tipo == 'B')
    {
        pos_tipo = i;
        pos_bandejaQ = 0;

    }
    if (tipo == 'D')
    {
        pos_tipo = i + 1;
        pos_bandejaQ = 1;
    }
    if (tipo == 'S')
    {
        pos_tipo = i + 2;
        pos_bandejaQ = 2;
    }

    string mutex = "Mut" + n + to_string(pos_tipo);
    string vacio = "Vacio" + n + to_string(pos_tipo);
    string lleno = "Lleno" + n + to_string(pos_tipo);
    string reactivo = "Reactivo" + n + to_string(pos_bandejaQ);

    arrayMut = sem_open(mutex.c_str(), 0);
    arrayVacio = sem_open(vacio.c_str(), 0);
    arrayLleno = sem_open(lleno.c_str(), 0);
    arrayReact = sem_open(reactivo.c_str(), 0);

    // variable para recorrer la bandeja
    int recorrido = 0;

    // posición inicial de la bandeja B|D|S
    char *pos = dirQ + sizeof(headerQ) + (pos_bandejaQ * q * sizeof(registrosalida));

    //Crear el registro de salida que d
    registrosalida registro;

    //hasta que no logre insertar intentar
    // Espera la semaforo para insertar, vacio para saber si hay cupo y el mutex
    sem_wait(arrayLleno);
    sem_wait(arrayMut);
    // ciclo que avanza dentro de una bandeja usando n, recorre bandeja
    while (recorrido < q)
    {

        //posición en la bandeja
        char *posn = (pos + (recorrido * sizeof(registrosalida)));
        registrosalida *pRegistro = (registrosalida *)posn;
        
        

        //si encuentro elemento a retirar
        if (pRegistro->cantidad > 0)
        {
            char* dirQ2 = man_mem.abrir_memoriaQ(n);
            headerQ *pHeaderQ2 = (headerQ *)dirQ2;

            //GENERACION del costo en reativo según tipo
            int costo;
            char tipodelregistro = pRegistro->tipo;
            for (int f = 0; f < pRegistro->cantidad; ++f)
            {
                if (tipodelregistro == 'B')
                    costo += rand() % ((7 + 1) - 1);
                if (tipodelregistro == 'D')
                    costo += 5 + rand() % ((20 + 1) - 5);
                if (tipodelregistro == 'S')
                    costo += 8 + rand() % ((25 + 1) - 8);
            }
            // Si es tipo B, Si no tengo suficiente reactivo libero el mutex y lo espero de nuevo
            if (tipodelregistro == 'B')
            {
                while (pHeaderQ2->b < costo)
                {
                    sem_wait(arrayReact);
                }
                pHeaderQ2->b -= costo;
            }
            // Si es tipo D, Si no tengo suficiente reactivo libero el mutex y lo espero de nuevo
            if (tipodelregistro == 'D')
            {
                while (pHeaderQ2->d < costo)
                {
                    sem_wait(arrayReact);
                }
                pHeaderQ2->d -= costo;
            }
            // Si es tipo S, Si no tengo suficiente reactivo libero el mutex y lo espero de nuevo
            if (tipodelregistro == 'S')
            {
                while (pHeaderQ2->s < costo)
                {
                    sem_wait(arrayReact);
                }
                pHeaderQ2->s -= costo;
            }
            

        //asigno los valores a devolver
        registro.cantidad = pRegistro->cantidad;
        registro.id = pRegistro->id;
        registro.tipo = pRegistro->tipo;
        registro.bandeja = pRegistro->bandeja;
        registro.time = pRegistro->time;

        //Pongo basura donde estaba
        //pRegistro->bandeja = bandeja;
        pRegistro->id = 0;
        pRegistro->tipo = '0';
        pRegistro->cantidad = 0;
        pRegistro->bandeja = 0;
        pRegistro->time = 0;
        sem_post(arrayMut);
        sem_post(arrayVacio);
        

        return registro;
        } else {
        recorrido++;
        }
        
    }
    return registro;
}

int Manejador_Mem::ingresarSalida(registrosalida registro, string n)
{

    Manejador_Mem man_mem;

    //accede a la memoria compartida
    // posición inicial
    char *dir = man_mem.abrir_memoria(n);
    header *pHeader = (header *)dir;
    int i = pHeader->i;
    int oe = pHeader->oe;
    int ie = pHeader->ie;

    //Llama los 3 semaforo requeridos, mutex, vacio lleno para el productor consumidor
    sem_t *arrayMut, *arrayVacio, *arrayLleno;
    int pos_sem = i + 3;
    string mutex = "Mut" + n + to_string(pos_sem);
    string vacio = "Vacio" + n + to_string(pos_sem);
    string lleno = "Lleno" + n + to_string(pos_sem);
    arrayMut = sem_open(mutex.c_str(), 0);
    arrayVacio = sem_open(vacio.c_str(), 0);
    arrayLleno = sem_open(lleno.c_str(), 0);
    int recorrido = 0;

    // posición inicial de la bandeja i
    char *pos = (i * ie * sizeof(registroentrada)) + dir + sizeof(header);

    //hasta que no logre insertar intentar
    // Espera la semaforo para insertar, vacio para saber si hay cupo y el mutex
    sem_wait(arrayVacio);
    sem_wait(arrayMut);

    // ciclo que avanza dentro de una bandeja usando n, recorre bandeja
    while (recorrido < oe)
    {
        //posición en la bandeja
        char *posn = (pos + (recorrido * sizeof(registrosalida)));
        registrosalida *pRegistro = (registrosalida *)posn;

        //si logra insertar se sale
        if (pRegistro->cantidad <= 0)
        {
        pRegistro->id = registro.id;
        pRegistro->tipo = registro.tipo;
        pRegistro->cantidad = registro.cantidad;
        pRegistro->bandeja = registro.bandeja;
        pRegistro->resultado = registro.resultado;
        pRegistro->time = registro.time;
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

int Manejador_Mem::recorrerOE(string n)
{
    Manejador_Mem man_mem;

    int temp1 = 0;

    // posición inicial
    char *dir = man_mem.abrir_memoria(n);
    header *pHeader = (header *)dir;

    int i = pHeader->i;
    int ie = pHeader->ie;
    int oe = pHeader->oe;
    char *pos = (i * ie * sizeof(registroentrada)) + dir + sizeof(header);

    while (temp1 < oe)
    {
        char *posn = (pos + (temp1 * sizeof(registrosalida)));
        registrosalida *pRegistro = (registrosalida *)posn;
        
        if (pRegistro->id != 0){
            cout << "[" << pRegistro->id << " "
                 << pRegistro->tipo << " " 
                 << pRegistro->cantidad << " " 
                 << pRegistro->resultado << "]"
                 << endl;
        }
        temp1++;
    }

    return 0;
}

int Manejador_Mem::IngresarReactivo(string nombre, int cantidad, char tipo)
{
    Manejador_Mem man_mem;

    if (cantidad < 0) return 1;

    //accede a la memoria compartida
    // posición inicial
    char *dirQ = man_mem.abrir_memoriaQ(nombre);
    headerQ *pHeaderQ = (headerQ *)dirQ;

    int b = pHeaderQ->b;
    int d = pHeaderQ->d;
    int s = pHeaderQ->s;
    int i = pHeaderQ->i;

    sem_t *arrayReact;
    int pos_tipo;

    if (tipo == 'B')
        pos_tipo = 0;
    if (tipo == 'D')
        pos_tipo = 1;
    if (tipo == 'S')
        pos_tipo = 2;

    string reactivo = "Reactivo" + nombre + to_string(pos_tipo);
    arrayReact = sem_open(reactivo.c_str(), 0);

    if (tipo == 'B')
    {
        pHeaderQ->b += cantidad;
    }
    if (tipo == 'D')
    {
        pHeaderQ->d += cantidad;
    }
    if (tipo == 'S')
    {
        pHeaderQ->s += cantidad;
    }
    sem_post(arrayReact);

    return 0;
}

int Manejador_Mem::ImprimirReactivo(string nombre)
{
    Manejador_Mem man_mem;

    char *dirQ = man_mem.abrir_memoriaQ(nombre);
    headerQ *pHeaderQ = (headerQ *)dirQ;

    int b = pHeaderQ->b;
    int d = pHeaderQ->d;
    int s = pHeaderQ->s;

    cout << "Tenemos " << b << " de reactivo B" << endl;
    cout << "Tenemos " << d << " de reactivo D" << endl;
    cout << "Tenemos " << s << " de reactivo S" << endl;
    
    return 0;
}

int Manejador_Mem::retornarContador(string nombre)
{
    Manejador_Mem man_mem;

  // accede a la memoria compartida
  // posición inicial
  char *dir = man_mem.abrir_memoria(nombre);
  header *pHeader = (header *)dir;

  int contador = pHeader->contador;
  cout << "Se han ingresado  " << contador << " registros"<<endl;

  return contador;
}
