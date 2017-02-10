#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <d2d1.h>			// Direct2D
#include <wincodec.h>		// IWICImaging
#include <wincodecsdk.h>	// IWICImaging
#include <dwrite.h>			// Text
#include <queue>
#include <map>
#include "Math.h"
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")
using namespace D2D1;
using namespace std;



#define RENDER RenderManager::Instance()

enum ALIGN_TYPE
{
	ALIGN_LEFT = 0, ALIGN_CENTER = 1, ALIGN_RIGHT = 2,
};

enum GRAPHICS_TYPE
{
	GRAPHICS_NONE, GRAPHICS_LINE, GRAPHICS_RECT, GRAPHICS_CIRCLE,
};

struct Text
{
	wstring str;
	wstring fontName;
	float x, y;
	ColorF color;
	int size;
	ALIGN_TYPE align;

	void Render(ID2D1RenderTarget* pRenderTarget, IDWriteFactory* pFactory)
	{
		IDWriteTextFormat* pFormat;
		pFactory->CreateTextFormat(fontName.c_str(), 0,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size, L"ko", &pFormat
		);

		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(color, &pBrush);
		pRenderTarget->DrawTextW(str.c_str(), str.length(), pFormat,
			RectF(x, y, x + 300, y + 300), pBrush);
	}
};

struct GraphicsObject
{
	GRAPHICS_TYPE type;
	float x, y;
	float width, height;
	ColorF color;
	float lineSize;

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(color, &pBrush);

		switch (type)
		{
		case GRAPHICS_LINE:
			pRenderTarget->DrawLine(Point2F(x, y), Point2F(width, height), pBrush, lineSize); break;
		case GRAPHICS_RECT:
			if (lineSize == 0)
			{
				pRenderTarget->FillRectangle(RectF(x, y, x + width, y + height), pBrush);
				break;
			}
			else
			{
				pRenderTarget->DrawRectangle(RectF(x, y, x + width, y + height), pBrush, lineSize);
				break;
			}
		case GRAPHICS_CIRCLE:
			float radiusX = width * 0.5f;
			float radiusY = height * 0.5f;
			if (lineSize == 0)
			{
				pRenderTarget->FillEllipse(Ellipse(Point2F(x + radiusX, y + radiusY), radiusX, radiusY), pBrush);
				break;
			}
			else
			{
				pRenderTarget->DrawEllipse(Ellipse(Point2F(x + radiusX, y + radiusY), radiusX, radiusY), pBrush, lineSize);
				break;
			}
		}
	}
};

class Sprite
{
	ID2D1Bitmap* m_pImage;
	float m_x, m_y;
	float m_width;
	float m_height;
	float m_scale;
	float m_anchorX;
	float m_anchorY;
	int m_dir;

public:
	Sprite(ID2D1Bitmap* pImage, float scale = 1.0f,
		float anchorX = 0.5f, float anchorY = 0.5f)
	{
		m_pImage = pImage;
		m_width = pImage->GetSize().width;
		m_height = pImage->GetSize().height;
		m_scale = scale;
		m_anchorX = anchorX;
		m_anchorY = anchorY;
		m_dir = 1;
	}

	void SetPosition(float x, float y) { m_x = x; m_y = y; }
	void SetDirection(int dir) { m_dir = dir; }
	void SetSize(float w, float h) { m_width = w; m_height = h; }
	float GetLeftX() { return m_x - GetWidth() * m_anchorX; }
	float GetTopY() { return m_y - GetHeight() * m_anchorY; }
	float GetWidth() { return m_width * m_scale; }
	float GetHeight() { return m_height * m_scale; }

