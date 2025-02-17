#ifndef FILA_DINAMICA_HPP
#define FILA_DINAMICA_HPP

#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>
#include "Cores.hpp"

// enum Cores 
// {
//     VERMELHO,
//     VERDE,
//     AZUL 
// };

class FilaDinamica
{
private:
    std::vector<Cores> fila;
    int comeco, fim, numElementos;
    std::string corParaString(Cores cor) const ;
public:
    FilaDinamica();
    bool enfileirar(int num);
    Cores desenfileirar();
    bool estaVazia() const;

    Cores mostrarFrente() const;

    void mostrarFila() const;

    int getQueueSize() const;

    Cores getAt(int i) const;

};


#endif