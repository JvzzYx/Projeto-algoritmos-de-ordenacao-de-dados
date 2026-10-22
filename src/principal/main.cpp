#include <windows.h>

int iniciarInterface(
    HINSTANCE hInstance,
    int nCmdShow
);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow
) {
    return iniciarInterface(
        hInstance,
        nCmdShow
    );
}