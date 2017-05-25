dnl $Id$
dnl config.m4 for extension base62

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(base62, for base62 support,
dnl Make sure that the comment is aligned:
dnl [  --with-base62             Include base62 support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(base62, whether to enable base62 support,
Make sure that the comment is aligned:
[  --enable-base62           Enable base62 support])

if test "$PHP_BASE62" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-base62 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/base62.h"  # you most likely want to change this
  dnl if test -r $PHP_BASE62/$SEARCH_FOR; then # path given as parameter
  dnl   BASE62_DIR=$PHP_BASE62
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for base62 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       BASE62_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$BASE62_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the base62 distribution])
  dnl fi

  dnl # --with-base62 -> add include path
  dnl PHP_ADD_INCLUDE($BASE62_DIR/include)

  dnl # --with-base62 -> check for lib and symbol presence
  dnl LIBNAME=base62 # you may want to change this
  dnl LIBSYMBOL=base62 # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BASE62_DIR/$PHP_LIBDIR, BASE62_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_BASE62LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong base62 lib version or lib not found])
  dnl ],[
  dnl   -L$BASE62_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(BASE62_SHARED_LIBADD)

  PHP_NEW_EXTENSION(base62, base62.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
