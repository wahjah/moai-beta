// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <uslsext/USColor.h>
#include <uslsext/USInterpolate.h>

#define WR 0.299f
#define WG 0.587f
#define WB 0.114f

#define U_MAX 0.436f
#define V_MAX 0.615f

//================================================================//
// USColor
//================================================================//

//----------------------------------------------------------------//
void USColor::Convert ( void* dest, Format destFmt, const void* src, Format srcFmt, u32 nColors ) {

	u32 buffer [ 1024 ];
	u32* bufferPtr = buffer;
	u32 color;
	
	switch ( srcFmt ) {
		
		case A_8:
		
			for ( u32 i = 0; i < nColors; ++i ) {
				buffer [ i ] = *( u8* )src;
				src = ( void* )(( u32 )src + 1 );
			}
			break;
		
		case RGB_888:
			
			for ( u32 i = 0; i < nColors; ++i ) {
				buffer [ i ] = ( *( u32* )src ) & 0x00FFFFFF;
				src = ( void* )(( u32 )src + 3 );
			}
			break;
			
		case RGB_565:
			
			for ( u32 i = 0; i < nColors; ++i ) {
				color = *( u16* )src;
				buffer [ i ] =	((( color >> 0x00 ) & 0x1F ) << 0x03 ) +
								((( color >> 0x05 ) & 0x3F ) << 0x02 ) +
								((( color >> 0x0B ) & 0x1F ) << 0x03 ) +
								0xff000000;
				src = ( void* )(( u32 )src + 2 );
			}
			break;
		
		case RGBA_5551: 
			
			for ( u32 i = 0; i < nColors; ++i ) {
				color = *( u16* )src;
				buffer [ i ] =	((( color >> 0x00 ) & 0x1F ) << 0x03 ) +
								((( color >> 0x05 ) & 0x1F ) << 0x0B ) +
								((( color >> 0x0A ) & 0x1F ) << 0x13 ) +
								(((( color >> 0x0F ) & 0xff ) ? 0xff : 0x00 ) << 0x18 );
				src = ( void* )(( u32 )src + 2 );
			}
			break;

		case RGBA_4444:
		
			for ( u32 i = 0; i < nColors; ++i ) {
				color = *( u32* )src;
				buffer [ i ] =	((( color >> 0x00 ) & 0x0F ) << 0x04 ) +
								((( color >> 0x04 ) & 0x0F ) << 0x0C ) +
								((( color >> 0x08 ) & 0x0F ) << 0x14 ) +
								((( color >> 0x0C ) & 0x0F ) << 0x1C );
				src = ( void* )(( u32 )src + 2 );
			}
			break;

		case RGBA_8888:
			bufferPtr = ( u32* )src;
			break;
		
		default:
			return;
	}
	
	switch ( destFmt ) {
	
		case A_8:
			
			for ( u32 i = 0; i < nColors; ++i ) {
				color = bufferPtr [ i ];
				(( u8* )dest )[ 0 ] = color & 0xFF;
				dest = ( void* )(( u32 )dest + 1 );
			}
			break;
	
		case RGB_888:
		
			for ( u32 i = 0; i < nColors; ++i ) {
				color = bufferPtr [ i ];
				(( u8* )dest )[ 0 ] = color & 0xFF;
				(( u8* )dest )[ 1 ] = ( color >> 8 ) & 0xFF;
				(( u8* )dest )[ 2 ] = ( color >> 16 ) & 0xFF;
				dest = ( void* )(( u32 )dest + 3 );
			}
			break;
			
		case RGB_565:
		
			for ( u32 i = 0; i < nColors; ++i ) {
				color = bufferPtr [ i ];
				*( u16* )dest =	((( color >> 0x03 ) & 0x1F ) << 0x0B ) +
								((( color >> 0x0A ) & 0x3F ) << 0x05 ) +
								((( color >> 0x13 ) & 0x1F ) << 0x00 );
				dest = ( void* )(( u32 )dest + 2 );
			}
			break;
					
		case RGBA_5551: 
			
			for ( u32 i = 0; i < nColors; ++i ) {
				color = bufferPtr [ i ];
				*( u16* )dest =		((( color >> 0x03 ) & 0x1F ) << 0x00 ) +
									((( color >> 0x0B ) & 0x1F ) << 0x05 ) +
									((( color >> 0x13 ) & 0x1F ) << 0x0A ) +
									(((( color >> 0x1C ) & 0x0F ) ? 0x01 : 0x00 ) << 0x0F );
				dest = ( void* )(( u32 )dest + 2 );
			}
			break;

		case RGBA_4444:
			
			for ( u32 i = 0; i < nColors; ++i ) {
				color = bufferPtr [ i ];
				*( u16* )dest =		((( color >> 0x04 ) & 0x0F ) << 0x0C ) +
									((( color >> 0x0C ) & 0x0F ) << 0x08 ) +
									((( color >> 0x14 ) & 0x0F ) << 0x04 ) +
									((( color >> 0x1C ) & 0x0F ) << 0x00 );
				dest = ( void* )(( u32 )dest + 2 );
			}
			break;

		case RGBA_8888:
			
			memcpy ( dest, bufferPtr, nColors * sizeof ( u32 ));
			break;
		
		default:
			break;
	}
}

