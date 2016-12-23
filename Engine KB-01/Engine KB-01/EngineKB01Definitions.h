#ifndef _ENGINEKB01DEFINITIONS_H_
#define _ENGINEKB01DEFINITIONS_H_

//Engine definition of DWORD
typedef unsigned long       EDWORD;

//Engine definition of BYTE
typedef unsigned char       EBYTE;

// color definitions
typedef EDWORD ECOLOR;
// end color definitions





// format definitions
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
	((EDWORD)(EBYTE)(ch0) | ((EDWORD)(EBYTE)(ch1) << 8) |       \
	((EDWORD)(EBYTE)(ch2) << 16) | ((EDWORD)(EBYTE)(ch3) << 24 ))

#endif /* defined(MAKEFOURCC) */

#define M_PI 3.14159265358979323846f

#define EFVF_XYZ              0x002
#define EFVF_TEX1             0x100
#define EFVF_NORMAL			  0x010
#define ECUSTOMFVF (EFVF_XYZ|EFVF_TEX1|EFVF_NORMAL)
#define ECUSTOMLIGHTLESSFVF (EFVF_XYZ|EFVF_TEX1)


struct MouseStruct
{
	long positionX; //The mouse's X coordinate
	long positionY; //The mouse's Y coordinate
	long z; // MouseWheel scrolling values
	bool button0; //Left Mouse Button
	bool button1; //Right Mouse Button
	bool button2; //MouseWheel click
	bool button3;
	bool button4;
	bool button5;
	bool button6;
	bool button7;
	bool buttonlock[8];
};


//Custom Engine VECTOR struct
struct VECTOR
{
	VECTOR()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

	VECTOR(float ix, float iy, float iz)
	{
		X = ix;
		Y = iy;
		Z = iz;
	}

	float X, Y, Z;
};


//Custom Engine Vertex struct, without the light components (no normal values)
struct LIGHTLESSVERTEX
{
	LIGHTLESSVERTEX()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		tu = 0.0f;
		tv = 0.0f;
	}

	LIGHTLESSVERTEX(float ix, float iy, float iz, float itu, float itv)
	{
		x = ix;
		y = iy;
		z = iz;
		tu = itu;
		tv = itv;
	}

	float x, y, z, tu, tv;
};

//Custom Engine Vertex struct, with the light components (normal values)
struct VERTEX
{
	VERTEX()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		tu = 0.0f;
		tv = 0.0f;
		nx = 0.0f;
		ny = 0.0f;
		nz = 0.0f;
	}

	VERTEX(float ix, float iy, float iz, float itu, float itv , float inx, float iny, float inz)
	{
		x = ix;
		y = iy;
		z = iz;
		tu = itu;
		tv = itv;
		nx = inx;
		ny = iny;
		nz = inz;
	}

	float x, y, z, nx, ny, nz, tu, tv;

};

//Custom Engine Read Only Format used by Renderer 
enum EFORMAT
{
	FMT_UNKNOWN = 0,

	FMT_R8G8B8 = 20,
	FMT_A8R8G8B8 = 21,
	FMT_X8R8G8B8 = 22,
	FMT_R5G6B5 = 23,
	FMT_X1R5G5B5 = 24,
	FMT_A1R5G5B5 = 25,
	FMT_A4R4G4B4 = 26,
	FMT_R3G3B2 = 27,
	FMT_A8 = 28,
	FMT_A8R3G3B2 = 29,
	FMT_X4R4G4B4 = 30,
	FMT_A2B10G10R10 = 31,
	FMT_A8B8G8R8 = 32,
	FMT_X8B8G8R8 = 33,
	FMT_G16R16 = 34,
	FMT_A2R10G10B10 = 35,
	FMT_A16B16G16R16 = 36,

	FMT_A8P8 = 40,
	FMT_P8 = 41,

	FMT_L8 = 50,
	FMT_A8L8 = 51,
	FMT_A4L4 = 52,

	FMT_V8U8 = 60,
	FMT_L6V5U5 = 61,
	FMT_X8L8V8U8 = 62,
	FMT_Q8W8V8U8 = 63,
	FMT_V16U16 = 64,
	FMT_A2W10V10U10 = 67,

