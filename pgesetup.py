#!/usr/bin/env python

from distutils.core import setup

long_description = """pge is a Python module which implements a
basic physics game engine for pygame"""


setup (name="pge",
       version="2.0",
       py_modules = ['pge', 'pgeif', 'pgeplayback'],
       description="pge is a Python module which implements a basic physics game engine for pygame",
       author="Gaius Mulley",
       author_email="gaius@gnu.org",
       url="http://floppsie.comp.glam.ac.uk/pge",
       license="GPL license",
       platforms="UNIX",
)
