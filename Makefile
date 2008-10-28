
all: _yahoo2.so

#test: test.py _yahoo2.so
#	python test.py
#
_yahoo2.so: callbacks.c _yahoo2.pyx
	python setup.py build_ext --inplace

clean:
	rm -f _yahoo2.c _yahoo2.h _yahoo2.so yahoo2.pyc