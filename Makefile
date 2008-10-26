
all: test

test: test.py _yahoo2.so
	python test.py

_yahoo2.c: _yahoo2.pyx
	pyrexc _yahoo2.pyx

_yahoo2.so: callbacks.c _yahoo2.c
	python setup.py build_ext --inplace

clean:
	rm _yahoo2.c _yahoo2.h _yahoo2.so