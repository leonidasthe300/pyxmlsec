#!/usr/bin/env python
# -*- coding: UTF-8 -*-
#
# $Id$
#
# PyXMLSec - Python bindings for XML Security library (XMLSec)
#
# Copyright (C) 2003-2004 Easter-eggs, Valéry Febvre
# http://pyxmlsec.labs.libre-entreprise.org
#
# Author: Valéry Febvre <vfebvre@easter-eggs.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

__doc__ = """Python bindings for XMLSec Library

PyXMLSec is a set of Python bindings for XML Security Library (XMLSec).
"""

classifiers = """\
Development Status :: 2 - Pre-Alpha
Intended Audience :: Developers
License :: OSI Approved :: GNU General Public License (GPL)
Operating System :: MacOS :: MacOS X
Operating System :: POSIX
Programming Language :: C
Programming Language :: Python
Topic :: Software Development :: Libraries :: Python Modules
"""

from distutils.core import setup, Extension
import sys, commands

# the crypto engine name : openssl, gnutls or nss
xmlsec1_crypto = "openssl"
#xmlsec1_crypto = "gnutls"
#xmlsec1_crypto = "nss"

define_macros = []
include_dirs  = []
library_dirs  = []
libraries     = []

def extract_cflags(cflags):
    global define_macros, include_dirs
    list = cflags.split(' ')
    for flag in list:
        if flag == '':
            continue
        flag = flag.replace("\\\"", "")
        if flag[:2] == "-I":
            if flag[2:] not in include_dirs:
                include_dirs.append(flag[2:])
        elif flag[:2] == "-D":
            t = tuple(flag[2:].split('='))
            if t not in define_macros:
                define_macros.append(t)
        else:
            print "Warning : cflag %s skipped" % flag

def extract_libs(libs):
    global library_dirs, libraries
    list = libs.split(' ')
    for flag in list:
        if flag == '':
            continue
        if flag[:2] == "-l":
            if flag[2:] not in libraries:
                libraries.append(flag[2:])
        elif flag[:2] == "-L":
            if flag[2:] not in library_dirs:
                library_dirs.append(flag[2:])
        else:
            print "Warning : linker flag %s skipped" % flag


libxml2_cflags = commands.getoutput('pkg-config libxml-2.0 --cflags')
if libxml2_cflags[:2] not in ["-I", "-D"]:
    libxml2_cflags = commands.getoutput('xml2-config --cflags')
if libxml2_cflags[:2] not in ["-I", "-D"]:
    print "Error : cannot get LibXML2 pre-processor and compiler flags"

libxml2_libs = commands.getoutput('pkg-config libxml-2.0 --libs')
if libxml2_libs[:2] not in ["-l", "-L"]:
    libxml2_libs = commands.getoutput('xml2-config --libs')
if libxml2_libs[:2] not in ["-l", "-L"]:
    print "Error : cannot get LibXML2 linker flags"

cmd = 'pkg-config xmlsec1-%s --cflags' % xmlsec1_crypto
xmlsec1_cflags = commands.getoutput(cmd)
if xmlsec1_cflags[:2] not in ["-I", "-D"]:
    cmd = 'xmlsec1-config --cflags --crypto=%s' % xmlsec1_crypto
    xmlsec1_cflags = commands.getoutput(cmd)
if xmlsec1_cflags[:2] not in ["-I", "-D"]:
    print "Error : cannot get XMLSec1 pre-processor and compiler flags"

cmd = 'pkg-config xmlsec1-%s --libs' % xmlsec1_crypto
xmlsec1_libs = commands.getoutput(cmd)
if xmlsec1_libs[:2] not in ["-l", "-L"]:
    cmd = 'xmlsec1-config --libs --crypto=%s' % xmlsec1_crypto
    xmlsec1_libs = commands.getoutput(cmd)
if xmlsec1_libs[:2] not in ["-l", "-L"]:
    print "Error : cannot get XMLSec1 linker flags"

#print libxml2_cflags
#print libxml2_libs
#print xmlsec1_cflags
#print xmlsec1_libs

extract_cflags(libxml2_cflags)
extract_libs(libxml2_libs)

extract_cflags(xmlsec1_cflags)
extract_libs(xmlsec1_libs)

#print define_macros
#print include_dirs
#print library_dirs
#print libraries

em = Extension("xmlsecmod",
               sources = ["wrap_objs.c",
                          "xmlsecmod.c", "app.c", "base64.c", "buffer.c",
                          "keyinfo.c", "keys.c", "keysdata.c", "keysmngr.c",
                          "list.c", "membuf.c", "nodeset.c", "parser.c",
                          "templates.c", "transforms.c", "version.c",
                          "xmldsig.c", "xmlenc.c", "xmlsec.c", "xmltree.c",
                          "x509.c"],
               define_macros = define_macros,
               include_dirs  = include_dirs,
               library_dirs  = library_dirs,
               libraries     = libraries
               )

doclines = __doc__.split("\n")

setup(name = "PyXMLSec",
      version = "0.20040124",
      description = doclines[0],
      long_description = "\n" . join(doclines[2:]),
      author = "Valéry Febvre",
      author_email = "vfebvre@easter-eggs.com",
      license = "GNU GPL",
      platforms = ["any"],
      url = "http://pyxmlsec.labs.libre-entreprise.org",
      ext_modules = [em],
      py_modules = ["xmlsec", "xmlsec_strings"]
)