	void Render(ID2D1RenderTarget* pRenderTarget, float opacity = 1.0f)
	{
		Vector leftTop = Vector(GetLeftX(), GetTopY());
		Vector size = Vector(GetWidth(), GetHeight());

		// 스케일 적용
		pRenderTarget->SetTransform(Matrix3x2F::Scale(m_dir, 1.0f,
			Point2F(leftTop.x + size.x * 0.5f, leftTop.y + size.y * 0.5f)));

		// 비트맵 드로우
		pRenderTarget->DrawBitmap(m_pImage,
			RectF(leftTop.x, leftTop.y, leftTop.x + size.x, leftTop.y + size.y), opacity);

		// 스케일 초기화
		pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
};

class Camera
{
	ID2D1BitmapRenderTarget* m_pBitmapTarget;
	Vector m_size;
	Vector m_center;
	float m_opacity;
	D2D1_RECT_F m_screenRect;
	bool m_isWave;
	int  m_wavePower;
	int m_waveTimer;

public:
	Camera(ID2D1BitmapRenderTarget* pBitmapTarget, float sizeX, float sizeY)
	{
		m_pBitmapTarget = pBitmapTarget;
		m_pBitmapTarget->BeginDraw();
		m_pBitmapTarget->Clear(ColorF(0, 0, 0, 0));
		m_pBitmapTarget->EndDraw();
		m_size = Vector(sizeX, sizeY);
		m_opacity = 1.0f;
		m_isWave = false;
		m_wavePower = 20;
		SetCenterPos(Vector(0, 0));
		SetScreenRect(0.0f, 0.0f, sizeX, sizeY);
	}

	Vector GetPos() { return m_center; }
	Vector ScreenToWorldPos(Vector ScreenPos) { return ScreenPos + GetLeftTop(); }
	Vector WorldToScreenPos(Vector WorldPos) { return WorldPos - GetLeftTop(); }

	Vector GetLeftTop() { return m_center - m_size * 0.5f; }
	Vector GetRightBottom() { return m_center + m_size * 0.5f; }
	bool   GetIsWave() { return m_isWave; }
	void   SetIsWaveTrue() { m_isWave = true; }
	void SetOpacity(float opacity) { m_opacity = opacity; }
	void SetScreenRect(float x, float y, float width, float height)
	{
		m_screenRect = RectF(x, y, x + width, y + height);
	}
	void SetCenterPos(Vector center)
	{
		

		m_center = center;

		AlignLeftTop();
		AlignRightBottom();
	}

	void ShakingCamera(int wavePower)
	{
		
		int pattern = (int)timeGetTime() / 5 % 30 % 2;
		int waveCount1 = (int)timeGetTime() / 5 % 30 % 7;
		int waveCount2 = 7 - waveCount1;
		cout << m_waveTimer << endl;
		
		float wave1 = sin(waveCount1*1.0f) * powf(1.0f, waveCount1);
		float wave2 = sin(waveCount2*1.0f) * powf(0.5f, waveCount2);
		
		if (pattern == 0)SetCenterPos(Vector(m_center.x + wave1 * wavePower, m_center.y + wave2 * wavePower));
		if (pattern == 1)SetCenterPos(Vector(m_center.x + wave2 * wavePower, m_center.y + wave1 * wavePower));


		m_waveTimer += pattern;
		if (m_waveTimer >= 8)
		{
			m_isWave = false;
			m_waveTimer = 0;
		}
	}


	void AlignLeftTop()
	{
		D2D1_SIZE_F bitmapSize = m_pBitmapTarget->GetSize();

		Vector leftTop = GetLeftTop();
		leftTop.x = MATH->Clamp(leftTop.x, 0.0f, bitmapSize.width);
		leftTop.y = MATH->Clamp(leftTop.y, 0.0f, bitmapSize.height);
		m_center = leftTop + m_size * 0.5f;
	}

	void AlignRightBottom()
	{
		D2D1_SIZE_F bitmapSize = m_pBitmapTarget->GetSize();

		Vector rightBottom = GetRightBottom();
		rightBottom.x = MATH->Clamp(rightBottom.x, 0.0f, bitmapSize.width);
		rightBottom.y = MATH->Clamp(rightBottom.y, 0.0f, bitmapSize.height);
		m_center = rightBottom - m_size * 0.5f;
	}

