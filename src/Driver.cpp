#include "Driver.h"

Driver::Driver() {
    // COMPLETAR
    p = new Programa;
}
Driver::~Driver() {
	// COMPLETAR
    delete c;
    delete p;
}

// Operaciones para agregar instrucciones

void Driver::begin(string rutina) {
	vector<Instruccion> i;
}

void Driver::end(string rutina) {
    for (int i = 0; i < get<1>(r).size(); i++) {
        (*p).AgInstruccion(rutina,get<1>(r)[i]);
    }
    get<1>(r).clear();
}

void Driver::push(int n) {
    Instruccion instr;
    instr.IPUSH(n);
	get<1>(r).push_back(instr);
}


void Driver::add() {
	Instruccion instr;
    instr.IADD();
    get<1>(r).push_back(instr);
}

void Driver::sub() {
	Instruccion instr;
    instr.ISUB();
    get<1>(r).push_back(instr);
}

void Driver::mul() {
	Instruccion instr;
    instr.IMUL();
    get<1>(r).push_back(instr);
}

void Driver::read(string variable) {
	Instruccion instr;
    instr.IREAD(variable);
    get<1>(r).push_back(instr);
}

void Driver::write(string variable) {
	Instruccion instr;
    instr.IWRITE(variable);
    get<1>(r).push_back(instr);
}

void Driver::jump(string rutina) {
	Instruccion instr;
    instr.IJUMP(rutina);
    get<1>(r).push_back(instr);
}

void Driver::jumpz(string rutina) {
	Instruccion instr;
    instr.IJUMPZ(rutina);
    get<1>(r).push_back(instr);
}

/////// Operaciones para ejecutar programas

void Driver::comenzarEjecucion(string rutina, int capacidadVentana) {
    c = new Calculadora;
    (*c).nuevaCalculadora((*p),rutina, capacidadVentana);

}

void Driver::asignarVariable(string x, int valor) {
    (*c).asignarVariable(x, valor);
}

bool Driver::ejecucionFinalizada() const {
    /*Calculadora c;   //preguntar si esta bien///

    bool termino = true;

    if(c.ejecutando()){
        termino = false;
    }
    return termino; */
    return !((*c).ejecutando());
}

void Driver::ejecutarInstruccionActual() {

    (*c).ejecutarUnPaso();
}

int Driver::topePila() const{
    if ((*c).Pila().empty())
        return 0;
    else
        return (*c).Pila().top();
}

int Driver::valorVariable(string x) const {
    return (*c).valorActualVariable(x);

}

int Driver::valorHistoricoVariable(string x, int t) const {
    return (*c).valorHistoricoVariable(x,t);
}

int Driver::instanteActual() const {
    return (*c).InstanteActual();
}

