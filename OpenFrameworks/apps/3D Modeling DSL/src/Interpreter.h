#pragma once

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>
#include "MeshNode.h"

using namespace tao::TAO_PEGTL_NAMESPACE;
using namespace tao::pegtl::parse_tree;

namespace ModelScript
{
	class Interpreter
	{
	private:
		static void formatToken(std::string& token)
		{
			//Remove whitespace
			token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());
			token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
		}

		static shared_ptr<MeshNode> instantiateNode(std::string token, bool hasChildren)
		{
			shared_ptr<MeshNode> node;

			if (token == "plane")
				node = make_shared<MeshNode>(PrimitiveType::Plane);
			else if (token == "sphere")
				node = make_shared<MeshNode>(PrimitiveType::Sphere);
			else if (token == "icosphere")
				node = make_shared<MeshNode>(PrimitiveType::IcoSphere);
			else if (token == "cylinder")
				node = make_shared<MeshNode>(PrimitiveType::Cylinder);
			else if (token == "cone")
				node = make_shared<MeshNode>(PrimitiveType::Cone);
			else if (token == "box")
				node = make_shared<MeshNode>(PrimitiveType::Box);
			else if (hasChildren)
				node = make_shared<MeshNode>();
			else
				node = nullptr;

			return node;
		}

	public:
		static shared_ptr<MeshNode> execute(std::unique_ptr<node> AstRoot)
		{
			shared_ptr<MeshNode> node;

			std::string token = std::string(AstRoot->m_begin.data, AstRoot->m_end.data);
			formatToken(token);

			auto& children = AstRoot->children;

			node = instantiateNode(token, !children.empty());

			for (int childIndex = 0; childIndex < children.size(); childIndex++)
			{
				shared_ptr<MeshNode> childNode = execute(move(children.at(childIndex)));

				if (childNode != nullptr)
					childNode->setParent(node);
			}

			return node;
		}
	};
}