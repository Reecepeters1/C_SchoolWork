tritest_application: trilib.h testtri.c trilib.c
	clang374 -o testtri_application testtri.c trilib.h trilib.c