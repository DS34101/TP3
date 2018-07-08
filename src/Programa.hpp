#include "Programa.h"
using namespace std;
//constructor inicializa lista prog en vacia y la cantidad de rutnias es 0

Programa::Programa():ListaProg(),cantRutina() {}

Programa::~Programa(){
    for(int i =0; i<cantRutina;i++){
        delete ListaProg[i];
    }
    ListaProg.clear();
}

void Programa::AgregarAunNoExiste(Instruccion instr, int indiceRut) {
    int i=0;
    bool encontrado = false;
    while(i<AunNoExistentes.size() && encontrado == false){
        if (get<0>(AunNoExistentes[i]) == instr.nombreRutina()){
            encontrado = true;
            get<1>(AunNoExistentes[i]).push_back(&((ListaProg[indiceRut])->instRut)[(ListaProg[indiceRut])->tamRut -1]);
        }
        i++;
    }
    if (encontrado == false) {
        vector<tuple<Instruccion, int>*> vacia;
        int tamaniodelaRutina = ListaProg[indiceRut]->tamRut;
        vacia.push_back(&(ListaProg[indiceRut])->instRut[tamaniodelaRutina-1]);
        AunNoExistentes.push_back(make_tuple(instr.nombreRutina(), vacia));
    }
}

void Programa::BuscarEnAunNoExiste(Id r, int indiceRut) {
    int i=0;
    bool encontrado = false;
    while(i<AunNoExistentes.size() && !encontrado) {
        if (get<0>(AunNoExistentes[i]) == r) {
            encontrado = true;
            int j=0;
            while (j<(get<1>(AunNoExistentes[i])).size()){
                get<1>(*(get<1>(AunNoExistentes[i])[j]))=indiceRut;
                j++;
            }
        }
        i++;
    }
    int l=0;
    for (int k = 0; k < AunNoExistentes.size()-1; ++k) {
        if (get<0>(AunNoExistentes[i]) == r)
            l++;
        AunNoExistentes[k]==AunNoExistentes[l];
        k++;
        l++;
    }
    AunNoExistentes.pop_back();
}


void Programa::AgInstruccion(string r,Instruccion inst){

    bool existe = false;
    int indiceRut = 0;

    for(int i=0; i<cantRutina;i++ ){
        if (ListaProg[i]->Rut == r){
            indiceRut = i;
            existe = true;
        }

    }

    if(existe){
        if(inst.OP() == OJUMP || inst.OP() == OJUMPZ ){
            bool esta = false;
            int indiceAux = 0;

            for(int j = 0;j<cantRutina;j++){

                if(inst.nombreRutina() == ListaProg[j]->Rut ){
                    esta = true;
                    indiceAux = j;

                }

            }
            if(esta){
                tuple<Instruccion,int> v(inst,indiceAux);
                ListaProg[indiceRut]->instRut.push_back(v);
                ListaProg[indiceRut]->tamRut++;

            }else{

                vector<tuple<Instruccion,int>> n;
                Rutina* rut = new Rutina(inst.nombreRutina(), n);
                ListaProg.push_back(rut);
                cantRutina++;
                tuple<Instruccion,int> w(inst,cantRutina-1);
                ListaProg[indiceRut]->instRut.push_back(w);


            }
        }else{
            tuple<Instruccion,int> x(inst,indiceRut);
            ListaProg[indiceRut]->instRut.push_back(x);
            ListaProg[indiceRut]->tamRut++;
        }


    }else{
        if(inst.OP() == OJUMP || inst.OP() == OJUMPZ ){
            bool esta = false;
            int indiceAux = 0;
            vector<tuple<Instruccion,int>> n2;
            Rutina* rut2 = new Rutina(r, n2);
            ListaProg.push_back(rut2);
            cantRutina = 0;

            for(int j = 0;j<cantRutina;j++){
                if(ListaProg[j]->Rut == inst.nombreRutina() ){
                    esta = true;
                    indiceAux = j;
                }
            }
            if(esta){
                tuple<Instruccion,int> v2(inst,indiceAux);
                ListaProg[cantRutina-1]->instRut.push_back(v2);
                ListaProg[cantRutina]->tamRut++;
                cantRutina++;
            }else{
                vector<tuple<Instruccion,int>> n2;
                /*Rutina* rut = new Rutina(inst.nombreRutina(), n2);
                ListaProg.push_back(rut);
                cantRutina++;*/
                tuple<Instruccion,int> w2(inst,-1);
                ListaProg[cantRutina-1]->instRut.push_back(w2);
            }
        }else{
            tuple<Instruccion,int> x2(inst,indiceRut);
            ListaProg[cantRutina-1]->instRut.push_back(x2);
            ListaProg[cantRutina-1]->tamRut++;
        }
    }
}

vector<string> Programa::Rutinas() const {
    vector<string> res;
    for(int i = 0; i<cantRutina;i++){
        res.push_back(ListaProg[i]->Rut);
    }
    return res;
}
int Programa::longitud(string r) const{
    int res = 0;
    for(int i = 0; i<cantRutina;i++){
        if(ListaProg[i]->Rut== r){
            res = ListaProg[i]->tamRut;
        }
    }
    return res;
}

Instruccion Programa::Instrucciones(string r, int n)const {
    Instruccion res;
    for(int i =0; i<cantRutina;i++){
        if(ListaProg[i]->Rut == r){
            tuple<Instruccion,int> t = ListaProg[i]-> instRut[n];
            res = get<0>(t);
        }
    }
    return res;
}
list <tuple<string,vector< tuple<Instruccion,int> >  ,int> > Programa::ParaCalculadora(){

    list <tuple<string,vector< tuple<Instruccion,int> >  ,int> >  res;

    for(int i=0;i<cantRutina;i++){
        vector<tuple<Instruccion,int>> vacia;
        tuple<string,vector< tuple<Instruccion,int> >  ,int> auxt(ListaProg[i]->Rut,vacia,ListaProg[i]->tamRut)
        ;
        res.push_back(auxt);
    }
    return res;
}
