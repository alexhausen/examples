// TODO copyright

#include <cassert>
#include <iostream>
#include "snd.h"

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Wrong number of parameters: " << argc << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "wav2pcmu input.wav output.wav" << std::endl;
		return 1;
	}

	snd::InFile in(argv[1]);
	assert(in.Good());

	SF_INFO info = in.info();
	info.format = SF_FORMAT_WAV | SF_FORMAT_ULAW;
	snd::OutFile out(argv[2], info);
	assert(out.Good());

	const size_t size = 4096;
	float buffer[size];
	int read = 0;
	while ((read = in.Read(buffer, size)) > 0) {
		int written = out.Write(buffer, read);
		if (written != read) {
			std::cout << "write errror. " << read << "!=" << written << std::endl;
		}
	}

	return 0;
}

