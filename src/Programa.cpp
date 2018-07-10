#include "Programa.h"

//constructor inicializa lista prog en vacia y la cantidad de rutnias es 0

Programa::Programa():ListaProg(),cantRutina(),ParaAgregar() {}


Programa::~Programa(){
    int control =ParaAgregar.size()-1;
    for(int i =0; i<control; i++){
        get<1>(ParaAgregar[i])=NULL;
    }
    ParaAgregar.clear();
    ListaProg.clear();
}
void Programa::SandDAUX(string r){
    tuple<string,tuple<Instruccion,int> > res;
    for(int i =0; i< ParaAgregar.size()-1;i++){
        if(get<0>(ParaAgregar[i])==r ){
            ParaAgregar.erase(ParaAgregar.begin() +i);
        }
    }
}

void Programa::AgInstruccion(string r,Instruccion inst){
    bool existe = false;
    int indiceRut = 0;
    for(int i=0; i<cantRutina;i++ ){
        if (ListaProg[i].Rut == r){
            indiceRut = i;
            existe = true;
        }
    }
    if(existe){
        if(inst.OP() == OJUMP || inst.OP() == OJUMPZ ){
            bool esta = false;
            int indiceAux = 0;
            for(int j = 0;j<cantRutina;j++){
                if(inst.nombreRutina() == ListaProg[j].Rut ){
                    esta = true;
                    indiceAux = j;
                }
            }
            if(esta){
                tuple<Instruccion,int> v;
                v=make_tuple(inst,indiceAux);
                ListaProg[indiceRut].instRut.push_back(v);
                ListaProg[indiceRut].tamRut++;
            }else{
                vector<tuple<Instruccion,int>> n;
                tuple<Instruccion,int> w;
                w=make_tuple(inst,-1);
                ListaProg[indiceRut].instRut.push_back(w);
                ListaProg[indiceRut].tamRut++;
                tuple<Instruccion,int>* puntinstr;
                puntinstr = &ListaProg[indiceRut].instRut[ListaProg[indiceRut].tamRut -1];
                tuple<string,tuple<Instruccion,int>*> PR(inst.nombreRutina(),puntinstr);
                ParaAgregar.push_back(PR);
            }
        }else{
            tuple<Instruccion,int> x;
            x=make_tuple(inst,indiceRut);
            ListaProg[indiceRut].instRut.push_back(x);
            ListaProg[indiceRut].tamRut++;
        }
    }else{
        vector<tuple<Instruccion,int>> n2;
        Rutina rut2(r, n2);
        ListaProg.push_back(rut2);
        cantRutina++;
        bool aux = false;
        int indexaux =0;
        int control = ParaAgregar.size();
            for(int i=0;i<control;i++){
                if(get<0>(ParaAgregar[i])==r){
                //    indexaux =i;
                    aux = true;
                    get<1>(*get<1>(ParaAgregar[i]))=cantRutina-1;
                }
            }
        if(aux){
      //  tuple<string,tuple<Instruccion,int>* >inf =ParaAgregar[indexaux];
        SandDAUX(r);
    //    get<1>(*get<1>(inf)) = ListaProg.size() -1;
        }
        if(inst.OP() == OJUMP || inst.OP() == OJUMPZ ){
            bool esta = false;
            int indiceAux = 0;
            for(int j = 0;j<cantRutina;j++){
                if(ListaProg[j].Rut == inst.nombreRutina() ){
                    esta = true;
                    indiceAux = j;
                }
            }
            if(esta){
                tuple<Instruccion,int> v2;
                v2 = make_tuple(inst,indiceAux);
                ListaProg[cantRutina-1].instRut.push_back(v2);
                ListaProg[cantRutina-1].tamRut++;
            }else{
                vector<tuple<Instruccion,int>> n2;
                /*Rutina* rut = new Rutina(inst.nombreRutina(), n2);
                ListaProg.push_back(rut);
                cantRutina++;*/
                tuple<Instruccion,int> w2;
                w2 = make_tuple(inst,-1);
                ListaProg[cantRutina-1].instRut.push_back(w2);
                ListaProg[indiceRut].tamRut++;
                tuple<Instruccion,int>* puntinstr;
                puntinstr = &ListaProg[indiceRut].instRut[ListaProg[indiceRut].tamRut-1];
                tuple<string,tuple<Instruccion,int>*> PR(inst.nombreRutina(),puntinstr);
                ParaAgregar.push_back(PR);
            }
        }else{
            tuple<Instruccion,int> x2;
            x2= make_tuple(inst,indiceRut);
            ListaProg[cantRutina-1].instRut.push_back(x2);
            ListaProg[cantRutina-1].tamRut++;
        }
    }
}

vector<string> Programa::Rutinas() const {
    vector<string> res;
    for(int i = 0; i<cantRutina;i++){
        res.push_back(ListaProg[i].Rut);

    }
    return res;

}
int Programa::longitud(string r) const{
    int res = 0;
    for(int i = 0; i<cantRutina;i++){
        if(ListaProg[i].Rut== r){
            res = ListaProg[i].tamRut;
        }
    }
    return res;
}

Instruccion Programa::Instrucciones(string r, int n)const {
    Instruccion res;
    bool encontrado = true;
    for(int i =0; i<cantRutina && encontrado;i++){
        if(ListaProg[i].Rut == r){
            tuple<Instruccion,int> t = ListaProg[i].instRut[n];
            res = get<0>(t);
            encontrado = false;
        }
    }

    return res;

}

list <tuple<string,vector< tuple<Instruccion,int> >  ,int> > Programa::ParaCalculadora(){

    list <tuple<string,vector< tuple<Instruccion,int> >  ,int> >  res;

    for(int i=0;i<cantRutina;i++){
        tuple<Id,vector< tuple<Instruccion,int> >  ,int> auxt(ListaProg[i].Rut,ListaProg[i].instRut,ListaProg[i].tamRut);
        res.push_back(auxt);

    }


    return res;
}