	void Draw(Sprite* sprite, Vector pos, int dir = -1, float opacity = 1.0f)
	{
		m_pBitmapTarget->BeginDraw();

		sprite->SetPosition(pos.x, pos.y);
		sprite->SetDirection(dir);
		sprite->Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawLine(Vector startPos, Vector endPos, ColorF color = ColorF::Black, float lineSize = 1)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject circle = { GRAPHICS_LINE, startPos.x, startPos.y, endPos.x, endPos.y, color, lineSize };
		circle.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawRect(Vector leftTop, Vector size,
		ColorF color = ColorF::Black, float lineSize = 1)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject rect = { GRAPHICS_RECT, leftTop.x, leftTop.y, size.x, size.y, color, lineSize };
		rect.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawCircle(Vector center, float radius, ColorF color = ColorF::Black, float lineSize = 1)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject circle = { GRAPHICS_CIRCLE, center.x, center.y, radius, radius, color, lineSize };
		circle.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawFillCircle(Vector center, float radius, ColorF color = ColorF::Black)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject circle = { GRAPHICS_CIRCLE, center.x, center.y, radius, radius, color, 0 };
		circle.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawFilledRect(Vector leftTop, Vector size, ColorF color = ColorF::Black)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject rect = { GRAPHICS_RECT, leftTop.x, leftTop.y, size.x, size.y, color, 0 };
		rect.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1Bitmap* pBitmap = NULL;
		m_pBitmapTarget->GetBitmap(&pBitmap);

		Vector leftTop = GetLeftTop();
		pRenderTarget->DrawBitmap(pBitmap,
			m_screenRect, m_opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			RectF(leftTop.x, leftTop.y, leftTop.x + m_size.x, leftTop.y + m_size.y));

		m_pBitmapTarget->BeginDraw();
		m_pBitmapTarget->Clear(ColorF(0, 0, 0, 0));
		m_pBitmapTarget->EndDraw();
	}
};

class RenderManager : public Singleton<RenderManager>
{
	ID2D1Factory*			m_pFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;

	IWICImagingFactory*		m_pImageFactory;

	IDWriteFactory*			m_pDWriteFactory;

	HWND				m_hWnd;

	map<wstring, ID2D1Bitmap*> m_images;
	map<int, Camera*> m_cameras;
	queue<Sprite*> m_queSprite;
	queue<Text> m_queText;
	queue<GraphicsObject> m_queGraphics;

public:
	void Init(HWND hWnd)
	{
		m_hWnd = hWnd;

		// 화면 사이즈
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2D1_SIZE_U size = SizeU(rc.right - rc.left, rc.bottom - rc.top);

		// D2D1Factory 생성
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

		// HwndRenderTarget 생성
		m_pFactory->CreateHwndRenderTarget(
			RenderTargetProperties(),
			HwndRenderTargetProperties(hWnd, size),
			&m_pRenderTarget);

		// WICImagingFactory 생성
		CoInitialize(NULL);
		CoCreateInstance(CLSID_WICImagingFactory, NULL,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));

