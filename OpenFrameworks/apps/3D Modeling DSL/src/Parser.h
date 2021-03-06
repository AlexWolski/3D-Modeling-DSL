#pragma once

#include <iostream>
#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>
#include <tao/pegtl/contrib/parse_tree_to_dot.hpp>

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
		struct modelString : TAO_PEGTL_STRING("model") {};
		struct whileString  : TAO_PEGTL_STRING("while") {};

		//All the keywords represented as key rules
		struct numberKey : key<numberString> {};
		struct modelKey : key<modelString> {};
		struct whileKey  : key<whileString> {};

		//A list of the keyword strings
		struct keywordStringList : sor<numberString, modelString, whileKey> {};

		//A grammar rule that succeeds when the token does not match any keyword
		struct keyword : key<keywordStringList> {};


		//Matches any number of spaces, tabs, or new lines
		struct whitespace : star<space> {};

		//Control structure characters
		struct semicolon : seq<whitespace, one<';'>, whitespace> {};
		struct openParen : seq<whitespace, one<'('>, whitespace> {};
		struct closeParen : seq<whitespace, one<')'>, whitespace> {};
		struct openBracket : seq<whitespace, one<'{'>, whitespace> {};
		struct closeBracket : seq<whitespace, one<'}'>, whitespace> {};

		//Alphanumeric variable or function name
		struct name : seq<not_at<keyword>, whitespace, identifier> {};

		//Functions don't currently take any inputs
		struct paramList : if_must<openParen, closeParen, semicolon> {};
		//Match a function name and parameter list, but rewind the parameter list
		struct funcitonName : if_must<name, at<paramList>> {};
		struct function : if_must<funcitonName, paramList> {};

		struct statement : sor<function> {};
		struct statementSeq : star<statement> {};
		struct block : if_must<openBracket, statementSeq, closeBracket> {};

		struct modelHeader : seq<whitespace, modelKey, name> {};
		struct modelBlock : if_must<modelHeader, block> {};

		struct expression : sor<statement, modelBlock> {};
		struct program : star<expression> {};

		struct grammar : must<program, eof> {};


		struct rearrange : parse_tree::apply<rearrange>
		{
			template<typename... States>
			static void transform(std::unique_ptr<parse_tree::node>& n, States&&... st) { }
		};

		// select which rules in the grammar will produce parse tree nodes:
		template<typename Rule>
		using selector = parse_tree::selector<
			Rule,
			parse_tree::store_content::on<funcitonName, modelHeader>,
			rearrange::on<modelBlock>
		>;

	public:
		static std::unique_ptr<node> parseScript(std::string& script)
		{
			memory_input<> parserInput(script, "Model Script");

			try {
				std::unique_ptr<node> AstRoot = parse_tree::parse<grammar, selector>(parserInput);
				parse_tree::print_dot(std::cout, *AstRoot);

				return std::move(AstRoot);
			}
			catch (const std::exception& e)
			{
				throw e;
			}
		}
	};
}