//----------------------------------------------------------------//
u32 USColor::ConvertFromRGBA ( u32 color, Format format ) {

	switch ( format ) {
		
		case A_8:
			return ( color >> 18 ) & 0x000000FF;
		
		case RGB_888:
			return color & 0x00FFFFFF;
			
		case RGB_565:
		
			return	((( color >> 0x03 ) & 0x1F ) << 0x0B ) +
					((( color >> 0x0A ) & 0x3F ) << 0x05 ) +
					((( color >> 0x13 ) & 0x1F ) << 0x00 );
					
		case RGBA_5551: 
			
			return	((( color >> 0x03 ) & 0x1F ) << 0x00 ) +
					((( color >> 0x0B ) & 0x1F ) << 0x05 ) +
					((( color >> 0x13 ) & 0x1F ) << 0x0A ) +
					(((( color >> 0x1C ) & 0x0F ) ? 0x01 : 0x00 ) << 0x0F );

		case RGBA_4444:
			
			return	((( color >> 0x04 ) & 0x0F ) << 0x0C ) +
					((( color >> 0x0C ) & 0x0F ) << 0x08 ) +
					((( color >> 0x14 ) & 0x0F ) << 0x04 ) +
					((( color >> 0x1C ) & 0x0F ) << 0x00 );

		case RGBA_8888:
			return color;
		
		default:
			break;
	}
	
	return 0;
}

//----------------------------------------------------------------//
u32 USColor::ConvertToRGBA ( u32 color, Format format ) {

	switch ( format ) {
		
		case A_8:
			return ( color << 18 ) & 0xFF000000;
		
		case RGB_888:
			return color | 0xFF000000;
			
		case RGB_565:
		
			return	((( color >> 0x00 ) & 0x1F ) << 0x03 ) +
					((( color >> 0x05 ) & 0x3F ) << 0x02 ) +
					((( color >> 0x0B ) & 0x1F ) << 0x03 ) +
					0xff000000;
					
		case RGBA_5551: 
			
			return	((( color >> 0x00 ) & 0x1F ) << 0x03 ) +
					((( color >> 0x05 ) & 0x1F ) << 0x0B ) +
					((( color >> 0x0A ) & 0x1F ) << 0x13 ) +
					(((( color >> 0x0F ) & 0xff ) ? 0xff : 0x00 ) << 0x18 );

		case RGBA_4444:
		
			return	((( color >> 0x00 ) & 0x0F ) << 0x04 ) +
					((( color >> 0x04 ) & 0x0F ) << 0x0C ) +
					((( color >> 0x08 ) & 0x0F ) << 0x14 ) +
					((( color >> 0x0C ) & 0x0F ) << 0x1C );

		case RGBA_8888:
			return color;
		
		default:
			break;
	}
	
	return 0;
}

//----------------------------------------------------------------//
u32 USColor::GetDepth ( Format format ) {

	switch ( format ) {
		case A_8:			return 8;
		case RGB_888:		return 24;
		case RGB_565:		return 16;
		case RGBA_5551:		return 16;
		case RGBA_4444:		return 16;
		case RGBA_8888:		return 32;
		default:			break;
	}
	return 0;
}

//----------------------------------------------------------------//
u32 USColor::GetMask ( Format format ) {

	switch ( format ) {
		case A_8:			return 0x000000FF;
		case RGB_888:		return 0x00ffffff;
		case RGB_565:		return 0x0000ffff;
		case RGBA_5551:		return 0x0000ffff;
		case RGBA_4444:		return 0x0000ffff;
		case RGBA_8888:		return 0xffffffff;
		default:			break;
	}
	return 0;
}

//----------------------------------------------------------------//
u32 USColor::GetSize ( Format format ) {

	switch ( format ) {
		case A_8:			return 1;
		case RGB_888:		return 3;
		case RGB_565:		return 2;
		case RGBA_5551:		return 2;
		case RGBA_4444:		return 2;
		case RGBA_8888:		return 4;
		default:			break;
	}
	return 0;
}

//----------------------------------------------------------------//
u32 USColor::PackRGBA ( int r, int g, int b, int a ) {

	return	( r << 0x00 ) +
			( g << 0x08 ) +
			( b << 0x10 ) +
			( a << 0x18 );
}

