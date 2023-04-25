#include "tostr.h"

namespace Lib {
	std::string
	to_str::name()
	{
		return "to_str";
	}

	std::shared_ptr<Obj::Object>
	to_str::invoke(std::vector<std::shared_ptr<Obj::Object>> args)
	{
		check_nargs(args, 1);
		return std::make_shared<Obj::String>(args[0]->to_str());
	}
}