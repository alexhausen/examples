// EBNF
// OnOff ::= 'ON' | 'OFF'
// Repeat ::= 'R'
// Idle ::= 'IDLE'
// Inactive ::= <Idle> '(' [0-9]+ ')'
// Active ::= <OnOff> '(' [0-9]+ ')'
// Sequence ::= <Active> (',' <Active>)*
// Repetition ::= '[' <Sequence> ']' [0-9]+
// Cycle ::= <Sequence> | <Repetition>
// Cadence ::= <Cycle> (',' <Cycle>)* (',' <Inactive>)? (',' <Repeat>)?

#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>

namespace client {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Parser : qi::grammar<Iterator, ascii::space_type> {
	Parser() : Parser::base_type(cadence) { 
		using qi::uint_;
		on_off =  qi::lit("ON") | qi::lit("OFF");
		repeat = qi::lit("R");
		idle = qi::lit("IDLE");
		inactive = idle >> '(' >> uint_ >> ')';
		active = on_off >> '(' >> uint_ >> ')';
		sequence = active >> *(',' >> active);
		repetition = '[' >> sequence >> ']' >> uint_;
		cycle = sequence | repetition;
		cadence = cycle >> *(',' >> cycle) >> -(',' >> inactive) >> -(',' >> repeat);
	}

	qi::rule<Iterator, ascii::space_type> on_off;
	qi::rule<Iterator, ascii::space_type> repeat;
	qi::rule<Iterator, ascii::space_type> idle;
	qi::rule<Iterator, ascii::space_type> inactive;
	qi::rule<Iterator, ascii::space_type> active;
	qi::rule<Iterator, ascii::space_type> sequence;
	qi::rule<Iterator, ascii::space_type> repetition;
	qi::rule<Iterator, ascii::space_type> cycle;
	qi::rule<Iterator, ascii::space_type> cadence;	
};

}

int main() {
	typedef client::Parser<std::string::const_iterator> Parser;
	Parser grammar;
	std::string str = "ON(10),OFF(-2),IDLE(3),R";
	
        std::string::const_iterator itr = str.begin();
        std::string::const_iterator end = str.end();
	bool r = phrase_parse(itr, end, grammar, boost::spirit::ascii::space);

	if (r && itr == end) {
		std::cout << "parse ok" << std::endl;
	} else {
		std::string error_at(itr, end);
		std::cout << "parse failed at: " << error_at << std::endl;
		return 1;
	}

	return 0;
}

