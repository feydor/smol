#ifndef EXPR_H
#define EXPR_H
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "llvm-includes.h"
#include "smol_error.h"

class SMOL;

// ExprAST - Base class for all expression nodes
class ExprAST {
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value *code_gen(SMOL &smol) = 0;
        static SmolCompilerError throwable_error(const std::string& message,
                                                 const std::string& found);
};

// NumberAST - Expression class for all numeric literals such as "1.9"
class NumberExprAST : public ExprAST {
    public:
        explicit NumberExprAST(double val) : val(val) {}
        virtual llvm::Value *code_gen(SMOL &smol) override;
    private:
        double val;
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
    public:
        explicit VariableExprAST(const std::string &name) : name(name) {}
        virtual llvm::Value *code_gen(SMOL &smol) override;
    private: 
        std::string name;
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
    public:
        BinaryExprAST(const std::string &op, std::unique_ptr<ExprAST> LHS,
                                             std::unique_ptr<ExprAST> RHS)
            : op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
        virtual llvm::Value *code_gen(SMOL &smol) override;
    private:
        std::string op;
        std::unique_ptr<ExprAST> LHS, RHS;
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
    public:
        CallExprAST(const std::string &callee,
                    std::vector<std::unique_ptr<ExprAST>> &&args)
            : callee(callee), args(std::move(args)) {}
        virtual llvm::Value *code_gen(SMOL &smol) override;
    private:
        std::string callee;
        std::vector<std::unique_ptr<ExprAST>> args;
};

// IfExprAST - Expression class for if/then/else
class IfExprAST : public ExprAST {
    public:
        IfExprAST(std::unique_ptr<ExprAST> conditional,
                  std::unique_ptr<ExprAST> then,
                  std::unique_ptr<ExprAST> else_)
        : conditional(std::move(conditional)), then(std::move(then)), else_(std::move(else_)) {}
        
        virtual llvm::Value *code_gen(SMOL &smol) override;
    private:
        std::unique_ptr<ExprAST> conditional;
        std::unique_ptr<ExprAST> then;
        std::unique_ptr<ExprAST> else_;
};

#endif