#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <semaphore.h>
#include "stop.h"
#include "memory_elements.h"

using namespace std;

void Stop::stop(string n)
{
  Memory_Elements mem_ele;

  cout << "Voy a borrar el espacio de memoria llamado..." << endl;
  cout << n << endl;
  cout << "Me pase eso por la galleta 4Head" << endl;
  
  char *dir = mem_ele.abrir_memoria(n);
  struct header *pHeader = (struct header *)dir;

  int i = pHeader->i;

  int totalsems = 4 + i;
  string mut = "Mut" + n;
  string llen = "Lleno" + n;
  string vac = "Vacio" + n;
  string reactivo = "Reactivo" + n;

  sem_unlink(((reactivo + "0")).c_str());
  sem_unlink(((reactivo + "1")).c_str());
  sem_unlink(((reactivo + "2")).c_str());

  n = "/" + n;
  shm_unlink(n.c_str());

  for (int h = 0; h < totalsems; ++h)
  {
    ostringstream namemut;
    namemut << mut << h;
    string realNameMut(namemut.str());
    sem_unlink(realNameMut.c_str());

    ostringstream namellen;
    namellen << llen << h;
    string realNameLlen(namellen.str());
    sem_unlink(realNameLlen.c_str());

    ostringstream namevac;
    namevac << vac << h;
    string realNameVac(namevac.str());
    sem_unlink(realNameVac.c_str());
  }

//  cout << "Cerrando memoria " << n << endl;

  return;
}