	FMT_UYVY = MAKEFOURCC('U', 'Y', 'V', 'Y'),
	FMT_R8G8_B8G8 = MAKEFOURCC('R', 'G', 'B', 'G'),
	FMT_YUY2 = MAKEFOURCC('Y', 'U', 'Y', '2'),
	FMT_G8R8_G8B8 = MAKEFOURCC('G', 'R', 'G', 'B'),
	FMT_DXT1 = MAKEFOURCC('D', 'X', 'T', '1'),
	FMT_DXT2 = MAKEFOURCC('D', 'X', 'T', '2'),
	FMT_DXT3 = MAKEFOURCC('D', 'X', 'T', '3'),
	FMT_DXT4 = MAKEFOURCC('D', 'X', 'T', '4'),
	FMT_DXT5 = MAKEFOURCC('D', 'X', 'T', '5'),

	FMT_D16_LOCKABLE = 70,
	FMT_D32 = 71,
	FMT_D15S1 = 73,
	FMT_D24S8 = 75,
	FMT_D24X8 = 77,
	FMT_D24X4S4 = 79,
	FMT_D16 = 80,

	FMT_D32F_LOCKABLE = 82,
	FMT_D24FS8 = 83,




	FMT_L16 = 81,

	FMT_VERTEXDATA = 100,
	FMT_INDEX16 = 101,
	FMT_INDEX32 = 102,

	FMT_Q16W16V16U16 = 110,

	FMT_MULTI2_ARGB8 = MAKEFOURCC('M', 'E', 'T', '1'),

	// Floating point surface formats

	// s10e5 formats (16-bits per channel)
	FMT_R16F = 111,
	FMT_G16R16F = 112,
	FMT_A16B16G16R16F = 113,

	// IEEE s23e8 formats (32-bits per channel)
	FMT_R32F = 114,
	FMT_G32R32F = 115,
	FMT_A32B32G32R32F = 116,

	FMT_CxV8U8 = 117,




	//FMT_FORCE_DWORD = 0x7fffffff
}; // end format definitions

//Custom Engine Read Only TRANSFORMSTATETYPE used by Renderer 
enum ETRANSFORMSTATETYPE {
	E_VIEW = 2,
	E_PROJECTION = 3,
	E_TEXTURE0 = 16,
	E_TEXTURE1 = 17,
	E_TEXTURE2 = 18,
	E_TEXTURE3 = 19,
	E_TEXTURE4 = 20,
	E_TEXTURE5 = 21,
	E_TEXTURE6 = 22,
	E_TEXTURE7 = 23,
	//E_FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
};

#define E_WORLDMATRIX(index) (ETRANSFORMSTATETYPE)(index + 256)
#define E_WORLD  E_WORLDMATRIX(0)

//Custom Engine Read Only POOL used by Renderer 
enum EPOOL
{
	EPOOL_DEFAULT = 0,
	EPOOL_MANAGED = 1,
	EPOOL_SYSTEMMEM = 2,
	EPOOL_SCRATCH = 3,

	//POOL_FORCE_DWORD = 0x7fffffff
}; // end pool definitions


//Custom Engine Read Only PRIMITIVETYPE used by Renderer 
enum EPRIMITIVETYPE {
	EPT_POINTLIST = 1,
	EPT_LINELIST = 2,
	EPT_LINESTRIP = 3,
	EPT_TRIANGLELIST = 4,
	EPT_TRIANGLESTRIP = 5,
	EPT_TRIANGLEFAN = 6,
	//EPT_FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
};

//Different types of Light objects can be
enum LIGHTTYPE
{
	DIVERGENT = 1,
	CONVERGENT = 2,
	PARALLEL = 3,
};

//Different types of Running State the Engine can have
enum ERUNSTATE {
	RUNNING = 1,
	PAUSED = 2,
	EXIT = 3,
	DEBUG = 4,
};

//Defines the type of Action. The action is used to relay to the listeners, if they have any input matching the requested action.
enum EACTION {
	ACTION_EXIT = 1,
	ACTION_XAXISMOVE = 2,
	ACTION_YAXISMOVE = 3,
	ACTION_ZAXISMOVE = 4,
	ACTION_PAUSE = 5,
	ACTION_ROTATECAMERA_X = 6,
	ACTION_ROTATECAMERA_Y = 7,
	ACTION_ZOOMCAMERA = 8,
	ACTION_SWITCHRENDERSTATE = 9,
	ACTION_TOGGLEDEBUG = 10,
};


#endif // end Edefinitions
