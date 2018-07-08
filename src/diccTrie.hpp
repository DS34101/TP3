//
// Created by dsalvia on 03/07/18.
//

#include  "diccTrie.h"

template<typename T>
dicc_trie<T>::dicc_trie() : _raiz(NULL){}

template<typename T>
dicc_trie<T>::~dicc_trie(){
    if (_raiz!=NULL)
        encontrarYBorrar(_raiz);
    _raiz=NULL;
}
template<typename T>
void dicc_trie<T>::definir(const string &key, const T& significado) {
    if(_raiz==NULL){
        Nodo* raiz = new Nodo;
        _raiz=raiz;
    }
    Nodo* actual = _raiz;
    int i = 0;
    while (i < key.length()){
        if(actual->_siguientes[int(key[i])] == NULL) {
            Nodo *_sig = new Nodo;
            actual->_siguientes[int(key[i])] = _sig;
        }
        actual = actual->_siguientes[int(key[i])];
        i++;
    }
    if(actual->definicion != NULL){
        //limpio lo que tenia
        delete (actual->definicion);
        actual->definicion = NULL;
    }
    T* definirlo = new T;
    *definirlo=significado;
    actual->definicion = definirlo;
}

template<typename T>
void dicc_trie<T>::definirporPuntero(const string &key, T* significado) {
    if(_raiz==NULL){
        Nodo* raiz = new Nodo;
        _raiz=raiz;
    }
    Nodo* actual = _raiz;
    int i = 0;
    while (i < key.length()){
        if(actual->_siguientes[int(key[i])] == NULL) {
            Nodo *_sig = new Nodo;
            actual->_siguientes[int(key[i])] = _sig;
        }
        actual = actual->_siguientes[int(key[i])];
        i++;
    }
    if(actual->definicion != NULL){
        //limpio lo que tenia
        delete (actual->definicion);
        actual->definicion = NULL;
    }
    actual->definicion = significado;
}

template<typename T>
bool dicc_trie<T>::definido(const string &key) const {
    int i = 0;
    bool esta = true;
    if (_raiz == NULL) {
        return false;
    } else {
        Nodo *actual = _raiz;
        while (i < key.size() and esta) {
            if (actual->_siguientes[int(key[i])] == NULL) {
                return false;
            } else {
                actual = actual->_siguientes[int(key[i])];
                i++;
            }
        }
        return (actual->definicion!=NULL);
    }
}


template<typename T>
T& dicc_trie<T>::obtener(const string &key) const {
    Nodo* actual = _raiz;
    int i = 0;
    while(i < key.length()){
        actual = actual->_siguientes[int(key[i])];
        i++;
    }
    return *actual->definicion;
}

