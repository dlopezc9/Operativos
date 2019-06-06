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
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include "init.h"   
#include "memory_elements.h"

using namespace std;

// Metodo init que inicia la memoria.
int Init::init(int i, int ie, int oe, string n, int b, int d, int s, int q){

    Memory_Elements mem_el;

    // Crea la memoria compartida.
    int fd = shm_open( n.c_str(), O_RDWR | O_CREAT | O_EXCL, 0660);

    // Atrapa los errores de la memoria compartida.
    if (fd < 0) 
    {
        cerr << "Error creando la memoria compartida: 1"
	    << errno << strerror(errno) << endl;
        exit(1);
    }

    if (ftruncate(fd, sizeof(struct header) != 0) ) 
    {
        cerr << "Error creando la memoria compartida: 2"
	    << errno << strerror(errno) << endl;
        exit(1);
    }

    // Mapea la memoria compartida.
    char *dir;
    if ((dir = (char*) mmap(NULL, sizeof(struct header) , PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) 
    {
        cerr << "Error mapeando la memoria compartida: 3"
	    << errno << strerror(errno) << endl;
        exit(1);
    }
  
    // Se crea el header y se asignan sus variables.
    struct header *pHeader = (struct header *) dir;
  
    pHeader->i = i;
    pHeader->ie = ie;
    pHeader->oe = oe;
    pHeader->q = q;
    pHeader->b = b;
    pHeader->d = d;
    pHeader->s = s;
    strcpy(pHeader->n , n.c_str());

    close(fd);

    // Se mapea la memoria.
    char* aux = mem_el.abrir_memoria(n);

    cout << "La memoria se creo con exito" << endl;

    // Empieza el poceso para crear los semaforos

    // Se crean 4 semaforos por defecto (Que son los que se encagan de la bandeja B, D, S y la bandeja de salida)
    // Luego, se crea un semaforo de cada tipo por cada una de las bandejas.
    int totalsems = 4 + i;
    sem_t **arraySemMut = new sem_t *[totalsems];
    sem_t **arraySemVacio = new sem_t *[totalsems];
    sem_t **arraySemLleno = new sem_t *[totalsems];
    sem_t **arraySemReactivo = new sem_t *[3];

    // Crea los templates de los nombres para los semaforos.
    string mut = "Mut" + n;
    string llen = "Lleno" + n;
    string vac = "Vacio" + n;
    string reactivo = "Reactivo" + n;
    int cantidadReact = 0;
    int espacios = ie;

    for (int j = 0; j < totalsems; j++)
    {
        // Asigna los valores del reactivo dependiendo de los semaforos que esta creando.
        // Sigue la logica de crear los primeros 3 semaforos para reactivos (mientras j < 3)
        // Luego crea aquellos para el resto de las bandejas.
        if (j == 0) cantidadReact = b;
        else if (j == 1) cantidadReact = d;
        else if (j == 2) cantidadReact = s;
        else if (j >= i) espacios = oe;

        // Crea los mutex.
        ostringstream namemut;
        namemut << mut << j;
        string realNameMut(namemut.str());
        arraySemMut[j] = sem_open(realNameMut.c_str(), O_CREAT | O_EXCL, 0660, 1);

        // Crea los Vacios.
        ostringstream namellen;
        namellen << llen << j;
        string realNameLlen(namellen.str());
        arraySemVacio[j] = sem_open(realNameLlen.c_str(), O_CREAT | O_EXCL, 0660, 0);

        // Crea los llenos.
        ostringstream namevac;
        namevac << vac << j;
        string realNameVac(namevac.str());
        arraySemLleno[j] = sem_open(realNameVac.c_str(), O_CREAT | O_EXCL, 0660, espacios);

        // Crea los reactivos (solo en las primeras 3 iteraciones)
        if (j < 3)
        {
            ostringstream namereact;
            namereact << reactivo << j;
            string realNameReact(namereact.str());
            arraySemReactivo[j] = sem_open(realNameReact.c_str(), O_CREAT | O_EXCL, 0660, cantidadReact);
        }

        // Atrapa errores en caso que no pueda crear los semaforos.
        if (arraySemMut[j] == SEM_FAILED) cerr << "Error creando los semaforos 'Mut'" << endl;
        if (arraySemVacio[j] == SEM_FAILED) cerr << "Error creando los semaforos 'Vacio'" << endl;
        if (arraySemLleno[j] == SEM_FAILED) cerr << "Error creando los semaforos 'Lleno'" << endl;

        // Atrapa errores en caso no pueda crear los semaforos reactivos.
        if (j < 3)
        {
            if (arraySemReactivo[j] == SEM_FAILED) cerr << "Error creando los semaforos 'Reactivo'" << endl;
        }

    }

    cout << "Se crearon los semaforos con exito" << endl;


    //INICIAR HILOS

    //    while(true)
    //    {
            //Este ciclo se descomenta cuando sepamos que hace el init mientras bloquea la consola
    //    }    

  return EXIT_SUCCESS;

}
