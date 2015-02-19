// EBNF
// OnOff ::= 'ON' | 'OFF'
// Repeat ::= 'R'
// Idle ::= 'IDLE'
// Inactive ::= <Idle> '(' [0-9]+ ')'
// Cycle ::= <OnOff> '(' [0-9]+ ')'
// Sequence ::= <Cycle> (',' <Cycle>)*
// Repetition ::= '[' <Sequence> ']' [0-9]+
// Cycle ::= <Sequence> | <Repetition>
// Cadence ::= <Cycle> (',' <Cycle>)* (',' <Inactive>)? (',' <Repeat>)?

#include <cassert>
#include <cmath>

#include <iostream>
#include <string>

#include <boost/spirit/include/qi.hpp>

#include "snd.h"

static const int kSampleRate = 8000;
static const int kAmplitude = 1.0 * 0x7F000000;
static const int kLeftFreq = 425.0 / kSampleRate;

class Cycle {
public:
	enum cycle_type { kOn, kOff };

	Cycle(cycle_type t) : duration_(0), type_(t) {
	}

	int NumberOfSamples() const {
		return duration_ / 1000 * kSampleRate;
	}

	cycle_type type() const {
		return type_;
	}

private:
	int duration_;
	cycle_type type_;
};

class Cadence {
public:
	Cadence() : repeat_(false), inactive_(0) {
	}

	void Add(const std::string& cycle_str) {
		Cycle::cycle_type type;
		if (cycle_str == "on") {
			type = Cycle::kOn;
		} else if (cycle_str == "off") {
			type = Cycle::kOff;
		} else {
			std::cout << "wrong type: " << cycle_str << std::endl;
			return;
		}
		Cycle cycle(type);
		cycles_.push_back(cycle);
	}


	int TotalSamples() const {
		int count = 0;
		std::vector<Cycle>::const_iterator it = cycles_.begin();
		for (; it != cycles_.end(); ++it) {
			const Cycle& c = *it;
			count += c.NumberOfSamples();
		}
		return count;
	}

	std::vector<Cycle> cycles() const {
		return cycles_;
	}

private:
	std::vector<Cycle> cycles_;
	bool repeat_;
	int inactive_;
};

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

int main(int argc, char** argv) {

	std::string str;
	std::string filename;
	if (argc == 2) {
		str = "ON(10),OFF(2),IDLE(3),R";
		filename = argv[1];
	} else if (argc == 3) {
		str = argv[1];
		filename = argv[2];
	} else {
		std::cout << "Wrong number of parameters: " << argc << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "ring2pcmu [\"ring tone sequence\"] output.wav" << std::endl;
		return 1;
	}

	// parse cadence
	typedef client::Parser<std::string::const_iterator> Parser;
	Parser grammar;

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

	//translate cadence in to wave
	Cadence cadence;
	std::vector<Cycle> cycles = cadence.cycles();
	int wav_buffer[cadence.TotalSamples()];
	int sample_index = 0;
	std::vector<Cycle>::const_iterator it_c = cycles.begin();
	for (; it_c != cycles.end(); ++it_c) {
		const Cycle& cycle = *it_c;
		for (int j = 0; j < cycle.NumberOfSamples(); ++j) {
			if (cycle.type() == Cycle::kOn) {
				wav_buffer[sample_index] = kAmplitude * sin(kLeftFreq * 2 * j * M_PI);
			} else {
				wav_buffer[sample_index] = 0;
			}
			std::cout << wav_buffer[sample_index] << " ";
			sample_index++;
		}
	}
	std::cout << std::endl;

	// write wave file
	SF_INFO info = snd::GetPcmuInfo(cadence.TotalSamples());
	snd::OutFile output(filename, info);
	assert(output.Good());
	int num_items = info.channels * cadence.TotalSamples();
	int written = output.Write(wav_buffer, num_items);
	if (written != num_items) {
		std::cout << "write errror. " << num_items << "!=" << written << std::endl;
		return 1;
	}

	return 0;
}

