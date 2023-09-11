#ifndef MESH_LOADER_ANEUMESHLOADER_H
#define MESH_LOADER_ANEUMESHLOADER_H

#include "MeshLoader.h"
#include "Exception.h"
#include <fstream>
#include "iostream"
#include "algorithm"
#include "string"


class AneuMeshLoader : public MeshLoader {
public:
    void loadMesh(const std::string&) override;
};
#endif
