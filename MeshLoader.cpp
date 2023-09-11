#include <unordered_set>
#include "MeshLoader.h"
#include "Hash.h"
#include <cmath>
#include <fstream>
#include <ranges>
#include <iomanip>
#include <algorithm>
#include <iomanip>



const std::vector<Node>& MeshLoader::getNodes() {
    return nodes;
}

const std::vector<FiniteElement>& MeshLoader::getFEs() {
    return fes;
}

const std::vector<FiniteElement>& MeshLoader::getBFEs() {
    return bfes;
}

std::vector<int> MeshLoader::getFEbyNodesId(int n1, int n2, int n3) {
    std::vector<int> res;
    std::for_each(fes.begin(), fes.end(), [&n1, &n2, &n3, &res](const FiniteElement& fe) {
        if ((std::find(fe.idLst.begin(), fe.idLst.end(), n1) != fe.idLst.end()) &&
        (std::find(fe.idLst.begin(), fe.idLst.end(), n2) != fe.idLst.end()) &&
            (std::find(fe.idLst.begin(), fe.idLst.end(), n3) != fe.idLst.end())) {
            res.push_back(fe.id);
        }
        });
    return res;
}

std::vector<int> MeshLoader::getFEbyEdge(int n1, int n2) {
    std::vector<int> res;
    std::for_each(fes.begin(), fes.end(), [&n1, &n2, &res](const FiniteElement& fe) {
        if ((std::find(fe.idLst.begin(), fe.idLst.end(), n1) != fe.idLst.end()) &&
        (std::find(fe.idLst.begin(), fe.idLst.end(), n2) != fe.idLst.end())) {
            res.push_back(fe.id);
        }
        });
    return res;
}

