#pragma once

#include "Fita.h"

/* Auxiliary Functions */
std::vector<std::string> particionaStr(std::string st);
/* End of Auxiliary Functions */

class Mtu{
private:

    /* Attributes */
    Fita fitas[3];
    std::string M, w;
    std::vector<std::string> estadosFinais, transicoes;
    /* End of Attributes*/

    /* Setters and Updates */
    void setFita(std::string fitaStr, int fitaId);
    void setTransicoes(std::string transicoesStr);
    void setEstadosFinais(std::string estadosFinaisStr);
    /* End of Setters and Updates */
public:
    /* Constructors */
    Mtu(std::string Mw);
    /* End of Constructors */

    /* Route Checkers */
    /* End of Route Checkers */

    /* Getters */
    void getFita(int fitaId);
    std::vector<std::string> getListaEstadosFinais();
    std::vector<std::string> getListaTransicoes();
    /* End of Getters */
};
