#pragma once
#include <memory>
#include <vector>
#include <string>
#include "lexer.h"

class ASTNode;

typedef enum class ast_type {
	JUSTNODE,
	BINARY,
	DEFINEVAR,
	ASSIGN,
	UNARY,
} ast_type;

using astptr = std::unique_ptr<ASTNode>;

class ASTNode {
public:
	ast_type kind;
    virtual ~ASTNode() = default;
	virtual void print() const = 0;
};

class Node : public ASTNode {
	public:
	token tok;
	Node(const token t) : tok(t) {
		kind = ast_type::JUSTNODE;
	};
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
	            : left(std::move(left_)), right(std::move(right_)), op(op_) {
					kind = ast_type::BINARY;
				};
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
	UnaryNode(astptr left_, const token_type &sign_) : left(std::move(left_)), sign(sign_) {
		kind = ast_type::UNARY;
	};
	void print() const override {
		std::cout << sign << '\n';
		left->print();
	}
};

class AssignmentNode : public ASTNode {
	public:
	token id;
	astptr val;
	AssignmentNode(const token &id_, astptr val_) : id(id_), val(std::move(val_)) {
		kind = ast_type::DEFINEVAR;
	};

	void print() const override {
		std::cout << id.type << '\n';
	}
};

class AssignmentNodeExpr : public ASTNode {
	public:
	token_type type_;
	token id;
	astptr val;
	AssignmentNodeExpr(const token_type &t_, const token &id_, astptr val_) : type_(t_), id(id_), val(std::move(val_)) {
		kind = ast_type::DEFINEVAR;
	};

	void print() const override {
		std::cout << id.type << '\n';
	}
};
