/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

// Adapted from Branimir Karadžić's platform.h (https://github.com/bkaradzic/bx)

#pragma once

#define ALTERTUM_VERSION_MAJOR "0"
#define ALTERTUM_VERSION_MINOR "0"
#define ALTERTUM_VERSION_PATCH "1"
#define ALTERTUM_VERSION_KEYWORD "alpha"

#define ALTERTUM_COMPILER_CLANG           0
#define ALTERTUM_COMPILER_CLANG_ANALYZER  0
#define ALTERTUM_COMPILER_GCC             0
#define ALTERTUM_COMPILER_MSVC            0
#define ALTERTUM_COMPILER_MSVC_COMPATIBLE 0

#define ALTERTUM_PLATFORM_ANDROID    0
#define ALTERTUM_PLATFORM_EMSCRIPTEN 0
#define ALTERTUM_PLATFORM_FREEBSD    0
#define ALTERTUM_PLATFORM_IOS        0
#define ALTERTUM_PLATFORM_LINUX      0
#define ALTERTUM_PLATFORM_OSX        0
#define ALTERTUM_PLATFORM_PS4        0
#define ALTERTUM_PLATFORM_WINDOWS    0
#define ALTERTUM_PLATFORM_WINRT      0
#define ALTERTUM_PLATFORM_XBOX360    0
#define ALTERTUM_PLATFORM_XBOXONE    0

#define ALTERTUM_CPU_ARM  0
#define ALTERTUM_CPU_JIT  0
#define ALTERTUM_CPU_MIPS 0
#define ALTERTUM_CPU_PPC  0
#define ALTERTUM_CPU_X86  0

#define ALTERTUM_ARCH_32BIT 0
#define ALTERTUM_ARCH_64BIT 0

#define ALTERTUM_CPU_ENDIAN_BIG    0
#define ALTERTUM_CPU_ENDIAN_LITTLE 0

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
#if defined(__clang__)
// clang defines __GNUC__ or _MSC_VER
#	undef  ALTERTUM_COMPILER_CLANG
#	define ALTERTUM_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#	if defined(__clang_analyzer__)
#		undef  ALTERTUM_COMPILER_CLANG_ANALYZER
#		define ALTERTUM_COMPILER_CLANG_ANALYZER 1
#	endif // defined(__clang_analyzer__)
#	if defined(_MSC_VER)
#		undef  ALTERTUM_COMPILER_MSVC_COMPATIBLE
#		define ALTERTUM_COMPILER_MSVC_COMPATIBLE _MSC_VER
#	endif // defined(_MSC_VER)
#elif defined(_MSC_VER)
#	undef  ALTERTUM_COMPILER_MSVC
#	define ALTERTUM_COMPILER_MSVC _MSC_VER
#	undef  ALTERTUM_COMPILER_MSVC_COMPATIBLE
#	define ALTERTUM_COMPILER_MSVC_COMPATIBLE _MSC_VER
#elif defined(__GNUC__)
#	undef  ALTERTUM_COMPILER_GCC
#	define ALTERTUM_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#	error "ALTERTUM_COMPILER_* is not defined!"
#endif //

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures
#if defined(__arm__)     || \
	defined(__aarch64__) || \
	defined(_M_ARM)
#	undef  ALTERTUM_CPU_ARM
#	define ALTERTUM_CPU_ARM 1
#	define ALTERTUM_CACHE_LINE_SIZE 64
#elif defined(__MIPSEL__)     || \
	  defined(__mips_isa_rev) || \
	  defined(__mips64)
#	undef  ALTERTUM_CPU_MIPS
#	define ALTERTUM_CPU_MIPS 1
#	define ALTERTUM_CACHE_LINE_SIZE 64
#elif defined(_M_PPC)        || \
	  defined(__powerpc__)   || \
	  defined(__powerpc64__)
#	undef  ALTERTUM_CPU_PPC
#	define ALTERTUM_CPU_PPC 1
#	define ALTERTUM_CACHE_LINE_SIZE 128
#elif defined(_M_IX86)    || \
	  defined(_M_X64)     || \
	  defined(__i386__)   || \
	  defined(__x86_64__)
