#!/usr/bin/env python

from setuptools import setup, Extension

yahoo2_pyx_module = Extension('_yahoo2',
                              sources=['_yahoo2.pyx', 'callbacks.c'],
                              libraries=['yahoo2'])

setup(name='yahoo2',
      version='0.1',
      author = "Foo",
      description="Play with Python binding for libyahoo2",
      ext_modules=[yahoo2_pyx_module],
      py_modules= ["yahoo2"]
)
