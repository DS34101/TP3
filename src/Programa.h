#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#include <vector>
#include <tuple>
#include <string>
#include <list>
#include "Instruccion.h"
using namespace std;




class Programa{
private:
    struct Rutina;

public:
    Programa();
    ~Programa();

    void AgInstruccion(string,Instruccion);
    vector<string> Rutinas() const;
    int longitud(string) const ;
    Instruccion Instrucciones(string , int) const;
    list <tuple<string,vector< tuple<Instruccion,int> >  ,int> > ParaCalculadora();




private:
    struct Rutina{

        /* inicia rutina vacia */
        Rutina(Id r, vector<tuple<Instruccion,int>> i):Rut(r),instRut(i),tamRut(){}
        /* *************************** */
        Id Rut;
        vector<tuple<Instruccion,int>> instRut;
        int tamRut;


    };
    vector<Rutina*> ListaProg;

    vector<tuple<string,tuple<Instruccion,int>* > > ParaAgregar;
    int cantRutina;

    void SandDAUX(string);
    void AgregarAunNoExiste(Instruccion,int);
    void BuscarEnAunNoExiste(Id, int);

};


#endif //SOLUCION_PROGRAMA_H
