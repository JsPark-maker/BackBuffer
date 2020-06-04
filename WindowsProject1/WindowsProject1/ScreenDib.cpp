#include "framework.h"
#include <iostream>
#include "ScreenDib.h"

//640, 480, 32
ScreenDib::ScreenDib(int iWidth, int iHeight, int iColorBit)
	//맴버변수 초기화
	:m_iWidth(iWidth), m_iHeight(iHeight), 
	m_iColorBit(iColorBit), m_iPitch(((iWidth * (iColorBit / 8)) + 3) & ~3)
{
	/*m_stDibInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_stDibInfo.bmiHeader.biWidth = iWidth;
	m_stDibInfo.bmiHeader.biHeight = iHeight;
	m_stDibInfo.bmiHeader.biBitCount = iColorBit;*/
	//Dib버퍼 생성
	CreateDibBuffer(iWidth, iHeight, iColorBit);
}

ScreenDib::~ScreenDib()
{
	delete[] m_bypBuffer;
}

void ScreenDib::CreateDibBuffer(int iWidth, int iHeight, int iColorBit)
{
	this->m_bypBuffer = new BYTE[m_iPitch * iHeight];
}

void ScreenDib::ReleaseDibBuffer()
{
}

void ScreenDib::Flip(HWND hWnd, int iX, int iY)
{
	HDC hdc = GetDC(hWnd);
	FILE* fp;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER fileInfo;

	_wfopen_s(&fp, L"download.bmp", L"rb");

	if (fp == nullptr)
	{
		MessageBoxW(NULL, L"sample2.bmp Open Error..", NULL, MB_OK);
		fclose(fp);
		return;
	}

	DWORD headerSize = sizeof(BITMAPFILEHEADER);
	DWORD infoSize = sizeof(BITMAPINFOHEADER);

	fread(&fileHeader, headerSize, 1, fp);
	fread(&fileInfo, infoSize, 1, fp);

	fseek(fp, fileHeader.bfOffBits, SEEK_SET);

	fread(m_bypBuffer, m_iHeight * m_iPitch, 1, fp);

	StretchDIBits(	
					hdc,
					iX,
					iY,
					m_iPitch,
					fileInfo.biHeight,
					0,
					0,
					m_iPitch,
					fileInfo.biHeight,
					m_bypBuffer,
					((LPBITMAPINFO)(&fileInfo)),
					DIB_RGB_COLORS,
					SRCCOPY
				);
	ReleaseDC(hWnd, hdc);

	fclose(fp);
}

BYTE* ScreenDib::GetDibBuffer()
{
	return this->m_bypBuffer;
}

int ScreenDib::GetWidth()
{
	return this->m_iWidth;
}

int ScreenDib::GetHeight()
{
	return this->m_iHeight;
}

int ScreenDib::GetPitch()
{
	return this->m_iHeight;
}
