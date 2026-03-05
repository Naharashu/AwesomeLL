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
	virtual void print() const = 0;
};

class Node : public ASTNode {
	public:
	token tok;
	Node(const token t) : tok(t) {};
	void print() const override {
		std::cout << tok.type << '\n';
	}
};



class BinaryNode : public ASTNode {
	public:
	astptr left;
	astptr right;
	token_type op;
	BinaryNode(astptr left_, astptr  right_, const token_type &op_) 
	            : left(std::move(left_)), right(std::move(right_)), op(op_) {};
	void print() const override {
		left->print();
		std::cout << op << '\n';
		right->print();
	}
};


class UnaryNode : public ASTNode {
	public:
	astptr left;
	token_type sign;
	UnaryNode(astptr left_, const token_type &sign_) : left(std::move(left_)), sign(sign_) {};
	void print() const override {
		std::cout << sign << '\n';
		left->print();
	}
};

class AssignmentNode : public ASTNode {
	public:
	token id;
	token_value val;
	AssignmentNode(const token &id_, const token_value &val_) : id(id_), val(val_) {};

	void print() const override {
		std::cout << id.type << '\n';
	}
};