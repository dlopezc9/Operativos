#include <string>

using namespace std;

class Manejador_Hil {
    public:
        void crear_hil(int i, string n);
        int ingresarBandejaQ(struct registrosalida registro, string n);
};

struct banNam {
  string nombre;
  int bandeja;
};