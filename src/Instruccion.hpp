#include "Instruccion.h"

Instruccion::Instruccion():_valor(),operacion(),nombre(){}

void Instruccion::IPUSH(int valor){
    operacion=OPUSH;
    _valor=valor;
}

void Instruccion::IADD(){
     operacion=OADD;

}

void Instruccion::ISUB(){
    operacion=OSUB;
}

void Instruccion::IMUL(){
    operacion=OMUL;
}

void Instruccion::IREAD(Id nombreRutina) {
    operacion = OREAD;
    nombre = nombreRutina;
}

void Instruccion::IWRITE(Id Variable) {
    operacion=OWRITE;
    nombre = Variable;

}

void Instruccion::IJUMP(Id nombreRutina) {
    operacion = OJUMP;
    nombre = nombreRutina;
}

void Instruccion::IJUMPZ(Id nombreRutina) {
    operacion = OJUMPZ;
    nombre = nombreRutina;
}

Operacion Instruccion::OP() const {
    return operacion;
}

int Instruccion::ConstanteNumerica() const {
    return _valor;
}

Id Instruccion::nombreRutina()const{
    return nombre;
}

Id Instruccion::nombreVariable() const {
    return nombre;
}