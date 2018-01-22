#ifndef _APPLICATION_WINDOW_H_
#define _APPLICATION_WINDOW_H_

// Max window title and class name strings size. 
#define MAX_LOADSTRING 100
#include <Windows.h>

/* @brief WIN32 Window class. Supports creating and managing simple window. */
class ApplicationWindow
{
public:
	/* @brief Window object constructor.  
       
       @param hInstance Application instance handle which will be copied in internal instance handle.
       @param appTitle Application window title.
       @param wndClass optional parameter which contains user specific window class parameters.
       (i.e. setting user custom window message procedure). If this parameter is not given, default
       window class attributes are used.

       @note If user calls constructor with non-null window class pointer, he is responsible for
       all window class attributes proper setting.
       @note appTitle and wndClass strings must not be greater than MAX_LOADSTRING value.
    */
    ApplicationWindow(HINSTANCE hInstance, const TCHAR appTitle[], const WNDCLASSEX* wndClass = nullptr);

    /* @brief Window object default destructor is used. */
    ~ApplicationWindow(void) = default;
	
    /*  @brief Creating and optionaly opening application window in chosen mode.

        @param nCmdShow Window initial opening mode (i.e. fullscreen mode, normal or minimized mode).
        @param width Window width when window is shown in non fullscreen mode.
        @param height Window height when window is shown in non fullscreen mode.

        @return true on window successfull creation, false otherwise.
    */
    bool InitWindow(int nCmdShow, int width, int height);

    /* @brief Default window procedure which only handle window destroy message. 
        
       @param hWnd Window handle.
       @param message which determines which window event has occurred.
       @param wParam additional parameter whos meaning depends on type of event (i.e pressed key).
       @param lParam additional parameter whos meaning depends on type of event (i.e mouse cursor position).

       @return resulting code of message processing.
    */ 
	virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    /* @brief Application main loop. Runs application window message processing and graphics rendering
       until window close event is triggered.
    */
	virtual int Run();
protected:
	
    /* @brief Register window class, internally called in application constructor. 
       
       @param wndClass Optional window class pointer which describes window class. 
       If this parameter is not specified default window class attributes are used.

       @return Result of window class registration.
    */
	ATOM MyRegisterClass(const WNDCLASSEX* wndClass = nullptr);
	
    /* @brief Empty graphic rendering procedure. 
       
       @note Graphic rendering is not performed as this is windows class 
       and graphics rendering is not its part. Graphic rendering should be done
       in class which derives from this one (by overriding render function). 
    */
	virtual void Render();

	HWND hAppMainWindow_;							// Application window
	HINSTANCE hInst_;                               // Internal program instance
	TCHAR szTitle_[MAX_LOADSTRING];					// The title bar text
	TCHAR szWindowClass_[MAX_LOADSTRING];			// the main window class name
};

#endif // _APPLICATION_WINDOW_H_