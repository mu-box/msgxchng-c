# -*- mode: Makefile; tab-width: 4; indent-tabs-mode: 1; st-rulers: [70] -*-
# vim: ts=8 sw=8 ft=Makefile noet

AM_CPPFLAGS = -I$(top_srcdir)/include

TESTS = run-tests

check_PROGRAMS = run-tests

run_tests_SOURCES = run-test.c

run_tests_LDADD = $(top_srcdir)/src/libmsgxchng.la
