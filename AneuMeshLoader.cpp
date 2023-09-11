#include "AneuMeshLoader.h"



void AneuMeshLoader::loadMesh(const std::string& fileName) {
    std::ifstream inf(fileName);
    if (!inf) {
        throw FileNotFoundException();
    }
    else {
        std::cout << "File " << fileName << " was opened successfully!" << std::endl;
    }

    int amount, dim;
    inf >> amount >> dim;
    nodes.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        Node tmp;
        inf >> tmp.coords[0] >> tmp.coords[1] >> tmp.coords[2];
        tmp.id = i;
        tmp.vertex = false;
        nodes.push_back(tmp);
    }

    inf >> amount >> dim;
    fes.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        FiniteElement tmp{};
        int nodeId;
        inf >> tmp.idM;
        for (int j = 0; j < dim; ++j) {
            inf >> nodeId;
            tmp.idLst.push_back(nodeId);
        }
        tmp.id = i;
        fes.push_back(std::move(tmp));
    }

    inf >> amount >> dim;
    bfes.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        FiniteElement tmp{};
        int nodeId;
        inf >> tmp.idM;
        for (int j = 0; j < dim; ++j) {
            inf >> nodeId;
            tmp.idLst.push_back(nodeId);
        }
        tmp.id = i;
        bfes.push_back(std::move(tmp));
    };

    std::cout << "Data was loaded successfully!" << std::endl;

    std::cout << "File was closed successfully!" << std::endl;
}
