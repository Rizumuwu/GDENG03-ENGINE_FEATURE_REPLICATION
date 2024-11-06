#include "Window.h"
#include "imgui.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

Window::Window() {

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	Window* window;

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	switch (msg) {
		case WM_CREATE:
			window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
			window->SetHWND(hwnd);
			window->OnCreate();
			break;
		case WM_SETFOCUS:
			window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->OnFocus();
			break;
		case WM_KILLFOCUS:
			window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->OnKillFocus();
			break;
		case WM_DESTROY:
			window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->OnDestroy();
			::PostQuitMessage(0);
			break;
		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;

	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", 
		WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	if (!m_hwnd)
		return false;

	// show window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_is_running = true;
	return true;
}

bool Window::broadcast() {

	MSG msg;

	this->OnUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);

	return true;
}

bool Window::release()
{
	//Destroy window
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::IsRunning()
{
	return m_is_running;
}

RECT Window::getClientWindowRect() {
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::SetHWND(HWND hwnd) {
	this->m_hwnd = hwnd;
}

void Window::OnCreate() {

}

void Window::OnUpdate() {

}

void Window::OnDestroy()
{
	m_is_running = false;
}

void Window::OnFocus() {

}

void Window::OnKillFocus() {

}

Window::~Window()
{
}
