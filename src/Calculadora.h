//
// Created by dn-01 on 01/07/18.
//
#ifndef CALCULADORA_H_
#define CALCULADORA_H_

#include "Programa.h"
#include "Ventana.h"
#include "diccTrie.hpp"
#include <tuple>

using namespace std;

typedef string rut;
typedef string Variable;

class Calculadora{
public:

    void nuevaCalculadora(Programa ,rut, int);

    ~Calculadora();

    bool ejecutando()const;

    void ejecutarUnPaso();

    void asignarVariable(Variable, int);

    int valorHistoricoVariable(Variable, int)const;

    int valorActualVariable(Variable)const;

    int IndiceInstruccionActual();

    int InstanteActual()const;

    rut rutinaActual();

    stack<int> Pila()const;

private:

    struct tuplaAsignacion{
        int valor;
        string variable;
        int instante;
    };
    struct tuplaVentana{
        int instante ;
        int valor;
    };
    struct Instr{
        Instruccion instruccion;
        int IndiceSalto;
        Ventana<tuplaVentana> *punteroVentana;
    };
    struct Rutina{
        string nombreRutina;
        list<Instr> Instrucciones;
        int tamanioRutina;
    };
    int momentoActual;
    int capacidadVentana;
    int indiceRutinaActual;
    int indiceInstruccion;
    stack<int> pila;
    vector<Rutina> progCalc;
    list<tuplaAsignacion> asignaciones;
    int cantidadAsignaciones;
    dicc_trie<Ventana<tuplaVentana>> varVentana;
    dicc_trie<int> varAsignacionActual;
    tuple<Programa, rut> inicio;
    list<Instr>::iterator itaInstruccion;
};


#endif //SOLUCION_CALCULADORA_H
