// FiveFunctionCalculator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "FiveFunctionCalculator.h"
#include <string>
#include "Calculate.h"

#define MAX_LOADSTRING 100
#define BUTTON0_ID 1000
#define BUTTON1_ID 1001
#define BUTTON2_ID 1002
#define BUTTON3_ID 1003
#define BUTTON4_ID 1004
#define BUTTON5_ID 1005
#define BUTTON6_ID 1006
#define BUTTON7_ID 1007
#define BUTTON8_ID 1008
#define BUTTON9_ID 1009
#define DISPLAY_PANEL 1010
#define BUTTON_DECIMAL_ID 1011
#define BUTTON_EQUALS_ID 1012
#define BUTTON_PERCENT_ID 1013
#define BUTTON_MULT_ID 1014
#define BUTTON_DIV_ID 1015
#define BUTTON_ADD_ID 1016
#define BUTTON_SUB_ID 1017
#define BUTTON_C_ID 1018
#define BUTTON_CE_ID 1019

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd; // main window
HWND hwndButton0, hwndButton1, hwndButton2, hwndButton3, hwndButton4, hwndButton5, hwndButton6, hwndButton7, hwndButton8, hwndButton9; // Number buttons
HWND displayPanel; // Display panel
HWND hwndButtonDecimal, hwndButtonEquals, hwndButtonPercent, hwndButtonMult, hwndButtonDiv, hwndButtonAdd, hwndButtonSub, hwndButtonC, hwndButtonCE; // Operator buttons

Calculate calculateObj; // Object for the logic of the calulator
std::wstring displayWStr;
LPCWSTR displayLPCWSTR;

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FIVEFUNCTIONCALCULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIVEFUNCTIONCALCULATOR));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIVEFUNCTIONCALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FIVEFUNCTIONCALCULATOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      750, 300, 360, 440, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        hwndButton1 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"1",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            260,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON1_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton2 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"2",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            70,         // x position 
            260,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON2_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton3 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"3",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            130,         // x position 
            260,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON3_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton4 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"4",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            200,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON4_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton5 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"5",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            70,         // x position 
            200,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON5_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton6 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"6",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            130,         // x position 
            200,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON6_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton7 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"7",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            140,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON7_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton8 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"8",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            70,         // x position 
            140,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON8_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton9 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"9",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            130,         // x position 
            140,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON9_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButton0 = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"0",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            320,         // y position 
            110,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON0_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        displayWStr = std::to_wstring(calculateObj.GetDisplay());
        displayLPCWSTR = displayWStr.c_str();
        displayPanel = CreateWindowW(
            L"STATIC",  // Predefined class; Unicode assumed 
            displayLPCWSTR,      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
            10,         // x position 
            80,         // y position 
            320,        // width
            50,        // height
            hWnd,     // Parent window
            (HMENU)DISPLAY_PANEL,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonDecimal = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L".",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            130,         // x position 
            320,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_DECIMAL_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonEquals = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"=",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            220,         // x position 
            320,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_EQUALS_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonPercent = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"%",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            280,         // x position 
            320,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_PERCENT_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonMult = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"*",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            220,         // x position 
            260,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_MULT_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonDiv = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"/",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            280,         // x position 
            260,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_DIV_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonAdd = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"+",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            220,         // x position 
            200,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_ADD_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonSub = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"-",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            280,         // x position 
            200,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_SUB_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonC = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"C",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            220,         // x position 
            140,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_C_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        hwndButtonCE = CreateWindowW(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"CE",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            280,         // x position 
            140,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)BUTTON_CE_ID,       // Button menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case BUTTON1_ID:
                calculateObj.NumberPress(1);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON2_ID:
                calculateObj.NumberPress(2);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON3_ID:
                calculateObj.NumberPress(3);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON4_ID:
                calculateObj.NumberPress(4);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON5_ID:
                calculateObj.NumberPress(5);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON6_ID:
                calculateObj.NumberPress(6);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON7_ID:
                calculateObj.NumberPress(7);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON8_ID:
                calculateObj.NumberPress(8);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON9_ID:
                calculateObj.NumberPress(9);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON0_ID:
                calculateObj.NumberPress(0);
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
                break;
            case BUTTON_ADD_ID:
                calculateObj.OperatorPress(1);
                break;
            case BUTTON_SUB_ID:
                calculateObj.OperatorPress(2);
                break;
            case BUTTON_MULT_ID:
                calculateObj.OperatorPress(3);
                break;
            case BUTTON_DIV_ID:
                calculateObj.OperatorPress(4);
                break;
            case BUTTON_EQUALS_ID:
                calculateObj.EqualsPress();
                displayWStr = std::to_wstring(calculateObj.GetDisplay());
                displayLPCWSTR = displayWStr.c_str();
                displayPanel = CreateWindowW(
                    L"STATIC",  // Predefined class; Unicode assumed 
                    displayLPCWSTR,      // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,  // Styles 
                    10,         // x position 
                    80,         // y position 
                    320,        // Button width
                    50,        // Button height
                    hWnd,     // Parent window
                    (HMENU)DISPLAY_PANEL,       // Button menu.
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                    NULL);      // Pointer not needed.
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

            TCHAR greeting[] = _T("Calculator");

            // TODO: Add any drawing code that uses hdc here...
            TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

            auto test = std::to_wstring(123);
            int test2a = 1234;
            LPCWSTR test2b = test.c_str();
            TextOut(hdc, 200, 5, test2b, _tcslen(test2b));
            //TextOut(hdc, 200, 5, test2b, _tcslen(test2b));

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

// Message handler for about box.
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