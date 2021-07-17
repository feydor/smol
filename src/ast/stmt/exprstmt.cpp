#include "stmt.h"
//#include <iostream>

namespace Ast {
	ExprStmt::ExprStmt(std::unique_ptr<Ast::Expr> expr)
        : expr_(std::move(expr)) {};

	// evaluate the expr and return
	void
	ExprStmt::exec()
	{
		expr_->eval(); // return of eval dies here
	}

	ExprStmt::~ExprStmt()
	{
		// delete expr_;
	}
}
