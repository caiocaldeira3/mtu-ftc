#include "Fita.h"

/* Constructors */
Fita::Fita(std::string _fita){
    for (char c : _fita) 
        this->fita.emplace_back(c);
}
/* End of Constructors */

/* Getters */
int Fita::getPos(){
    return this->pos;
}
std::vector<char> const& Fita::getFita(){
    return this->fita;
}
/* End of Getters */

/* Setters */
int Fita::direita() {
   return this->pos++; 
}
int Fita::esquerda() {
    return this->pos--;
}
/* End of Setters */