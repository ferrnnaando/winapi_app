
//ferrnnaando
#define _WIN32_WINNT 0x501
#include "framework.h"
#include "winapi_app.h"
#include <string>
#include <commctrl.h> //Para parametros de progress bar
#include <shellapi.h>
#include <WinUser.h>
/*  Declaracion del procedimiento de windows  */
wchar_t loginUser[36];
wchar_t loginPass[36];
wchar_t regGmail[36];
wchar_t regUser[36];
wchar_t regPass[36];

#define MAX_LOADSTRING 100


// Variables globales:
HINSTANCE hInst;                           
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal
WNDCLASSEXW wcex;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM MyRegisterClass(HINSTANCE hInstance);
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

    // TODO: Colocar código aquí.
    // 

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIAPP));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
    wcex.cbSize = sizeof(WNDCLASSEX);


    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(16, 16, 16));
    wcex.lpszMenuName = nullptr;
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(nullptr, L"Envia esta referencia de error a nuestros desarrolladores:\n (err 37.324.2)\n\nhttps://discord.gg/xzMUbUdH3U", L"void* proyect", MB_OK | MB_ICONERROR);
        return 1;
    }
    else {
      
        return 0;
    }
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   
    hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_VISIBLE |  WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX,
      200, 200, 1200, 800, nullptr, nullptr, hInstance, nullptr);



   if (!hWnd)
   {
      return FALSE;
   }

   UpdateWindow(hWnd);

return TRUE;
}

