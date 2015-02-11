#include "MinGUI.h"





//void DialogHandlerDefault(int data, int pid) {
//	std::cout << pid << ") DialogHandlerDefault ";
//	switch(data) {
//	case DGANSW_CANCEL:
//		std::cout <<  "DGANSW_CANCEL "<< std::endl;
//		break;
//	case DGANSW_NO:
//		std::cout <<  "DGANSW_NO " << std::endl;
//		break;
//	case DGANSW_YES:
//		std::cout <<  "DGANSW_YES " << std::endl;
//		break;
//	case DGANSW_OK:
//		std::cout <<  "DGANSW_OK " << std::endl;
//		break;
//	case DGANSW_CLOSED:
//		std::cout <<  "DGANSW_CLOSED " << std::endl;
//		break;
//	default:
//		std::cout <<  "answ =  " << data << std::endl;
//		break;
//	}
//}
		
#ifdef ASTOX_OS_WINDOWS
		
		int MINGUI_Dialog(const char * title, const char * message, void (*callback)(int stat, int pid), int flags, int pid) {
			int result = MessageBox(NULL, title, message, __msgListFlags[flags]);
			if(callback != NULL) {
				callback(result, pid);
			}
			return result;
		}

		void MINGUI_Notification(const char * title, const char * subtitle, const char * footer, int lifetime){
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


		LRESULT CALLBACK __WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
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


		int WINAPI __WinMain ( const char * title, const char * text, const char * footer) {
				HINSTANCE hThisInstance = GetModuleHandle(NULL);
				//HINSTANCE hPrevInstance = NULL;
				LPSTR lpszArgument = NULL;
				int nFunsterStil = 1,  _winWidth = 200, _winHeight = 60,
					_winX = GetSystemMetrics(SM_CXSCREEN ) - _winWidth - 4, _winY =  0;//GetSystemMetrics(SM_CYSCREEN ) - _winHeight - 4;

				HWND hwnd; WNDCLASSEX wincl;  
				wincl.hInstance = hThisInstance;
				wincl.lpszClassName = title;
				wincl.lpfnWndProc = __WindowProcedure;      /* This function is called by windows */
				wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
				wincl.cbSize = sizeof (WNDCLASSEX);
				wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
				wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
				wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
				wincl.lpszMenuName = NULL;                 /* No menu */
				wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
				wincl.cbWndExtra = 0;                      /* structure or the window instance */
		//		wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
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
				
				HWND subtitle = CreateWindowEx(0, TEXT("STATIC"),TEXT(footer), WS_CHILD|WS_VISIBLE|SS_LEFT, 
						0,19,200,12,
						hwnd,HMENU(NULL),GetModuleHandle(NULL),NULL);

				/* Make the window visible on the screen */
				ShowWindow (hwnd, nFunsterStil);
				SendMessage (titleComp, WM_SETFONT, WPARAM (hfFont1), TRUE);
			    SendMessage (subtitle, WM_SETFONT, WPARAM (hfFont2), TRUE);
				return 0; //messages.wParam;
			}

#endif

#ifdef ASTOX_ENABLE_GTK
		void InitGUI(int argc, char *argv[]){
			 gtk_init (&argc, &argv);
		}

		int MINGUI_Dialog(const char * title, const char * message, void (*callback)(int stat, int pid), int flags, int pid) {
			  GtkWidget *dialog;

			  switch(flags){
			  case DG_DEFAULT:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, message);
				  break;

			  case DG_OK_WARNING:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, message);
				  break;

			  case DG_OK_ERROR:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, message);
				  break;

			  case DG_OK_INFO:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message);
				  break;

			  case DG_OKCANCEL:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK_CANCEL, message);
				  break;

			  case DG_OKCANCEL_WARNING:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK_CANCEL, message);
				  break;

			  case DG_OKCANCEL_ERROR:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK_CANCEL, message);
				  break;

			  case DG_OKCANCEL_INFO:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK_CANCEL, message);
				  break;

			  case DG_YESNO:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_YES_NO, message);
				  break;

			  case DG_YESNO_WARNING:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, message);
				  break;

			  case DG_YESNO_ERROR:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_YES_NO, message);
				  break;

			  case DG_YESNO_INFO:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_YES_NO, message);
				  break;

			  default:
				  dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK_CANCEL, message);
				  break;
			  }


			  gtk_window_set_title(GTK_WINDOW(dialog), title);
			  gint result = gtk_dialog_run(GTK_DIALOG(dialog));
			  gtk_widget_destroy(dialog);
			  if(callback!=NULL){
				  callback(result, pid);
			  }

		};
		void MINGUI_Notification(const char * title, const char * text, const char * footer, int lifetime){
			notify_init(title);
			NotifyNotification * notification;
			std::string cmptxt = text;
			cmptxt.append("\n");
			cmptxt.append(footer);
			notification = notify_notification_new(title, cmptxt.c_str(), NULL);
			notify_notification_set_timeout(notification, lifetime);
			notify_notification_close(notification, NULL);
			notify_notification_show(notification, NULL);
		};
#endif
