# -*- shell-script -*-
#
# Simple configure.in for pidgin-encryption
#

#
# Init autoconf
#

AC_INIT(./encrypt.c)
AC_PREREQ(2.52)
AC_CANONICAL_SYSTEM

#
# Init automake
# The third argument to AM_INIT_AUTOMAKE surpresses the PACKAGE and
# VERSION macors
#

PIDGIN_ENC_VERSION="`cat $srcdir/VERSION`"

AM_INIT_AUTOMAKE(pidgin-encryption, $PIDGIN_ENC_VERSION, 'no-define')
AC_DEFINE_UNQUOTED(ENC_VERSION, "$PIDGIN_ENC_VERSION",
    [Version of pidgin-encryption plugin])

AC_DEFINE_UNQUOTED(ENC_PACKAGE, "$PACKAGE",
    [Version of pidgin-encryption plugin])
 
# before gettexting, in case iconv matters
case "$host_os" in
darwin*)
        AC_MSG_CHECKING([for fink])
        if test -d /sw; then
                AC_MSG_RESULT([found, adding /sw to search paths])
                CFLAGS="$CFLAGS -I/sw/include"
        else
                AC_MSG_RESULT([not found])
        fi
        ;;
*)
        ;;
esac
 
ALL_LINGUAS="bg cs da de es fr hu it ja lt nl nn pl pt_BR pt_PT ro ru sl sv ta tr uk zh_CN zh_TW"
AM_GNU_GETTEXT_VERSION(0.10.40)
AM_GNU_GETTEXT


#
# Setup the header file
#

AH_TOP([/* Pidgin-encryption header file */

#ifndef _PIDGIN_ENCRYPTION_CONFIG_H
#define _PIDGIN_ENCRYPTION_CONFIG_H
])
AH_BOTTOM([
#endif /* _PIDGIN_ENCRYPTION_CONFIG_H */
])


#
# Look for the C compiler
#

CFLAGS_save="$CFLAGS"
AC_PROG_CC
CFLAGS="$CFLAGS_save"


#
# Utility function
#

check_for_header() {
    file="$1"
    bases="$2"
    variations=". $3"

    result=
    for dir in $bases; do
	if test -z "$result"; then
	    for variant in $variations; do
		if test -z "$result" -a -f "$dir/$variant/$file"; then
		    result="$dir/$variant"
		fi
	    done
	fi
    done

    if test -z "$result"; then
	AC_MSG_RESULT([not found!])
	AC_MSG_ERROR([*** Cannot continue])
    fi
}

check_for_lib() {
    func="$1"
    lib="$2"
    bases="$3"
    variations="$4"

    LIBS_save="$LIBS"
    LDFLAGS_save="$LDFLAGS"

    found=0
    result=
    LIBS="-l$lib $LIBS_save"
    AC_CHECK_FUNC($func, result="$dir/$variant")
    if test -z "$result"; then
	for dir in $bases; do
	    if test -z "$result"; then
		for variant in $variations; do
		    echo checking: $dir/$variant
		    if test -z "$result"; then
			if test -d "$dir/$variant"; then
			    LDFLAGS="-L$dir/$variant $LDFLAGS_save"
			    AC_CHECK_FUNC($func, result="$dir/$variant")
			fi
			cmd="unset ac_cv_func_$func"
			eval $cmd
			unset cmd
		    fi
		done
	    fi
	done
    fi

    if test -z "$result"; then
	AC_MSG_RESULT([could not find $lib])
	AC_MSG_ERROR([*** Cannot continue])
    fi

    LDFLAGS="-L$result $LDFLAGS_save"
}


#
# Check for Pidgin
#

PKG_CHECK_MODULES(PIDGIN, pidgin,
[
	AC_DEFINE(HAVE_PIDGIN, 1, [Define if we have found pidgin.])
])

AC_SUBST(PIDGIN_CFLAGS)
PIDGIN_DATADIR=`pkg-config --variable=datadir pidgin`
AC_SUBST(PIDGIN_DATADIR)

#
# Check for libpurple
#

PKG_CHECK_MODULES(PURPLE, purple,
[
	AC_DEFINE(HAVE_PURPLE, 1, [Define if we have found purple.])
])

AC_SUBST(PURPLE_CFLAGS)
PIDGIN_DATADIR=`pkg-config --variable=datadir purple`
AC_SUBST(PURPLE_DATADIR)