//
//  PROPÓSITO: Procesa mensajes de la ventana principal.

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND ComeBackLogin, btnLogin, btnLogin2, btnSelect, hButton, TextFieldLoginUser, TextFieldLoginPass, hProgress;
    static HWND ComeBackReg, btnReg, btnReg2, TextFieldRegUser, TextFieldRegGmail, TextFieldRegPass, hProgressReg;
    static HWND closeAd, mensajeAd;
    static HWND credits, verOld, closeOld;

    static bool toggleAd = true;
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    unsigned int windowWidth = clientRect.right - clientRect.left;
    unsigned int windowHeight = clientRect.bottom - clientRect.top;

    unsigned int buttonWidthCloseAd = 45;
    unsigned int buttonWidth = 100;
    unsigned int buttonHeight = 20;
    unsigned int buttonX = windowWidth / 2;
    unsigned int buttonX2 = windowHeight / 2;

    // hay tres tipos de variaciones de la misma funcion: Function(), FunctionA() y Function

    switch (message) {

    case WM_CREATE:
    { 
        verOld = CreateWindowEx(0, L"BUTTON", L"Ver antiguo", WS_CHILD | WS_VISIBLE, 0, 750 - 40, 120, 35, hWnd, (HMENU)oldmenu, nullptr, nullptr); ///////////CHECK buttonHeight / 2
        mensajeAd = CreateWindowEx(0, L"STATIC", L"Obten la version de paga y deja de consumir anuncios. Totalmente brutal.", WS_CHILD | WS_VISIBLE, buttonX - buttonWidth, buttonHeight / 2, 500, 20, hWnd, nullptr, nullptr, nullptr);
        closeAd = CreateWindowEx(0, L"BUTTON", L"X", BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, clientRect.right - buttonWidthCloseAd, 0, buttonWidthCloseAd, 35, hWnd, (HMENU)closeAd_IDF, nullptr, nullptr);
        
        return 0;
    }
    
    break;
    case WM_COMMAND:
    {
        if (LOWORD(closeAd_IDF) == wParam) {
            toggleAd = !toggleAd;
            ShowWindow(closeAd, SW_HIDE);
            ShowWindow(mensajeAd, SW_HIDE);
            InvalidateRect(hWnd, nullptr, TRUE);
        } else if (LOWORD(wParam) == oldmenu) {
            ShowWindow(verOld, SW_HIDE);
            btnLogin = CreateWindowEx(0, L"BUTTON", L"Iniciar sesion", WS_TABSTOP | WS_CHILD | WS_VISIBLE, buttonX, 70, 130, 35, hWnd, (HMENU)btnLogin_IDF, nullptr, nullptr);
            btnReg = CreateWindowEx(0, L"BUTTON", L"Crear una cuenta", WS_TABSTOP | WS_CHILD | WS_VISIBLE, buttonX, 110, 130, 35, hWnd, (HMENU)btnRegister_IDF, nullptr, nullptr);
            credits = CreateWindowEx(0, L"BUTTON", L"Disclaimer (c)", WS_TABSTOP | WS_CHILD | WS_VISIBLE, buttonX + 5, 220, 110, 35, hWnd, (HMENU)CopyDisclaimer_IDF, nullptr, nullptr);
            closeOld = CreateWindowEx(0, L"BUTTON", L"Cerrar", WS_TABSTOP | WS_CHILD | WS_VISIBLE, 0, 750 - 40, 120, 35, hWnd, (HMENU)closeOld_IDF, nullptr, nullptr);
        }
        else if (LOWORD(closeOld_IDF) == wParam) {
            ShowWindow(closeOld, SW_HIDE);
            ShowWindow(btnLogin, SW_HIDE);
            ShowWindow(btnReg, SW_HIDE);
            ShowWindow(credits, SW_HIDE);
            ShowWindow(verOld, SW_SHOW);
        }
        else if (LOWORD(wParam) == btnLogin_IDF) {
            ShowWindow(btnLogin, SW_HIDE);
            ShowWindow(btnSelect, SW_HIDE);
            ShowWindow(btnReg, SW_HIDE);
            TextFieldLoginUser = CreateWindowEx(0, L"EDIT", L"Introduce un nombre de usuario.", BS_FLAT | WS_BORDER | WS_CHILD | WS_VISIBLE, buttonX, 80, 250, 25, hWnd, nullptr, nullptr, nullptr);
            TextFieldLoginPass = CreateWindowEx(0, L"EDIT", L"Introduce la contrasena.", WS_BORDER | WS_CHILD | WS_VISIBLE, buttonX, 110, 250, 25, hWnd, nullptr, nullptr, nullptr);

            
            ComeBackLogin = CreateWindowEx(0, L"BUTTON", L"Volver", BS_FLAT | WS_CHILD | WS_VISIBLE, buttonX + buttonWidth + 30, 145, 120, 25, hWnd, (HMENU)GoBackLogin_IDF, nullptr, nullptr);
            btnLogin2 = CreateWindowEx(0, L"BUTTON", L"Iniciar sesion", BS_FLAT | WS_CHILD | WS_VISIBLE, buttonX, 145, 120, 25, hWnd, (HMENU)btnLogin2_IDF, nullptr, nullptr);
            hProgress = CreateWindowEx(0, L"msctls_progress32", L"AAA", BS_FLAT | WS_CHILD | WS_VISIBLE, buttonX, 175, 250, 30, hWnd, nullptr, GetModuleHandle(nullptr), nullptr);

            SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
            SendMessage(hProgress, PBM_SETPOS, 40, 10);
        }
        else if (LOWORD(wParam) == GoBackLogin_IDF) {
            ShowWindow(ComeBackLogin, SW_HIDE);
            ShowWindow(btnLogin2, SW_HIDE);
            ShowWindow(TextFieldLoginUser, SW_HIDE);
            ShowWindow(TextFieldLoginPass, SW_HIDE);
            ShowWindow(hProgress, SW_HIDE);
            ShowWindow(btnLogin, SW_SHOW);
            ShowWindow(btnSelect, SW_SHOW);
            ShowWindow(btnReg, SW_SHOW);
        }
        else if (LOWORD(wParam) == btnLogin2_IDF) {
            GetWindowTextW(TextFieldLoginUser, loginUser, 36);
            GetWindowTextW(TextFieldLoginPass, loginPass, 36);

            // Verificar si se ingresaron valores en ambas ventanas
            if (std::wstring(loginUser) == L"Introduce un nombre de usuario." || std::wstring(loginPass) == L"Introduce la contrasena.") {
                MessageBoxW(hWnd, L"Los valores introducidos son incorrectos.\n\n- No pueden superar los 36 caracteres de longitud.\n- No pueden ser datos vacios o nulos.", L"void* proyect | Error", MB_OK | MB_ICONERROR);
            }
            else if (wcslen(loginUser) > 0 && wcslen(loginPass) > 0) {
                //MYSQL* connect;
              //connect = mysql_init(0);
              //connect = mysql_real_connect(connect, "sql8.freesqldatabase.com", "sql8627850", "iK6xe8xnbQ", "sql8627850", 3306, 0, nullptr);
              //mysql_query(connect, std::string("SELECT * FROM users").c_str());
                SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
                SendMessage(hProgress, PBM_SETPOS, 100, 10);
            }
        } 
        else if (LOWORD(wParam) == btnRegister_IDF) {
                ShowWindow(btnLogin, SW_HIDE);
                ShowWindow(btnSelect, SW_HIDE);
                ShowWindow(btnReg, SW_HIDE);

                TextFieldRegUser = CreateWindowEx(0, L"EDIT", L"Moóp´p Introduce un nombre de usuario.", WS_VISIBLE | WS_CHILD | WS_BORDER, buttonX, 60, 250, 25, hWnd, nullptr, nullptr, nullptr);
                TextFieldRegPass = CreateWindowEx(0, L"EDIT", L"Introduce una contrasena.", WS_BORDER | WS_CHILD | WS_VISIBLE, buttonX, 90, 250, 25, hWnd, nullptr, nullptr, nullptr);
                TextFieldRegGmail = CreateWindowEx(0, L"EDIT", L"Introduce un correo.", WS_BORDER | WS_CHILD | WS_VISIBLE, buttonX, 120, 250, 25, hWnd, nullptr, nullptr, nullptr);

                btnReg2 = CreateWindowEx(0, L"BUTTON", L"Crear cuenta", WS_CHILD | WS_VISIBLE, buttonX + buttonWidth + 30, 155, 120, 25, hWnd, (HMENU)btnLogin2_IDF, nullptr, nullptr);
                ComeBackReg = CreateWindowEx(0, L"BUTTON", L"Volver", WS_CHILD | WS_VISIBLE, buttonX, 155, 120, 25, hWnd, (HMENU)GoBackRegister_IDF, nullptr, nullptr);
                hProgressReg = CreateWindowEx(0, L"msctls_progress32", NULL, WS_CHILD | WS_VISIBLE, buttonX, 185, 250, 30, hWnd, nullptr, GetModuleHandle(nullptr), nullptr
                );

                // Establecer el rango de la barra de progreso
                SendMessage(hProgressReg, PBM_SETRANGE, 0, MAKELPARAM(0, 100));

                // Establecer el valor inicial de la barra de progreso
                SendMessage(hProgressReg, PBM_SETPOS, 20, 10);
        } 
        else if (LOWORD(wParam) == GoBackRegister_IDF) {
                ShowWindow(ComeBackReg, SW_HIDE);
                ShowWindow(btnReg2, SW_HIDE);
                ShowWindow(TextFieldRegUser, SW_HIDE);
                ShowWindow(TextFieldRegPass, SW_HIDE);
                ShowWindow(TextFieldRegGmail, SW_HIDE);
                ShowWindow(hProgressReg, SW_HIDE);
                ShowWindow(btnLogin, SW_SHOW);
                ShowWindow(btnSelect, SW_SHOW);
                ShowWindow(btnReg, SW_SHOW);
        }
        else if (LOWORD(wParam) == CopyDisclaimer_IDF) {
                ShellExecute(0, 0, L"https://discord.gg/bYDhwFFVk5", 0, 0, SW_SHOW);
                MessageBoxW(hWnd, L"void* proyect. (c) Todos los derechos reservados", L"void* proyect", MB_OK | MB_ICONEXCLAMATION);
        }

        return 0;
    }
        break;
   case WM_DRAWITEM: {
       // Personalizar el aspecto del botón
       LPDRAWITEMSTRUCT lpDrawItemStruct = reinterpret_cast<LPDRAWITEMSTRUCT>(lParam);
       HDC hdc = lpDrawItemStruct->hDC;

       // Establecer el fondo transparente
       SetBkMode(hdc, TRANSPARENT);

       // Dibujar el texto del botón
       WCHAR buttonText[] = L"X";
       DrawText(hdc, buttonText, lstrlen(buttonText), &(lpDrawItemStruct->rcItem), DT_CENTER | DT_VCENTER);

       break;
   }
    case WM_PAINT:
    
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

      if(toggleAd) {
          HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
          RECT rect;
          GetClientRect(hWnd, &rect);
          rect.left = 0;
          rect.top = 0;
          rect.right = windowWidth;
          rect.bottom = 35;
          FillRect(hdc, &rect, hBrush);
          DeleteObject(hBrush);
      }

      HICON hIcon = (HICON)LoadImage(NULL, L"D:\test.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
      if (hIcon)
      {
          DrawIcon(hdc, 10, 10, hIcon);
          DestroyIcon(hIcon);
      }


      ICONINFO iconInfo;
      GetIconInfo(hIcon, &iconInfo);
      HBITMAP hBitmap = iconInfo.hbmColor;

      // Crear un contexto de dispositivo compatible y seleccionar la imagen en él
      HDC hdcMem = CreateCompatibleDC(hdc);
      HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

      // Obtener las dimensiones de la imagen
      BITMAP bitmap;
      GetObject(hBitmap, sizeof(BITMAP), &bitmap);

      // Dibujar la imagen en el contexto de dispositivo principal
      BitBlt(hdc, 10, 10, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 10, 10, SRCCOPY);

      // Restaurar el contexto de dispositivo y liberar los recursos
      SelectObject(hdcMem, hOldBitmap);
      DeleteDC(hdcMem);
      DeleteObject(hBitmap);

        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_CTLCOLORBTN:
    {
        HBRUSH hBrushBtn;
        hBrushBtn = (HBRUSH)GetStockObject(NULL_BRUSH);
        SetBkMode((HDC)wParam, TRANSPARENT);
        return ((LRESULT)hBrushBtn);
    }
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0)); // Cambiar el color de texto aquí
        SetBkMode(hdcStatic, TRANSPARENT); // Establecer el modo de fondo transparente
        return (LRESULT)GetStockObject(NULL_BRUSH);
    }

    /*case WM_MOUSEMOVE:
    {   
        MessageBoxW(hWnd, L"A", L"A", MB_OK);
        return 0;
    }*/
        break;
    case WM_DESTROY:
    {
            PostQuitMessage(0);
        
    }
    break;


    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

