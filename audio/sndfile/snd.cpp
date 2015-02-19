// TODO copyright

#include "snd.h"
#include <iostream>
#include <cstring>

namespace snd {

File::File()
	: snd_file_(0) { 
}

File::~File() {
	Close();
}

bool File::Good() const {
	return snd_file_ != 0;
}

SF_INFO File::info() const {
	return info_;
}

void File::Open(const std::string& name, int mode) {
	snd_file_ = sf_open(name.c_str(), mode, &info_);
	if (!snd_file_) {
		std::cout << sf_strerror(NULL) << " '" << name << "'" << std::endl;
		return;
	}
	if (!sf_format_check(&info_)) {
		std::cout << "Invalid format." << std::endl;
		Close();
	}
}

void File::Close() {
	if (snd_file_) {
		sf_close(snd_file_);
	}
	snd_file_ = 0;
}

InFile::InFile(const std::string& name)
	: File() {
	Open(name, SFM_READ);
}

InFile::~InFile() {
}

int InFile::Read(float buffer[], size_t buffer_size) {
	if (snd_file_ == 0) {
		std::cout << "File not opened" << std::endl;
		return 0u;
	}
	return sf_read_float(snd_file_, buffer, buffer_size);
}

OutFile::OutFile(const std::string& name, const SF_INFO& sf_info)
	: File() {
	info_ = sf_info;
	Open(name, SFM_WRITE);
}

OutFile::~OutFile() {
}

//return number of floats written
int OutFile::Write(const float buffer[], size_t count) {
	if (snd_file_ == 0) {
		std::cout << "File not opened" << std::endl;
		return 0;
	}
	return sf_write_float(snd_file_, buffer, count);
}

//return number of integers written
int OutFile::Write(const int buffer[], size_t count) {
	if (snd_file_ == 0) {
		std::cout << "File not opened" << std::endl;
		return 0;
	}
	return sf_write_int(snd_file_, buffer, count);
}

SF_INFO GetPcmuInfo(int sample_counts) {
	SF_INFO info;
	memset(&info, 0, sizeof(info));
	info.samplerate = 8000;
	info.channels = 1;
	info.format = SF_FORMAT_WAV | SF_FORMAT_ULAW;
	info.frames = sample_counts;
	return info;
}

}