		// DWriteFactory 생성
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(*m_pDWriteFactory),
			(IUnknown**)&m_pDWriteFactory);
	}

	void Release()
	{
	}

	Camera* CreateCamera(int tag, float maxSizeX, float maxSizeY, float sizeX, float sizeY)
	{
		if (m_cameras.find(tag) != m_cameras.end()) return NULL;

		ID2D1BitmapRenderTarget* pCameraTarget = NULL;
		m_pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(maxSizeX, maxSizeY), &pCameraTarget);
		m_cameras[tag] = new Camera(pCameraTarget, sizeX, sizeY);
		return m_cameras[tag];
	}

	Camera* GetCamera(int tag)
	{
		if (m_cameras.find(tag) == m_cameras.end()) return NULL;
		return m_cameras[tag];
	}

	void DestroyCamera(int tag)
	{
		Camera* pCamera = GetCamera(tag);
		if (pCamera != NULL)
		{
			m_cameras.erase(tag);
			delete pCamera;
		}
	}

	void LoadImageFile(wstring key, wstring filename)
	{
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pFrameDecode = NULL;
		IWICFormatConverter* pConverter = NULL;
		ID2D1Bitmap* pBitmap = NULL;

		if (m_images.find(key) == m_images.end())
		{
			// 이미지 파일을 Decoding
			m_pImageFactory->CreateDecoderFromFilename(filename.c_str(), NULL,
				GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
			pDecoder->GetFrame(0, &pFrameDecode);

			// Converter 생성 및 초기화
			m_pImageFactory->CreateFormatConverter(&pConverter);
			pConverter->Initialize(pFrameDecode, GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);

			// Bitmap으로 변환 및 생성
			m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &pBitmap);
			m_images[key] = pBitmap;
		}
	}

	void LoadImageFiles(wstring key, wstring filename, wstring extension, int count)
	{
		TCHAR strKey[100] = {};
		TCHAR strName[100] = {};
		for (int i = 0; i < count; i++)
		{
			wsprintf(strKey, TEXT("%s%d"), key.c_str(), i);
			wsprintf(strName, TEXT("%s%d.%s"), filename.c_str(), i, extension.c_str());
			LoadImageFile(strKey, strName);
		}
	}

	


	ID2D1Bitmap* GetImage(wstring key)
	{
		if (m_images.find(key) == m_images.end()) return NULL;
		return m_images[key];
	}

	void Draw(Sprite* pSprite, float x, float y, int dir = 1)
	{
		if (pSprite != NULL)
		{
			pSprite->SetPosition(x, y);
			pSprite->SetDirection(dir);
			m_queSprite.push(pSprite);
		}
	}

	void Draw(wstring str, float x, float y, ColorF color = ColorF::Black,
		int size = 10, ALIGN_TYPE align = ALIGN_LEFT,
		wstring fontName = TEXT("Arial"))
	{
		Text text = { str, fontName, x, y, color, size, align };
		m_queText.push(text);
	}

	void Draw(Box box, ColorF color, float lineSize = 1)
	{
		DrawLine(box.LeftTop(), box.RightTop(), color, lineSize);
		DrawLine(box.LeftTop(), box.LeftBottom(), color, lineSize);
		DrawLine(box.RightBottom(), box.RightTop(), color, lineSize);
		DrawLine(box.RightBottom(), box.LeftBottom(), color, lineSize);
	}

	void DrawLine(Vector startPos, Vector endPos,
		ColorF color = ColorF::Black, float lineSize = 1)
	{
		GraphicsObject line = { GRAPHICS_LINE, startPos.x, startPos.y,
			endPos.x - startPos.x, endPos.y - startPos.y, color, lineSize };
		m_queGraphics.push(line);
	}

	void DrawRect(float x, float y, float width, float height,
		ColorF color = ColorF::Black, float lineSize = 1)
	{
		GraphicsObject rect = { GRAPHICS_RECT, x, y, width, height, color, lineSize };
		m_queGraphics.push(rect);
	}

	void DrawCircle(Vector center, float radius,
		ColorF color = ColorF::Black, float lineSize = 1)
	{
		GraphicsObject rect = { GRAPHICS_CIRCLE, center.x, center.y, radius,radius, color, lineSize };
		m_queGraphics.push(rect);
	}

	void Render(HDC hdc)
	{
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->Clear(ColorF(ColorF::Black));

		// 카메라 출력
		map<int, Camera*>::iterator it;
		for (it = m_cameras.begin(); it != m_cameras.end(); it++)
		{
			it->second->Render(m_pRenderTarget);
		}

		// 스프라이트 출력
		while (m_queSprite.size() > 0)
		{
			Sprite* pSprite = m_queSprite.front();
			pSprite->Render(m_pRenderTarget);
			m_queSprite.pop();
		}

		// 도형 출력
		while (m_queGraphics.size() > 0)
		{
			m_queGraphics.front().Render(m_pRenderTarget);
			m_queGraphics.pop();
		}

		// 텍스트 출력
		while (m_queText.size() > 0)
		{
			m_queText.front().Render(m_pRenderTarget, m_pDWriteFactory);
			m_queText.pop();
		}

		m_pRenderTarget->EndDraw();
	}
};