#ifndef MESH_LOADER_MESHLOADER_H
#define MESH_LOADER_MESHLOADER_H

#include "Structures.h"
#include <set>
#include <algorithm>
#include <ranges>

class MeshLoader {
protected:
    std::vector<Node> nodes;
    std::vector<FiniteElement> fes;
    std::vector<FiniteElement> bfes;
public:
    virtual void loadMesh(const std::string&) = 0;
    virtual ~MeshLoader() = default;

    const std::vector<Node>& getNodes();
    const std::vector<FiniteElement>& getFEs();
    const std::vector<FiniteElement>& getBFEs();

    std::vector<int> getFEbyNodesId(int, int, int);
    std::vector<int> getFEbyEdge(int, int);
    std::vector<int> getNodesBySurfaceId(int id);
    std::vector<int> getFEsBySurfaceId(int);
    std::vector<int> getFEsByMaterialId(int);
    void Angles(int ang1, int ang2, const std::string& fname);


    void insertNodeMid();

    static void printNode(const Node&);
    static void printFE(const FiniteElement&);

    std::vector<std::set<int>> createNeighborsVector();
private:
    Node getMidNode(const Edge&);
    std::array<double, Node::dim> getMidEdge(const Edge&);
    std::array<double, Node::dim> getNodeCoords(int);
};





#endif //MESH_LOADER_MESHLOADER_H
