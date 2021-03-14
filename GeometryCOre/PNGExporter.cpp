#include "PNGExporter.h"
#include "lodepng.h"

PNGExporter::PNGExporter(unsigned char* buffer, const unsigned width, const unsigned height)
{
	_buffer = buffer;
	_width = width;
	_height = height;
}

void PNGExporter::Export(const std::string& path_to_file) const
{
	lodepng::encode(path_to_file, _buffer, _width, _height);
}