#	undef  ALTERTUM_CPU_X86
#	define ALTERTUM_CPU_X86 1
#	define ALTERTUM_CACHE_LINE_SIZE 64
#else // PNaCl doesn't have CPU defined.
#	undef  ALTERTUM_CPU_JIT
#	define ALTERTUM_CPU_JIT 1
#	define ALTERTUM_CACHE_LINE_SIZE 64
#endif //

#if ALTERTUM_CPU_PPC
#	undef  ALTERTUM_CPU_ENDIAN_BIG
#	define ALTERTUM_CPU_ENDIAN_BIG 1
#else
#	undef  ALTERTUM_CPU_ENDIAN_LITTLE
#	define ALTERTUM_CPU_ENDIAN_LITTLE 1
#endif // ALTERTUM_PLATFORM_

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
#if defined(_XBOX_VER)
#	undef  ALTERTUM_PLATFORM_XBOX360
#	define ALTERTUM_PLATFORM_XBOX360 1
#elif defined (_DURANGO)
#	undef  ALTERTUM_PLATFORM_XBOXONE
#	define ALTERTUM_PLATFORM_XBOXONE 1
#elif defined(_WIN32) || defined(_WIN64)
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif // NOMINMAX
//  If _USING_V110_SDK71_ is defined it means we are using the v110_xp or v120_xp toolset.
#	if defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
#		include <winapifamily.h>
#	endif // defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
#	if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#		undef  ALTERTUM_PLATFORM_WINDOWS
#		if !defined(WINVER) && !defined(_WIN32_WINNT)
#			if ALTERTUM_ARCH_64BIT
//				When building 64-bit target Win7 and above.
#				define WINVER 0x0601
#				define _WIN32_WINNT 0x0601
#			else
//				Windows Server 2003 with SP1, Windows XP with SP2 and above
#				define WINVER 0x0502
#				define _WIN32_WINNT 0x0502
#			endif // ALTERTUM_ARCH_64BIT
#		endif // !defined(WINVER) && !defined(_WIN32_WINNT)
#		define ALTERTUM_PLATFORM_WINDOWS _WIN32_WINNT
#	else
#		undef  ALTERTUM_PLATFORM_WINRT
#		define ALTERTUM_PLATFORM_WINRT 1
#	endif
#elif defined(__VCCOREVER__)
// RaspberryPi compiler defines __linux__
#	undef  ALTERTUM_PLATFORM_RPI
#	define ALTERTUM_PLATFORM_RPI 1
#elif defined(__native_client__)
// NaCl compiler defines __linux__
#	include <ppapi/c/pp_macros.h>
#	undef  ALTERTUM_PLATFORM_NACL
#	define ALTERTUM_PLATFORM_NACL PPAPI_RELEASE
#elif defined(__ANDROID__)
// Android compiler defines __linux__
#	include <android/api-level.h>
#	undef  ALTERTUM_PLATFORM_ANDROID
#	define ALTERTUM_PLATFORM_ANDROID __ANDROID_API__
#elif defined(__linux__)
#	undef  ALTERTUM_PLATFORM_LINUX
#	define ALTERTUM_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#	undef  ALTERTUM_PLATFORM_IOS
#	define ALTERTUM_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#	undef  ALTERTUM_PLATFORM_OSX
#	define ALTERTUM_PLATFORM_OSX 1
#elif defined(EMSCRIPTEN)
#	undef  ALTERTUM_PLATFORM_EMSCRIPTEN
#	define ALTERTUM_PLATFORM_EMSCRIPTEN 1
#elif defined(__ORBIS__)
#	undef  ALTERTUM_PLATFORM_PS4
#	define ALTERTUM_PLATFORM_PS4 1
#elif defined(__QNX__)
#	undef  ALTERTUM_PLATFORM_QNX
#	define ALTERTUM_PLATFORM_QNX 1
#elif defined(__FreeBSD__)
#	undef  ALTERTUM_PLATFORM_FREEBSD
#	define ALTERTUM_PLATFORM_FREEBSD 1
#else
#	error "ALTERTUM_PLATFORM_* is not defined!"
#endif //

