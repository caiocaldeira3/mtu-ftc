#include "Fita.h"

/* Auxiliary Functions */
std::vector<std::string> particionaStr (std::string st, std::string prt, int endPos) {
    std::vector<std::string> vret;
    int stPos = 0;
    int atPos = st.find(prt, stPos);
    while (atPos != -1) {
        vret.emplace_back(st.substr(stPos, atPos - stPos));
        stPos = atPos + prt.size();
        atPos = st.find(prt, stPos);
    }
    vret.emplace_back(st.substr(stPos, endPos - stPos));
    return vret;
}
/* End of Auxiliary Functions */


/* Constructors */
Fita::Fita (std::string const& _fita){
    this->fita = particionaStr(_fita, "0", _fita.size());
}
/* End of Constructors */

/* Getters */
int Fita::getPos (void) {
    return this->pos;
}
std::string Fita::getStrPos (void) {
    return this->fita[this->pos];
}
std::vector<std::string> const& Fita::getFita (void) {
    return this->fita;
}
/* End of Getters */

/* Setters */
void Fita::write (std::string const& stW) {
    this->fita[this->pos] = stW;
}
int Fita::direita (void) {
    return this->pos++; 
}
int Fita::esquerda (void) {
    return this->pos--;
}
/* End of Setters */

/* Auxiliary Functions */
void Fita::debug (void) {
    std::cout << "O cabeçote da fita está na posição " << this->pos << std::endl;
    for (size_t i = 0; i < this->fita.size(); i++) {
        std::cout << "Fita na posição " << i + 1 << ": " << this->fita[i] << std::endl;
    }
    std::cout << std::endl;
}
/* End of Auxiliary Functions */