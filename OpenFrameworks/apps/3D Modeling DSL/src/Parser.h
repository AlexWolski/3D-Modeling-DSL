#pragma once

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>

using namespace tao::TAO_PEGTL_NAMESPACE;
using namespace tao::pegtl::parse_tree;

//Parts of code adapted from https://github.com/taocpp/PEGTL/tree/2.x/src/example/pegtl
namespace ModelScript
{
	class Parser
	{
	private:
		//A grammar rule that succeeds when the token does not match a given keyword
		template <typename Key>
		struct key : seq<Key, not_at<identifier_other>> {};

		//All the keywords represented as strings
		struct numberString : TAO_PEGTL_STRING("number") {};
		struct moduleString : TAO_PEGTL_STRING("module") {};
		struct whileString  : TAO_PEGTL_STRING("while") {};

		//All the keywords represented as key rules
		struct numberKey : key<numberString> {};
		struct moduleKey : key<moduleString> {};
		struct whileKey  : key<whileString> {};

		//A list of the keyword strings
		struct keywordStringList : sor<numberString, moduleString, whileKey> {};

		//A grammar rule that succeeds when the token does not match any keyword
		struct keyword : key<keywordStringList> {};

	public:
		static std::unique_ptr<node> parseScript(const char* script)
		{
			return nullptr;
		}
	};
}