dnl #
dnl # Check for NSS if it's specified, or if GNUTLS checks failed.
dnl #
if test "x$enable_nss" != "xno"; then

	AC_ARG_WITH(nspr-includes,
		[  --with-nspr-includes=PREFIX     Specify location of Mozilla nspr4 includes.],
		[with_nspr_includes="$withval"])

	AC_ARG_WITH(nspr-libs,
		[  --with-nspr-libs=PREFIX         Specify location of Mozilla nspr4 libs.],
		[with_nspr_libs="$withval"])

	AC_ARG_WITH(nss-includes,
		[  --with-nss-includes=PREFIX      Specify location of Mozilla nss3 includes.],
		[with_nss_includes="$withval"])

	AC_ARG_WITH(nss-libs,
		[  --with-nss-libs=PREFIX          Specify location of Mozilla nss3 libs.],
		[with_nss_libs="$withval"])


	if test -n "$with_nspr_includes" || test -n "$with_nspr_libs" || \
	   test -n "$with_nss_includes"  || test -n "$with_nss_libs"  ||
	   test "x$enable_nss" = "xstatic"; then

		nss_manual_check="yes"
	else
		nss_manual_check="no"
	fi

	enable_nss="no"

	if test "x$nss_manual_check" = "xno"; then
		if `$PKG_CONFIG --exists mozilla-nss`; then
			PKG_CHECK_MODULES(NSS, mozilla-nss, have_nss="yes", have_nss="no")
			mozilla_nspr="mozilla-nspr"
			mozilla_nss="mozilla-nss"
		else
			if `$PKG_CONFIG --exists nss`; then
				PKG_CHECK_MODULES(NSS, nss, have_nss="yes")
				mozilla_nspr="nspr"
				mozilla_nss="nss"
			fi
		fi

		if test "x$have_nss" = "xyes"; then

			AC_DEFINE(HAVE_NSS, 1, [Define if you have Mozilla NSS])
			AC_DEFINE(HAVE_SSL, 1, [Define if you have SSL])

			msg_nss="Mozilla NSS"
			enable_nss="yes"
		else
			nss_manual_check="yes"
		fi
	fi

	if test "x$nss_manual_check" = "xyes"; then
		mozilla_nss=""
		have_nspr_includes="no"

		if test "x$with_nspr_includes" != "xno"; then
			CPPFLAGS_save=$CPPFLAGS

			AC_MSG_CHECKING(for Mozilla nspr4 includes in $with_nspr_includes)
			AC_MSG_RESULT("")

			CPPFLAGS="$CPPFLAGS -I$with_nspr_includes"
			AC_CHECK_HEADERS(nspr.h prio.h, [ moz_nspr_includes="yes" ])
			CPPFLAGS=$CPPFLAGS_save

			if test "x$moz_nspr_includes" != "xno" -a \
			        "x$moz_nspr_includes" != "x"; then

				have_nspr_includes="yes"
				NSPR_CFLAGS="-I$with_nspr_includes"
			fi
		else
			AC_MSG_CHECKING(for Mozilla nspr4 includes)
			AC_MSG_RESULT(no)

			enable_nss="no"
		fi

		have_nspr_libs="no"

		if test "x$with_nspr_libs"     != "xno" -a \
		        "x$have_nspr_includes" != "xno"; then

			CFLAGS_save=$CFLAGS
			LDFLAGS_save=$LDFLAGS

			if test "$enable_nss" = "static"; then
				if test -z "$with_nspr_libs"; then
					AC_MSG_ERROR(
						[Static linkage requested, but path to nspr libraries not set.]
						[Please specify the path to libnspr4.a]
						[Example: --with-nspr-libs=/usr/lib])

					enable_nss="no"
				else
					nsprlibs="$LIBDL $with_nspr_libs/libplc4.a $with_nspr_libs/libplds4.a $with_nspr_libs/libnspr4.a $PTHREAD_LIB"
				fi
			else
				nsprlibs="$LIBDL -lplc4 -lplds4 -lnspr4 $PTHREAD_LIB"
			fi

			AC_CACHE_CHECK([for Mozilla nspr libraries], moz_nspr_libs,
			[
				LIBS_save=$LIBS
				CFLAGS="$CFLAGS $NSPR_CFLAGS"

				LIBS="$nsprlibs"

				if test "x$with_nspr_libs" != "x"; then
					LDFLAGS="$LDFLAGS -L$with_nspr_libs"
				else
					LDFLAGS="$LDFLAGS"
				fi

				AC_TRY_LINK_FUNC(PR_Init,
					[moz_nspr_libs="yes"],
					[moz_nspr_libs="no"])

				CFLAGS=$CFLAGS_save
				LDFLAGS=$LDFLAGS_save
				LIBS=$LIBS_save
			])

			if test "x$moz_nspr_libs" != "xno"; then
				have_nspr_libs="yes"
				NSPR_LIBS="-L$with_nspr_libs $nsprlibs"
			else
				NSPR_CFLAGS=""
				enable_nss="no"
			fi
		else
			AC_MSG_CHECKING(for Mozilla nspr4 libraries)
			AC_MSG_RESULT(no)
		fi

		have_nss_includes="no"

		if test "x$with_nss_includes" != "xno" -a \
				"x$have_nspr_libs"    != "xno"; then

			CPPFLAGS_save=$CPPFLAGS

			AC_MSG_CHECKING(for Mozilla nss3 includes in $with_nss_includes)
			AC_MSG_RESULT("")

			if test "x$with_nspr_includes" != "x"; then
				CPPFLAGS="$CPPFLAGS -I$with_nspr_includes -I$with_nss_includes"
			else
				CPPFLAGS="$CPPFLAGS -I$with_nss_includes"
			fi

			AC_CHECK_HEADERS(nss.h ssl.h smime.h keyhi.h,
				[moz_nss_includes="yes"],
				[moz_nss_includes="no"])

			CPPFLAGS=$CPPFLAGS_save

			if test "x$moz_nss_includes" = "xyes"; then
				have_nss_includes="yes"
				NSS_CFLAGS="-I$with_nss_includes"
			else
				NSPR_CFLAGS=""
				NSPR_LIBS=""
				enable_nss="no"
			fi
		else
			AC_MSG_CHECKING(for Mozilla nss3 includes)
			AC_MSG_RESULT(no)
			enable_nss="no"
		fi

		if test "x$with_nss_libs"     != "xno" -a \
				"x$have_nss_includes" != "xno"; then

			LDFLAGS_save=$LDFLAGS

			if test "$enable_nss" = "static"; then
				if test -z "$with_nss_libs"; then
					AC_MSG_ERROR(
						[Static linkage requested, but path to nss libraries not set.]
						[Please specify the path to libnss3.a]
						[Example: --with-nspr-libs=/usr/lib/mozilla])
					enable_nss="no"
				else
					nsslibs="-ldb1 $with_nss_libs/libnssckfw.a $with_nss_libs/libasn1.a $with_nss_libs/libcrmf.a $with_nss_libs/libswfci.a $with_nss_libs/libjar.a $with_nss_libs/libpkcs12.a $with_nss_libs/libpkcs7.a $with_nss_libs/libpki1.a $with_nss_libs/libsmime.a $with_nss_libs/libssl.a $with_nss_libs/libnss.a $with_nss_libs/libpk11wrap.a $with_nss_libs/libsoftokn.a $with_nss_libs/libfreebl.a $with_nss_libs/libnsspki.a $with_nss_libs/libnssdev.a $with_nss_libs/libcryptohi.a $with_nss_libs/libcerthi.a $with_nss_libs/libcertdb.a $with_nss_libs/libsecutil.a $with_nss_libs/libnssb.a"

					case "$host" in
						*solaris*)
							nsslibs="$nsslibs $with_nss_libs/libfreeb1.a"
							;;
					esac
				fi
			else
				nsslibs="-lssl3 -lsmime3 -lnss3 -lsoftokn3"
			fi

			AC_CACHE_CHECK([for Mozilla nss libraries], moz_nss_libs,
			[
				LIBS_save=$LIBS
				LDFLAGS="$LDFLAGS -L$with_nspr_libs $nsprlibs -L$with_nss_libs $nsslibs"
				LIBS="$nsslibs $nsprlibs"

				AC_TRY_LINK_FUNC(NSS_Init,
					[moz_nss_libs="yes"],
					[moz_nss_libs="no"])

				if test "x$moz_nss_libs" = "xno"; then
					nsslibs="-lssl3 -lsmime3 -lnss3 -lsoftokn3"
					LDFLAGS="$LDFLAGS -L$with_nspr_libs $nsprlibs -L$with_nss_libs $nsslibs"
					AC_TRY_LINK_FUNC(NSS_Init,
						[moz_nss_libs="yes"],
						[moz_nss_libs="no"])
				fi

				LDFLAGS=$LDFLAGS_save
				LIBS=$LIBS_save
			])

			if test "x$moz_nss_libs" != "xno"; then
				AC_DEFINE(HAVE_NSS)
				AC_DEFINE(HAVE_SSL)

				NSS_LIBS="-L$with_nss_libs $nsslibs"

				if test "$enable_nss" = "static"; then
					msg_nss="Mozilla NSS (static)"
				else
					msg_nss="Mozilla NSS"
				fi

				enable_nss="yes"
			else
				NSS_CFLAGS=""
				NSPR_CFLAGS=""
				NSPR_LIBS=""
				enable_nss="no"
			fi
		else
			AC_MSG_CHECKING(for Mozilla nss libraries)
			AC_MSG_RESULT(no)
		fi

		NSS_CFLAGS="$NSPR_CFLAGS $NSS_CFLAGS"
		NSS_LIBS="$NSPR_LIBS $NSS_LIBS"
	fi

	AC_SUBST(NSS_CFLAGS)
	AC_SUBST(NSS_LIBS)
fi

AM_PATH_GTK_2_0(2.0.0,,AC_MSG_ERROR([
*** GTK+ 2.0 is required to build Pidgin-Encryption; please make sure you have the GTK+
*** development headers installed. The latest version of GTK+ is
*** always available at http://www.gtk.org/.]))
CPPFLAGS="$GTK_CFLAGS $CPPFLAGS"


#
# A little tomfoolery to make this buildable both in the pidgin
# structure and standalone
#
want_plugins=yes
AM_CONDITIONAL(PLUGINS, test "$want_plugins" = "yes")

#
# Setup libtool
#

AM_PROG_LIBTOOL


#
# Party on
#

AM_CONFIG_HEADER(pre-config.h)

AC_OUTPUT([Makefile pixmaps/Makefile intl/Makefile po/Makefile.in])
