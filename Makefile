
all: test

test: test.py _yahoo2.so
	python test.py

yahoo2_wrap.c: yahoo2.i
	swig -python yahoo2.i

_yahoo2pyx.c: _yahoo2pyx.pyx
	pyrexc _yahoo2pyx.pyx

_yahoo2.so: yahoo2_wrap.c callbacks.c _yahoo2pyx.c
	python setup.py build_ext --inplace