#define ALTERTUM_PLATFORM_POSIX (0 \
						|| ALTERTUM_PLATFORM_ANDROID \
						|| ALTERTUM_PLATFORM_EMSCRIPTEN \
						|| ALTERTUM_PLATFORM_FREEBSD \
						|| ALTERTUM_PLATFORM_IOS \
						|| ALTERTUM_PLATFORM_LINUX \
						|| ALTERTUM_PLATFORM_NACL \
						|| ALTERTUM_PLATFORM_OSX \
						|| ALTERTUM_PLATFORM_QNX \
						|| ALTERTUM_PLATFORM_PS4 \
						|| ALTERTUM_PLATFORM_RPI \
						)

#ifndef  ALTERTUM_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS
#	define ALTERTUM_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS 0
#endif // ALTERTUM_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS

#if ALTERTUM_COMPILER_GCC
#	define ALTERTUM_COMPILER_NAME "GCC " \
				ALTERTUM_STRINGIZE(__GNUC__) "." \
				ALTERTUM_STRINGIZE(__GNUC_MINOR__) "." \
				ALTERTUM_STRINGIZE(__GNUC_PATCHLEVEL__)
#elif ALTERTUM_COMPILER_CLANG
#	define ALTERTUM_COMPILER_NAME "Clang " \
				ALTERTUM_STRINGIZE(__clang_major__) "." \
				ALTERTUM_STRINGIZE(__clang_minor__) "." \
				ALTERTUM_STRINGIZE(__clang_patchlevel__)
#elif ALTERTUM_COMPILER_MSVC
#	if ALTERTUM_COMPILER_MSVC >= 1900
#		define ALTERTUM_COMPILER_NAME "MSVC 14.0"
#	elif ALTERTUM_COMPILER_MSVC >= 1800
#		define ALTERTUM_COMPILER_NAME "MSVC 12.0"
#	elif ALTERTUM_COMPILER_MSVC >= 1700
#		define ALTERTUM_COMPILER_NAME "MSVC 11.0"
#	elif ALTERTUM_COMPILER_MSVC >= 1600
#		define ALTERTUM_COMPILER_NAME "MSVC 10.0"
#	elif ALTERTUM_COMPILER_MSVC >= 1500
#		define ALTERTUM_COMPILER_NAME "MSVC 9.0"
#	else
#		define ALTERTUM_COMPILER_NAME "MSVC"
#	endif //
#endif // ALTERTUM_COMPILER_

#if ALTERTUM_PLATFORM_ANDROID
#	define ALTERTUM_PLATFORM_NAME "Android " \
				ALTERTUM_STRINGIZE(ALTERTUM_PLATFORM_ANDROID)
#elif ALTERTUM_PLATFORM_EMSCRIPTEN
#	define ALTERTUM_PLATFORM_NAME "asm.js " \
				ALTERTUM_STRINGIZE(__EMSCRIPTEN_major__) "." \
				ALTERTUM_STRINGIZE(__EMSCRIPTEN_minor__) "." \
				ALTERTUM_STRINGIZE(__EMSCRIPTEN_tiny__)
#elif ALTERTUM_PLATFORM_FREEBSD
#	define ALTERTUM_PLATFORM_NAME "FreeBSD"
#elif ALTERTUM_PLATFORM_IOS
#	define ALTERTUM_PLATFORM_NAME "iOS"
#elif ALTERTUM_PLATFORM_LINUX
#	define ALTERTUM_PLATFORM_NAME "Linux"
#elif ALTERTUM_PLATFORM_NACL
#	define ALTERTUM_PLATFORM_NAME "NaCl " \
				ALTERTUM_STRINGIZE(ALTERTUM_PLATFORM_NACL)
