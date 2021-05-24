#pragma once

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>
#include "MeshNode.h"

using namespace tao::TAO_PEGTL_NAMESPACE;
using namespace tao::pegtl::parse_tree;

namespace ModelScript
{
	class Parser
	{
		static shared_ptr<MeshNode> execute(std::unique_ptr<node> AstRoot);
	};
}