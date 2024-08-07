#include <iostream>
#include <vector>
#include <stdexcept>
#include <filesystem>

#include "compiler.hpp"
#include "toml.hpp"

namespace fs = std::filesystem;

Builder::Builder() {
    try {
        allan = toml::parse_file("Allan.toml");
    } catch (const toml::parse_error& er) {
        std::cout << er << std::endl;
        abort();
    }

    name = allan["package"]["name"].value_or("ALLAN_THE_GOAT");
    cppverison = allan["package"]["cstd"].value_or(20);
    toml::array* libraries = allan["depen"]["libs"].as_array();

    if (libraries->is_value()) {
        for (const toml::node& lib : *libraries) {
            std::string push;
            push = lib.as_string()->get();
            libs.push_back(push);
        }
    }
}

void Builder::build() {
    std::string command = "clang++ src/*.cpp -Iincludes/ -Lbin/";

    std::cout << "Here?" << std::endl;

    if (name.find(' ') != std::string::npos) {
        std::cout << "name can not contain a space" << std::endl;
        abort();
    }

    command += " -o build/";
    command += name;
    #ifdef _WIN32 || _WIN64
    command += ".exe ";
    #endif
    //clang++ src/*.cpp -Iincludes/ -Lbin/ -o name.exe

    command += "-std=c++";
    command += std::to_string(cppverison);
    std::cout << command << std::endl;
    command += " "; //clang++ src/*.cpp -Iincludes/ -Lbin/ -o name.exe -cstd=c++20

    for (std::string& lib : libs) {
        command += lib;
        command += " ";
    }
    std::cout << command << std::endl;

    std::string remove_path = "build/";
    remove_path += name;
    #ifdef _WIN32 || _WIN64
    remove_path += ".exe";
    #endif
    fs::remove(remove_path);

    try {
        system(command.c_str());
    } catch (const std::exception& er) {
        std::cout << er.what() << "OK";
    }
}

void Builder::print() const {
    std::cout << name << std::endl
        << cppverison << std::endl
        << allan << std::endl;

    for (const std::string& lib: libs) {
        std::cout << lib << std::endl;
    }
}
