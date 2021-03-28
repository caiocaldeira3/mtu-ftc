#pragma once
#include "Fita.h"

class Mtu{
private:

    /* Attributes */
    Fita fitas[3];
    std::string M, w;
    std::vector<std::string> estadosFinais, transicoes;
    /* End of Attributes*/

    /* Setters and Updates */
    void setFita (std::string const& fitaStr, int fitaId);
    void setTransicoes (int lastState);
    void setEstadosFinais (int lastState);
    /* End of Setters and Updates */
    /* Auxiliary Functions */
    std::string const buscaTransicao (std::string const& rgPref);
    bool verificaEstadoFinal ();
    /* End of Auxiliary Functions */
public:
    /* Constructors */
    Mtu (std::string const& Mw);
    /* End of Constructors */

    /* Getters */
    Fita const& getFita (int fitaId);
    std::string const& getMaquina (void);
    std::string const& getWord (void);
    std::vector<std::string> const& getListaEstadosFinais (void);
    std::vector<std::string> const& getListaTransicoes (void);
    /* End of Getters */

    /* Problem Solver */
    std::string wEstadoFinal (void);
    /* End of Problem Solver */
};
