#!/usr/bin/env python

from distutils.core import setup, Extension

yahoo2_module = Extension('_yahoo2',
                          sources=['yahoo2_wrap.c', 'callbacks.c'],
                          libraries=['yahoo2'])

yahoo2_pyx_module = Extension('_yahoo2pyx',
                              sources=['_yahoo2pyx.c', 'callbacks.c'],
                              libraries=['yahoo2'])

setup(name='yahoo2',
      version='0.1',
      author = "Foo",
      description="Play with SWIG wrapping of libyahoo2",
      ext_modules=[yahoo2_module, yahoo2_pyx_module],
      py_modules= ["yahoo2"]
)
