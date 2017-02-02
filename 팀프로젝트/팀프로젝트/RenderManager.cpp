#include "RenderManager.h"


void RenderManager::Init(HWND hWnd)
{
	// ID2D1Factory 积己
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	// HwndRenderTarget 积己
	m_pFactory->CreateHwndRenderTarget(
		RenderTargetProperties(),
		HwndRenderTargetProperties(hWnd, SizeU(VIEW_WIDTH, VIEW_HEIGHT)),
		&m_pRenderTarget);

	// DWriteFactory 积己
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(*m_pWriteFactory),
		(IUnknown**)&m_pWriteFactory);
}

void RenderManager::Release()
{
	RELEASE_OBJECT(m_pWriteFactory);
	RELEASE_OBJECT(m_pRenderTarget);
	RELEASE_OBJECT(m_pFactory);
}

void RenderManager::Draw(wstring text, Vector pos, float size, ColorF color, TEXT_ALIGN align , wstring font )
{
	IDWriteTextFormat* pFormat = NULL;
	m_pWriteFactory->CreateTextFormat(font.c_str(), 0,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size, TEXT("ko"), &pFormat);

	pFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)align);
	m_queGraphics.push(new GText(pFormat, text, pos, size, color));
}

void RenderManager::DrawLine(Vector startPos, Vector endPos, ColorF color , float lineSize )
{
	m_queGraphics.push(new GLine(startPos, endPos, color, lineSize));
}

void RenderManager::FillRect(Vector center, Vector size, ColorF color )
{
	m_queGraphics.push(new GRect(center, size, color, 0));
}

void RenderManager::DrawRect(Vector center, Vector size, ColorF color , float lineSize )
{
	m_queGraphics.push(new GRect(center, size, color, lineSize));
}

void RenderManager::FillCircle(Vector center, float radius, ColorF color )
{
	m_queGraphics.push(new GCircle(center, radius, color, 0));
}

void RenderManager::DrawCircle(Vector center, float radius, ColorF color , float lineSize )
{
	m_queGraphics.push(new GCircle(center, radius, color, lineSize));
}

void RenderManager::Render()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear();

	// 档屈 免仿
	while (m_queGraphics.size() > 0)
	{
		m_queGraphics.front()->Render(m_pRenderTarget);
		delete m_queGraphics.front();
		m_queGraphics.pop();
	}

	m_pRenderTarget->EndDraw();
}