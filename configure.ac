# rebuild: autoreconf -fvi 

AC_PREREQ(2.61)

AC_INIT([libmsgxchng], [0.0.1])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([src/msgxchng.c])

AC_PROG_CC
AC_PROG_LIBTOOL

AC_CHECK_HEADERS(msgpack.h,
  [],
  [AC_MSG_ERROR([msgpack header files not found.]); break]
)

AC_CHECK_LIB(msgpack, msgpack_object_print,
  [],
  [AC_MSG_ERROR([msgpack libraries not found.])]
)

AC_OUTPUT(Makefile src/Makefile)