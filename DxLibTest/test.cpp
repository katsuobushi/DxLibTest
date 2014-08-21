#include <windows.h>
int i, r, a = 640, b = 400;
long t[11] = { 40, 640, 400, 2097153 };
char*k, y[0xfa000];

long WINAPI WndProc(HWND d, UINT m, UINT w, long l)
{//test
	PAINTSTRUCT p;
	switch (m){

	case 15: /* WM_PAINT */
		HBITMAP q;
		HDC e;
		e = CreateCompatibleDC(BeginPaint(d, &p));

		GetDIBits(e,
			(q = CreateCompatibleBitmap(p.hdc, a, b)), 0, b, 0, (BITMAPINFO*)t, 0);

		for (k = y; k<y + a*b * 4; k += 4)
			*k = *(k + 1) = *(k + 2) = (r = r * 9 + 5) >> 16;

		SetDIBitsToDevice(p.hdc, 0, 0, a, b, 0, 0, 0, b, y, (BITMAPINFO*)t, 0);
		DeleteObject(q);
		DeleteDC(e);
		EndPaint(d, &p);
		InvalidateRect(d, 0, 0);
		return 0;

	case 2: /* WM_DESTROY */
		PostQuitMessage(0);

	}
	return DefWindowProc(d, m, w, l);
}

int WINAPI WinMain(HINSTANCE i, HINSTANCE, LPSTR, int n)
{
	MSG m;
	WNDCLASS w;

	w.style = 3;
	w.lpfnWndProc = WndProc;
	w.cbWndExtra = w.cbClsExtra = 0;
	w.lpszMenuName = 0;
	w.hIcon = 0;
	w.hbrBackground = 0;
	w.hCursor = LoadCursor(0, IDC_ARROW);
	w.lpszClassName = "Tricky";
	w.hInstance = i;

	RegisterClass(&w);

	ShowWindow(CreateWindow("Tricky", "çª", 1 << 19, 99, 99, a, b, 0, 0, i, 0), n);

	while (GetMessage(&m, 0, 0, 0))
		DispatchMessage(&m);

	return 0;
}