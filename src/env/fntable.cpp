#include "fntable.h"
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<FFInterface>> FnTable::fn_table = {};

void
FnTable::set_fn(std::shared_ptr<FFInterface> fn)
{
    fn_table[fn->name()] = fn;
}

bool
FnTable::exists(const std::string& name)
{
    return fn_table.find(name) != fn_table.end();
}

std::shared_ptr<FFInterface>
FnTable::get_fn(const std::string& name)
{
    if (exists(name))
        return fn_table[name];
    else { //throw new std::runtime_error();
        std::cout << "FnTable::get_fn fn '" + name + "'does not exist.\n";
        return nullptr;
    }
}

std::string
FnTable::to_str()
{
    std::string out("");
    out += "--------FN_TABLE-------\n";
    out += "size: " + std::to_string(fn_table.size()) + "\n";
    for (const auto& fn_pair : fn_table) {
        out += fn_pair.first + "\n";
    }
    return out;
}