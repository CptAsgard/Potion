#include "Label.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>
#include <utf8/utf8.h>

#include "..\Utils\Defines.hpp"
#include "..\Utils\Utils.hpp"
#include "..\OpenGL.hpp"

using namespace std;

namespace IGAD
{
	const uint maxBufferWidth = 1028;
	const uint maxBufferHeight = 512;

	uint NextPowerOfTwo( uint val )
	{
		uint t = 2;
		while( t < val ) t *= 2;
		return t;
	}


	unsigned char ttf_buffer[ 1 << 20 ];

	Label::Label( const string& labelText,
		const string& fontFilename,
		unsigned fontsize,
		float maxWidth )
		: _fontsize( fontsize )
		, _maxWidth( maxWidth )
	{
		// We'll start basic by caching just the raw font blob,
		// at some point we could also cache the FT_Face instance.
		auto fontdata = IGAD::ReadFile( fontFilename );

#ifdef _WIN32 // defined to 32 and 64
		FILE* file;
		if( fopen_s( &file, fontFilename.c_str(), "rb" ) )
			fread( ttf_buffer, 1, 1 << 20, file );
		else
			ASSERT( false );
#elif 
		fread( ttf_buffer, 1, 1 << 20, fopen( fontFilename.c_str(), "rb" ) );
#endif

		stbtt_fontinfo fontinfo;

		stbtt_InitFont( &fontinfo, ttf_buffer, stbtt_GetFontOffsetForIndex( ttf_buffer, 0 ) );

		//	stbtt_InitFont(&fontinfo, reinterpret_cast<const unsigned char*>(fontdata.c_str()), 0);

		const auto& text = labelText;

		Vector2 outSize, outUV;
		//     bool multiline = false;

		// Check for invalid utf-8 (for a simple yes/no check, there is also utf8::is_valid function)
		auto end_it = utf8::find_invalid( text.begin(), text.end() );
		if( end_it != text.end() )
			LOG( "Invalid UTF-8 encoding detected" );

		vector<uint> utf32text;
		utf8::utf8to32( text.begin(), text.end(), back_inserter( utf32text ) );

		int ascent;
		float scale = stbtt_ScaleForPixelHeight( &fontinfo, float( fontsize ) );	// get the scale for certain
		stbtt_GetFontVMetrics( &fontinfo, &ascent, nullptr, nullptr );			// get the the ascent
		int baseline = static_cast<int>(ascent*scale);							// calculate the baseline in pixels


		unsigned char* buffer = static_cast<unsigned char*>(calloc( maxBufferWidth * maxBufferHeight, sizeof( char ) ));

		float xpos = 2;
		float ymax = -FLT_MAX;
		for( uint ch = 0; ch < utf32text.size(); ++ch )
		{
			auto codepoint = utf32text[ ch ];
			int advance, lsb, x0, y0, x1, y1;
			float x_shift = xpos - static_cast<float>(floor( xpos ));

			stbtt_GetCodepointHMetrics( &fontinfo,	// font
				static_cast<int>(codepoint),		// current
				&advance,							// advance
				&lsb );								// left side bearing

			stbtt_GetCodepointBitmapBoxSubpixel( &fontinfo,  // font
				static_cast<int>(codepoint),	// current character
				scale,							// scale x (not in pixels)
				scale,							// scale y (not in pixels)
				x_shift,						// subpixel shift x
				0,								// subpixel shift y
				&x0,							// x min (from)
				&y0,							// y min (from)
				&x1,							// x max (to)
				&y1 );							// y max (to)

			int idx = (baseline + y0) * maxBufferWidth + static_cast<int>(xpos) + x0;

			// This output can be saved into a bitmap and
			stbtt_MakeCodepointBitmapSubpixel( &fontinfo,  // font
				&buffer[ idx ],							  // pos in final image
				x1 - x0,                                  // output_width
				y1 - y0,                                  // output_height
				maxBufferWidth,                           // stride
				scale,                                    // scale x
				scale,                                    // scale y
				x_shift,                                  // subpixel shift x
				0,                                        // subpixel shift y
				static_cast<int>(codepoint) );             // codepoint

			xpos += (advance * scale);
			if( ch < utf32text.size() - 1 )
				xpos += scale * stbtt_GetCodepointKernAdvance(
					&fontinfo,
					static_cast<int>(codepoint),
					static_cast<int>(utf32text[ ch + 1 ]) );

			if( (y1 - y0) > ymax )
				ymax = float( y1 - y0 );
		}

		ymax *= 1.5;

		float xmax = xpos;

		outSize.X = xmax;
		outSize.Y = ymax;
		_yoffset = 0;
		uint sizex = NextPowerOfTwo( uint( xmax ) );
		uint sizey = NextPowerOfTwo( uint( ymax ) );

		outUV.X = static_cast<float>(xmax) / sizex;
		outUV.Y = static_cast<float>(ymax) / sizey;


		// Set the texture internal properties:
		_size = outSize;
		_uvTo = outUV;
		width = sizex;
		height = sizey;
		auto size = width * height * 4;
		GLubyte*  imageData = static_cast<GLubyte*>(calloc( size, 1 ));

		if( textureID != 0 )
		{
			glDeleteTextures( 1, &textureID );
			textureID = 0;
		}

		glGenTextures( 1, &textureID );               // Gen
		GL_GET_ERROR();
		glBindTexture( GL_TEXTURE_2D, textureID );    // Bind
		GL_GET_ERROR();
		//
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );   // Minmization
		GL_GET_ERROR();
		//
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );   // Magnification
		GL_GET_ERROR();

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		GL_GET_ERROR();

		// Draw a solid label background:
		for( int i = 0; i < height; i++ )
		{
			for( int j = 0; j < width; j++ )
			{
				unsigned char c = buffer[ i * maxBufferWidth + j ];

				// Base index in buffer
				int baseIdx = (i * width + j) * 4;
				imageData[ baseIdx + 0 ] = static_cast<GLubyte>(255);
				imageData[ baseIdx + 1 ] = static_cast<GLubyte>(255);
				imageData[ baseIdx + 2 ] = static_cast<GLubyte>(255);
				imageData[ baseIdx + 3 ] = static_cast<GLubyte>(c);
			}
		}

		glTexImage2D( GL_TEXTURE_2D,         // What (target)
			0,								// Mip-map level
			GL_RGBA,						// Internal format
			width,                         // Width
			height,                        // Height
			0,								// Border
			GL_RGBA,						// Format (how to use)
			GL_UNSIGNED_BYTE,				// Type   (how to intepret)
			imageData );						// Data

		GL_GET_ERROR();

		free( buffer );
		free( imageData );
	}
}