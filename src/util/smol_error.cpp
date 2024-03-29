#include "smol_error.h"
#include "smol.h"
#include <fstream>
#include <string>
#include <iostream>

void
SmolParserError::print() const
{
	print_error_message_and_found(this->found);
	print_error_line_number(this->line);
	print_line_from_file(this->line - 1);
	print_line_from_file_bold(this->line);
	print_line_from_file(this->line + 1);
	print_abort_message();
}

void
SmolLexerError::print() const
{
	print_error_message_and_found(this->found);
	print_error_line_number(this->line);
	print_line_from_file(this->line - 1);
	print_line_from_file_bold(this->line);
	print_line_from_file(this->line + 1);
}

void
SmolCompilerError::print() const
{
	print_error_message_and_found(this->found);
}

void
SmolError::print_error_message() const
{
	std::cout << err << "error" << resetc << ": " << bold << this->message << resetf << "\n";
}

void
SmolError::print_error_line_number(int line) const
{
	std::cout << secondary << " -->" << resetc << SMOL::fname + ":" + std::to_string(line) + "\n";
}

void
SmolError::print_line_from_file(int line) const
{
	std::cout << secondary << std::to_string(line) << " |" << resetc << get_file_line(line) << "\n";
}

void
SmolError::print_line_from_file_bold(int line) const
{
	std::cout << secondary << std::to_string(line) << " |" << resetc << bold << get_file_line(line) << resetf << "\n";
}

void
SmolError::print_abort_message() const
{
	std::cout << err << "error" << resetc << ": " << bold << "aborting due to previous errors.\n" << resetf;
}

void
SmolError::print_error_message_and_found(const std::string& found) const
{
	std::cout << err << "error" << resetc << ": " << bold << this->message << resetf << " ";
	std::cout << bold << add_quotemarks(found) << resetf << "\n";
}

/**
 * @brief gets the nth line of the current file name
 * 
 * @param line 
 * @return std::string
 */
std::string
SmolError::get_file_line(int line) const
{
	std::string out;
	std::fstream file(SMOL::fname);
	file.seekg(std::ios::beg);
	for (int i = 0; i < line; ++i)
		std::getline(file, out);
	return out;
}

/**
 * @brief wraps the argument in quotemarks and returns it
 * 
 * @param s 
 * @return std::string 
 */
std::string
SmolError::add_quotemarks(const std::string& s) const
{
	return "'" + s + "'";
}
