#include "GameUtil.h"
#include "Image.h"

using namespace std;

Image::Image()
	: mWidth(0),
	  mHeight(0),
	  mNumPixels(0),
	  mPixelData(NULL)
{
}

Image::Image(uint width, uint height)
	: mWidth(width),
	  mHeight(height),
	  mNumPixels(width*height)
{
	mPixelData = new uchar[4*mNumPixels];
}

Image::Image(uint width, uint height, const string& rgb_filename)
	: mWidth(width),
	  mHeight(height),
	  mNumPixels(width*height)
{
	mPixelData = new uchar[4*mNumPixels];
	LoadRawRGB(rgb_filename);
}

Image::Image(uint width, uint height, const string& rgb_filename, const string& alpha_filename)
	: mWidth(width),
	  mHeight(height),
	  mNumPixels(width*height)
{
	mPixelData = new uchar[4*mNumPixels];
	LoadRawRGB(rgb_filename);
	LoadRawAlpha(alpha_filename);
}

Image::Image(Image* image, uint x, uint y, uint width, uint height)
	: mWidth(width),
	  mHeight(height),
	  mNumPixels(width*height)
{
	mPixelData = new uchar[4*mNumPixels];
	uchar *src_pixels = image->GetPixelData();
	uint dst = 0;
	
	for (uint j = 0; j < height; j++)
	{
		for (uint i = 0; i < width; i++)
		{
			mPixelData[dst++] = 255;
			mPixelData[dst++] = 0;
			mPixelData[dst++] = 0;
			mPixelData[dst++] = 255;
		}
	}
	dst = 0;
	
	for (uint j = 0; j < height; j++)
	{
		uint src = 4 * (x + ((y + j) * image->GetWidth()));
		for (uint i = 0; i < width; i++)
		{
			mPixelData[dst++] = src_pixels[src++];
			mPixelData[dst++] = src_pixels[src++];
			mPixelData[dst++] = src_pixels[src++];
			mPixelData[dst++] = src_pixels[src++];
		}
	}
}

Image::~Image()
{
	delete[] mPixelData;
}

void Image::SetTransparentColour(uchar r, uchar g, uchar b)
{
	for (uint i = 0; i < 4*mNumPixels; i += 4) {
		if (mPixelData[i] == r && mPixelData[i+1] == g && mPixelData[i+2] == b) {
			// Make pixel transparent
			mPixelData[i+3] = 0;
		} else {
			// Make pixel opaque
			mPixelData[i+3] = 255;
		}
	}
}

void Image::LoadRawRGB(const string& rgb_filename)
{	
	string filename;
	filename = "..//..//ASSETS//";
	filename += rgb_filename;

	uchar* rgb_data = new uchar[3*mNumPixels];
    ifstream rgb_file(filename.c_str(), ios::in | ios::binary);
	ifstream rgb_file2(rgb_filename.c_str(), ios::in | ios::binary);
   
	if (!rgb_file && !rgb_file2)
	{
		cerr << "Error opening " << rgb_filename; exit(1); 
	}

	
	if (rgb_file)
	{
		rgb_file.read((char*)rgb_data, 3*mNumPixels);
		if (!rgb_file) { cerr << "Error reading " << filename; exit(2); }

	} else {
		rgb_file2.read((char*)rgb_data, 3*mNumPixels);
		if (!rgb_file2) { cerr << "Error reading " << rgb_filename; exit(2); }
	}

	uint rgb_index = 0;
	for (uint i = 0; i < 4*mNumPixels; i += 4) {
		mPixelData[i]   = rgb_data[rgb_index++];
		mPixelData[i+1] = rgb_data[rgb_index++];
		mPixelData[i+2] = rgb_data[rgb_index++];
		mPixelData[i+3] = 255;
	}

	delete[] rgb_data;
}

void Image::LoadRawAlpha(const string& alpha_filename)
{
	string filename;
	filename = "..//..//ASSETS//";
	filename += alpha_filename;

	uchar* alpha_data = new uchar[mNumPixels];
    ifstream alpha_file(filename.c_str(), ios::in | ios::binary);
	ifstream alpha_file2(alpha_filename.c_str(), ios::in | ios::binary);


    if (!alpha_file && !alpha_file2) 
	{ 
		cerr << "Error opening " << alpha_filename; exit(3); 
	}

	if (alpha_file) {
		alpha_file.read((char*)alpha_data, mNumPixels);
		if (!alpha_file) { cerr << "Error reading " << alpha_filename; exit(4); }
	} else {
		alpha_file2.read((char*)alpha_data, mNumPixels);
		if (!alpha_file2) { cerr << "Error reading " << alpha_filename; exit(4); }
	}

	uint alpha_index = 0;
	for (uint i = 3; i < 4*mNumPixels; i += 4) {
		mPixelData[i] = alpha_data[alpha_index++];
	}

	delete[] alpha_data;
}
