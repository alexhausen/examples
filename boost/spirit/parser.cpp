
// EBNF
// symbol_tone ::= 'ON' | 'OFF'
// symbol_repeat ::= 'R'
// tone ::= <symbol_tone> '(' [0-9]+ ')' | <symbol_repeat>
// tone_list ::= <tone> (',' <tone>)*

#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>

namespace client {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Parser : qi::grammar<Iterator, ascii::space_type> {
	Parser() : Parser::base_type(start) { 
		using qi::int_;

		symbol_tone = qi::lit("ON") | qi::lit("OFF");
		symbol_repeat = 'R';
		tone = symbol_tone >> '(' >> int_ >> ')' | symbol_repeat;
		tone_list = tone >> *( ',' >> tone);
		start = tone_list;
	}

	qi::rule<Iterator, ascii::space_type> start;
	qi::rule<Iterator, ascii::space_type> symbol_tone;
	qi::rule<Iterator, ascii::space_type> symbol_repeat;
	qi::rule<Iterator, ascii::space_type> tone;
	qi::rule<Iterator, ascii::space_type> tone_list;
};

}

int main() {

	typedef client::Parser<std::string::const_iterator> Parser;
	Parser grammar;
	std::string str = "ON(10),OFF(20),R";
	
        std::string::const_iterator itr = str.begin();
        std::string::const_iterator end = str.end();
	bool r = phrase_parse(itr, end, grammar, boost::spirit::ascii::space);

	if (r && itr == end) {
		std::cout << "parse ok" << std::endl;
	} else {
		std::cout << "parse failed" << std::endl;
	}

	return 0;
}

