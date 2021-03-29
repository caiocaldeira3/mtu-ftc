#pragma once
#include<bits/stdc++.h>

/* Auxiliary Functions */
std::vector<std::string> particionaStr (std::string st, std::string prt, int endPos);
/* End of Auxiliary Functions */

class Fita{
private:
    /* Attributes */
    size_t pos = 0;
    std::vector<std::string> fita;
    /* End of Attributes */
public:
    /* Constructors */
    Fita (void) {};
    Fita (std::string const& _fita);
    /* End of Constructors */
    /* Getters */
    int getPos (void);
    std::string getStrPos (void);
    std::vector<std::string> const& getFita (void);
    /* End of Getters */
    /* Setters */
    void write (std::string const& stW);
    int direita (void);
    int esquerda (void);
    /* End of Setters */
    /* Auxiliary Functions */
    void debug (void);
    /* End of Auxiliary Functions */
};
