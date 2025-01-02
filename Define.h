#pragma once
#define OCX		854
#define OCY		480
#define WINCX		860
#define WINCY		480
#define	PURE		= 0
#define PI			3.141592f
#define VK_MAX		0xff
#define OBJ_NOEVENT	0
#define OBJ_DEAD	1
#define SOUNDPATH	L"Assets/Sounds/"
#define	SPRITEPATH	L"Assets/Temp/"
#define	CHARACTERPATH	L"Assets/Temp/ObjectsCharacter.png";
#define PNG_EXTENSION L".png"
#define TARGETFPS 144
#define FRAMETIME 1.0f / TARGETFPS

#define	TILECX				24
#define	TILECY				24

#define TILEX				24
#define TILEY				18

#define BORDERCOLOR Color(255, 78, 98, 192)
#define FILLCOLOR Color(255, 43, 51, 92)

extern HWND g_hWnd;
extern bool g_bDevmode;
extern bool g_bAnimate;

enum class SCENEID
{
	Menu, Game, Test, Edit, End
};

enum class LEVELID
{

};

enum class STAGEID
{

};

enum class UITYPE
{
	None, Button, Panel, End
};

enum class CHANNELID
{
	SOUND_BGM, SOUND_EFFECT, END
};

enum OBJID
{
	BLOCK, PARTICLE, END
};

enum class BLOCKTYPE
{
	NONE, TEXT, CHARACTER, OBJECT, CURSOR, LEVEL, END
};

enum class DIRECTION
{
	NONE, LEFT, RIGHT, UP, DOWN
};

enum class TileState {
	NONE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	LEFT_RIGHT,
	LEFT_TOP,
	LEFT_BOTTOM,
	RIGHT_TOP,
	RIGHT_BOTTOM,
	TOP_BOTTOM,
	ALL
};

typedef struct tagInfo
{
	float fX, fY, fCX, fCY;
} INFO;

typedef struct tagFrame
{
	int		iFrameAnimation;
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;
	ULONG64	ullSpeed;
	ULONG64	ullTime;
} FRAME;

typedef struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString){}

public:
	template<typename T>
	bool	operator()(T& rObj)
	{
		return !lstrcmp(m_pString, rObj.first);
	}

private:
	const TCHAR* m_pString;
	
} FINDER;

typedef struct tagCharFinder
{
public:
	tagCharFinder(const TCHAR c) : m_Char(c) {}
	template<typename T>
	bool	operator()(T& rObj)
	{
		return (m_Char == rObj.first);
	}
private:
	const TCHAR m_Char;
} CHARFINDER;


// tagVector zero를 static 멤버로 선언하고 외부에서 초기화
#define Vector2_zero  Vector2(0, 0)
//const Vector2 Vector2::zero = Vector2(0, 0);

typedef struct tagVector
{
	float x, y;
	tagVector() : x(0.f), y(0.f) {}
	tagVector(float x, float y) : x(x), y(y) {}

	tagVector operator()(float x, float y) const
	{
		return tagVector(x, y);
	}
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

static void DrawRoundedRect(Gdiplus::Graphics* graphics, Gdiplus::Rect rect, int radius) {
	// GraphicsPath 객체 생성
	Gdiplus::GraphicsPath path;

	// 좌상단 모서리
	path.AddArc(rect.X, rect.Y, radius * 2, radius * 2, 180, 90);
	// 우상단 모서리
	path.AddArc(rect.X + rect.Width - radius * 2, rect.Y, radius * 2, radius * 2, 270, 90);
	// 우하단 모서리
	path.AddArc(rect.X + rect.Width - radius * 2, rect.Y + rect.Height - radius * 2, radius * 2, radius * 2, 0, 90);
	// 좌하단 모서리
	path.AddArc(rect.X, rect.Y + rect.Height - radius * 2, radius * 2, radius * 2, 90, 90);
	// 경로 닫기
	path.CloseFigure();

	// 펜 생성 (색상 및 두께 설정)
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0), 2);

	// 라운드 렉트 그리기
	graphics->DrawPath(&pen, &path);
}

static void HitBox(HDC hDC, Gdiplus::Rect& rect)
{
	//내부색
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	//외곽선
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	RECT rc{};
	rc.left = rect.X;
	rc.top = rect.Y;
	rc.right = rect.Width;
	rc.bottom = rect.Height;

	FrameRect(hDC, &rc, hBrush);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

static void FillRoundedRect(Gdiplus::Graphics* graphics, Gdiplus::Rect rect, int radius, Gdiplus::Color PenColor, Gdiplus::Color BrushColor) {
	// GraphicsPath 객체 생성
	Gdiplus::GraphicsPath path;

	// 좌상단 모서리
	path.AddArc(rect.X, rect.Y, radius * 2, radius * 2, 180, 90);
	// 우상단 모서리
	path.AddArc(rect.X + rect.Width - radius * 2, rect.Y, radius * 2, radius * 2, 270, 90);
	// 우하단 모서리
	path.AddArc(rect.X + rect.Width - radius * 2, rect.Y + rect.Height - radius * 2, radius * 2, radius * 2, 0, 90);
	// 좌하단 모서리
	path.AddArc(rect.X, rect.Y + rect.Height - radius * 2, radius * 2, radius * 2, 90, 90);
	// 경로 닫기
	path.CloseFigure();

	Gdiplus::SolidBrush brush(BrushColor);
	// 펜 생성 (색상 및 두께 설정)
	Gdiplus::Pen pen(Gdiplus::Color(PenColor), 2);

	graphics->FillPath(&brush, &path);
	// 라운드 렉트 그리기
	graphics->DrawPath(&pen, &path);
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