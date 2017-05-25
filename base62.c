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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_base62.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>

/* If you declare any globals in php_base62.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(base62)
*/

/* True global resources - no need for thread safety here */
static int le_base62;
static char randStr[] = "vPh7zZwA2LyU4bGq5tcVfIMxJi6XaSoK9CNp0OWljYTHQ8REnmu31BrdgeDkFs";
char *encodeStr = NULL;
/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("base62.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_base62_globals, base62_globals)
    STD_PHP_INI_ENTRY("base62.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_base62_globals, base62_globals)
PHP_INI_END()
*/
/* }}} */


PHP_FUNCTION(base62_encode){
    
    int number;
    size_t arg_len;
    zend_string *strg;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &number, &arg_len) == FAILURE) {
        return;
    }
    
    int forNumber = floor(log10(number) / log10(62));
    encodeStr = ecalloc(forNumber + 2,sizeof(char *));
    int t = forNumber;
    for(t;t>=0;t--){
        int a = floor(number / pow(62, t));
        char *str = substr(randStr,a, 1);
        strcat(encodeStr,str);
        efree(str);
        
        number = number - (a * pow(62, t));
    }
    strg = strpprintf(0,"%s",encodeStr);
    RETURN_STR(strg);
}

PHP_FUNCTION(base62_decode){
    char *encodeStr = NULL;
    size_t arg_len;
    zend_string *str;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS(),"s",&encodeStr,&arg_len) == FAILURE){
        return;
    }
    
    int number = 0;
    int stringLength = (unsigned int)strlen(encodeStr) - 1;
    int t = 0;
    
    for(t;t<=stringLength;t++){
        char *searchChar = substr(encodeStr, t, 1);
        number = number + strpos(randStr,*searchChar) * pow(62, stringLength - t);
        efree(searchChar);
    }
    
    RETURN_LONG(number);
}

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_base62_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_base62_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "base62", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_base62_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_base62_init_globals(zend_base62_globals *base62_globals)
{
	base62_globals->global_value = 0;
	base62_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(base62)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(base62)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(base62)
{
#if defined(COMPILE_DL_BASE62) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(base62)
{
    efree(encodeStr);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(base62)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "base62 support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ base62_functions[]
 *
 * Every user visible function must have an entry in base62_functions[].
 */
const zend_function_entry base62_functions[] = {
    PHP_FE(base62_decode,NULL)
    PHP_FE(base62_encode,NULL)
	PHP_FE(confirm_base62_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in base62_functions[] */
};
/* }}} */

char* substr(char* string,int start,int length){
    
    char *outString = ecalloc(length + 1,sizeof(char*));
    
    int stringLength = (unsigned int)strlen(string);
    
    if(length > stringLength){
        return string;
    }
    
    if(start > stringLength){
        start = 0;
    }
    
    strncpy(outString,string+start,length);
//    printf("outString = %s\n",outString);
    return outString;
}

long int strpos(const char* str,char c){
    long int pos = 0;
    
    char * stringInPos;
    stringInPos = strchr(str, c);
    
    
    if(stringInPos != NULL){
        //        printf("stringInPos - str = %ld\n",stringInPos - str);
        pos = stringInPos - str;
    }
    
    return pos;
}

/* {{{ base62_module_entry
 */
zend_module_entry base62_module_entry = {
	STANDARD_MODULE_HEADER,
	"base62",
	base62_functions,
	PHP_MINIT(base62),
	PHP_MSHUTDOWN(base62),
	PHP_RINIT(base62),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(base62),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(base62),
	PHP_BASE62_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BASE62
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(base62)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
