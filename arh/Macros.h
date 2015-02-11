
//TODO work on C

#ifndef ASTOX_STMACROS_H
#define ASTOX_STMACROS_H





/*check for qt file crawler requirements*/
#ifdef QFILE_H
    #define ASTOX_QT_HAS_FILE
#endif

#ifdef QSTRING_H
    #define ASTOX_QT_HAS_STRING
#endif

#ifdef QDIR_H
    #define ASTOX_QT_HAS_QDIR
#endif

#ifdef QDATETIME_H
    #define ASTOX_QT_HAS_QDATETIME
#endif


#ifdef ASTOX_QT_HAS_FILE
    #ifdef ASTOX_QT_HAS_STRING
        #ifdef ASTOX_QT_HAS_QDIR
            #ifdef ASTOX_QT_HAS_QDATETIME
                #define ASTOX_FILE_CRAWL_ON_QT
            #endif
        #endif
    #endif
#endif


#ifdef _MSC_VER
	#define ASTOX_COMPILER_MSC
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
	#define ASTOX_COMPILER_CYGWIN
#elif defined(__GNUC__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__)
	#define ASTOX_COMPILER_GNU 
#endif
	


#if defined(_WIN32) || defined (__WIN32__) || defined(WIN32) || defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__TOS_WIN__) || defined(__WINDOWS__)// note the underscore: without it, it's not msdn official!
    #define ASTOX_OS_WINDOWS 1
	#define ASTOX_SOCK_WIN 1
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__linux__) // all unices, not all compilers
    #define ASTOX_OS_LINUX
	#define ASTOX_SOCK_UNIX
#elif defined(__APPLE__) || defined(__MACH__)
    #define ASTOX_OS_MAC
	#define ASTOX_SOCK_UNIX
#endif



#if defined(_UNICODE) || defined(UNICODE)
    #define ASTOX_COMPILER_UNICODE
#endif



#ifdef ASTOX_OS_WINDOWS
	#define ASTOX_OS_SEPARATOR '\\'
	#define ASTOX_OS_SEPARATOR_OTHER '/'
#else
	#define ASTOX_OS_SEPARATOR '/'
	#define ASTOX_OS_SEPARATOR_OTHER '\\'
#endif

#ifdef __cplusplus
	#define ASTOX_COMP_CPP
#else
	#define ASTOX_COMP_C
#endif



#ifdef ASTOX_SOCK_WIN

	#define astox_socket_close(socket)\
	{\
		closesocket(socket);\
	};

	#define astox_socket_clean()\
	{\
		 WSACleanup() ;\
	};

	#define astox_close_thread(thread)\
	{\
		CloseHandle(thread);\
	};

#elif defined(ASTOX_SOCK_UNIX)

	#define astox_socket_close(socket)\
	{\
			free(socket);\
	};

	#define astox_socket_clean()\
	{\
		 ;;\
	};

	#define astox_close_thread(thread)\
	{\
		;;\
	};


#endif



//allow file crawl for QT:
//ASTOX_FILE_CRAWL_ON_QT
#endif // STMACROS_H
