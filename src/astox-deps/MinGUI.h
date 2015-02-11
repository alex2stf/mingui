/*
 * MinGUI.h
 *
 *  Created on: Feb 9, 2015
 *      Author: alexandru
 */

#ifndef MINGUI_H_
#define MINGUI_H_
#include <stdlib.h>

#ifdef __MACOSX_CORE__
	#pragma once
#endif


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

enum DialogAnswers{
			DGANSW_OK = 0,
			DGANSW_CANCEL = 1,
			DGANSW_YES = 0,
			DGANSW_NO = 1,
			DGANSW_CLOSED = -2
		};

int MINGUI_Dialog(const char * title, const char * message, void (*callback)(int stat, int pid) = NULL, int flags = 0, int pid = 1);
void MINGUI_Notification(const char * title = "NotificationTitle", const char * subtitle = "notificationSubtitle", const char * footer = "notificationFooter", int lifetime = 5);








#endif /* MINGUI_H_ */
