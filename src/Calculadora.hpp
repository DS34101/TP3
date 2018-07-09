#include <cmath>
#include "Calculadora.h"

void Calculadora::nuevaCalculadora(Programa prog, rut r, int W) {
    int i = 0;
    get<0>(inicio) = prog;
    get<1>(inicio) = r;
    indiceInstruccion = 0;
    momentoActual = 0;
    cantidadAsignaciones = 0;
    capacidadVentana = W;
    indiceRutinaActual = -1;
    list<tuple<string, vector<tuple<Instruccion, int> >, int> > rutinasYinstrucciones = prog.ParaCalculadora();
    list<tuple<string, vector<tuple<Instruccion, int> >, int> >::iterator itRut = rutinasYinstrucciones.begin();
    int j = rutinasYinstrucciones.size();
    progCalc.resize(j);
    while (itRut != rutinasYinstrucciones.end()) {
        list<tuple<Instruccion, int, Ventana<tuple<int, int>> *>> v;
        vector<tuple<Instruccion, int>>::iterator itInstr = get<1>(*itRut).begin();
        int cantinstrucciones = get<2>(*itRut);
        while (itInstr != get<1>(*itRut).end()) {
            if (get<0>(*itInstr).OP() == OPUSH || (get<0>(*itInstr)).OP() == OADD || (get<0>(*itInstr)).OP() == OMUL ||
                (get<0>(*itInstr)).OP() == OSUB || (get<0>(*itInstr)).OP() == OJUMP ||
                (get<0>(*itInstr)).OP() == OJUMPZ) {
                Ventana<tuple<int, int>> *ptrVentana = NULL;
                v.push_back(make_tuple(get<0>(*itInstr), get<1>(*itInstr), ptrVentana));
            }
            if ((get<0>(*itInstr)).OP() == OWRITE || (get<0>(*itInstr)).OP() == OREAD) {
                if (!varVentana.definido(get<0>(*itInstr).nombreVariable())) {
                    Ventana<tuple<int, int>> *v = new Ventana<tuple<int, int>>(W);
                    varVentana.definirporPuntero((get<0>(*itInstr)).nombreVariable(), v);
                    v = NULL;
                }
                Ventana<tuple<int, int>> *ptrVentana = &varVentana.obtener((get<0>(*itInstr)).nombreVariable());
                v.push_back(make_tuple((get<0>(*itInstr)), (get<1>(*itInstr)), ptrVentana));
            }
            itInstr++;
        }
        progCalc[i] = make_tuple(get<0>(*itRut), v, cantinstrucciones);
        if (r == get<0>(*itRut)) {
            indiceRutinaActual = i;
            itaInstruccion = ((get<1>(progCalc[i])).begin());
        }
        itRut++;
        i++;
    }
}

Calculadora::~Calculadora() {
    asignaciones.clear();
    progCalc.clear();
    progCalc.erase(progCalc.begin(), progCalc.end());
    while (!pila.empty()) {
        pila.pop();
    }
}


bool Calculadora::ejecutando() const {
    if (indiceRutinaActual > -1 && indiceInstruccion < (get<2>(progCalc[indiceRutinaActual])))
        return true;
    else
        return false;
}

void Calculadora::ejecutarUnPaso() {
    bool nojump = true;
    if (get<0>(*itaInstruccion).OP() == OADD) {
        if (pila.empty())
            pila.push(0);
        else if (pila.size() >= 2) {
            int a = pila.top();
            pila.pop();
            pila.top() = pila.top() + a;
        }
    } else if ((get<0>(*itaInstruccion).OP() == OMUL)) {
        if (pila.empty())
            pila.push(0);
        else if (pila.size() >= 2) {
            int a = pila.top();
            pila.pop();
            pila.top() = pila.top() * a;
        } else if (pila.size() == 1) {
            pila.pop();
            pila.push(0);
        }
    } else if ((get<0>(*itaInstruccion).OP() == OSUB)) {
        if (pila.empty())
            pila.push(0);
        else if (pila.size() >= 2) {
            int a = pila.top();
            pila.pop();
            pila.top() = pila.top() - a;
        } else if (pila.size() == 1) {
            pila.top() = pila.top() * (-1);
        }
    } else if ((get<0>(*itaInstruccion).OP() == OPUSH)) {
        pila.push(get<0>(*itaInstruccion).ConstanteNumerica());
    } else if ((get<0>(*itaInstruccion).OP() == OREAD)) {
        int ult = (*get<2>(*itaInstruccion)).tam();
        if (ult == 0)
            pila.push(0);
        else {
            ult = ult -1;
            pila.push(get<1>((*get<2>(*itaInstruccion)).operator[](ult)));
        }
    } else if ((get<0>(*itaInstruccion).OP() == OWRITE)) {
        if (pila.empty())
            (*get<2>(*itaInstruccion)).registrar(make_tuple(momentoActual, 0));
        else {
            (*get<2>(*itaInstruccion)).registrar(make_tuple(momentoActual, pila.top()));
            pila.pop();
        }
    } else if ((get<0>(*itaInstruccion).OP() == OJUMP)) {
        nojump = false;
        indiceRutinaActual = get<1>(*itaInstruccion);
        itaInstruccion=get<1>(progCalc[indiceRutinaActual]).begin();
        indiceInstruccion = 0;

    } else if ((get<0>(*itaInstruccion).OP() == OJUMPZ)) {
        if (pila.empty() || pila.top() == 0) {
            nojump = false;
            indiceRutinaActual = get<1>(*itaInstruccion);
            indiceInstruccion = 0;
            itaInstruccion=get<1>(progCalc[indiceRutinaActual]).begin();
            if (!pila.empty())
                pila.pop();
        }
    }
    if (nojump)
        itaInstruccion++;
    momentoActual++;
    indiceInstruccion++;
}

