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


        Nodo() : _siguientes(NULL), definicion(NULL) /*it_clave()*/{
            _siguientes = new Nodo *[256];
            int i = 0;
            while (i < 256) {
                _siguientes[i] = NULL;
                i++;
            }
        };
    };

    Nodo* _raiz;

    void encontrarYBorrar(Nodo *punt) {
        for (int i = 0; i < 256; ++i) {
            if (punt->_siguientes[i] != NULL)
                encontrarYBorrar(punt->_siguientes[i]);
            punt->_siguientes[i] = NULL;
        }
        delete[] punt->_siguientes;
        if (punt->definicion != NULL) {
            delete punt->definicion;
            punt->definicion = NULL;
        }
        delete punt;
    }
/*
 Realmente no hay razon para que este
public:
    //iterador del trie
    class iterador{
        //permite que los metodos de dicc trie
        //accedan a la parte privada del iterator
        friend class dicc_trie<T>;

        // Constructor por defecto del iterador.
        // (Nota: puede construir un iterador inválido).
        iterador();

        //devuelve true si hay mas claves para recorrer
        bool hayMas() const;

        //devuelve una tupla con el elemento actual y su significado
        par actual() const;

        //avanza a la posicion siguiente del iterador
        void avanzar();

    private:
        dicc_trie<T>* _dicc;
        std::set<string>::iterator _itClave;
    };
    */
};


#endif //SOLUCION_DICCTRIE_H
