# Copyright (C) 2010-2019 Dzhelil S. Rufat. All Rights Reserved.
from glob import glob

import numpy
from setuptools import setup, Extension

version = '0.1'

include_dirs = [
    'pybindcpp/include',
    '/usr/include/eigen3',
    '/usr/local/include/eigen3',
    numpy.get_include(),
]

headers = [
    *glob('pybindcpp/include/pybindcpp/*.h'),
]

depends = ['setup.py', *headers]
extra_compile_args = [
    '-std=c++11',
    '-g',
    '-DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION',
]
libraries = []

ext_modules = [

    Extension(
        'pybindcpp.core.ufunc',
        sources=[
            'pybindcpp/core/ufunc.cpp',
        ],
        depends=depends,
        include_dirs=include_dirs,
        extra_compile_args=extra_compile_args,
        language="c++",
        libraries=libraries,
    ),

    Extension(
        'pybindcpp.ext.example',
        sources=[
            'pybindcpp/ext/example.cpp',
        ],
        depends=depends,
        include_dirs=include_dirs,
        extra_compile_args=extra_compile_args,
        language="c++",
        libraries=libraries,
    ),

    Extension(
        'pybindcpp.ext.sample',
        sources=[
            'pybindcpp/ext/sample.cpp',
        ],
        depends=depends,
        include_dirs=include_dirs,
        extra_compile_args=extra_compile_args,
        language="c++",
        libraries=libraries,
    ),

    Extension(
        'pybindcpp.ext.ufunc',
        sources=[
            'pybindcpp/ext/ufunc.cpp',
        ],
        depends=depends,
        include_dirs=include_dirs,
        extra_compile_args=extra_compile_args,
        language="c++",
        libraries=libraries,
    ),

    Extension(
        'pybindcpp.ext.eigen',
        sources=[
            'pybindcpp/ext/eigen.cpp',
        ],
        depends=depends,
        include_dirs=include_dirs,
        extra_compile_args=extra_compile_args,
        language="c++",
        libraries=libraries,
    ),

    Extension(
        'pybindcpp.ext.fftw',
        sources=[
            'pybindcpp/ext/fftw.cpp',
        ],
        depends=depends,
        include_dirs=include_dirs,
        extra_compile_args=extra_compile_args,
        language="c++",
        libraries=libraries + ['fftw3'],
    ),

]

setup(
    name='pybindcpp',
    packages=[
        'pybindcpp'
    ],
    package_dir={
        'pybindcpp': 'pybindcpp'
    },
    package_data={
        'pybindcpp': ['include/*.h', 'include/pybindcpp/*.h'],
    },
    ext_modules=ext_modules,
    version=version,
    description='Python Bindings from C++',
    author='Dzhelil Rufat',
    author_email='d@rufat.be',
    license='GPLv3',
)
