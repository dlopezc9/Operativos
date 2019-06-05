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

int Init::init(int i, int ie, int oe, string n, int b, int d, int s, int q){

    int fd = shm_open( n.c_str(), O_RDWR | O_CREAT | O_EXCL, 0660);

    //CREAR SEMAFOROS

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

    char *dir;

    if ((dir = (char*) mmap(NULL, sizeof(struct header) , PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) 
    {
        cerr << "Error mapeando la memoria compartida: 3"
	    << errno << strerror(errno) << endl;
        exit(1);
    }
  
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

    cout << "La memoria se creo con exito" << endl;

    //    while(true)
    //    {
            //Este ciclo se descomenta cuando sepamos que hace el init mientras bloquea la consola
    //    }    

  return EXIT_SUCCESS;

}
