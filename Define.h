#pragma once
#define WINCX		1280
#define WINCY		720
#define	PURE		= 0
#define PI			3.141592f
#define VK_MAX		0xff
#define OBJ_NOEVENT	0
#define OBJ_DEAD	1
#define SOUNDPATH	"../../NoitaClone/Sounds/"
#define	SPRITEPATH	L"../../NoitaClone/Assets"
#define SAMPLESOUND	L"../../NoitaClone/Sounds/music/00.wav"
#define PLAYERSPRITE L"../../NoitaClone/Assets/enemies_gfx/player_old"
#define PLAYERHOTSPOT L"../../NoitaClone/Assets/ragdolls/player/filenames.txt"
#define PNG_EXTENSION L".png"
#define TARGETFPS 60
#define FRAMETIME 1.0f / TARGETFPS
#define FIXEDUPDATETIME 0.05f

extern HWND g_hWnd;
extern bool g_bDevmode;

enum class SCENEID
{
	Menu, Game, Test, Edit, End
};

enum OBJID
{
	None, Player, Test, Edit, End
};

typedef struct tagInfo
{
	float fX, fY, fCX, fCY;
} INFO;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;
	ULONG64	ullSpeed;
	ULONG64	ullTime;
} FRAME;

typedef struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& rObj)
	{
		return !lstrcmp(m_pString, rObj.first);
	}

private:
	const TCHAR* m_pString;
} FINDER;

typedef struct tagVector
{
	#define Vector2_zero Vector2(0, 0);
	float x, y;
} Vector2;

template<typename T>
void SafeDelete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct DeleteMap
{
public:
	template<typename T>
	void	operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};


static float Lerp(float start, float end, float t) {
	return start + (end - start) * t;
}

static void ChangeImageColor(Gdiplus::Image*& image, Gdiplus::Color color)
{
	Gdiplus::ColorMatrix colorMatrix = {
	color.GetR() / 255.f, 0.0f, 0.0f, 0.0f, 0.0f,  // 빨간색
	0.0f, color.GetG() / 255.f, 0.0f, 0.0f, 0.0f,  // 녹색
	0.0f, 0.0f, color.GetB() / 255.f, 0.0f, 0.0f,  // 파란색
	0.0f, 0.0f, 0.0f, color.GetA(), 0.0f,  // 알파
	0.0f, 0.0f, 0.0f, 0.0f, 1.0f   // w
	};

	Gdiplus::ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix);
	// 새로운 Bitmap 객체 생성 (힙에 할당)
	Gdiplus::Bitmap* newBitmap = new Gdiplus::Bitmap(image->GetWidth(), image->GetHeight(), PixelFormat32bppARGB);

	// Graphics 객체 생성
	Gdiplus::Graphics graphics(newBitmap);

	// ImageAttributes를 사용하여 이미지 그리기
	graphics.DrawImage(
		image,
		Gdiplus::Rect(0, 0, image->GetWidth(), image->GetHeight()), // 대상 사각형
		0, 0, image->GetWidth(), image->GetHeight(),      // 소스 사각형
		Gdiplus::UnitPixel,
		&imageAttributes);

	// 메모리 해제
	SafeDelete<Gdiplus::Image*>(image);
	image = newBitmap;
}