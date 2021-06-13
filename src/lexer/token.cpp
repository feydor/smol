#include "token.h"

Token::Token(Token_t type, std::string lexeme, int line)
    : type(type), lexeme(std::move(lexeme)), line(line)
{
    this->literal = 0.0;
}

Token::Token(Token_t type, std::string lexeme, int line,
    std::variant<double, std::string> literal)
    : type(type), lexeme(std::move(lexeme)), line(line), 
    literal(std::move(literal))
{}

Token::Token() {}

Token_t
Token::get_type() const
{
    return this->type;
}

std::string
Token::get_lexeme() const
{
    return this->lexeme;
}

int
Token::get_line() const
{
    return this->line;
}

double
Token::get_literal_num() const
{
    return std::get<double>(this->literal);
}

std::string
Token::get_literal_str() const
{
    return std::get<std::string>(this->literal);
}

std::string
Token::to_string() const
{
    return this->lexeme;
}

std::string
Token::type_to_string(Token_t type)
{
    switch (type) {
        case LEFT_PAREN: return "(";
        case RIGHT_PAREN: return ")";
        case LEFT_BRACE: return "{";
        case RIGHT_BRACE: return "}";
        case LEFT_BRACKET: return "[";
        case RIGHT_BRACKET: return "]";
        case COMMA: return ",";
        case DOT: return ".";
        case MINUS: return "-";
        case PLUS: return "+";
        case SEMICOLON: return ";";
        case SLASH: return "/"; 
        case STAR: return "*";
        case BANG: return "!";
        case BANG_EQUAL: return "!=";
        case EQUAL: return "=";
        case EQUAL_EQUAL: return "==";
        case GREATER: return ">";
        case GREATER_EQUAL: return ">=";
        case LESS: return "<";
        case LESS_EQUAL: return "<=";
        case IDENTIFIER: return "IDENTIFIER";
        case STRING: return "STRING";
        case NUMBER: return "NUMBER";
        case AND: return "AND";
        case ELSE: return "ELSE";
        case FALSE: return "FALSE";
        case FN: return "FN";
        case FOR: return "FOR";
        case IF: return "IF";
        case NIL: return "NIL";
        case OR: return "OR";
        case SAY: return "SAY";
        case RETURN: return "RET";
        case TRUE: return "TRUE";
        case LET: return "LET";
        case WHILE: return "WHILE";
        case _EOF: return "EOF";
        case EOL: return "EOL";
        default: return "Not yet identifed.";
    }
}
