/* $Id$ 
 *
 * PyXMLSec - Python bindings for XML Security library (XMLSec)
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

#include "wrap_objs.h"

#include "nodeset.h"

PyObject *xmlsec_NodeSetCreate(PyObject *self, PyObject *args) {
  PyObject *doc_obj, *nodes_obj;
  xmlDocPtr doc;
  xmlNodeSetPtr nodes;
  xmlSecNodeSetType type;
  xmlSecNodeSetPtr nset;
  PyObject *ret;

  if (!PyArg_ParseTuple(args, "OOi:nodeSetCreate", &doc_obj, &nodes_obj, &type))
    return NULL;

  doc = xmlDocPtr_get(doc_obj);
  nodes = xmlNodeSetPtr_get(nodes_obj);
  nset = xmlSecNodeSetCreate(doc, nodes, type);
  
  ret = PyCObject_FromVoidPtrAndDesc((void *) nset,
				     (char *) "xmlSecNodeSetPtr", NULL);
  return (ret);
}

PyObject *xmlsec_NodeSetDestroy(PyObject *self, PyObject *args) {
  PyObject *nset_obj;
  xmlSecNodeSetPtr nset;

  if (!PyArg_ParseTuple(args, "O:nodeSetDestroy", &nset_obj))
    return NULL;

  nset = xmlSecNodeSetPtr_get(nset_obj);
  xmlSecNodeSetDestroy(nset);

  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *xmlsec_NodeSetDocDestroy(PyObject *self, PyObject *args) {
  PyObject *nset_obj;
  xmlSecNodeSetPtr nset;

  if (!PyArg_ParseTuple(args, "O:nodeSetDocDestroy", &nset_obj))
    return NULL;

  nset = xmlSecNodeSetPtr_get(nset_obj);
  xmlSecNodeSetDocDestroy(nset);

  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *xmlsec_NodeSetContains(PyObject *self, PyObject *args) {
  PyObject *nset_obj, *node_obj, *parent_obj;
  xmlSecNodeSetPtr nset;
  xmlNodePtr node;
  xmlNodePtr parent;
  int ret;

  if (!PyArg_ParseTuple(args, "OOO:nodeSetContains", &nset_obj, &node_obj,
			&parent_obj))
    return NULL;

  nset = xmlSecNodeSetPtr_get(nset_obj);
  node = xmlNodePtr_get(node_obj);
  parent = xmlNodePtr_get(parent_obj);
  ret = xmlSecNodeSetContains(nset, node, parent);

  return (wrap_int(ret));
}

PyObject *xmlsec_NodeSetAdd(PyObject *self, PyObject *args) {
  PyObject *nset_obj, *newNSet_obj;
  xmlSecNodeSetPtr nset;
  xmlSecNodeSetPtr newNSet;
  xmlSecNodeSetOp op;
  xmlSecNodeSetPtr cnset;
  PyObject *ret;

  if (!PyArg_ParseTuple(args, "OOi:nodeSetAdd", &nset_obj, &newNSet_obj, &op))
    return NULL;

  nset = xmlSecNodeSetPtr_get(nset_obj);
  newNSet = xmlSecNodeSetPtr_get(newNSet_obj);
  cnset = xmlSecNodeSetAdd(nset, newNSet, op);

  ret = PyCObject_FromVoidPtrAndDesc((void *) cnset,
				     (char *) "xmlSecNodeSetPtr", NULL);
  return (ret);
}

PyObject *xmlsec_NodeSetAddList(PyObject *self, PyObject *args) {
  PyObject *nset_obj, *newNSet_obj;
  xmlSecNodeSetPtr nset;
  xmlSecNodeSetPtr newNSet;
  xmlSecNodeSetOp op;
  xmlSecNodeSetPtr cnset;
  PyObject *ret;

  if (!PyArg_ParseTuple(args, "OOi:nodeSetAddList", &nset_obj, &newNSet_obj, &op))
    return NULL;

  nset = xmlSecNodeSetPtr_get(nset_obj);
  newNSet = xmlSecNodeSetPtr_get(newNSet_obj);
  cnset = xmlSecNodeSetAddList(nset, newNSet, op);

  ret = PyCObject_FromVoidPtrAndDesc((void *) cnset,
				     (char *) "xmlSecNodeSetPtr", NULL);
  return (ret);
}

PyObject *xmlsec_NodeSetGetChildren(PyObject *self, PyObject *args) {
  PyObject *doc_obj, *parent_obj;
  xmlDocPtr doc;
  xmlNodePtr parent = NULL;
  int withComments, invert;
  xmlSecNodeSetPtr cnset;
  PyObject *ret;

  if (!PyArg_ParseTuple(args, "OOii:nodeSetGetChildren", &doc_obj, &parent_obj,
			&withComments, &invert))
    return NULL;

  doc = xmlDocPtr_get(doc_obj);
  /* parent may be NULL */
  if (parent_obj != Py_None) {
    parent = xmlNodePtr_get(parent_obj);
  }
  cnset = xmlSecNodeSetGetChildren(doc, parent, withComments, invert);

  ret = PyCObject_FromVoidPtrAndDesc((void *) cnset,
				     (char *) "xmlSecNodeSetPtr", NULL);
  return (ret);
}

PyObject *xmlsec_NodeSetWalk(PyObject *self, PyObject *args) {
  PyObject *nset_obj, *walkFunc_obj, *data_obj;
  xmlSecNodeSetPtr nset;
  int ret;

  if (!PyArg_ParseTuple(args, "OOO:nodeSetWalk", &nset_obj, &walkFunc_obj,
			&data_obj))
    return NULL;

  nset = xmlSecNodeSetPtr_get(nset_obj);
  ret = xmlSecNodeSetWalk(nset, PyCObject_AsVoidPtr(walkFunc_obj),
			  PyCObject_AsVoidPtr(data_obj));

  return (wrap_int(ret));
}

PyObject *xmlsec_NodeSetDumpTextNodes(PyObject *self, PyObject *args) {
  PyObject *nset_obj, *out_obj;
  xmlSecNodeSetPtr nset;
  xmlOutputBufferPtr out;
  int ret;

  if (!PyArg_ParseTuple(args, "OO:nodeSetDumpTextNodes", &nset_obj, &out_obj))
    return NULL;

  nset = xmlSecNodeSetPtr_get(nset_obj);
  out = xmlOutputBufferPtr_get(out_obj);
  ret = xmlSecNodeSetDumpTextNodes(nset, out);

  return (wrap_int(ret));
}

PyObject *xmlsec_NodeSetDebugDump(PyObject *self, PyObject *args) {
  PyObject *nset_obj;
  xmlSecNodeSetPtr nset;
  const char *output_path;
  FILE *output;

  if (!PyArg_ParseTuple(args, "Os:nodeSetDebugDump", &nset_obj, &output_path))
    return NULL;

  nset = xmlSecNodeSetPtr_get(nset_obj);
  output = fopen(output_path, "a+");
  xmlSecNodeSetDebugDump(nset, output);
  fclose(output);

  Py_INCREF(Py_None);
  return Py_None;
}
