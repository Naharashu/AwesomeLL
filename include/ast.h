#pragma once
#include <memory>
#include <vector>
#include <string>

class ASTNode {
public:
    virtual ~ASTNode() = default;

    virtual void print(int indent = 0) const = 0;
};