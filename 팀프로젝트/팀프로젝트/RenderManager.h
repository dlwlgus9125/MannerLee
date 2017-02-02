#pragma once
#include "Common.h"
#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")
using namespace D2D1;

#define RENDER RenderManager::Instance()

enum TEXT_ALIGN
{
	TEXT_ALIGN_LEFT = 0, TEXT_ALIGN_RIGHT = 1, TEXT_ALIGN_CENTER = 2,
};

class IGraphics
{
public:
	virtual void Render(ID2D1RenderTarget* pRenderTarget) {}
};

class GText : public IGraphics
{
	IDWriteTextFormat* m_pFormat;
	wstring m_text;
	Vector m_pos;
	ColorF m_color;
	float m_size;

public:
	GText(IDWriteTextFormat* pFormat, wstring text, Vector pos
		, float size, ColorF color) : m_color(color)
	{
		m_pFormat = pFormat;
		m_text = text;
		m_pos = pos;
		m_size = size;
	}

	~GText() { RELEASE_OBJECT(m_pFormat); }

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		D2D1_RECT_F rect = RectF(m_pos.x, m_pos.y, m_pos.x + 500, m_pos.y);

		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);
		pRenderTarget->DrawTextW(m_text.c_str(), m_text.length(), m_pFormat, rect, pBrush);
		RELEASE_OBJECT(pBrush);
	}
};

class GLine : public IGraphics
{
	Vector m_start, m_end;
	ColorF m_color;
	float m_lineSize;

public:
	GLine(Vector start, Vector end, ColorF color, float lineSize) : m_color(color)
	{
		m_start = start;
		m_end = end;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D2D1_POINT_2F startPos = Point2F(m_start.x, m_start.y);
		D2D1_POINT_2F endPos = Point2F(m_end.x, m_end.y);
		pRenderTarget->DrawLine(startPos, endPos, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};

class GRect : public IGraphics
{
	Vector m_center, m_size;
	ColorF m_color;
	float m_lineSize;

public:
	GRect(Vector center, Vector size, ColorF color, float lineSize) : m_color(color)
	{
		m_center = center;
		m_size = size;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		Vector leftTop = m_center - m_size * 0.5f;
		Vector rightBottom = m_center + m_size * 0.5f;
		D2D1_RECT_F rect = RectF(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

		if (m_lineSize == 0) pRenderTarget->FillRectangle(rect, pBrush);
		else pRenderTarget->DrawRectangle(rect, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};

class GCircle : public IGraphics
{
	Vector m_center;
	float m_radius;
	ColorF m_color;
	float m_lineSize;

public:
	GCircle(Vector center, float radius, ColorF color, float lineSize) : m_color(color)
	{
		m_center = center;
		m_radius = radius;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D2D1_POINT_2F center = Point2F(m_center.x, m_center.y);
		D2D1_ELLIPSE ellipse = Ellipse(center, m_radius, m_radius);

		if (m_lineSize == 0) pRenderTarget->FillEllipse(ellipse, pBrush);
		else pRenderTarget->DrawEllipse(ellipse, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};

class RenderManager : public Singleton<RenderManager>
{
	ID2D1Factory*			m_pFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	IDWriteFactory*			m_pWriteFactory;

	queue<IGraphics*>		m_queGraphics;

public:
	void Init(HWND hWnd);

	void Release();

	void Draw(wstring text, Vector pos, float size = 10, ColorF color = ColorF::White,
		TEXT_ALIGN align = TEXT_ALIGN_LEFT, wstring font = TEXT("Arial"));

	void DrawLine(Vector startPos, Vector endPos, ColorF color = ColorF::White, float lineSize = 1);

	void FillRect(Vector center, Vector size, ColorF color = ColorF::White);

	void DrawRect(Vector center, Vector size, ColorF color = ColorF::White, float lineSize = 1);

	void FillCircle(Vector center, float radius, ColorF color = ColorF::White);

	void DrawCircle(Vector center, float radius, ColorF color = ColorF::White, float lineSize = 1);

	void Render();
};