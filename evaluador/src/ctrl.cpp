#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "ctrl.h"
#include "elements.h"
#include "manejador_mem.h"

using namespace std;

// Metodo que hace update a los datos,
// n = nombre de la memoria
// tipo = {B|D|S}
// carga = la carga a potenciar
void Ctrl::update(string n, int cantidad, char tipo)
{

  Manejador_Mem man_men;
  man_men.IngresarReactivo(n, cantidad, tipo);

  return;
}


// Metodo que genera los reportes
// n = nombre de la memoria
// subcomando = subcomando deseado
void Ctrl::list(string n, string subcomando){

  Manejador_Mem man_mem;

  if(subcomando == "processing"){

    cout << "Processing:" << endl;
    man_mem.recorrerQ(n);

  } else if(subcomando == "waiting"){

    cout << "Waiting: " << endl;
    man_mem.recorrer_mem(n);


  } else if(subcomando == "reported"){

    cout << "Reported: " << endl;
    man_mem.recorrerOE(n);

  } else if(subcomando == "reactive"){

    man_mem.ImprimirReactivo(n);

  } else if(subcomando == "all"){

    cout << "Processing:" << endl;
    man_mem.recorrerQ(n);
    cout << "Waiting: " << endl;
    man_mem.recorrer_mem(n);
    cout << "Reported: " << endl;
    man_mem.recorrerOE(n);
    int x = man_mem.retornarContador(n);    
    
  } 

  return;
}
