#include <windows.h>
#include <string>
#include "cert_operations.h"

#define IDC_CERT_NAME 301
#define IDC_GEN_CSR 302
#define IDC_SIGN_CERT 303

// Обработчик сообщений окна
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit, hBtnGenCSR, hBtnSignCert;
    char certName[256] = "";

    switch (message)
    {
    case WM_CREATE:
        CreateWindowA("STATIC", "Введите имя сертификата:", WS_VISIBLE | WS_CHILD,
            20, 20, 200, 20, hWnd, NULL, NULL, NULL);

        hEdit = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 50, 200, 20, hWnd, (HMENU)IDC_CERT_NAME, NULL, NULL);

        hBtnGenCSR = CreateWindowA("BUTTON", "Создать CSR", WS_VISIBLE | WS_CHILD,
            20, 80, 140, 30, hWnd, (HMENU)IDC_GEN_CSR, NULL, NULL);

        hBtnSignCert = CreateWindowA("BUTTON", "Подписать сертификат", WS_VISIBLE | WS_CHILD,
            180, 80, 180, 30, hWnd, (HMENU)IDC_SIGN_CERT, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_GEN_CSR)
        {
            GetWindowTextA(hEdit, certName, 256);
            if (strlen(certName) > 0) {
                generateCSR(certName);
            }
            else {
                MessageBoxA(hWnd, "Введите имя сертификата!", "Ошибка", MB_OK | MB_ICONERROR);
            }
        }
        else if (LOWORD(wParam) == IDC_SIGN_CERT)
        {
            GetWindowTextA(hEdit, certName, 256);
            if (strlen(certName) > 0) {
                signCertificate(certName);
            }
            else {
                MessageBoxA(hWnd, "Введите имя сертификата!", "Ошибка", MB_OK | MB_ICONERROR);
            }
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CertWindow";
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowA("CertWindow", "Сертификаты PKI", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
