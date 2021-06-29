#include "expr.h"
#include "fntable.h"

namespace Ast {

    Obj::Object*
    FnExpr::eval()
    {
        if (!FnTable::exists(name_))
            throw std::runtime_error("Function " + name_ + " is not a defined function.");

        std::vector<Obj::Object*> args = {};
        for (const auto& arg : args_)
            args.push_back(arg->eval());

        return FnTable::get_fn(name_)->invoke(args);
    }

    void
    FnExpr::add_arg(Expr* arg)
    {
        args_.push_back(arg);
    }

    std::string
    FnExpr::to_str() const
    {
        std::string res(name_ + " (");
        for (const auto& arg : args_)
            res += arg->to_str() + ", ";
        return res.substr(0, res.size() - 2) + ")";
    }

    FnExpr::~FnExpr()
    {
        for (auto& arg : args_)
            delete arg;
    }
}
