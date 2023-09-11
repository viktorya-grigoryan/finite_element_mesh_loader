#ifndef MESH_LOADER_STRUCTURES_H
#define MESH_LOADER_STRUCTURES_H

#include <iostream>
#include <vector>
#include <array>

struct Node {
    int id{};
    static constexpr int dim = 3;
    std::array<double, dim> coords{};
    bool vertex{};

    Node() = default;
    Node(int, const std::array<double, dim>&, bool);

    friend std::ostream& operator<<(std::ostream&, const Node&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<Node>&);

    bool operator<(const Node&) const;
    bool operator==(const Node&) const;
};

struct FiniteElement {
    int id;
    int idM;
    std::vector<int> idLst;

    friend std::ostream& operator<<(std::ostream&, const FiniteElement&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<FiniteElement>&);
};

struct Edge {
    std::pair<int, int> edgeNodes;
    int midNode = -1;
    Edge() = default;
    Edge(int, int);
    void updMid(int);
    bool operator==(const Edge&) const;
    friend std::istream& operator>>(std::istream&, Edge&);
    friend std::ostream& operator<<(std::ostream&, Edge&);
};



#endif //MESH_LOADER_STRUCTURES_H
