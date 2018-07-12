//
// Created by dsalvia on 03/07/18.
//

#ifndef SOLUCION_DICCTRIE_H
#define SOLUCION_DICCTRIE_H
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class dicc_trie{
public:
    //forward declaration
    //struct par;
    //class iterador;

    //constructor
    //crea un diccionario vacio
    dicc_trie();

    ~dicc_trie();

    //define el significado
    void definir(const string &key, const T& siginificado);

    void definirporPuntero(const string &key, T* significado);

    //devuelve true sii la clave tiene una definicion en el diccionario
    bool definido(const string &key) const;

    // devuelve el significado de la clave pasada por parametro en el dicc
    // Pre: la clave esta definida
    T& obtener(const string& key)const;

    struct par{
        string _clave;
        T _dato;
        par(string &c, T &d) : _clave(c),  _dato(d){};
    };

private:
    struct Nodo{
        Nodo** _siguientes;
        T* definicion; // es el significado
    //    std::set::iterator it_clave; // este iteredor es de conjunto


        Nodo();
    };
    Nodo* _raiz;

    void encontrarYBorrar(Nodo* );

};


#endif //SOLUCION_DICCTRIE_H
