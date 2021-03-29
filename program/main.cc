#include<bits/stdc++.h>
#include "Mtu.h"

int main(int argc, char **argv){
    
    std::string Mw;
    if (argc >= 2) {
        std::string inName = argv[1];
        inName = "tests/" + inName;

        std::ifstream inFile(inName);

        inFile >> Mw;

        Mtu mtu(Mw);

        std::string outName = argv[1];
        outName = "outputs/" + outName;

        std::ofstream outFile(outName);

        outFile << mtu.wEstadoFinal() << std::endl;
    } else {
        while(std::cin >> Mw) {
            Mtu mtu(Mw);
            std::cout << mtu.wEstadoFinal() << std::endl;
        }
    }

    return 0;
}
