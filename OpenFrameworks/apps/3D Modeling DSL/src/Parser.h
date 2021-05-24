#pragma once

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>

using namespace tao::TAO_PEGTL_NAMESPACE;
using namespace tao::pegtl::parse_tree;

namespace ModelScript
{
	class Parser
	{
		static std::unique_ptr<node> parseScript(const char* script);
	};
}