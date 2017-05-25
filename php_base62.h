/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_BASE62_H
#define PHP_BASE62_H

extern zend_module_entry base62_module_entry;
#define phpext_base62_ptr &base62_module_entry

#define PHP_BASE62_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_BASE62_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BASE62_API __attribute__ ((visibility("default")))
#else
#	define PHP_BASE62_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(base62)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(base62)
*/

/* Always refer to the globals in your function as BASE62_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define BASE62_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(base62, v)

#if defined(ZTS) && defined(COMPILE_DL_BASE62)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_BASE62_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
