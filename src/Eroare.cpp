#include "../headers/Eroare.h"

Eroare::Eroare(const string &arg) : runtime_error(arg) {}

eroare_coliziune::eroare_coliziune(const string &arg) : Eroare(arg) {}
