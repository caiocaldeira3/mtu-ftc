#include<bits/stdc++.h>
#include "Mtu.h"

int main(int argc, char **argv){
    
    std::string Mw;
    if (argc >= 2) {
        std::string fileName = argv[1];
        fileName = "tests/" + fileName;

        std::ifstream inFile(fileName);

        inFile >> Mw;

        Mtu mtu(Mw);

        std::string fileName = argv[1];
        fileName = "outputs/" + fileName;

        std::ofstream outFile(fileName);

        outFile << mtu.wEstadoFinal() << std::endl;
    } else {
        while(std::cin >> Mw) {
            Mtu mtu(Mw);
            std::cout << mtu.wEstadoFinal() << std::endl;
        }
    }
    
    return 0;
}