//----------------------------------------------------------------//
u32 USColor::PackRGBA ( float r, float g, float b, float a ) {

	return	(( u8 )( r * 255.0f ) << 0x00) +
			(( u8 )( g * 255.0f ) << 0x08 ) +
			(( u8 )( b * 255.0f ) << 0x10 ) +
			(( u8 )( a * 255.0f ) << 0x18 );
}

//----------------------------------------------------------------//
void USColor::PremultiplyAlpha ( void* colors, Format format, u32 nColors ) {

	u32 color;
	u32 alpha;
	
	switch ( format ) {
		
		case A_8:
			break;
		
		case RGB_888:
			break;
			
		case RGB_565:
			break;
		
		case RGBA_5551: 
			
			for ( u32 i = 0; i < nColors; ++i ) {
				color = *( u16* )colors;
				alpha = ( color >> 0x0F ) & 0x01;
				*( u16* )colors = ( u16 )(	(((( color >> 0x00 ) & 0x1F ) * alpha ) << 0x00 ) +
											(((( color >> 0x05 ) & 0x1F ) * alpha ) << 0x05 ) +
											(((( color >> 0x0A ) & 0x1F ) * alpha ) << 0x0A ) +
											( alpha << 0x0F ));
				colors = ( void* )(( u32 )colors + 2 );
			}
			break;

		case RGBA_4444:
		
			for ( u32 i = 0; i < nColors; ++i ) {
				color = *( u16* )colors;
				alpha = color & 0x0F;
				*( u16* )colors = ( u16 )(	alpha +
											((((( color >> 0x04 ) & 0x0F ) * alpha ) >> 0x04 ) << 0x04 ) +
											((((( color >> 0x08 ) & 0x0F ) * alpha ) >> 0x04 ) << 0x08 ) +
											((((( color >> 0x0c ) & 0x0F ) * alpha ) >> 0x04 ) << 0x0C ));
				colors = ( void* )(( u32 )colors + 2 );
			}
			break;

		case RGBA_8888:
		
			for ( u32 i = 0; i < nColors; ++i ) {
				color = *( u32* )colors;
				alpha = ( color >> 0x18 ) & 0xFF;
				*( u32* )colors =	((((( color >> 0x00 ) & 0xFF ) * alpha ) >> 0x08 ) << 0x00 ) +
									((((( color >> 0x08 ) & 0xFF ) * alpha ) >> 0x08 ) << 0x08 ) +
									((((( color >> 0x10 ) & 0xFF ) * alpha ) >> 0x08 ) << 0x10 ) +
									( alpha << 0x18 );
				colors = ( void* )(( u32 )colors + 4 );
			}
			break;
		
		default:
			break;
	}
}

//----------------------------------------------------------------//
u32 USColor::ReadRGBA ( const void* stream, Format format ) {

	u32 size = USColor::GetSize ( format );
	return USColor::ConvertToRGBA ( USPixel::ReadPixel ( stream, size ), format );
}

//----------------------------------------------------------------//
void USColor::WriteRGBA ( void* stream, u32 color, Format format ) {

	u32 size = USColor::GetSize ( format );
	USPixel::WritePixel ( stream, USColor::ConvertFromRGBA ( color, format ), size );
}

//================================================================//
// USPixel
//================================================================//

//----------------------------------------------------------------//
u32 USPixel::GetDepth ( Format format, USColor::Format colorFormat ) {

	switch ( format ) {
		case TRUECOLOR:		return USColor::GetDepth ( colorFormat );
		case INDEX_4:		return 4;
		case INDEX_8:		return 8;
		default:			break;
	}
	return 0;
}

//----------------------------------------------------------------//
u32 USPixel::GetMask ( Format format, USColor::Format colorFormat ) {

	switch ( format ) {
		case TRUECOLOR:		return USColor::GetMask ( colorFormat );
		case INDEX_4:		return 0x0000000F;
		case INDEX_8:		return 0x000000FF;
		default:			break;
	}
	return 0;
}

//----------------------------------------------------------------//
u32 USPixel::GetPaletteCount ( Format format ) {

	switch ( format ) {
		case TRUECOLOR:		return 0;
		case INDEX_4:		return 16;
		case INDEX_8:		return 256;
		default:			break;
	}
	return 0;
}

//----------------------------------------------------------------//
u32 USPixel::GetPaletteSize ( Format format, USColor::Format colorFormat ) {

	return ( USPixel::GetPaletteCount ( format ) * USColor::GetSize ( colorFormat ));
}

//----------------------------------------------------------------//
float USPixel::GetSize ( Format format, USColor::Format colorFormat ) {

	switch ( format ) {
		case TRUECOLOR:		return ( float )USColor::GetSize ( colorFormat );
		case INDEX_4:		return 0.5f;
		case INDEX_8:		return 1.0f;
		default:			break;
	}
	return 0;
}

