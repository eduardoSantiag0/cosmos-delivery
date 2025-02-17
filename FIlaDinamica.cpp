#include "FilaDinamica.hpp"

FilaDinamica::FilaDinamica() : comeco(0), fim(0), numElementos(0)
{
}

bool FilaDinamica::enfileirar (int num) 
{
    Cores novoElemento;
    switch (num) {
        case 0: novoElemento = Cores::VERMELHO; break;
        case 1: novoElemento = Cores::VERDE; break;
        case 2: novoElemento = Cores::AZUL; break;
    }
    // int novo = utilsAED::randomIntGenerator(3);
    // Cores novoElemento = static_cast<Cores>(num);
    // fila[fim] = novoElemento;
    fila.push_back(novoElemento);

    fim++;
    numElementos++;
    return true;
}

Cores FilaDinamica::desenfileirar() 
{    


    // Cores out = fila[comeco];
    // if (estaVazia()) {
    //     throw std::out_of_range("Fila vazia!");
    // }

    Cores out = fila.front();

    fila.erase(fila.begin());

    std::cout << "Removendo... " << corParaString(out) << std::endl;

    numElementos--;
    return out;
}

std::string FilaDinamica::corParaString(Cores cor) const 
{
    switch (cor) {
        case Cores::VERMELHO: return "VERMELHO";
        case Cores::AZUL: return "AZUL";
        case Cores::VERDE: return "VERDE";
        default: return "DESCONHECIDA";
    }
}

void FilaDinamica::mostrarFila() const
{
    if (estaVazia()) {
        std::cout << "FILA ESTA VAZIA " << std::endl;
        return;
    }

    for (Cores cor : fila) {
        std::cout << corParaString(cor) << " ";
    }

    std::cout << "\tFIM DA FILA" << std::endl;
}

bool FilaDinamica::estaVazia() const
{
    return numElementos == 0;
}


Cores FilaDinamica::mostrarFrente() const 
{
    return fila.front();
}


int FilaDinamica::getQueueSize() const
{
    return fila.size();
}

Cores FilaDinamica::getAt(int i) const
{
    return fila.at(i);
}