std::vector<int> MeshLoader::getNodesBySurfaceId(int id) {
    std::set<int> res;
    auto cur = bfes.begin();

    while (cur != bfes.end()) {
        cur = std::find_if(cur, bfes.end(), [id](const FiniteElement& bfe) {
            return bfe.idM == id;
            });
        if (cur != bfes.end()) {
            for (const auto& elem : cur->idLst) { 
                res.insert(elem);                 
            ++cur;
        }
    }
    return std::vector<int>(res.begin(), res.end());
}

std::vector<int> MeshLoader::getFEsByMaterialId(int id) {
    std::vector<int> res;
    std::for_each(fes.begin(), fes.end(), [&id, &res](const FiniteElement& fe) {
        if (fe.idM == id) {
            res.push_back(fe.id);
        }
        });
    return res;
}

std::vector<int> MeshLoader::getFEsBySurfaceId(int id) {
    std::vector<int> res;
    std::for_each(bfes.begin(), bfes.end(), [&id, &res](const FiniteElement& bfe) {
        if (bfe.idM == id) {
            res.push_back(bfe.id);
        }
        });
    return res;
}

void MeshLoader::printNode(const Node& node) {
    std::cout << node;
}

void MeshLoader::printFE(const FiniteElement& fe) {
    std::cout << fe;
}

void MeshLoader::insertNodeMid() {
    std::unordered_set<Edge, hash> edges;
    for (auto& elem : fes) {
        std::vector<int> feNodesId = elem.idLst;
        for (int first = 0; first < 4; ++first) {
            for (auto sec = first + 1; sec < 4; ++sec) {
                Edge curEdge(feNodesId[first], feNodesId[sec]);
                if (edges.insert(curEdge).second) {
                    Node newNode = getMidNode(curEdge);
                    curEdge.updMid(newNode.id);
                    nodes.push_back(newNode);
                    elem.idLst.push_back(newNode.id);
                }
                else {
                    elem.idLst.push_back(curEdge.midNode);
                }
            }
        }
    }
    for (auto& el : bfes) {
        std::vector<int> bfeNodesId = el.idLst;
        for (auto first = 0; first < 3; ++first) {
            for (auto sec = first + 1; sec < 3; ++sec) {
                auto curEdgeIter = edges.find({ bfeNodesId[first], bfeNodesId[sec] });
                if (curEdgeIter == edges.end()) {
                    curEdgeIter = edges.find({ bfeNodesId[sec], bfeNodesId[first] });
                }
                el.idLst.push_back(curEdgeIter->midNode);
            }
        }
    }
}


std::array<double, 3> MeshLoader::getMidEdge(const Edge& edge) {
    double midX = ((nodes.at(edge.edgeNodes.first - 1).coords.at(0)) +
        (nodes.at(edge.edgeNodes.second - 1).coords.at(0))) / 2;
    double midY = ((nodes.at(edge.edgeNodes.first - 1).coords.at(1)) +
        (nodes.at(edge.edgeNodes.second - 1).coords.at(1))) / 2;
    double midZ = ((nodes.at(edge.edgeNodes.first - 1).coords.at(2)) +
        (nodes.at(edge.edgeNodes.second - 1).coords.at(2))) / 2;
    return { midX, midY, midZ };
}

Node MeshLoader::getMidNode(const Edge& edge) {
    Node newNode(nodes.size() + 1, getMidEdge(edge), false);
    return newNode;
}

std::array<double, 3> MeshLoader::getNodeCoords(int id) {
    return nodes.at(id).coords;
}

std::vector<std::set<int>> MeshLoader::createNeighborsVector() {
    std::vector<std::set<int>> neighbors(nodes.size() + 1);
    for (const auto& elem : bfes) {
        for (auto nodeId : elem.idLst)
            for (auto anthNodeId : elem.idLst)
                if (nodeId != anthNodeId)
                    neighbors[nodeId].insert(anthNodeId);
    }

    return neighbors;
}



namespace std {
    ostream& operator<<(ostream& out, const array<double, 3>& ar) {
        for (const double& coord : ar)
            out << std::left << std::setw(10) << coord << " ";
        return out;
    }
}




void MeshLoader::Angles(int ang1, int ang2, const std::string& fname) {
    std::ofstream out(fname);
    auto check = [&](const auto& elem) {
        double a = std::sqrt(std::pow(nodes[elem.idLst[0] - 1].coords[0] - nodes[elem.idLst[1] - 1].coords[0], 2) +
            std::pow(nodes[elem.idLst[0] - 1].coords[1] - nodes[elem.idLst[1] - 1].coords[1], 2) +
            std::pow(nodes[elem.idLst[0] - 1].coords[2] - nodes[elem.idLst[1] - 1].coords[2], 2));
        double b = std::sqrt(std::pow(nodes[elem.idLst[0] - 1].coords[0] - nodes[elem.idLst[2] - 1].coords[0], 2) +
            std::pow(nodes[elem.idLst[0] - 1].coords[1] - nodes[elem.idLst[2] - 1].coords[1], 2) +
            std::pow(nodes[elem.idLst[0] - 1].coords[2] - nodes[elem.idLst[2] - 1].coords[2], 2));
        double c = std::sqrt(std::pow(nodes[elem.idLst[2] - 1].coords[0] - nodes[elem.idLst[1] - 1].coords[0], 2) +
            std::pow(nodes[elem.idLst[2] - 1].coords[1] - nodes[elem.idLst[1] - 1].coords[1], 2) +
            std::pow(nodes[elem.idLst[2] - 1].coords[2] - nodes[elem.idLst[1] - 1].coords[2], 2));
        std::vector<double> angles(3);
        angles[0] = (a * a + b * b - c * c) / (2 * a * b);
        angles[1] = (b * b + c * c - a * a) / (2 * b * c);
        angles[2] = (a * a + c * c - b * b) / (2 * a * c);
        double min_angle = std::ranges::max(angles);
        return (std::cos((3.141592 / 180) * ang2) <= min_angle) && (std::cos((3.141592 / 180) * ang1) >= min_angle);
    };
    auto result = bfes | std::ranges::views::filter(check) | std::ranges::views::transform(
        [&](auto& n) {
            double a = (nodes[n.idLst[0] - 1].coords[0] + nodes[n.idLst[1] - 1].coords[0] + nodes[n.idLst[2] - 1].coords[0]) / 3;
    double b = (nodes[n.idLst[0] - 1].coords[1] + nodes[n.idLst[1] - 1].coords[1] + nodes[n.idLst[2] - 1].coords[1]) / 3;
    double c = (nodes[n.idLst[0] - 1].coords[2] + nodes[n.idLst[1] - 1].coords[2] + nodes[n.idLst[2] - 1].coords[2]) / 3;
    return std::array<double, 3> {a, b, c};
        });
    std::ranges::copy(result, std::ostream_iterator<std::array<double, 3>>(out, "\n"));
    out.close();
}

