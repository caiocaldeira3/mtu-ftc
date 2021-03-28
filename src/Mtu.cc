#include "Mtu.h"

/* Setters and Updates */
void Mtu::setFita (std::string const& fitaStr, int fitaId) {
    this->fitas[fitaId] = Fita(fitaStr);
}
void Mtu::setTransicoes (int lastState) {
    this->transicoes = particionaStr(
        this->M.substr(lastState, this->M.size() - lastState), "00", this->M.size()
    );
}
void Mtu::setEstadosFinais (int lastState) {
    this->estadosFinais = particionaStr(this->M.substr(0, lastState), "0", lastState);
}
/* End of Setters and Updates */

/* Auxiliary Functions */
std::string const Mtu::buscaTransicao (std::string const& rgPref) {
    size_t rgSz = rgPref.size();
    for (std::string const& st: this->transicoes) {
        std::string stPref = st.substr(0, std::min(rgSz, st.size()));
        if (stPref == rgPref) {
            return st;
        }
    }
    return "";
}
bool Mtu::verificaEstadoFinal () {
    for (std::string estadoFinal: this->estadosFinais) {
        if (this->fitas[2].getStrPos() == estadoFinal) {
            return true;
        }
    }
    return false;
}
/* End of Auxiliary Functions */

/* Constructors */
Mtu::Mtu (std::string const& Mw) {
    size_t wpos = Mw.find("000");
    if (wpos != std::string::npos) {
        this->w = Mw.substr(wpos + 3, Mw.size() - wpos + 3);
        this->M = Mw.substr(0, wpos);
    }
    else {
        this->w = "";
        this->M = "";
        return;
    }

    std::cout << M << " " << w << std::endl;
    size_t lastState = Mw.find("00");
    if (lastState == wpos) {
        return;
    }

    this->setEstadosFinais(lastState);
    for(std::string const& st: this->estadosFinais)
        std::cout << st << "aq ? " << std::endl;
    std::cout << std::endl;

    this->setFita(Mw.substr(lastState, Mw.size() - lastState), 0);
    this->setTransicoes(lastState + 2);

    for(std::string const& st: this->transicoes)
        std::cout << st << std::endl;
    std::cout << std::endl;

    this->setFita(this->w, 1);
    this->fitas[1].debug();

    std::string const dummy = "1";
    this->setFita(dummy, 0);
}
/* End of Constructors */

/* Getters */
Fita const& Mtu::getFita (int fitaId) {
    return this->fitas[fitaId];
}
std::string const& Mtu::getMaquina (void) {
    return this->M;
}
std::string const& Mtu::getWord (void) {
    return this->w;
}
std::vector<std::string> const& Mtu::getListaEstadosFinais (void) {
    return this->estadosFinais;
}
std::vector<std::string> const& Mtu::getListaTransicoes (void) {
    return this->transicoes;
}
/* End of Getters */

/* Problem Solver */
std::string Mtu::wEstadoFinal (void) {
    int op = 0;
    while (this->fitas[1].getPos() < 1000 && this->fitas[2].getPos() < 1000 && op < 1000) {

        std::string wordPos = this->fitas[1].getStrPos();
        std::string statePos = this->fitas[2].getStrPos();
        std::string transPref = statePos + "0" + wordPos + "0";

        std::string trans = this->buscaTransicao(transPref);

        if (!trans.empty()) {
            std::vector<std::string> partTrans = particionaStr(trans, "0", trans.size());

            this->fitas[1].write(partTrans[2]);
            this->fitas[2].write(partTrans[3]);

            if (partTrans[4] == "1") {
                this->fitas[1].direita();
            } else {
                this->fitas[1].esquerda();
            }
        
            op++;
        } else {
            if (this->verificaEstadoFinal()) {
                return "A palavra pertence à linguagem.";
            } else {
                return "A palavra não pertence à linguagem.";
            }
        }
    }
    return "A palavra não pôde ser processada em menos que 1000 passos.";
}
/* End of Problem Solver */