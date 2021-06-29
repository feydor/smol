#include "object.h"
#include <cmath>  // for std::fmod

namespace Obj {
	
	// Binary operators
	Object*
	Object::operator+(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM) {
			if (other.type() == Object_t::NUM)
				return new Obj::Number(((Number*)a)->num() + ((Number*)b)->num());
			else if (other.type() == Object_t::STR)
				return new String(((Number*)a)->to_str() + ((String*)b)->str());
		}
		else if (type() == Object_t::STR) {
			if (other.type() == Object_t::STR)
				return new String(((String*)a)->str() + ((String*)b)->str());
			else if (other.type() == Object_t::NUM)
				return new String(((String*)a)->str() + ((Number*)b)->to_str());
		}
		else if (type() == Object_t::BOOL) {
			if (other.type() == Object_t::BOOL)
				return new Bool(((Bool*)a)->bol() && ((Bool*)b)->bol());
		}
		throw type_error("Cannot add", type(), other.type());
	}

	Object*
	Object::operator-(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM && other.type() == Object_t::NUM)
			return new Number(((Number*)a)->num() - ((Number*)b)->num());
		throw type_error("Cannot subtract", type(), other.type());
	}

	Object*
	Object::operator*(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM && other.type() == Object_t::NUM)
			return new Number(((Number*)a)->num() * ((Number*)b)->num());
		throw type_error("Cannot multiply", type(), other.type());
	}

	Object*
	Object::operator/(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM && other.type() == Object_t::NUM)
			return new Number(((Number*)a)->num() / ((Number*)b)->num());
		throw type_error("Cannot divide", type(), other.type());
	}

	Object*
	Object::operator%(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM && other.type() == Object_t::NUM)
			return new Number(std::fmod(((Number*)a)->num(), ((Number*)b)->num()));
		throw type_error("Cannot mod", type(), other.type());
	}

	// Conditional operators
	Object*
	Object::operator==(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM) {
			if (other.type() == Object_t::NUM)
				return new Bool(((Number*)a)->num() == ((Number*)b)->num());
			else if (other.type() == Object_t::BOOL)
				return new Bool(((Number*)a)->is_truthy() == ((Bool*)b)->bol());
		} else if (type() == Object_t::BOOL) {
			if (other.type() == Object_t::BOOL)
				return new Bool(((Bool*)a)->bol() == ((Bool*)b)->bol());
			else if (other.type() == Object_t::NUM)
				return new Bool(((Bool*)a)->bol() == ((Number*)b)->is_truthy());
		} else if (type() == Object_t::STR) {
			if (other.type() == Object_t::STR)
				return new Bool(((String*)a)->compare((String*)b));
		} else if (type() == Object_t::ARR) {
			if (other.type() == Object_t::ARR)
				return new Bool(((Array*)a)->compare((Array*)b));
		}
		throw type_error("Cannot compare(==)", type(), other.type());
	}

	Object*
	Object::operator!=(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM) {
			if (other.type() == Object_t::NUM)
				return new Bool(((Number*)a)->num() != ((Number*)b)->num());
			else if (other.type() == Object_t::BOOL)
				return new Bool(((Number*)a)->is_truthy() != ((Bool*)b)->bol());
		} else if (type() == Object_t::BOOL) {
			if (other.type() == Object_t::BOOL)
				return new Bool(((Bool*)a)->bol() != ((Bool*)b)->bol());
			else if (other.type() == Object_t::NUM)
				return new Bool(((Bool*)a)->bol() != ((Number*)b)->is_truthy());
		} else if (type() == Object_t::STR) {
			if (other.type() == Object_t::STR)
				return new Bool(((String*)a)->compare((String*)b));
		} else if (type() == Object_t::ARR) {
			if (other.type() == Object_t::ARR)
				return new Bool(((Array*)a)->compare((Array*)b));
		}

		throw type_error("Cannot compare(!=)", type(), other.type());
	}

	Object*
	Object::operator&&(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::BOOL && other.type() == Object_t::BOOL)
			return new Bool( ((Bool*)a)->bol() && ((Bool*)b)->bol() );
		throw type_error("Cannot do boolean operation(&&)", type(), other.type());
	}

	Object*
	Object::operator||(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::BOOL && other.type() == Object_t::BOOL)
			return new Bool( ((Bool*)a)->bol() || ((Bool*)b)->bol() );
		throw type_error("Cannot do boolean operation(||)", type(), other.type());
	}

	Object*
	Object::operator<(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM && other.type() == Object_t::NUM)
			return new Bool( ((Number*)a)->num() < ((Number*)b)->num() );
		throw type_error("Cannot compare(<)", type(), other.type());
	}

	// TODO: make this operator work with strings and arrays... maybe
	Object*
	Object::operator<=(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM && other.type() == Object_t::NUM)
			return new Bool( ((Number*)a)->num() <= ((Number*)b)->num() );
		throw type_error("Cannot compare(<=)", type(), other.type());
	}

	Object*
	Object::operator>(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM && other.type() == Object_t::NUM)
			return new Bool( ((Number*)a)->num() > ((Number*)b)->num() );
		throw type_error("Cannot compare(>)", type(), other.type());
	}

	Object*
	Object::operator>=(const Object& other) const
	{
		const Object* a = this;
		const Object* b = &other;
		if (type() == Object_t::NUM && other.type() == Object_t::NUM)
			return new Bool( ((Number*)a)->num() >= ((Number*)b)->num() );
		throw type_error("Cannot compare(>=)", type(), other.type());
	}

	// Unary operators
	Object*
	Object::operator-() const
	{
		if (type() == Object_t::NUM)
			return new Number( -((Number*)this)->num() );
		throw type_error("Cannot make negative", type());
	}

	Object*
	Object::operator!() const
	{
		return new Bool(!this->is_truthy());
	}

	// utility functions
	std::string
	Object::type_str() const
	{
		return Object::type_str(type());
	}

	std::string
	Object::type_str(Object_t type)
	{
		switch (type) {
			case Object_t::NUM: return "Number";
			case Object_t::STR: return "String";
			case Object_t::BOOL: return "Bool";
			case Object_t::ARR: return "Array";
			case Object_t::HASH: return "Hash";
			case Object_t::NIL: return "Nil";
		}
	}

	// binary error
	std::runtime_error
	Object::type_error(const std::string& msg, Object_t t1, Object_t t2) const
	{
		return std::runtime_error("error: " + msg + " '" + Object::type_str(t1) +
			"'' and '" + Object::type_str(t2) + "'.");
	}

	// unary error
	std::runtime_error
	Object::type_error(const std::string& msg, Object_t t1) const
	{
		return std::runtime_error("error: " + msg + " '" +
			Object::type_str(t1) + "'.");
	}

}