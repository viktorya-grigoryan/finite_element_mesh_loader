#ifndef MESH_LOADER_EXCEPTIONS_H
#define MESH_LOADER_EXCEPTIONS_H

#include <exception>
#include <string>

class BadFormatException : public std::exception {
    std::string error;
public:
    BadFormatException() {
        error.assign("Unknown or unsupported file format!");
    }

    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

class FileNotFoundException : public std::exception {
    std::string error;
public:
    FileNotFoundException() {
        error.assign("Cannot open file or it does not exist!");
    }

    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

#endif //MESH_LOADER_EXCEPTIONS_H
