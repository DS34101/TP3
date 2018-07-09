 //
// Created by dn-01 on 28/06/18.
//
#ifndef INSTRUCCION_H_
#define INSTRUCCION_H_

#include <stack>
#include <string>
#include <list>
#include <tuple>

using namespace std;


typedef int Operacion;

const Operacion OPUSH = 1;
const Operacion OADD = 2;
const Operacion OSUB = 3;
const Operacion OMUL = 4;
const Operacion OWRITE = 5;
const Operacion OREAD = 6;
const Operacion OJUMP = 7;
const Operacion OJUMPZ = 8;

typedef std::string Id;


class Instruccion {
public:
    Instruccion();
    void IPUSH(int);

    void IADD();

    void ISUB();

    void IMUL();

    void IWRITE(Id);

    void IREAD(Id);

    void IJUMP(Id);

    void IJUMPZ(Id);

    Operacion OP() const;

    int ConstanteNumerica() const;

    Id nombreVariable() const;

    Id nombreRutina()const;

private:
    Operacion operacion;
    int _valor;
    Id nombre;
    // COMPLETAR
};


#endif //SOLUCION_INSTRUCCION_H
