#pragma once
#include <string>

class PNGExporter
{
	unsigned char* _buffer;
	unsigned int _width;
	unsigned int _height;

public:
	PNGExporter(unsigned char* buffer, unsigned int width, unsigned int height);

	void Export(const std::string& path_to_file) const;
};

