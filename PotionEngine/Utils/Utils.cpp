#include <sstream>
#include <fstream>

#include "Utils.hpp"
#include "Defines.hpp"

using namespace Potion;

std::string Potion::ReadFile(const std::string& filename)
{
	unsigned int length;
	char* buffer;

	std::ifstream is;
	is.open(filename.c_str(), std::ifstream::in);

	// Check for bad paths
	if (!is.is_open())
	{
		LOG("Unable to open file: %s\n", filename.c_str());
		return "";
	}

	// get length of file:
	is.seekg(0, std::ios::end);
	length = static_cast<unsigned int>(is.tellg());
	is.seekg(0, std::ios::beg);

	// allocate memory
	buffer = new char[length + 1];
	memset(buffer, 0, length + 1);

	// read data as a block:
	is.read(buffer, length);
	is.close();

	// NB: specifying a length parameter will solve any null byte issues, even when
	// reading arbitrary binary data.
	std::string ret = std::string(buffer, length + 1);
	delete[] buffer;

	return ret;
}

bool Potion::SaveFile(const std::string& filename,
	const std::string& text)
{
	std::ofstream os;
	os.open(filename.c_str(), std::ofstream::out);

	// Check for bad paths
	if (!os.is_open())
	{
#ifdef DEBUG
		LOG("Unable to open file for writing: %s\n", filename.c_str());
#endif
		return false;
	}


	// get length of file:
	os.write(text.c_str(), text.size());

	return true;
}

Potion::SphericalCoordinates Potion::CartesianToSpherical(const Vector3& cvec)
{
	SphericalCoordinates scoord;
	scoord.r		= sqrt(cvec.X*cvec.X + cvec.Y*cvec.Y + cvec.Z*cvec.Z);
	scoord.theta	= acos(cvec.Y / scoord.r);
	float ratio		= cvec.Z / cvec.X;
	scoord.fi		= isnan(ratio) ? 0.0f : atan(ratio);
	return scoord;
}

Vector3 Potion::SphericalToCartesian(const SphericalCoordinates& scoord)
{
	Vector3 cvec;	
	cvec.X = scoord.r * sin(scoord.theta) * cosf(scoord.fi);
	cvec.Y = scoord.r * cosf(scoord.theta);
	cvec.Z = scoord.r * sinf(scoord.theta) * sinf(scoord.fi);
	return cvec;
}
