/* $Id$ 
 *
 * pyxmlsec -- A Python binding for XML Security library (XMLSec)
 *
 * Copyright (C) 2003 Easter-eggs, Valery Febvre
 * http://pyxmlsec.labs.libre-entreprise.org/
 * 
 * Author: Valery Febvre <vfebvre@easter-eggs.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <Python.h>

#include "xmlsecmod.h"
#include "parser.h"

PyObject *xmlsec_ParseFile(PyObject *self, PyObject *args) {
  const char *filename;
  xmlDocPtr doc;
  PyObject *ret;

  if (!PyArg_ParseTuple(args, "s:parseFile", &filename))
    return NULL;

  doc = xmlSecParseFile(filename);
  if (doc == NULL) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  
  ret = PyCObject_FromVoidPtrAndDesc((void *) doc, (char *) "xmlDocPtr", NULL);
  return (ret);
}

PyObject *xmlsec_ParseMemory(PyObject *self, PyObject *args) {
  const xmlSecByte *buffer;
  xmlSecSize size;
  int recovery;
  xmlDocPtr doc;
  PyObject *ret;

  if (!PyArg_ParseTuple(args, "sii:parseMemory", &buffer, &size, &recovery))
    return NULL;

  doc = xmlSecParseMemory(buffer, size, recovery);
  if (doc == NULL) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  
  ret = PyCObject_FromVoidPtrAndDesc((void *) doc, (char *) "xmlDocPtr", NULL);
  return (ret);
}

PyObject *xmlsec_ParseMemoryExt(PyObject *self, PyObject *args) {
  const xmlSecByte *prefix;
  xmlSecSize prefixSize;
  const xmlSecByte *buffer;
  xmlSecSize bufferSize;
  const xmlSecByte *postfix;
  xmlSecSize postfixSize;
  xmlDocPtr doc;
  PyObject *ret;

  if (!PyArg_ParseTuple(args, "sisisi:parseMemoryExt", &prefix, &prefixSize,
			&buffer, &bufferSize, &postfix, &postfixSize))
    return NULL;

  doc = xmlSecParseMemoryExt(prefix, prefixSize,
			     buffer, bufferSize,
			     postfix, postfixSize);
  if (doc == NULL) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  
  ret = PyCObject_FromVoidPtrAndDesc((void *) doc, (char *) "xmlDocPtr", NULL);
  return (ret);
}

PyObject *xmlsec_TransformXmlParserId(PyObject *self, PyObject *args) {
  return PyCObject_FromVoidPtr((void *) xmlSecTransformXmlParserId, NULL);
}
