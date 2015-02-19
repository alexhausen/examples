//TODO copyright

#include <string>

#include <sndfile.h>

namespace snd {

class File {
protected:
	File();
	void Open(const std::string& name, int mode);
	SNDFILE* snd_file_;
	SF_INFO info_;

public:
	virtual ~File();
	bool Good() const;
	void Close();
	SF_INFO info() const;
};

// input libsndfile wrapper
class InFile : public File {
public:
	InFile(const std::string& name);
	virtual ~InFile();
	int Read(float buffer[], size_t max_size);
};

// output libsndfile wrapper
class OutFile : public File {
public:
	OutFile(const std::string& name, const SF_INFO& sf_info);
	~OutFile();
	int Write(const float buffer[], size_t count);
	int Write(const int buffer[], size_t count);
};

// structure to configure a PCMU OutFile
SF_INFO GetPcmuInfo(int sample_counts);

}

