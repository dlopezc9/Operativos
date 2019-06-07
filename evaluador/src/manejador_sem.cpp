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
#include <semaphore.h>
#include "elements.h"
#include "manejador_sem.h"

using namespace std;

void Manejador_Sem::crear_sem(int i, int ie, int oe, string n, int b, int d, int s, int q){

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

    return;
}