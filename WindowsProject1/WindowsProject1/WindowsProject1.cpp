// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <iostream>
#include "framework.h"
#include "WindowsProject1.h"
#include "ScreenDib.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
void BitMap(HWND hWnd);
ScreenDib screenDib(259, 194, 24);

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    //memset(screenDib.GetDibBuffer(), 0, screenDib.GetPitch() * screenDib.GetHeight());

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    //while (1) 
    //{
    //    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
    //    {
    //        if (msg.message == WM_QUIT)
    //            break;

    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //    else 
    //    {
    //        //
    //    }
    //}

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            screenDib.Flip(hWnd, 300, 300);
            //BitMap(hWnd);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void BitMap(HWND hWnd)
{
    FILE* pBmpFile;
    HDC hdc = GetDC(hWnd);
    _wfopen_s(&pBmpFile, L"download.bmp", L"rb");
    if (pBmpFile == nullptr)
    {
        MessageBoxW(NULL, L"sample2.bmp Open Error..", NULL, MB_OK);
        fclose(pBmpFile);
        return;
    }

    BITMAPFILEHEADER bitmapFileHeader;
    BITMAPINFOHEADER bitmapInfoHeader;

    DWORD headerSize = sizeof(BITMAPFILEHEADER);
    DWORD infoSize = sizeof(BITMAPINFOHEADER);
    fread(&bitmapFileHeader, headerSize, 1, pBmpFile);
    fread(&bitmapInfoHeader, infoSize, 1, pBmpFile);

    LONG lWidth = bitmapInfoHeader.biWidth * (bitmapInfoHeader.biBitCount / 8);
    int iPitch = (lWidth + 3) & ~3;

    int iImageSize = iPitch * bitmapInfoHeader.biHeight;

    BYTE* pImage = new BYTE[iImageSize];

    fseek(pBmpFile, bitmapFileHeader.bfOffBits, SEEK_SET);

    fread(pImage, iImageSize, 1, pBmpFile);

    fclose(pBmpFile);

    StretchDIBits
    (
        hdc,                                    // 목적지 DC
        40,                                      // x 좌표
        0,                                      // y 좌표
        iPitch,                                 // 목적지 너비
        bitmapInfoHeader.biHeight,              // 목적지 높이
        40,                                      // 출력소스 x 좌표
        0,                                      // 출력소스 y 좌표
        iPitch,                                 // 출력소스 너비
        bitmapInfoHeader.biHeight,              // 출력소스 높이
        pImage,                                 // 이미지가 위치한 포인터
        (LPBITMAPINFO)(&bitmapInfoHeader),      // BITMAPINFO = (BITMAPINFOHEADER + RGBQUAD) -> type캐스팅 해야한다. 
        DIB_RGB_COLORS,                         // DIB_RGB_COLORS
        SRCCOPY                                 // 출력모드
    );

    // 동적 할당 해제
    delete[] pImage;
    ReleaseDC(hWnd, hdc);
    return;
}
