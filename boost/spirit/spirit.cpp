/*
Parse grammar:
 symbol_tone ::= 'ON' | 'OFF'
 symbol_repeat ::= 'R'
 tone ::= <symbol_tone> '(' [0-9]+ ')' | <symbol_repeat>
 tone_list ::= <tone> <tone_list_tail>
 tone_list_tail ::= <tone_list> | (',' <tone>)*

Print ~ for on(s) and . for off(s).
*/

#include <iostream>
#include <string>

#include <boost/spirit/include/qi.hpp>

template <typename Iterator>
bool parse_numbers(Iterator first, Iterator last)
{
    using qi::double_;
    using qi::phrase_parse;
    using ascii::space;

    bool r = phrase_parse(
        first,                          
        last,                           
        double_ >> *(',' >> double_),   
        space                           
    );
    if (first != last) // fail if we did not get a full match
        return false;
    return r;
}

int main(int argc, char** argv) {

	std::string input;
	//input1 = "ON(1),OFF(20),ON(30),OFF(50)";
	input = "";
	typedef client::Parser<std::string::const_iterator> Parser;
	Parser parser;
	bool parsed = boost::spirit::qi::parse(input.begin(), input.end(), parser);

	std::cout << std::boolalpha << parsed << std::endl;

	return 0;
}

