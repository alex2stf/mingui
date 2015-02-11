/*
 * MinGUI.h
 *
 *  Created on: Feb 9, 2015
 *      Author: alexandru
 */

#ifndef MINGUI_H_
#define MINGUI_H_
#include <stdlib.h>
//#include "Macros.h"


enum DialogFlags {
	DG_DEFAULT,
	DG_OK_WARNING,
	DG_OK_ERROR,
	DG_OK_INFO,
	DG_OKCANCEL,
	DG_OKCANCEL_WARNING,
	DG_OKCANCEL_ERROR,
	DG_OKCANCEL_INFO,
	DG_YESNO,
	DG_YESNO_WARNING,
	DG_YESNO_ERROR,
	DG_YESNO_INFO,
};


#ifdef ASTOX_OS_WINDOWS
	#include <windows.h>
	#include <stdlib.h>
	#include <string.h>
	#include <tchar.h>
	#include <ctime>
	#include <iostream>
	enum DialogAnswers{
		DGANSW_OK = IDOK,
		DGANSW_CANCEL = IDCANCEL,
		DGANSW_YES = IDYES,
		DGANSW_NO = IDNO,
		DGANSW_CLOSED= IDABORT
	};
	//LRESULT CALLBACK __WindowProcedure (HWND, UINT, WPARAM, LPARAM);
	//int WINAPI __WinMain (const char * title, const char * text, const char * footer);
	extern UINT __msgListFlags[] = {
		NULL,
		MB_OK|MB_ICONWARNING|MB_ICONEXCLAMATION,
		MB_OK|MB_ICONSTOP|MB_ICONERROR|MB_ICONHAND,
		MB_OK|MB_ICONINFORMATION|MB_ICONASTERISK,
		MB_OKCANCEL,
		MB_OKCANCEL|MB_ICONWARNING|MB_ICONEXCLAMATION,
		MB_OKCANCEL|MB_ICONSTOP|MB_ICONERROR|MB_ICONHAND,
		MB_OKCANCEL|MB_ICONINFORMATION|MB_ICONASTERISK,
		MB_YESNO,
		MB_YESNO|MB_ICONWARNING|MB_ICONEXCLAMATION,
		MB_YESNO|MB_ICONSTOP|MB_ICONERROR|MB_ICONHAND,
		MB_YESNO|MB_ICONINFORMATION|MB_ICONASTERISK,
	};


	inline LRESULT CALLBACK __WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		HDC hdcStatic;
		switch (message) {
			case WM_CREATE:
				return 0;  
			case WM_DESTROY:
				PostQuitMessage (0);
				break;
			case WM_CTLCOLORSTATIC:
					hdcStatic = (HDC) wParam; 
					SetTextColor(hdcStatic, RGB(0,0,0));    
				SetBkMode (hdcStatic, TRANSPARENT);
				return (LRESULT)GetStockObject(NULL_BRUSH);
			default:                
				return DefWindowProc (hwnd, message, wParam, lParam);
		}

		return 0;
	}


	inline int WINAPI __WinMain ( const char * title, const char * text, const char * footer) {
			HINSTANCE hThisInstance = GetModuleHandle(NULL); LPSTR lpszArgument = NULL;
			int nFunsterStil = 1,  _winWidth = 200, _winHeight = 60, _winX = GetSystemMetrics(SM_CXSCREEN ) - _winWidth - 4, _winY =  0;

			HWND hwnd; WNDCLASSEX wincl;  
			wincl.hInstance = hThisInstance; wincl.lpszClassName = title;
			wincl.lpfnWndProc = __WindowProcedure; wincl.style = CS_DBLCLKS; wincl.cbSize = sizeof (WNDCLASSEX);
			wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION); wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
			wincl.hCursor = LoadCursor (NULL, IDC_ARROW); wincl.lpszMenuName = NULL; wincl.cbClsExtra = 0; wincl.cbWndExtra = 0;
			wincl.hbrBackground = (HBRUSH) CTLCOLOR_DLG;

			/* Register the window class, and if it fails quit the program */
			if (!RegisterClassEx (&wincl))
				return 0;

				hwnd = CreateWindowEx (
					0,                   /* Extended possibilites for variation */
					title,         /* Classname */
					title,       /* Title Text */
					WS_DLGFRAME , /* default window */  //WS_POPUP  pentru no title and title bar
					_winX,       /* Windows decides the position */
					_winY,       /* where the window ends up on the screen */
					_winWidth,                 /* The programs width */
					_winHeight,                 /* and height in pixels */
					HWND_DESKTOP,        /* The window is a child-window to desktop */
					NULL,                /* No menu */
					hThisInstance,       /* Program Instance handler */
					NULL                 /* No Window Creation data */
					);

			//HWND_TOPMOST o mentine in fata
				SetWindowPos(hwnd, HWND_TOPMOST,  _winX, _winY, _winWidth, _winHeight, SWP_SHOWWINDOW);
				HFONT  hfFont1 = CreateFont (14, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
				HFONT  hfFont2 = CreateFont (13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
			    /*HWND hwnd_st_u = CreateWindowEx(0,  "static", NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, 0, 200, 10,  hwnd,   (HMENU)(2),  (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE),   NULL);*/

			HWND titleComp = CreateWindowEx(0, TEXT("STATIC"),TEXT(text), WS_CHILD|WS_VISIBLE|SS_LEFT, 
					0,2,200,14,
					hwnd,HMENU(NULL),GetModuleHandle(NULL),NULL);
				
			HWND subtitle = CreateWindowEx(0, TEXT("STATIC"),TEXT(footer), WS_CHILD|WS_VISIBLE|SS_LEFT, 0,19,200,12, hwnd,HMENU(NULL),GetModuleHandle(NULL),NULL);

			/* Make the window visible on the screen */
			ShowWindow (hwnd, nFunsterStil);
			SendMessage (titleComp, WM_SETFONT, WPARAM (hfFont1), TRUE);
			SendMessage (subtitle, WM_SETFONT, WPARAM (hfFont2), TRUE);
			return 0; //messages.wParam;
		}


		inline int MINGUI_Dialog(const char * title, const char * message, void (*callback)(int stat, int pid), int flags, int pid) {
			int result = MessageBox(NULL, title, message, __msgListFlags[flags]);
			if(callback != NULL) {
				callback(result, pid);
			}
			return result;
		}

		inline void MINGUI_Notification(const char * title, const char * subtitle, const char * footer, int lifetime){
			clock_t startedAt = clock(); // da 0, 2000
			clock_t updateAt = 0; // da 1, 2001
			int diff = updateAt - startedAt; // MSG messages; 
			__WinMain(title, subtitle, footer);
			while (diff <= lifetime) { //	while (GetMessage (&messages, NULL, 0, 0)) {
				updateAt = clock();
				diff = updateAt - startedAt;
				std::cout << diff << std::endl; //TranslateMessage(&messages); //DispatchMessage(&messages);
			}
		}
#endif

#ifdef ASTOX_ENABLE_GTK
	#include <gtk/gtk.h>
	#include <libnotify/notify.h>
	enum DialogAnswers{
		DGANSW_OK = GTK_RESPONSE_OK,
		DGANSW_CANCEL = GTK_RESPONSE_CANCEL,
		DGANSW_YES=GTK_RESPONSE_YES,
		DGANSW_NO = GTK_RESPONSE_NO,
		DGANSW_CLOSED= GTK_RESPONSE_CLOSE
	};
#endif

#ifdef __MACOSX_CORE__
	#pragma once
	enum DialogAnswers{
		DGANSW_OK = 0,
		DGANSW_CANCEL = 1,
		DGANSW_YES = 0,
		DGANSW_NO = 1,
		DGANSW_CLOSED = -2
	};

	int MINGUI_Dialog(const char * title, const char * message, void (*callback)(int stat, int pid) = NULL, int flags = 0, int pid = 1);
	void MINGUI_Notification(const char * title = "NotificationTitle", const char * subtitle = "notificationSubtitle", const char * footer = "notificationFooter", int lifetime = 5);
#endif
















#endif /* MINGUI_H_ */
