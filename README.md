# Operativos
Final Operativos

Para compilar el proyecto se debe ubicar en ./evaluador/src/ y realizar el comando make, se espera a que se compile y cree el ejecutable evaluador.exe.

Para la ejecucion se pueden utilizar los siguientes comandos
  ./evaluador init [-i <integer>] [-ie <integer>] [-oe <integer>][-n <string>] [-b <integer>] [-d <integer>][-s <integer>] [-q <integer>]
  
  ./evaluator reg [-n <string>]{{<filename>}... | -}
  
  ./evaluator ctrl [-n <string>]
    > list [ processing  | waiting | reported | reactive | all ] NL

Para usar como referencia:
  https://tiswww.cwru.edu/php/chet/readline/rltop.html#Introduction
  Leer lineas de comando de manera dinamica.
  
  https://hackernoon.com/learn-c-multi-threading-in-5-minutes-8b881c92941f
  Hacer multi-threads para dummies
  
  https://github.com/catchorg/Clara
  A simple to use, composable, command line parser for C++ 11 and beyond
  
  https://github.com/fcardonaEAFIT/ProductorConsumidorProcesos/blob/master/initMemSem.cpp
