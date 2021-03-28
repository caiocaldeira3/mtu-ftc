#pragma once
#include<bits/stdc++.h>

class Fita{
private:
    /* Attributes */
    int pos = 0;
    std::string fita;
    /* End of Attributes */
public:
    /* Constructors */
    Fita(std::string st);
    /* End of Constructors */
    /* Getters */
    int getPos();
    std::vector<int> getFita();
    /* End of Getter */
};
