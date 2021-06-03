/* gen_ast - generates the class headers of expr.h */
#include <regex>
#include <fstream>
#include <iostream>
#include <vector>
#define NAME "generate_ast"

void define_ast(std::string const& outdir, std::string basename,
        std::vector<std::string> types);
void define_type(std::ofstream &out, std::string const& basename, 
        std::string const& classname, std::string const& fieldlist);
void tokenize(std::string const& str, char delim, std::vector<std::string> &res);

int main (int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "Usage: " << NAME << " <output dir>" << "\n";
        exit(64);
    }
    std::string outdir = argv[1];
    std::vector<std::string> types = {
        "Binary   : Expr left, Token op, Expr right",
        "Grouping : Expr expr",
        "Literal  : Placeholder val",
        "Unary    : Token op, Expr right"
    };
    define_ast(outdir, "Expr", types);
    return 0;
}

void define_ast(std::string const& outdir, std::string basename,
        std::vector<std::string> types)
{
    std::string bname(basename);
    std::transform(bname.begin(), bname.end(), bname.begin(),
            [](unsigned char c){ return std::tolower(c); });
    std::string pathname(outdir + "/" + bname + ".h");
    std::ofstream out(pathname, std::ofstream::out);
    out << "#ifndef EXPR_H\n" << "#define EXPR_H\n";
    out << "#include \"token.h\"\n#include <variant>\n";
    out << "class " + basename + " {}\n";

    // AST classes
    std::regex trim_ws("^ +| +$|( ) +");
    std::string name_delim(":");
    for (auto type : types) {
        std::string classname = type.substr(0, type.find(name_delim));
        classname = std::regex_replace(classname, trim_ws, "$1");
        std::string fields = type.substr(type.find(name_delim) + 1);
        fields = std::regex_replace(fields, trim_ws, "$1");
        define_type(out, basename, classname, fields);
    }
    out.close();
}

void define_type(std::ofstream &out, std::string const& basename, 
        std::string const& classname, std::string const& fieldlist)
{
    out << "class " + classname + " : " + basename + " {\n";
    
    // write fields
    std::vector<std::string> fields;
    tokenize(fieldlist, ',', fields);
    std::regex trim_ws("^ +| +$|( ) +");
    for (auto field : fields) {
        field = std::regex_replace(field, trim_ws, "$1");
        out << "    " + field + ";\n";
    }
    out << "\npublic:\n     " + classname + "(";

    // write constructor
    out << fieldlist + ")\n    : ";
    
    // remove commas
    std::string s(fieldlist.size(), '0');
    s.erase(std::remove_copy(fieldlist.begin(), fieldlist.end(), s.begin(), ','), s.end());

    // write initializer list
    std::vector<std::string> params;
    tokenize(s, ' ', params);
    for (size_t i = 0; i < params.size(); ++i) {
        size_t I = i+1;

        // have param, so remove trailing comma and write
        if (I % 2 == 0) {
            std::string param(params.at(i).substr(0, params.at(i).length()));
            i == (params.size() - 1) 
                ? out << param + "(" + param + ") {};\n\n"
                : out << param + "(" + param + "), ";
        }
    }
    out << "};\n\n";
}

/**
 * splits a string by a delimiter into a passed in vector
 */
void tokenize(std::string const& str, char delim, std::vector<std::string> &res) 
{
    size_t start, end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) 
            != std::string::npos) {
        end = str.find(delim, start);
        res.push_back(str.substr(start, end - start));
    }
}
