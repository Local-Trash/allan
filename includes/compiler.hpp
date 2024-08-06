#pragma once

#include <vector>
#include <string>

#include "toml.hpp"

class Builder {
public:
    Builder();
    void build();
    void print() const;
private:
    int cppverison;
    std::vector<std::string> libs;
    std::string_view name;
    toml::table allan;
};