#ifndef OOP_PROJECT_EROARE_H
#define OOP_PROJECT_EROARE_H
#include <iostream>
using namespace std;

class Eroare : runtime_error
{
public:
    explicit Eroare(const string &arg);
};

class eroare_coliziune : public Eroare
{
public:
    explicit eroare_coliziune(const string &arg = "Game Over!");
};

#endif
