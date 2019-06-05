#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "ctrl.h"

using namespace std;

void Ctrl::update(string n, string tipo, int carga)
{

  return;
}

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
