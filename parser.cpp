#include "include/parser.h"
#include "include/ast.h"
#include "include/common.h"
#include "include/lexer.h"
#include <cstdlib>
#include <memory>
#include <utility>
#include <vector>

astptr parser::parse_factor() {
  token tok = consume();
  if (tok.type == token_type::BYTE) {
    return std::make_unique<Node>(tok);
  }
  if (tok.type == token_type::WORD) {
    return std::make_unique<Node>(tok);
  }
  if (tok.type == token_type::INT) {
    return std::make_unique<Node>(tok);
  }
  if (tok.type == token_type::LONG) {
    return std::make_unique<Node>(tok);
  } else if (tok.type == token_type::NULL_) {
    return std::make_unique<Node>(tok);
  }
  if (tok.type == token_type::FLOAT) {
    return std::make_unique<Node>(tok);
  }
  if (tok.type == token_type::DOUBLE) {
    return std::make_unique<Node>(tok);
  } else if (tok.type == token_type::TRUE) {
    return std::make_unique<Node>(tok);
  } else if (tok.type == token_type::FALSE) {
    return std::make_unique<Node>(tok);
  } else if (tok.type == token_type::STRING) {
    return std::make_unique<Node>(tok);
  } else if (tok.type == token_type::ID) {
    if (peek().type == L_BRACKET) {
      consume();
      std::vector<astptr> args_;

      while (peek().type != R_BRACKET) {
        args_.push_back(parse_expr());
        if (peek().type == COMA)
          consume();
      }
      consume(R_BRACKET);
      return std::make_unique<FuncCallNode>(tok, std::move(args_));
    }
    return std::make_unique<Node>(tok);
  } else if (tok.type == token_type::L_BRACKET) {
    astptr node = parse_expr();

    token close = consume(token_type::R_BRACKET);

    return node;

  } else {
    std::cerr << "Error in parsing factor -> " + std::to_string(tok.type) +
                     '\n';
    exit(EXIT_FAILURE);
  }
}

astptr parser::parse_unary() {
  token op = peek();
  if (op.type == token_type::PLUS || op.type == token_type::MINUS) {
    consume();
    astptr unary = parse_unary();
    return std::make_unique<UnaryNode>(std::move(unary), op.type);
  }
  return parse_factor();
}

astptr parser::parse_term() {
  astptr node = parse_unary();

  while (true) {
    token op = peek();
    if (op.type != token_type::STAR && op.type != token_type::SLASH)
      break;

    consume();
    astptr rhs = parse_unary();
    node =
        std::make_unique<BinaryNode>(std::move(node), std::move(rhs), op.type);
  }

  return node;
}

astptr parser::parse_expr() {
  astptr node = parse_term();

  while (true) {
    token op = peek();
    if (op.type != token_type::PLUS && op.type != token_type::MINUS)
      break;
    consume();
    astptr rhs = parse_term();
    node =
        std::make_unique<BinaryNode>(std::move(node), std::move(rhs), op.type);
  }

  return node;
}

astptr parser::parse_assignment() {
  token type = consume();
  if (type.type == ID) {
    if(peek().type == L_BRACKET) {
        indx--;
        return parse_factor();
    }
    consume(EQ);
    astptr value = parse_expr();
    consume(SEMI);
    return std::make_unique<AssignmentNode>(type, std::move(value));
  }
  if (type.type != BYTE_TYPE && type.type != WORD_TYPE &&
      type.type != INT_TYPE && type.type != LONG_TYPE &&
      type.type != FLOAT_TYPE && type.type != DOUBLE_TYPE &&
      type.type != STRING_TYPE && type.type != BOOL_TYPE &&
      type.type != UNSIGNED_8_TYPE && type.type != UNSIGNED_16_TYPE &&
      type.type != UNSIGNED_32_TYPE && type.type != UNSIGNED_64_TYPE) {
    std::cerr << "Error: expected one of next types to make variable: i8, u8, "
                 "i16, u16, i32, u32, i64, u64, f32, f64, bool, string\n";
    exit(1);
  }
  token id = consume(token_type::ID);
  if (peek().type == SEMI) {
    consume();
    return std::make_unique<AssignmentNodeExpr>(type.type, id, astptr{});
  }
  consume(token_type::EQ);
  astptr value = parse_expr();
  consume(SEMI);
  return std::make_unique<AssignmentNodeExpr>(type.type, id, std::move(value));
}

astptr parser::parse_statement() {
  token tok = peek();
  switch (tok.type) {
  /*
  case token_type::IF:
      return parse_if_statement();
  case token_type::WHILE:
      return parse_while_statement();
  case token_type::FOR:
      return parse_for_statement();
  case token_type::FUNC:
      return parse_func_statement();
  */
  case token_type::BYTE_TYPE:
  case token_type::WORD_TYPE:
  case token_type::INT_TYPE:
  case token_type::LONG_TYPE:
  case token_type::BOOL_TYPE:
  case token_type::FLOAT_TYPE:
  case token_type::DOUBLE_TYPE:
  case token_type::STRING_TYPE:
  case token_type::UNSIGNED_8_TYPE:
  case token_type::UNSIGNED_16_TYPE:
  case token_type::UNSIGNED_32_TYPE:
  case token_type::UNSIGNED_64_TYPE:
  case token_type::ID:
    return parse_assignment();
  default:
    return parse_expr();
  }
  return parse_expr();
}

std::vector<std::unique_ptr<ASTNode>> parser::parse() {
  std::vector<std::unique_ptr<ASTNode>> parsed;
  while (indx < src.size() && src[indx].type != token_type::EOF_) {
    parsed.push_back(std::move(parse_statement()));
  }
  return parsed;
}