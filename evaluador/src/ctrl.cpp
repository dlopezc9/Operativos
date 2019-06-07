#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "ctrl.h"
#include "elements.h"

using namespace std;

// Metodo que hace update a los datos,
// n = nombre de la memoria
// tipo = {B|D|S}
// carga = la carga a potenciar
void Ctrl::update(string n, string tipo, int carga)
{

  return;
}


// Metodo que genera los reportes
// n = nombre de la memoria
// subcomando = subcomando deseado
void Ctrl::list(string n, string subcomando){

  if(subcomando == "processing"){
    cout << "Eligio processing" << endl;
  } else if(subcomando == "waiting"){
    cout << "Eligio waiting" << endl;
  } else if(subcomando == "reported"){
    cout << "Eligio reported" << endl;
  } else if(subcomando == "reactive"){
    cout << "Eligio reactive" << endl;
  } else if(subcomando == "all"){
    cout << "Eligio all" << endl;
  } 

  return;
}