//----------------------------------------------------------------//
u32 USPixel::ReadPixel ( const void* stream, u32 nBytes ) {

	const u8* bytes = ( const u8* )stream;
	u32 pixel = 0;
	u32 shift = 0;

	switch ( nBytes ) {
		
		case 4:
			pixel += ( *( bytes++ )) << shift;
			shift += 0x08;
		case 3:
			pixel += ( *( bytes++ )) << shift;
			shift += 0x08;
		case 2:
			pixel += ( *( bytes++ )) << shift;
			shift += 0x08;
		case 1:
			pixel += ( *( bytes++ )) << shift;
	}
	
	return pixel;
}

//----------------------------------------------------------------//
void USPixel::WritePixel ( void* stream, u32 pixel, u32 nBytes ) {

	u8* bytes = ( u8* )stream;
	u32 shift = 0;

	switch ( nBytes ) {

		case 4:
			*( bytes++ ) = ( pixel >> shift ) & 0xff;
			shift += 0x08;
		case 3:
			*( bytes++ ) = ( pixel >> shift ) & 0xff;
			shift += 0x08;
		case 2:
			*( bytes++ ) = ( pixel >> shift ) & 0xff;
			shift += 0x08;
		case 1:
			*( bytes++ ) = ( pixel >> shift ) & 0xff;
	}
}

//================================================================//
// USColorVec
//================================================================//

//----------------------------------------------------------------//
void USColorVec::FromYUV ( float y, float u, float v ) {

	this->mR = y + ( v * (( 1.0f - WR ) / V_MAX ));
	this->mG = y - ( u * (( WB * ( 1.0f - WB )) / ( U_MAX * WG ))) - ( v * (( WR * ( 1.0f - WR )) / ( V_MAX * WG )));
	this->mB = y + ( u * (( 1.0f - WB ) / U_MAX ));
}

//----------------------------------------------------------------//
float USColorVec::GetLuma () {

	return ( WR * this->mR ) + ( WG * this->mG ) + ( WB * this->mB );
}

//----------------------------------------------------------------//
void USColorVec::Lerp ( const USColorVec& v0, const USColorVec& v1, float t ) {

	this->mR = USInterpolate::Linear ( v0.mR, v1.mR, t );
	this->mG = USInterpolate::Linear ( v0.mG, v1.mG, t );
	this->mB = USInterpolate::Linear ( v0.mB, v1.mB, t );
	this->mA = USInterpolate::Linear ( v0.mA, v1.mA, t );
}

//----------------------------------------------------------------//
void USColorVec::LoadGfxState () const {

	glColor4f ( this->mR, this->mG, this->mB, this->mA );
}

//----------------------------------------------------------------//
void USColorVec::Modulate ( const USColorVec& v0 ) {

	this->mR = this->mR * v0.mR;
	this->mG = this->mG * v0.mG;
	this->mB = this->mB * v0.mB;
	this->mA = this->mA * v0.mA;
}

//----------------------------------------------------------------//
u32 USColorVec::PackRGBA () {

	return USColor::PackRGBA ( this->mR, this->mG, this->mB, this->mA );
}

//----------------------------------------------------------------//
void USColorVec::SetRGBA ( u32 color ) {

	this->mR = ( float )(( color ) & 0xff ) / 255.0f;
	this->mG = ( float )(( color >> 8 ) & 0xff ) / 255.0f;
	this->mB = ( float )(( color >> 16 ) & 0xff ) / 255.0f;
	this->mA = ( float )(( color >> 24 ) & 0xff ) / 255.0f;
}

//----------------------------------------------------------------//
void USColorVec::Set ( float r, float g, float b, float a ) {

	this->mR = r;
	this->mG = g;
	this->mB = b;
	this->mA = a;
}

//----------------------------------------------------------------//
void USColorVec::SetBlack () {

	this->Set ( 0.0f, 0.0f, 0.0f, 1.0f );
}

//----------------------------------------------------------------//
void USColorVec::SetWhite () {

	this->Set ( 1.0f, 1.0f, 1.0f, 1.0f );
}

//----------------------------------------------------------------//
void USColorVec::ToYUV ( float& y, float& u, float& v ) {
	
	y = ( WR * this->mR ) + ( WG * this->mG ) + ( WB * this->mB );
	u = U_MAX * (( this->mB - y ) / ( 1.0f - WB ));
	v = V_MAX * (( this->mR - y ) / ( 1.0f - WR ));
}

//----------------------------------------------------------------//
USColorVec::USColorVec () {
}

//----------------------------------------------------------------//
USColorVec::USColorVec ( float r, float g, float b, float a ) {

	this->mR = r;
	this->mG = g;
	this->mB = b;
	this->mA = a;
}