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
        list<Instr> v;
        vector<tuple<Instruccion, int>>::iterator itInstr = get<1>(*itRut).begin();
        int cantinstrucciones = get<2>(*itRut);
        while (itInstr != get<1>(*itRut).end()) {
            if (get<0>(*itInstr).OP() == OPUSH || (get<0>(*itInstr)).OP() == OADD || (get<0>(*itInstr)).OP() == OMUL ||
                (get<0>(*itInstr)).OP() == OSUB || (get<0>(*itInstr)).OP() == OJUMP ||
                (get<0>(*itInstr)).OP() == OJUMPZ) {
                Ventana<tuplaVentana> *ptrVentana = NULL;
                Instr i;
                i.instruccion=get<0>(*itInstr);
                i.IndiceSalto=get<1>(*itInstr);
                i.punteroVentana=ptrVentana;

                v.push_back(i);
            }
            if ((get<0>(*itInstr)).OP() == OWRITE || (get<0>(*itInstr)).OP() == OREAD) {
                if (!varVentana.definido(get<0>(*itInstr).nombreVariable())) {
                    Ventana<tuplaVentana> *v = new Ventana<tuplaVentana>(W);
                    varVentana.definirporPuntero((get<0>(*itInstr)).nombreVariable(), v);
                }
                Ventana<tuplaVentana> *ptrVentana = &varVentana.obtener((get<0>(*itInstr)).nombreVariable());
                Instr i;
                i.instruccion=get<0>(*itInstr);
                i.IndiceSalto=get<1>(*itInstr);
                i.punteroVentana=ptrVentana;
                v.push_back(i);
            }
            itInstr++;
        }
        Rutina rutina;
        rutina.Instrucciones=v;
        rutina.tamanioRutina=cantinstrucciones;
        rutina.nombreRutina=get<0>(*itRut);
        progCalc[i] = rutina;
        if (r == rutina.nombreRutina) {
            indiceRutinaActual = i;
            itaInstruccion = ((progCalc[i]).Instrucciones.begin());
        }
        itRut++;
        i++;
    }
}

Calculadora::~Calculadora() {
    asignaciones.clear();
    for (int i = 0; i < progCalc.size(); ++i) {
        list<Instr>::iterator it = (progCalc[i]).Instrucciones.begin();
        while (it != ((progCalc[i]).Instrucciones).end()) {
            (*it).punteroVentana=NULL;
            it++;
        }
    }
    progCalc.clear();
    progCalc.erase(progCalc.begin(), progCalc.end());
    while (!pila.empty()) {
        pila.pop();
    }
}


bool Calculadora::ejecutando() const {
    if (indiceRutinaActual > -1 && indiceInstruccion < (progCalc[indiceRutinaActual].tamanioRutina))
        return true;
    else
        return false;
}

void Calculadora::ejecutarUnPaso() {
    momentoActual++;
    bool nojump = true;
    if ((*itaInstruccion).instruccion.OP() == OADD) {
        if (pila.empty())
            pila.push(0);
        else if (pila.size() >= 2) {
            int a = pila.top();
            pila.pop();
            pila.top() = pila.top() + a;
        }
    } else if ((*itaInstruccion).instruccion.OP() == OMUL) {
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
    } else if ((*itaInstruccion).instruccion.OP() == OSUB) {
        if (pila.empty())
            pila.push(0);
        else if (pila.size() >= 2) {
            int a = pila.top();
            pila.pop();
            pila.top() = pila.top() - a;
        } else if (pila.size() == 1) {
            pila.top() = pila.top() * (-1);
        }
    } else if ((*itaInstruccion).instruccion.OP() == OPUSH) {
        pila.push((*itaInstruccion).instruccion.ConstanteNumerica());
    } else if ((*itaInstruccion).instruccion.OP() == OREAD) {
        int ult = itaInstruccion->punteroVentana->tam();
        if (ult == 0)
            pila.push(0);
        else {
            ult = ult -1;
            pila.push(((itaInstruccion)->punteroVentana->operator[](ult)).valor);
        }
    } else if ((*itaInstruccion).instruccion.OP() == OWRITE) {
        if (pila.empty()) {
            tuplaVentana tv;
            tv.valor=0;
            tv.instante=momentoActual;
            (*(*itaInstruccion).punteroVentana).registrar(tv);
        }else {
            tuplaVentana tv;
            tv.valor=pila.top();
            tv.instante=momentoActual;
            (*(*itaInstruccion).punteroVentana).registrar(tv);
            pila.pop();
        }
    } else if ((*itaInstruccion).instruccion.OP() == OJUMP) {
        nojump = false;
        indiceRutinaActual = (*itaInstruccion).IndiceSalto;
        itaInstruccion= ((progCalc[indiceRutinaActual]).Instrucciones).begin();
        indiceInstruccion = 0;
    } else if ((*itaInstruccion).instruccion.OP() == OJUMPZ) {
        if (pila.empty() || pila.top() == 0) {
            nojump = false;
            indiceRutinaActual = (*itaInstruccion).IndiceSalto;
            indiceInstruccion = 0;
            itaInstruccion=(progCalc[indiceRutinaActual]).Instrucciones.begin();
            if (!pila.empty())
                pila.pop();
        }
    }
    if (nojump) {
        itaInstruccion++;
        indiceInstruccion++;
    }


}

