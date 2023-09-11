#include "AneuMeshLoader.h"
#include <algorithm>
#include <ranges>
#include "iostream"

void testMeshLoader(AneuMeshLoader* loader, const std::string& filepath) {
    loader->loadMesh(filepath);
    std::vector<int> nodes;
    std::vector<int> fes;
    std::vector<int> bfes;

    std::cout << "Result of getFEbyId(15, 48, 98) function:\n";
    fes = loader->getFEbyNodesId(15, 48, 98);
    for (int ind : fes) {
        std::cout << ind << " ";
    }
    fes.clear();

    std::cout << "\nResult of getFEbyEdge(15, 48) function:\n";
    fes = loader->getFEbyEdge(15, 48);
    for (int ind : fes) {
        std::cout << ind << " ";
    }
    fes.clear();

    std::cout << "\nResult of getNodesBySurfaceId(1) function:\n";
    nodes = loader->getNodesBySurfaceId(1);
    for (int ind : nodes) {
        std::cout << ind << " ";
    }
    nodes.clear();

    std::cout << "\nResult of getFEsByMaterialId(1) function:\n";
    fes = loader->getFEsByMaterialId(1);
    for (int ind : fes) {
        std::cout << ind << ' ';
    }
    fes.clear();

    std::cout << "\nResult of getBFEsBySurfaceId(1) function:\n";
    bfes = loader->getFEsBySurfaceId(1);
    for (int ind : bfes) {
        std::cout << ind << ' ';
    }
    bfes.clear();


    std::cout << "\n Angles (between 30 and 60): Done!\n";
    loader->Angles(30, 60, "text.txt");

}


int main(int argc, char* argv[]) {
    auto* loader = new AneuMeshLoader;
    std::string path = "cube.mesh";
    testMeshLoader(loader, path);
    delete loader;
    return 0;
}
