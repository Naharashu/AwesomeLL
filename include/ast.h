#pragma once
#include <memory>
#include <vector>
#include <string>
#include "lexer.h"

class ASTNode;

using astptr = std::unique_ptr<ASTNode>;

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class Node : public ASTNode {
	public:
	token tok;
	Node(const token t) : tok(t) {};
};



class BinaryNode : public ASTNode {
	public:
	token_type op;
	astptr left;
	astptr right;
	BinaryNode(astptr left_, astptr  right_, const token_type &op_) 
	            : left(std::move(left_)), right(std::move(right_)), op(op_) {};
};


class UnaryNode : public ASTNode {
	public:
	token_type sign;
	astptr left;
	UnaryNode(astptr left_, const token_type &sign_) : left(std::move(left_)), sign(sign_) {};
};