int Calculadora::IndiceInstruccionActual() {
    return indiceInstruccion;
}

int Calculadora::InstanteActual() const {
    return momentoActual;
}

rut Calculadora::rutinaActual() {
    return (progCalc[indiceRutinaActual]).nombreRutina;
}

stack<int> Calculadora::Pila() const {
    return pila;
}

void Calculadora::asignarVariable(Variable v, int n) {
    tuplaAsignacion ta;
    ta.valor=n;
    ta.instante=momentoActual;
    ta.variable=v;
    asignaciones.push_back(ta);
    cantidadAsignaciones++;
    if (varVentana.definido(v)) {
        tuplaVentana tv;
        tv.instante=momentoActual;
        tv.valor=n;
        (varVentana.obtener(v)).registrar(tv);
    } else {
        varAsignacionActual.definir(v, n);
    }
}

int Calculadora::valorHistoricoVariable(Variable v, int i) const {
    if (varVentana.definido(v)) {
        if (varVentana.obtener(v).tam() == 0) {
            return 0;
        } else {
            int l = 0;
            int r = varVentana.obtener(v).tam()-1;
            if (i >= (varVentana.obtener(v).operator[](l)).instante) {
                if ((varVentana.obtener(v).operator[](r)).instante<i)
                    return (varVentana.obtener(v).operator[](r)).valor;
                if (l!=r){
                while (l <= r) {
                    int m = l + (r - l) / 2;
                    if ((varVentana.obtener(v).operator[](m)).instante==i)
                        return (varVentana.obtener(v).operator[](m).valor);
                    if ((varVentana.obtener(v)[m]).instante < i)
                        l = m + 1;
                    else
                        r = m - 1;
                }
            }
                if (varVentana.obtener(v).operator[](l).instante<=i)
                    return (varVentana.obtener(v).operator[](l).valor);
                else
                    return (varVentana.obtener(v).operator[](r).valor);
            } else {
            /*    Programa progAUX;
                for (int k = 0; k < progCalc.size(); ++k) {
                    list<tuple<Instruccion,int,Ventana<tuple<int,int>>*>>::const_iterator it = get<1>(progCalc[k]).begin();
                    while (it != get<1>(progCalc[k]).end()){
                        progAUX.AgInstruccion(get<0>(progCalc[k]),get<0>(*it));
                        it++;
                    }
                }
              */  Calculadora nc;
                nc.nuevaCalculadora(get<0>(inicio), get<1>(inicio), capacidadVentana);
                int j = 0;
                int a = 0;
                list<tuplaAsignacion>::const_iterator itAsignaciones = asignaciones.begin();
                while (j <= i) {
                    while (cantidadAsignaciones > a && (*itAsignaciones).instante <= j) {
                        nc.asignarVariable((*itAsignaciones).variable, (*itAsignaciones).valor);
                        a++;
                        itAsignaciones++;
                    }
                    nc.ejecutarUnPaso();
                    j++;
                }
                int res = nc.valorActualVariable(v);
                return res;
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
            list<tuplaAsignacion>::const_iterator itAsignaciones = asignaciones.begin();
            while (j < cantidadAsignaciones) {
                if ((*itAsignaciones).variable == v) {
                    if ((*itAsignaciones).instante <= i)
                        res = (*itAsignaciones).valor;
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
        Ventana<tuplaVentana> ventana = varVentana.obtener(v);
        if (ventana.tam() != 0)
            return (ventana[ventana.tam()-1].valor);
        else
            return 0;
    } else
        return varAsignacionActual.obtener(v);
}


