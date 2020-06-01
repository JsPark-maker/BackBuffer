#pragma once

class ScreenDib
{
public:
	ScreenDib(int iWidth, int iHeight, int iColorBit);
	~ScreenDib();
protected:
	void CreateDibBuffer(int iWidth, int iHeight, int iColorBit);
	void ReleaseDibBuffer();
public:
	void Flip(HWND hWnd, int iX = 0, int iY = 0);

	BYTE* GetDibBuffer();
	int GetWidth();
	int GetHeight();
	int GetPitch();
protected:
	BITMAPINFOHEADER	m_stDibInfo;
	BYTE*		m_bypBuffer;

	int			m_iWidth;
	int			m_iHeight;
	int			m_iPitch;	//4����Ʈ ���ĵ� �� ���� ����Ʈ ��
	int			m_iColorBit;
	int			m_iBufferSize;
};

