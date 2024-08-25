#include <windows.h>
#include <gl/gl.h>
#include <cmath>
#include <ctime>
#include "circle.h"
#include "Vector2.h"

#define W 500
#define H 500

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;


    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1000,
                          1000,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);


    Color col1(255, 0, 0);
    Color col2(0, 255, 0);
    Color col3(0, 0, 255);

    Circle c1(50, 250, 20, col1);
    Circle c2(100, 50, 20, col2);
    Circle c3(250, 250, 20, col3);

    Vector2 dc1(rand() % 10, rand() % 10);
    Vector2 dc2(rand() % 10, rand() % 10);
    Vector2 dc3(rand() % 10, rand() % 10);


    glLoadIdentity();
    glOrtho(0, W, 0, H, -1, 1);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);


            c1.draw();
            c2.draw();
           // c3.draw();

            //перша круг

            c1.x += dc1.x;
            c1.y += dc1.y;

            if( (c1.x + c1.r > W) || (c1.x - c1.r < 0) )
            {
                dc1.x = -dc1.x;
            }

            if( (c1.y + c1.r > H) || (c1.y - c1.r < 0) )
            {
                dc1.y = -dc1.y;
            }


            //другий круг

            c2.x += dc2.x;
            c2.y += dc2.y;

            if( (c2.x + c2.r > W) || (c2.x - c2.r < 0) )
            {
                dc2.x = -dc2.x;
            }

            if( (c2.y + c2.r > H) || (c2.y - c2.r < 0) )
            {
                dc2.y = -dc2.y;
            }

            //третій круг

            c3.x += dc3.x;
            c3.y += dc3.y;

            if( (c3.x + c3.r > W) || (c3.x - c3.r < 0) )
            {
                dc3.x = -dc3.x;
            }

            if( (c3.y + c3.r > H) || (c3.y - c3.r < 0) )
            {
                dc3.y = -dc3.y;
            }







            float dx = c1.x - c2.x;
            float dy = c1.y - c2.y;
            float d = sqrt(dx * dx + dy * dy);

            //if(d == 0) { d = 0.01; }  якщо координати однокаві до d = 0

            float s = dx / d;
            float e = dy / d;

            if(c1.r + c2.r > d)
            {
                float vn1 = dc2.x * s + dc2.y * e;
                float vn2 = dc1.x * s + dc1.y * e;

                float vt1 = -dc2.x * e + dc2.y * s;
                float vt2 = -dc1.x * e + dc1.y * s;

                float tmp = vn2;
                vn2 = vn1;
                vn1 = tmp;

                dc1.x = vn2 * s - vt2 * e;
                dc1.y = vn2 * e + vt2 * s;
                dc2.x = vn1 * s - vt1 * e;
                dc2.y = vn1 * e + vt1 * s;
            }

            SwapBuffers(hDC);
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

