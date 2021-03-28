#pragma once
#include<bits/stdc++.h>

class Fita{
private:
    /* Attributes */
    int pos = 0;
    std::vector<char> fita;
    /* End of Attributes */
public:
    /* Constructors */
    Fita(std::string _fita);
    /* End of Constructors */
    /* Getters */
    int getPos();
    std::vector<char> const& getFita();
    /* End of Getters */
    /* Setters */
    int direita();
    int esquerda();
    /* End of Setters */
};