#elif ALTERTUM_PLATFORM_OSX
#	define ALTERTUM_PLATFORM_NAME "OSX"
#elif ALTERTUM_PLATFORM_PS4
#	define ALTERTUM_PLATFORM_NAME "PlayStation 4"
#elif ALTERTUM_PLATFORM_QNX
#	define ALTERTUM_PLATFORM_NAME "QNX"
#elif ALTERTUM_PLATFORM_RPI
#	define ALTERTUM_PLATFORM_NAME "RaspberryPi"
#elif ALTERTUM_PLATFORM_WINDOWS
#	define ALTERTUM_PLATFORM_NAME "Windows"
#elif ALTERTUM_PLATFORM_WINRT
#	define ALTERTUM_PLATFORM_NAME "WinRT"
#elif ALTERTUM_PLATFORM_XBOX360
#	define ALTERTUM_PLATFORM_NAME "Xbox 360"
#elif ALTERTUM_PLATFORM_XBOXONE
#	define ALTERTUM_PLATFORM_NAME "Xbox One"
#endif // ALTERTUM_PLATFORM_

#if ALTERTUM_CPU_ARM
#	define ALTERTUM_CPU_NAME "ARM"
#elif ALTERTUM_CPU_MIPS
#	define ALTERTUM_CPU_NAME "MIPS"
#elif ALTERTUM_CPU_PPC
#	define ALTERTUM_CPU_NAME "PowerPC"
#elif ALTERTUM_CPU_JIT
#	define ALTERTUM_CPU_NAME "JIT-VM"
#elif ALTERTUM_CPU_X86
#	define ALTERTUM_CPU_NAME "x86"
#endif // ALTERTUM_CPU_

#if ALTERTUM_ARCH_32BIT
#	define ALTERTUM_ARCH_NAME "32-bit"
#elif ALTERTUM_ARCH_64BIT
#	define ALTERTUM_ARCH_NAME "64-bit"
#endif // ALTERTUM_ARCH_

#if ALTERTUM_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS && ALTERTUM_COMPILER_MSVC
#	pragma warning(error:4062) // ENABLE warning C4062: enumerator'...' in switch of enum '...' is not handled
#	pragma warning(error:4121) // ENABLE warning C4121: 'symbol' : alignment of a member was sensitive to packing
//#	pragma warning(error:4127) // ENABLE warning C4127: conditional expression is constant
#	pragma warning(error:4130) // ENABLE warning C4130: 'operator' : logical operation on address of string constant
#	pragma warning(error:4239) // ENABLE warning C4239: nonstandard extension used : 'argument' : conversion from '*' to '* &' A non-const reference may only be bound to an lvalue
//#	pragma warning(error:4244) // ENABLE warning C4244: 'argument' : conversion from 'type1' to 'type2', possible loss of data
#	pragma warning(error:4245) // ENABLE warning C4245: 'conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
#	pragma warning(error:4263) // ENABLE warning C4263: 'function' : member function does not override any base class virtual member function
#	pragma warning(error:4265) // ENABLE warning C4265: class has virtual functions, but destructor is not virtual
#	pragma warning(error:4431) // ENABLE warning C4431: missing type specifier - int assumed. Note: C no longer supports default-int
#	pragma warning(error:4545) // ENABLE warning C4545: expression before comma evaluates to a function which is missing an argument list
#	pragma warning(error:4549) // ENABLE warning C4549: 'operator' : operator before comma has no effect; did you intend 'operator'?
#	pragma warning(error:4701) // ENABLE warning C4701: potentially uninitialized local variable 'name' used
#	pragma warning(error:4706) // ENABLE warning C4706: assignment within conditional expression
#	pragma warning(error:4100) // ENABLE warning C4100: '' : unreferenced formal parameter
#	pragma warning(error:4189) // ENABLE warning C4189: '' : local variable is initialized but not referenced
#	pragma warning(error:4505) // ENABLE warning C4505: '' : unreferenced local function has been removed
#endif // ALTERTUM_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS && ALTERTUM_COMPILER_MSVC