int Calculadora::IndiceInstruccionActual() {
    return indiceInstruccion;
}

instante Calculadora::InstanteActual() const {
    return momentoActual;
}

rut Calculadora::rutinaActual() {
    return get<0>(progCalc[indiceRutinaActual]);
}

stack<int> Calculadora::Pila() const {
    return pila;
}

void Calculadora::asignarVariable(Variable v, int n) {
    asignaciones.push_back(make_tuple(n, v, momentoActual));
    cantidadAsignaciones++;
    if (varVentana.definido(v)) {
        (varVentana.obtener(v)).registrar(make_tuple(momentoActual,n));
    } else {
        varAsignacionActual.definir(v, n);
    }
}

int Calculadora::valorHistoricoVariable(Variable v, instante i) const {
    if (varVentana.definido(v)) {
        if (varVentana.obtener(v).tam() == 0) {
            return 0;
        } else {
            int l = 0;
            int r = varVentana.obtener(v).tam()-1;
            if (i >= get<0>(varVentana.obtener(v).operator[](l))) {
                while(l < r){
                    int m = l + (r-l)/2;
                    if (get<0>(varVentana.obtener(v)[l]) <= i && get<0>(varVentana.obtener(v)[l+1]) > i)
                        return get<1>(varVentana.obtener(v)[l]);
                    if (get<0>(varVentana.obtener(v)[l]) < i)
                        l = m + 1;
                    else
                        r = m - 1;
                }
                return get<1>(varVentana.obtener(v)[l]);
            } else {
            /*    Programa progAUX;
                for (int k = 0; k < progCalc.size(); ++k) {
                    list<tuple<Instruccion,int,Ventana<tuple<int,int>>*>>::const_iterator it = get<1>(progCalc[k]).begin();
                    while (it != get<1>(progCalc[k]).end()){
                        progAUX.AgInstruccion(get<0>(progCalc[k]),get<0>(*it));
                        it++;
                    }
                }
              */  Calculadora* nc = new Calculadora;
                (*nc).nuevaCalculadora(get<0>(inicio), get<1>(inicio), capacidadVentana);
                int j = 0;
                int a = 0;
                list<tuple<int, Variable, instante>>::const_iterator itAsignaciones = asignaciones.begin();
                while (j <= i) {
                    while (cantidadAsignaciones > a && get<2>(*itAsignaciones) <= j) {
                        (*nc).asignarVariable(get<1>(*itAsignaciones), get<0>(*itAsignaciones));
                        a++;
                        itAsignaciones++;
                    }
                    (*nc).ejecutarUnPaso();
                    j++;
                }
                return (*nc).valorActualVariable(v);
            }
        }
    } else {
        if (cantidadAsignaciones == 0) {
            return 0;
        } else {
            Calculadora nc;
            nc.nuevaCalculadora(get<0>(inicio), get<1>(inicio), capacidadVentana);
            int j = 0;
            int res = 0;
            list<tuple<int, Variable, instante>>::const_iterator itAsignaciones = asignaciones.begin();
            while (j < cantidadAsignaciones) {
                if (get<1>(*itAsignaciones) == v) {
                    if (get<2>(*itAsignaciones) <= i)
                        res = get<0>(*itAsignaciones);
                }
                itAsignaciones++;
                j++;
            }
            return res;
        }
    }
}

int Calculadora::valorActualVariable(Variable v) const {
    if (varVentana.definido(v)) {
        Ventana<tuple<int, int>> ventana = varVentana.obtener(v);
        if (ventana.tam() != 0)
            return get<1>(ventana[ventana.tam()-1]);
        else
            return 0;
    } else
        return varAsignacionActual.obtener(v);
}


