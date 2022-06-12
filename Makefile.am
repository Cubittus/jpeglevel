GCC_FLAGS=-march=native -O2 -pipe -fno-common -fconcepts
GCC_WARNINGS_MAIN=-Wall -Wextra -Weffc++ -Wformat=2 -Werror -fmax-errors=10
GCC_WARNINGS_CXX=-Wctor-dtor-privacy -Wnoexcept -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wwrite-strings
GCC_WARNINGS_SUGGEST=-Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wsuggest-override
GCC_WARNINGS_EXTRA1=-Wduplicated-cond -Wuninitialized -Wstrict-overflow -Wtrampolines -Wfloat-equal -Wundef -Wunused-macros -Wconversion
GCC_WARNINGS_EXTRA2=-Wnull-dereference -Wdouble-promotion -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wuseless-cast -Wlogical-op
GCC_WARNINGS_EXTRA3=-Wzero-as-null-pointer-constant -Wmissing-declarations -Wredundant-decls -Wno-virtual-move-assign -Wvla
GCC_WARNINGS_EXTRA4=-Wdisabled-optimization -Wduplicated-branches -Walloc-zero -Wrestrict
GCC_WARNINGS_EXTRA=${GCC_WARNINGS_EXTRA1} ${GCC_WARNINGS_EXTRA2} ${GCC_WARNINGS_EXTRA3} ${GCC_WARNINGS_EXTRA4}
GCC_WARNINGS=${GCC_WARNINGS_MAIN} ${GCC_WARNINGS_CXX} ${GCC_WARNINGS_SUGGEST} ${GCC_WARNINGS_EXTRA}

AM_CFLAGS=${GCC_FLAGS} ${GCC_WARNINGS} -std=gnu2a -Wl,--fatal-warnings
AM_CXXFLAGS=${GCC_FLAGS} ${GCC_WARNINGS} -std=gnu++2a -Wl,--fatal-warnings

AM_MAKEFLAGS=--no-print-directory -j 4

bin_PROGRAMS = jpeglevel

jpeglevel_SOURCES = jpeglevel.cc JPEGFile.cc JPEGFile.h
jpeglevel_LDADD=-lturbojpeg

