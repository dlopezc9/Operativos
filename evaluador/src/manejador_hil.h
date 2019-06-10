#include <string>

using namespace std;

class Manejador_Hil {
    public:
        void crear_hil(string n);
        void crearHiloProcesadores(string n);
};

struct banNam {
  string nombre;
  int bandeja;
};

struct banHilo
{
    int bandeja;
    string nombre;
};

struct banPros
{
    char tipo;
    string nombre;
};
