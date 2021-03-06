/* -- THIS FILE IS GENERATED - DO NOT EDIT *//* -*- Mode: C; c-basic-offset: 4 -*- */

#include <Python.h>



#line 3 "src/gwp-py-mappings.override"
#include <Python.h>
#include <pygobject.h>
#include "global.h"
#include "race.h"
#include "gwp-engspec.h"
#include "gwp-hullspec.h"
#include "gwp-beamspec.h"
#include "gwp-torpspec.h"
#include "gwp-object.h"
#include "gwp-planet.h"
#include "gwp-flying-object.h"
#include "gwp-ion-storm.h"
#include "gwp-ship.h"
#include "gwp-starbase.h"
#include "gwp-location.h"
#include "gwp-minefield.h"
#include "gwp-py-functions.h"
#include "gwp-race.h"
#include "gwp-starchart.h"
#include "gwp-marker.h"
#line 29 "src/gwp-py-mappings.c"


/* ---------- types from other modules ---------- */
static PyTypeObject *_PyGObject_Type;
#define PyGObject_Type (*_PyGObject_Type)


/* ---------- forward type declarations ---------- */
PyTypeObject PyGwpBeamSpec_Type;
PyTypeObject PyGwpEngSpec_Type;
PyTypeObject PyGwpGameState_Type;
PyTypeObject PyGwpHullSpec_Type;
PyTypeObject PyGwpObject_Type;
PyTypeObject PyGwpMinefield_Type;
PyTypeObject PyGwpMarker_Type;
PyTypeObject PyGwpLocation_Type;
PyTypeObject PyGwpFlyingObject_Type;
PyTypeObject PyGwpIonStorm_Type;
PyTypeObject PyGwpPlanet_Type;
PyTypeObject PyGwpRace_Type;
PyTypeObject PyGwpShip_Type;
PyTypeObject PyGwpStarbase_Type;
PyTypeObject PyGwpStarchart_Type;
PyTypeObject PyGwpTorpSpec_Type;


/* ----------- GwpBeamSpec ----------- */

static PyObject *
_wrap_gwp_beamspec_get_id(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_id(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_id", kwlist, &id))
        return NULL;
    gwp_beamspec_set_id(GWP_BEAM_SPEC(self->obj), id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_beamspec_get_name(GWP_BEAM_SPEC(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_set_name(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpBeamSpec.set_name", kwlist, &name))
        return NULL;
    gwp_beamspec_set_name(GWP_BEAM_SPEC(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_cost(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_cost(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_cost(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "cost", NULL };
    int cost;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_cost", kwlist, &cost))
        return NULL;
    gwp_beamspec_set_cost(GWP_BEAM_SPEC(self->obj), cost);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_tritanium(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tri", NULL };
    int tri;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_tritanium", kwlist, &tri))
        return NULL;
    gwp_beamspec_set_tritanium(GWP_BEAM_SPEC(self->obj), tri);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_duranium(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dur", NULL };
    int dur;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_duranium", kwlist, &dur))
        return NULL;
    gwp_beamspec_set_duranium(GWP_BEAM_SPEC(self->obj), dur);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_molybdenum(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mol", NULL };
    int mol;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_molybdenum", kwlist, &mol))
        return NULL;
    gwp_beamspec_set_molybdenum(GWP_BEAM_SPEC(self->obj), mol);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_mass(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_mass(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_mass(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mass", NULL };
    int mass;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_mass", kwlist, &mass))
        return NULL;
    gwp_beamspec_set_mass(GWP_BEAM_SPEC(self->obj), mass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_tech_level(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_tech_level(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_tech_level(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tl", NULL };
    int tl;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_tech_level", kwlist, &tl))
        return NULL;
    gwp_beamspec_set_tech_level(GWP_BEAM_SPEC(self->obj), tl);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_kill_value(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_kill_value(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_kill_value(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "kv", NULL };
    int kv;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_kill_value", kwlist, &kv))
        return NULL;
    gwp_beamspec_set_kill_value(GWP_BEAM_SPEC(self->obj), kv);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_beamspec_get_damage_value(PyGObject *self)
{
    int ret;

    ret = gwp_beamspec_get_damage_value(GWP_BEAM_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_beamspec_set_damage_value(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dv", NULL };
    int dv;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpBeamSpec.set_damage_value", kwlist, &dv))
        return NULL;
    gwp_beamspec_set_damage_value(GWP_BEAM_SPEC(self->obj), dv);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpBeamSpec_methods[] = {
    { "get_id", (PyCFunction)_wrap_gwp_beamspec_get_id, METH_NOARGS },
    { "set_id", (PyCFunction)_wrap_gwp_beamspec_set_id, METH_VARARGS|METH_KEYWORDS },
    { "get_name", (PyCFunction)_wrap_gwp_beamspec_get_name, METH_NOARGS },
    { "set_name", (PyCFunction)_wrap_gwp_beamspec_set_name, METH_VARARGS|METH_KEYWORDS },
    { "get_cost", (PyCFunction)_wrap_gwp_beamspec_get_cost, METH_NOARGS },
    { "set_cost", (PyCFunction)_wrap_gwp_beamspec_set_cost, METH_VARARGS|METH_KEYWORDS },
    { "get_tritanium", (PyCFunction)_wrap_gwp_beamspec_get_tritanium, METH_NOARGS },
    { "set_tritanium", (PyCFunction)_wrap_gwp_beamspec_set_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_duranium", (PyCFunction)_wrap_gwp_beamspec_get_duranium, METH_NOARGS },
    { "set_duranium", (PyCFunction)_wrap_gwp_beamspec_set_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_molybdenum", (PyCFunction)_wrap_gwp_beamspec_get_molybdenum, METH_NOARGS },
    { "set_molybdenum", (PyCFunction)_wrap_gwp_beamspec_set_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_mass", (PyCFunction)_wrap_gwp_beamspec_get_mass, METH_NOARGS },
    { "set_mass", (PyCFunction)_wrap_gwp_beamspec_set_mass, METH_VARARGS|METH_KEYWORDS },
    { "get_tech_level", (PyCFunction)_wrap_gwp_beamspec_get_tech_level, METH_NOARGS },
    { "set_tech_level", (PyCFunction)_wrap_gwp_beamspec_set_tech_level, METH_VARARGS|METH_KEYWORDS },
    { "get_kill_value", (PyCFunction)_wrap_gwp_beamspec_get_kill_value, METH_NOARGS },
    { "set_kill_value", (PyCFunction)_wrap_gwp_beamspec_set_kill_value, METH_VARARGS|METH_KEYWORDS },
    { "get_damage_value", (PyCFunction)_wrap_gwp_beamspec_get_damage_value, METH_NOARGS },
    { "set_damage_value", (PyCFunction)_wrap_gwp_beamspec_set_damage_value, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpBeamSpec_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.BeamSpec",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpBeamSpec_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpEngSpec ----------- */

static PyObject *
_wrap_gwp_engspec_get_fuel_usage_full(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dist", "speed", "mass", NULL };
    int speed, mass, ret;
    double dist;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dii:GwpEngSpec.get_fuel_usage_full", kwlist, &dist, &speed, &mass))
        return NULL;
    ret = gwp_engspec_get_fuel_usage_full(GWP_ENG_SPEC(self->obj), dist, speed, mass);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_engspec_get_id(PyGObject *self)
{
    int ret;

    ret = gwp_engspec_get_id(GWP_ENG_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_engspec_set_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpEngSpec.set_id", kwlist, &id))
        return NULL;
    gwp_engspec_set_id(GWP_ENG_SPEC(self->obj), id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_engspec_get_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_engspec_get_name(GWP_ENG_SPEC(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_engspec_set_name(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpEngSpec.set_name", kwlist, &name))
        return NULL;
    gwp_engspec_set_name(GWP_ENG_SPEC(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_engspec_get_cost(PyGObject *self)
{
    int ret;

    ret = gwp_engspec_get_cost(GWP_ENG_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_engspec_set_cost(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "cost", NULL };
    int cost;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpEngSpec.set_cost", kwlist, &cost))
        return NULL;
    gwp_engspec_set_cost(GWP_ENG_SPEC(self->obj), cost);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_engspec_get_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_engspec_get_tritanium(GWP_ENG_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_engspec_set_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tri", NULL };
    int tri;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpEngSpec.set_tritanium", kwlist, &tri))
        return NULL;
    gwp_engspec_set_tritanium(GWP_ENG_SPEC(self->obj), tri);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_engspec_get_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_engspec_get_duranium(GWP_ENG_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_engspec_set_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dur", NULL };
    int dur;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpEngSpec.set_duranium", kwlist, &dur))
        return NULL;
    gwp_engspec_set_duranium(GWP_ENG_SPEC(self->obj), dur);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_engspec_get_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_engspec_get_molybdenum(GWP_ENG_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_engspec_set_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mol", NULL };
    int mol;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpEngSpec.set_molybdenum", kwlist, &mol))
        return NULL;
    gwp_engspec_set_molybdenum(GWP_ENG_SPEC(self->obj), mol);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_engspec_get_tech_level(PyGObject *self)
{
    int ret;

    ret = gwp_engspec_get_tech_level(GWP_ENG_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_engspec_set_tech_level(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tl", NULL };
    int tl;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpEngSpec.set_tech_level", kwlist, &tl))
        return NULL;
    gwp_engspec_set_tech_level(GWP_ENG_SPEC(self->obj), tl);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_engspec_get_fuel_usage(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "warp", NULL };
    int warp, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpEngSpec.get_fuel_usage", kwlist, &warp))
        return NULL;
    ret = gwp_engspec_get_fuel_usage(GWP_ENG_SPEC(self->obj), warp);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_engspec_set_fuel_usage(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "warp", "fuel", NULL };
    int warp, fuel;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpEngSpec.set_fuel_usage", kwlist, &warp, &fuel))
        return NULL;
    gwp_engspec_set_fuel_usage(GWP_ENG_SPEC(self->obj), warp, fuel);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpEngSpec_methods[] = {
    { "get_fuel_usage_full", (PyCFunction)_wrap_gwp_engspec_get_fuel_usage_full, METH_VARARGS|METH_KEYWORDS },
    { "get_id", (PyCFunction)_wrap_gwp_engspec_get_id, METH_NOARGS },
    { "set_id", (PyCFunction)_wrap_gwp_engspec_set_id, METH_VARARGS|METH_KEYWORDS },
    { "get_name", (PyCFunction)_wrap_gwp_engspec_get_name, METH_NOARGS },
    { "set_name", (PyCFunction)_wrap_gwp_engspec_set_name, METH_VARARGS|METH_KEYWORDS },
    { "get_cost", (PyCFunction)_wrap_gwp_engspec_get_cost, METH_NOARGS },
    { "set_cost", (PyCFunction)_wrap_gwp_engspec_set_cost, METH_VARARGS|METH_KEYWORDS },
    { "get_tritanium", (PyCFunction)_wrap_gwp_engspec_get_tritanium, METH_NOARGS },
    { "set_tritanium", (PyCFunction)_wrap_gwp_engspec_set_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_duranium", (PyCFunction)_wrap_gwp_engspec_get_duranium, METH_NOARGS },
    { "set_duranium", (PyCFunction)_wrap_gwp_engspec_set_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_molybdenum", (PyCFunction)_wrap_gwp_engspec_get_molybdenum, METH_NOARGS },
    { "set_molybdenum", (PyCFunction)_wrap_gwp_engspec_set_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_tech_level", (PyCFunction)_wrap_gwp_engspec_get_tech_level, METH_NOARGS },
    { "set_tech_level", (PyCFunction)_wrap_gwp_engspec_set_tech_level, METH_VARARGS|METH_KEYWORDS },
    { "get_fuel_usage", (PyCFunction)_wrap_gwp_engspec_get_fuel_usage, METH_VARARGS|METH_KEYWORDS },
    { "set_fuel_usage", (PyCFunction)_wrap_gwp_engspec_set_fuel_usage, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpEngSpec_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.EngSpec",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpEngSpec_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpGameState ----------- */

static int
_wrap_gwp_game_state_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.GameState.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_game_state_postinit(PyGObject *self)
{
    gwp_game_state_postinit(GWP_GAME_STATE(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_full_path(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "filename", NULL };
    char *filename;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpGameState.get_full_path", kwlist, &filename))
        return NULL;
    ret = gwp_game_state_get_full_path(GWP_GAME_STATE(self->obj), filename);
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_last_coords(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    int x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpGameState.set_last_coords", kwlist, &x, &y))
        return NULL;
    gwp_game_state_set_last_coords(GWP_GAME_STATE(self->obj), x, y);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_dat_filename(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "prefix", "suffix", NULL };
    char *prefix, *suffix;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ss:GwpGameState.get_dat_filename", kwlist, &prefix, &suffix))
        return NULL;
    ret = gwp_game_state_get_dat_filename(GWP_GAME_STATE(self->obj), prefix, suffix);
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_name(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpGameState.set_name", kwlist, &name))
        return NULL;
    gwp_game_state_set_name(GWP_GAME_STATE(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_name(PyGObject *self)
{
    const gchar *ret;

    ret = gwp_game_state_get_name(GWP_GAME_STATE(self->obj));
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_dir(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dir", NULL };
    char *dir;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpGameState.set_dir", kwlist, &dir))
        return NULL;
    gwp_game_state_set_dir(GWP_GAME_STATE(self->obj), dir);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_dir(PyGObject *self)
{
    gchar *ret;

    ret = gwp_game_state_get_dir(GWP_GAME_STATE(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_starchart_zoom(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "zoom", NULL };
    double zoom;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "d:GwpGameState.set_starchart_zoom", kwlist, &zoom))
        return NULL;
    gwp_game_state_set_starchart_zoom(GWP_GAME_STATE(self->obj), zoom);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_starchart_zoom(PyGObject *self)
{
    double ret;

    ret = gwp_game_state_get_starchart_zoom(GWP_GAME_STATE(self->obj));
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_gwp_game_state_set_race(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race_num", NULL };
    int race_num;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_race", kwlist, &race_num))
        return NULL;
    gwp_game_state_set_race(GWP_GAME_STATE(self->obj), race_num);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_race_nr(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_race_nr(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_last_x_coord(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", NULL };
    int x;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_last_x_coord", kwlist, &x))
        return NULL;
    gwp_game_state_set_last_x_coord(GWP_GAME_STATE(self->obj), x);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_last_x_coord(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_last_x_coord(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_last_y_coord(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "y", NULL };
    int y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_last_y_coord", kwlist, &y))
        return NULL;
    gwp_game_state_set_last_y_coord(GWP_GAME_STATE(self->obj), y);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_last_y_coord(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_last_y_coord(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_turn_number(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "turn", NULL };
    int turn;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_turn_number", kwlist, &turn))
        return NULL;
    gwp_game_state_set_turn_number(GWP_GAME_STATE(self->obj), turn);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_turn_number(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_turn_number(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_player_email(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "pe", NULL };
    char *pe;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpGameState.set_player_email", kwlist, &pe))
        return NULL;
    gwp_game_state_set_player_email(GWP_GAME_STATE(self->obj), pe);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_player_email(PyGObject *self)
{
    gchar *ret;

    ret = gwp_game_state_get_player_email(GWP_GAME_STATE(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_host_email(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "he", NULL };
    char *he;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpGameState.set_host_email", kwlist, &he))
        return NULL;
    gwp_game_state_set_host_email(GWP_GAME_STATE(self->obj), he);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_email(PyGObject *self)
{
    gchar *ret;

    ret = gwp_game_state_get_host_email(GWP_GAME_STATE(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_trn_dir(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dir", NULL };
    char *dir;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpGameState.set_trn_dir", kwlist, &dir))
        return NULL;
    gwp_game_state_set_trn_dir(GWP_GAME_STATE(self->obj), dir);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_trn_dir(PyGObject *self)
{
    gchar *ret;

    ret = gwp_game_state_get_trn_dir(GWP_GAME_STATE(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_rst_dir(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dir", NULL };
    char *dir;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpGameState.set_rst_dir", kwlist, &dir))
        return NULL;
    gwp_game_state_set_rst_dir(GWP_GAME_STATE(self->obj), dir);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_rst_dir(PyGObject *self)
{
    gchar *ret;

    ret = gwp_game_state_get_rst_dir(GWP_GAME_STATE(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_host_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "type", NULL };
    int type;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_type", kwlist, &type))
        return NULL;
    gwp_game_state_set_host_type(GWP_GAME_STATE(self->obj), type);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_type(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_type(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_planet_names(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "show", NULL };
    int show;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_planet_names", kwlist, &show))
        return NULL;
    gwp_game_state_set_planet_names(GWP_GAME_STATE(self->obj), show);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_planet_names(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_planet_names(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_scanner_area(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "show", NULL };
    int show;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_scanner_area", kwlist, &show))
        return NULL;
    gwp_game_state_set_scanner_area(GWP_GAME_STATE(self->obj), show);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_scanner_area(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_scanner_area(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_minefields(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "show", NULL };
    int show;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_minefields", kwlist, &show))
        return NULL;
    gwp_game_state_set_minefields(GWP_GAME_STATE(self->obj), show);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_minefields(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_minefields(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_ion_storms(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "show", NULL };
    int show;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_ion_storms", kwlist, &show))
        return NULL;
    gwp_game_state_set_ion_storms(GWP_GAME_STATE(self->obj), show);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_ion_storms(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_ion_storms(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_extra_panel_open(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "show", NULL };
    int show;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_extra_panel_open", kwlist, &show))
        return NULL;
    gwp_game_state_set_extra_panel_open(GWP_GAME_STATE(self->obj), show);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_extra_panel_open(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_extra_panel_open(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_get_selected_ship(PyGObject *self)
{
    GwpShip *ret;

    ret = gwp_game_state_get_selected_ship(GWP_GAME_STATE(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gwp_game_state_get_selected_planet(PyGObject *self)
{
    GwpPlanet *ret;

    ret = gwp_game_state_get_selected_planet(GWP_GAME_STATE(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gwp_game_state_get_host_recycle_col_ship(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_recycle_col_ship(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_recycle_col_ship(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "percent", NULL };
    int percent;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_recycle_col_ship", kwlist, &percent))
        return NULL;
    gwp_game_state_set_host_recycle_col_ship(GWP_GAME_STATE(self->obj), percent);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_set_host_large_meteor_impact(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "percent", NULL };
    int percent;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_large_meteor_impact", kwlist, &percent))
        return NULL;
    gwp_game_state_set_host_large_meteor_impact(GWP_GAME_STATE(self->obj), percent);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_large_meteor_impact(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_large_meteor_impact(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_space_mines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_space_mines", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_space_mines(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_space_mines(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_space_mines(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_get_host_alchemy_ships(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_alchemy_ships(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_alchemy_ships(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_alchemy_ships", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_alchemy_ships(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_delete_old_msgs(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_delete_old_msgs(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_delete_old_msgs(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_delete_old_msgs", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_delete_old_msgs(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_disable_pwd(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_disable_pwd(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_disable_pwd(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_disable_pwd", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_disable_pwd(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_rebel_build_fighters(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_rebel_build_fighters(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_rebel_build_fighters(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_rebel_build_fighters", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_rebel_build_fighters(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_colonial_build_fighters(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_colonial_build_fighters(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_colonial_build_fighters(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_colonial_build_fighters", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_colonial_build_fighters(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_robots_build_fighters(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_robots_build_fighters(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_robots_build_fighters(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_robots_build_fighters", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_robots_build_fighters(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_cloak_failure(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_cloak_failure(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_cloak_failure(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "percent", NULL };
    int percent;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_cloak_failure", kwlist, &percent))
        return NULL;
    gwp_game_state_set_host_cloak_failure(GWP_GAME_STATE(self->obj), percent);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_priv_rob_cloak(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_priv_rob_cloak(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_priv_rob_cloak(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_priv_rob_cloak", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_priv_rob_cloak(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_dark_sense_range(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_dark_sense_range(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_dark_sense_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "percent", NULL };
    int percent;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_dark_sense_range", kwlist, &percent))
        return NULL;
    gwp_game_state_set_host_dark_sense_range(GWP_GAME_STATE(self->obj), percent);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_ground_attack_ratio(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", NULL };
    int race, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.get_host_ground_attack_ratio", kwlist, &race))
        return NULL;
    ret = gwp_game_state_get_host_ground_attack_ratio(GWP_GAME_STATE(self->obj), race);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_ground_attack_ratio(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", "ratio", NULL };
    int race, ratio;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpGameState.set_host_ground_attack_ratio", kwlist, &race, &ratio))
        return NULL;
    gwp_game_state_set_host_ground_attack_ratio(GWP_GAME_STATE(self->obj), race, ratio);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_ships_visible_range(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_ships_visible_range(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_ships_visible_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "range", NULL };
    int range;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_ships_visible_range", kwlist, &range))
        return NULL;
    gwp_game_state_set_host_ships_visible_range(GWP_GAME_STATE(self->obj), range);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_lizard_hiss_mission(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_lizard_hiss_mission(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_lizard_hiss_mission(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "hiss", NULL };
    int hiss;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_lizard_hiss_mission", kwlist, &hiss))
        return NULL;
    gwp_game_state_set_host_lizard_hiss_mission(GWP_GAME_STATE(self->obj), hiss);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_rebel_ground_attack(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_rebel_ground_attack(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_rebel_ground_attack(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_rebel_ground_attack", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_rebel_ground_attack(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_fed_super_refit(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_fed_super_refit(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_fed_super_refit(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_fed_super_refit", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_fed_super_refit(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_crystal_web_mines(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_crystal_web_mines(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_crystal_web_mines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_crystal_web_mines", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_crystal_web_mines(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_ground_defense_ratio(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", NULL };
    int race, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.get_host_ground_defense_ratio", kwlist, &race))
        return NULL;
    ret = gwp_game_state_get_host_ground_defense_ratio(GWP_GAME_STATE(self->obj), race);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_ground_defense_ratio(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", "ration", NULL };
    int race, ration;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpGameState.set_host_ground_defense_ratio", kwlist, &race, &ration))
        return NULL;
    gwp_game_state_set_host_ground_defense_ratio(GWP_GAME_STATE(self->obj), race, ration);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_cloak_fuel_use(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_cloak_fuel_use(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_cloak_fuel_use(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "use", NULL };
    int use;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_cloak_fuel_use", kwlist, &use))
        return NULL;
    gwp_game_state_set_host_cloak_fuel_use(GWP_GAME_STATE(self->obj), use);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_sensors_range(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_sensors_range(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_sensors_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "range", NULL };
    int range;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_sensors_range", kwlist, &range))
        return NULL;
    gwp_game_state_set_host_sensors_range(GWP_GAME_STATE(self->obj), range);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_new_natives(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_new_natives(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_new_natives(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_new_natives", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_new_natives(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_planets_attack_ships(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_planets_attack_ships(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_planets_attack_ships(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_planets_attack_ships", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_planets_attack_ships(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_borg_assimilation_rate(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_borg_assimilation_rate(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_borg_assimilation_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    int rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_borg_assimilation_rate", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_borg_assimilation_rate(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_starbase_free_fighters(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", NULL };
    int race, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.get_host_starbase_free_fighters", kwlist, &race))
        return NULL;
    ret = gwp_game_state_get_host_starbase_free_fighters(GWP_GAME_STATE(self->obj), race);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_starbase_free_fighters(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", "free", NULL };
    int race, free;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpGameState.set_host_starbase_free_fighters", kwlist, &race, &free))
        return NULL;
    gwp_game_state_set_host_starbase_free_fighters(GWP_GAME_STATE(self->obj), race, free);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_webmine_decay(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_webmine_decay(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_webmine_decay(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "decay", NULL };
    int decay;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_webmine_decay", kwlist, &decay))
        return NULL;
    gwp_game_state_set_host_webmine_decay(GWP_GAME_STATE(self->obj), decay);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_mine_decay(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_mine_decay(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_mine_decay(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "decay", NULL };
    int decay;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_mine_decay", kwlist, &decay))
        return NULL;
    gwp_game_state_set_host_mine_decay(GWP_GAME_STATE(self->obj), decay);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_max_mine_radius(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_max_mine_radius(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_max_mine_radius(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "radius", NULL };
    int radius;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_max_mine_radius", kwlist, &radius))
        return NULL;
    gwp_game_state_set_host_max_mine_radius(GWP_GAME_STATE(self->obj), radius);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_isotope_tudr(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_isotope_tudr(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_isotope_tudr(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tudr", NULL };
    int tudr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_isotope_tudr", kwlist, &tudr))
        return NULL;
    gwp_game_state_set_host_isotope_tudr(GWP_GAME_STATE(self->obj), tudr);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_structure_decay(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_structure_decay(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_structure_decay(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "decay", NULL };
    int decay;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_structure_decay", kwlist, &decay))
        return NULL;
    gwp_game_state_set_host_structure_decay(GWP_GAME_STATE(self->obj), decay);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_mining_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", NULL };
    int race, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.get_host_mining_rate", kwlist, &race))
        return NULL;
    ret = gwp_game_state_get_host_mining_rate(GWP_GAME_STATE(self->obj), race);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_mining_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", "rate", NULL };
    int race, rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpGameState.set_host_mining_rate", kwlist, &race, &rate))
        return NULL;
    gwp_game_state_set_host_mining_rate(GWP_GAME_STATE(self->obj), race, rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_colonists_eat_supplies(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_colonists_eat_supplies(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_colonists_eat_supplies(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_colonists_eat_supplies", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_colonists_eat_supplies(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_zero_fuel_ships_move(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_zero_fuel_ships_move(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_zero_fuel_ships_move(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_zero_fuel_ships_move", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_zero_fuel_ships_move(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_mine_hit_odds(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_mine_hit_odds(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_mine_hit_odds(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ratio", NULL };
    int ratio;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_mine_hit_odds", kwlist, &ratio))
        return NULL;
    gwp_game_state_set_host_mine_hit_odds(GWP_GAME_STATE(self->obj), ratio);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_webmine_hit_odds(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_webmine_hit_odds(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_webmine_hit_odds(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ratio", NULL };
    int ratio;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_webmine_hit_odds", kwlist, &ratio))
        return NULL;
    gwp_game_state_set_host_webmine_hit_odds(GWP_GAME_STATE(self->obj), ratio);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_mine_detect_range(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_mine_detect_range(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_mine_detect_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "range", NULL };
    int range;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_mine_detect_range", kwlist, &range))
        return NULL;
    gwp_game_state_set_host_mine_detect_range(GWP_GAME_STATE(self->obj), range);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_tax_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", NULL };
    int race, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.get_host_tax_rate", kwlist, &race))
        return NULL;
    ret = gwp_game_state_get_host_tax_rate(GWP_GAME_STATE(self->obj), race);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_tax_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "race", "rate", NULL };
    int race, rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpGameState.set_host_tax_rate", kwlist, &race, &rate))
        return NULL;
    gwp_game_state_set_host_tax_rate(GWP_GAME_STATE(self->obj), race, rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_mines_destroy_mines(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_mines_destroy_mines(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_mines_destroy_mines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_mines_destroy_mines", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_mines_destroy_mines(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_es_bonus(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_es_bonus(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_es_bonus(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_es_bonus", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_es_bonus(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_es_bonus_rate(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_es_bonus_rate(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_es_bonus_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    int rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_es_bonus_rate", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_es_bonus_rate(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_colonial_sweep_rate(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_colonial_sweep_rate(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_colonial_sweep_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    int rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_colonial_sweep_rate", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_colonial_sweep_rate(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_colonial_sweep_webs(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_colonial_sweep_webs(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_colonial_sweep_webs(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_colonial_sweep_webs", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_colonial_sweep_webs(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_mine_sweep_rate(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_mine_sweep_rate(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_mine_sweep_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    int rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_mine_sweep_rate", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_mine_sweep_rate(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_webmine_sweep_rate(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_webmine_sweep_rate(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_webmine_sweep_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    int rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_webmine_sweep_rate", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_webmine_sweep_rate(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_hiss_mission_effect(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_hiss_mission_effect(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_hiss_mission_effect(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "effect", NULL };
    int effect;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_hiss_mission_effect", kwlist, &effect))
        return NULL;
    gwp_game_state_set_host_hiss_mission_effect(GWP_GAME_STATE(self->obj), effect);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_rob_mission_failure(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_rob_mission_failure(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_rob_mission_failure(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "failure", NULL };
    int failure;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_rob_mission_failure", kwlist, &failure))
        return NULL;
    gwp_game_state_set_host_rob_mission_failure(GWP_GAME_STATE(self->obj), failure);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_planet_attack_rebel(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_planet_attack_rebel(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_planet_attack_rebel(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_planet_attack_rebel", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_planet_attack_rebel(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_planet_attack_fascist(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_planet_attack_fascist(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_planet_attack_fascist(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_planet_attack_fascist", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_planet_attack_fascist(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_mine_sweep_range(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_mine_sweep_range(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_mine_sweep_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "range", NULL };
    int range;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_mine_sweep_range", kwlist, &range))
        return NULL;
    gwp_game_state_set_host_mine_sweep_range(GWP_GAME_STATE(self->obj), range);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_webmine_sweep_range(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_webmine_sweep_range(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_webmine_sweep_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "range", NULL };
    int range;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_webmine_sweep_range", kwlist, &range))
        return NULL;
    gwp_game_state_set_host_webmine_sweep_range(GWP_GAME_STATE(self->obj), range);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_science_missions(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_science_missions(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_science_missions(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_science_missions", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_science_missions(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_cloaked_mine_hit(PyGObject *self)
{
    double ret;

    ret = gwp_game_state_get_host_cloaked_mine_hit(GWP_GAME_STATE(self->obj));
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_cloaked_mine_hit(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    double rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "d:GwpGameState.set_host_cloaked_mine_hit", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_cloaked_mine_hit(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_cloak_prevent_damage(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_cloak_prevent_damage(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_cloak_prevent_damage(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    int rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_cloak_prevent_damage", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_cloak_prevent_damage(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_fed_crew_bonus(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_fed_crew_bonus(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_fed_crew_bonus(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_fed_crew_bonus", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_fed_crew_bonus(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_one_engine_tow(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_one_engine_tow(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_one_engine_tow(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_one_engine_tow", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_one_engine_tow(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_hyperdrive_ships(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_hyperdrive_ships(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_hyperdrive_ships(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_hyperdrive_ships", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_hyperdrive_ships(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_climate_death_rate(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_climate_death_rate(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_climate_death_rate(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    int rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_climate_death_rate", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_climate_death_rate(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_gravity_well(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_gravity_well(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_gravity_well(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_gravity_well", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_gravity_well(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_crystal_desert_adv(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_crystal_desert_adv(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_crystal_desert_adv(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_crystal_desert_adv", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_crystal_desert_adv(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_mines_destroy_webs(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_mines_destroy_webs(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_mines_destroy_webs(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_mines_destroy_webs", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_mines_destroy_webs(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_climate_limit_pop(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_climate_limit_pop(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_climate_limit_pop(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_climate_limit_pop", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_climate_limit_pop(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_max_planet_income(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_max_planet_income(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_max_planet_income(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "max", NULL };
    int max;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_max_planet_income", kwlist, &max))
        return NULL;
    gwp_game_state_set_host_max_planet_income(GWP_GAME_STATE(self->obj), max);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_ion_storms(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_ion_storms(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_ion_storms(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storm", NULL };
    int storm;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_ion_storms", kwlist, &storm))
        return NULL;
    gwp_game_state_set_host_ion_storms(GWP_GAME_STATE(self->obj), storm);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_firecloud_chunnel(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_firecloud_chunnel(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_firecloud_chunnel(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_firecloud_chunnel", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_firecloud_chunnel(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_superspy_deluxe(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_superspy_deluxe(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_superspy_deluxe(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_superspy_deluxe", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_superspy_deluxe(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_storms_hide_mines(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_storms_hide_mines(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_storms_hide_mines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_storms_hide_mines", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_storms_hide_mines(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_fascist_glory_device(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_fascist_glory_device(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_fascist_glory_device(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_fascist_glory_device", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_fascist_glory_device(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_loki_anticloak(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_loki_anticloak(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_loki_anticloak(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_loki_anticloak", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_loki_anticloak(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_ladyroyale_gambling(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_ladyroyale_gambling(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_ladyroyale_gambling(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_ladyroyale_gambling", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_ladyroyale_gambling(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_cloaked_ships_attack(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_cloaked_ships_attack(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_cloaked_ships_attack(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_cloaked_ships_attack", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_cloaked_ships_attack(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_ship_cloning(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_ship_cloning(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_ship_cloning(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_ship_cloning", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_ship_cloning(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_boarding_party(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_boarding_party(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_boarding_party(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_boarding_party", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_boarding_party(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_imperial_assault(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_imperial_assault(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_imperial_assault(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_imperial_assault", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_imperial_assault(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_cobol_fuel(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_cobol_fuel(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_cobol_fuel(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rate", NULL };
    int rate;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_cobol_fuel", kwlist, &rate))
        return NULL;
    gwp_game_state_set_host_cobol_fuel(GWP_GAME_STATE(self->obj), rate);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_hulltech_slowed_minehits(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_hulltech_slowed_minehits(GWP_GAME_STATE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_game_state_set_host_hulltech_slowed_minehits(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tech", NULL };
    int tech;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_hulltech_slowed_minehits", kwlist, &tech))
        return NULL;
    gwp_game_state_set_host_hulltech_slowed_minehits(GWP_GAME_STATE(self->obj), tech);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_aries_makes_fuel(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_aries_makes_fuel(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_aries_makes_fuel(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_aries_makes_fuel", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_aries_makes_fuel(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_bioscanners(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_bioscanners(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_bioscanners(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_bioscanners", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_bioscanners(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_loki_decloak_birds(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_loki_decloak_birds(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_loki_decloak_birds(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_loki_decloak_birds", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_loki_decloak_birds(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_game_state_get_host_vpa_extras(PyGObject *self)
{
    int ret;

    ret = gwp_game_state_get_host_vpa_extras(GWP_GAME_STATE(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_game_state_set_host_vpa_extras(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bool", NULL };
    int bool;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpGameState.set_host_vpa_extras", kwlist, &bool))
        return NULL;
    gwp_game_state_set_host_vpa_extras(GWP_GAME_STATE(self->obj), bool);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpGameState_methods[] = {
    { "postinit", (PyCFunction)_wrap_gwp_game_state_postinit, METH_NOARGS },
    { "get_full_path", (PyCFunction)_wrap_gwp_game_state_get_full_path, METH_VARARGS|METH_KEYWORDS },
    { "set_last_coords", (PyCFunction)_wrap_gwp_game_state_set_last_coords, METH_VARARGS|METH_KEYWORDS },
    { "get_dat_filename", (PyCFunction)_wrap_gwp_game_state_get_dat_filename, METH_VARARGS|METH_KEYWORDS },
    { "set_name", (PyCFunction)_wrap_gwp_game_state_set_name, METH_VARARGS|METH_KEYWORDS },
    { "get_name", (PyCFunction)_wrap_gwp_game_state_get_name, METH_NOARGS },
    { "set_dir", (PyCFunction)_wrap_gwp_game_state_set_dir, METH_VARARGS|METH_KEYWORDS },
    { "get_dir", (PyCFunction)_wrap_gwp_game_state_get_dir, METH_NOARGS },
    { "set_starchart_zoom", (PyCFunction)_wrap_gwp_game_state_set_starchart_zoom, METH_VARARGS|METH_KEYWORDS },
    { "get_starchart_zoom", (PyCFunction)_wrap_gwp_game_state_get_starchart_zoom, METH_NOARGS },
    { "set_race", (PyCFunction)_wrap_gwp_game_state_set_race, METH_VARARGS|METH_KEYWORDS },
    { "get_race_nr", (PyCFunction)_wrap_gwp_game_state_get_race_nr, METH_NOARGS },
    { "set_last_x_coord", (PyCFunction)_wrap_gwp_game_state_set_last_x_coord, METH_VARARGS|METH_KEYWORDS },
    { "get_last_x_coord", (PyCFunction)_wrap_gwp_game_state_get_last_x_coord, METH_NOARGS },
    { "set_last_y_coord", (PyCFunction)_wrap_gwp_game_state_set_last_y_coord, METH_VARARGS|METH_KEYWORDS },
    { "get_last_y_coord", (PyCFunction)_wrap_gwp_game_state_get_last_y_coord, METH_NOARGS },
    { "set_turn_number", (PyCFunction)_wrap_gwp_game_state_set_turn_number, METH_VARARGS|METH_KEYWORDS },
    { "get_turn_number", (PyCFunction)_wrap_gwp_game_state_get_turn_number, METH_NOARGS },
    { "set_player_email", (PyCFunction)_wrap_gwp_game_state_set_player_email, METH_VARARGS|METH_KEYWORDS },
    { "get_player_email", (PyCFunction)_wrap_gwp_game_state_get_player_email, METH_NOARGS },
    { "set_host_email", (PyCFunction)_wrap_gwp_game_state_set_host_email, METH_VARARGS|METH_KEYWORDS },
    { "get_host_email", (PyCFunction)_wrap_gwp_game_state_get_host_email, METH_NOARGS },
    { "set_trn_dir", (PyCFunction)_wrap_gwp_game_state_set_trn_dir, METH_VARARGS|METH_KEYWORDS },
    { "get_trn_dir", (PyCFunction)_wrap_gwp_game_state_get_trn_dir, METH_NOARGS },
    { "set_rst_dir", (PyCFunction)_wrap_gwp_game_state_set_rst_dir, METH_VARARGS|METH_KEYWORDS },
    { "get_rst_dir", (PyCFunction)_wrap_gwp_game_state_get_rst_dir, METH_NOARGS },
    { "set_host_type", (PyCFunction)_wrap_gwp_game_state_set_host_type, METH_VARARGS|METH_KEYWORDS },
    { "get_host_type", (PyCFunction)_wrap_gwp_game_state_get_host_type, METH_NOARGS },
    { "set_planet_names", (PyCFunction)_wrap_gwp_game_state_set_planet_names, METH_VARARGS|METH_KEYWORDS },
    { "get_planet_names", (PyCFunction)_wrap_gwp_game_state_get_planet_names, METH_NOARGS },
    { "set_scanner_area", (PyCFunction)_wrap_gwp_game_state_set_scanner_area, METH_VARARGS|METH_KEYWORDS },
    { "get_scanner_area", (PyCFunction)_wrap_gwp_game_state_get_scanner_area, METH_NOARGS },
    { "set_minefields", (PyCFunction)_wrap_gwp_game_state_set_minefields, METH_VARARGS|METH_KEYWORDS },
    { "get_minefields", (PyCFunction)_wrap_gwp_game_state_get_minefields, METH_NOARGS },
    { "set_ion_storms", (PyCFunction)_wrap_gwp_game_state_set_ion_storms, METH_VARARGS|METH_KEYWORDS },
    { "get_ion_storms", (PyCFunction)_wrap_gwp_game_state_get_ion_storms, METH_NOARGS },
    { "set_extra_panel_open", (PyCFunction)_wrap_gwp_game_state_set_extra_panel_open, METH_VARARGS|METH_KEYWORDS },
    { "get_extra_panel_open", (PyCFunction)_wrap_gwp_game_state_get_extra_panel_open, METH_NOARGS },
    { "get_selected_ship", (PyCFunction)_wrap_gwp_game_state_get_selected_ship, METH_NOARGS },
    { "get_selected_planet", (PyCFunction)_wrap_gwp_game_state_get_selected_planet, METH_NOARGS },
    { "get_host_recycle_col_ship", (PyCFunction)_wrap_gwp_game_state_get_host_recycle_col_ship, METH_NOARGS },
    { "set_host_recycle_col_ship", (PyCFunction)_wrap_gwp_game_state_set_host_recycle_col_ship, METH_VARARGS|METH_KEYWORDS },
    { "set_host_large_meteor_impact", (PyCFunction)_wrap_gwp_game_state_set_host_large_meteor_impact, METH_VARARGS|METH_KEYWORDS },
    { "get_host_large_meteor_impact", (PyCFunction)_wrap_gwp_game_state_get_host_large_meteor_impact, METH_NOARGS },
    { "set_host_space_mines", (PyCFunction)_wrap_gwp_game_state_set_host_space_mines, METH_VARARGS|METH_KEYWORDS },
    { "get_host_space_mines", (PyCFunction)_wrap_gwp_game_state_get_host_space_mines, METH_NOARGS },
    { "get_host_alchemy_ships", (PyCFunction)_wrap_gwp_game_state_get_host_alchemy_ships, METH_NOARGS },
    { "set_host_alchemy_ships", (PyCFunction)_wrap_gwp_game_state_set_host_alchemy_ships, METH_VARARGS|METH_KEYWORDS },
    { "get_host_delete_old_msgs", (PyCFunction)_wrap_gwp_game_state_get_host_delete_old_msgs, METH_NOARGS },
    { "set_host_delete_old_msgs", (PyCFunction)_wrap_gwp_game_state_set_host_delete_old_msgs, METH_VARARGS|METH_KEYWORDS },
    { "get_host_disable_pwd", (PyCFunction)_wrap_gwp_game_state_get_host_disable_pwd, METH_NOARGS },
    { "set_host_disable_pwd", (PyCFunction)_wrap_gwp_game_state_set_host_disable_pwd, METH_VARARGS|METH_KEYWORDS },
    { "get_host_rebel_build_fighters", (PyCFunction)_wrap_gwp_game_state_get_host_rebel_build_fighters, METH_NOARGS },
    { "set_host_rebel_build_fighters", (PyCFunction)_wrap_gwp_game_state_set_host_rebel_build_fighters, METH_VARARGS|METH_KEYWORDS },
    { "get_host_colonial_build_fighters", (PyCFunction)_wrap_gwp_game_state_get_host_colonial_build_fighters, METH_NOARGS },
    { "set_host_colonial_build_fighters", (PyCFunction)_wrap_gwp_game_state_set_host_colonial_build_fighters, METH_VARARGS|METH_KEYWORDS },
    { "get_host_robots_build_fighters", (PyCFunction)_wrap_gwp_game_state_get_host_robots_build_fighters, METH_NOARGS },
    { "set_host_robots_build_fighters", (PyCFunction)_wrap_gwp_game_state_set_host_robots_build_fighters, METH_VARARGS|METH_KEYWORDS },
    { "get_host_cloak_failure", (PyCFunction)_wrap_gwp_game_state_get_host_cloak_failure, METH_NOARGS },
    { "set_host_cloak_failure", (PyCFunction)_wrap_gwp_game_state_set_host_cloak_failure, METH_VARARGS|METH_KEYWORDS },
    { "get_host_priv_rob_cloak", (PyCFunction)_wrap_gwp_game_state_get_host_priv_rob_cloak, METH_NOARGS },
    { "set_host_priv_rob_cloak", (PyCFunction)_wrap_gwp_game_state_set_host_priv_rob_cloak, METH_VARARGS|METH_KEYWORDS },
    { "get_host_dark_sense_range", (PyCFunction)_wrap_gwp_game_state_get_host_dark_sense_range, METH_NOARGS },
    { "set_host_dark_sense_range", (PyCFunction)_wrap_gwp_game_state_set_host_dark_sense_range, METH_VARARGS|METH_KEYWORDS },
    { "get_host_ground_attack_ratio", (PyCFunction)_wrap_gwp_game_state_get_host_ground_attack_ratio, METH_VARARGS|METH_KEYWORDS },
    { "set_host_ground_attack_ratio", (PyCFunction)_wrap_gwp_game_state_set_host_ground_attack_ratio, METH_VARARGS|METH_KEYWORDS },
    { "get_host_ships_visible_range", (PyCFunction)_wrap_gwp_game_state_get_host_ships_visible_range, METH_NOARGS },
    { "set_host_ships_visible_range", (PyCFunction)_wrap_gwp_game_state_set_host_ships_visible_range, METH_VARARGS|METH_KEYWORDS },
    { "get_host_lizard_hiss_mission", (PyCFunction)_wrap_gwp_game_state_get_host_lizard_hiss_mission, METH_NOARGS },
    { "set_host_lizard_hiss_mission", (PyCFunction)_wrap_gwp_game_state_set_host_lizard_hiss_mission, METH_VARARGS|METH_KEYWORDS },
    { "get_host_rebel_ground_attack", (PyCFunction)_wrap_gwp_game_state_get_host_rebel_ground_attack, METH_NOARGS },
    { "set_host_rebel_ground_attack", (PyCFunction)_wrap_gwp_game_state_set_host_rebel_ground_attack, METH_VARARGS|METH_KEYWORDS },
    { "get_host_fed_super_refit", (PyCFunction)_wrap_gwp_game_state_get_host_fed_super_refit, METH_NOARGS },
    { "set_host_fed_super_refit", (PyCFunction)_wrap_gwp_game_state_set_host_fed_super_refit, METH_VARARGS|METH_KEYWORDS },
    { "get_host_crystal_web_mines", (PyCFunction)_wrap_gwp_game_state_get_host_crystal_web_mines, METH_NOARGS },
    { "set_host_crystal_web_mines", (PyCFunction)_wrap_gwp_game_state_set_host_crystal_web_mines, METH_VARARGS|METH_KEYWORDS },
    { "get_host_ground_defense_ratio", (PyCFunction)_wrap_gwp_game_state_get_host_ground_defense_ratio, METH_VARARGS|METH_KEYWORDS },
    { "set_host_ground_defense_ratio", (PyCFunction)_wrap_gwp_game_state_set_host_ground_defense_ratio, METH_VARARGS|METH_KEYWORDS },
    { "get_host_cloak_fuel_use", (PyCFunction)_wrap_gwp_game_state_get_host_cloak_fuel_use, METH_NOARGS },
    { "set_host_cloak_fuel_use", (PyCFunction)_wrap_gwp_game_state_set_host_cloak_fuel_use, METH_VARARGS|METH_KEYWORDS },
    { "get_host_sensors_range", (PyCFunction)_wrap_gwp_game_state_get_host_sensors_range, METH_NOARGS },
    { "set_host_sensors_range", (PyCFunction)_wrap_gwp_game_state_set_host_sensors_range, METH_VARARGS|METH_KEYWORDS },
    { "get_host_new_natives", (PyCFunction)_wrap_gwp_game_state_get_host_new_natives, METH_NOARGS },
    { "set_host_new_natives", (PyCFunction)_wrap_gwp_game_state_set_host_new_natives, METH_VARARGS|METH_KEYWORDS },
    { "get_host_planets_attack_ships", (PyCFunction)_wrap_gwp_game_state_get_host_planets_attack_ships, METH_NOARGS },
    { "set_host_planets_attack_ships", (PyCFunction)_wrap_gwp_game_state_set_host_planets_attack_ships, METH_VARARGS|METH_KEYWORDS },
    { "get_host_borg_assimilation_rate", (PyCFunction)_wrap_gwp_game_state_get_host_borg_assimilation_rate, METH_NOARGS },
    { "set_host_borg_assimilation_rate", (PyCFunction)_wrap_gwp_game_state_set_host_borg_assimilation_rate, METH_VARARGS|METH_KEYWORDS },
    { "get_host_starbase_free_fighters", (PyCFunction)_wrap_gwp_game_state_get_host_starbase_free_fighters, METH_VARARGS|METH_KEYWORDS },
    { "set_host_starbase_free_fighters", (PyCFunction)_wrap_gwp_game_state_set_host_starbase_free_fighters, METH_VARARGS|METH_KEYWORDS },
    { "get_host_webmine_decay", (PyCFunction)_wrap_gwp_game_state_get_host_webmine_decay, METH_NOARGS },
    { "set_host_webmine_decay", (PyCFunction)_wrap_gwp_game_state_set_host_webmine_decay, METH_VARARGS|METH_KEYWORDS },
    { "get_host_mine_decay", (PyCFunction)_wrap_gwp_game_state_get_host_mine_decay, METH_NOARGS },
    { "set_host_mine_decay", (PyCFunction)_wrap_gwp_game_state_set_host_mine_decay, METH_VARARGS|METH_KEYWORDS },
    { "get_host_max_mine_radius", (PyCFunction)_wrap_gwp_game_state_get_host_max_mine_radius, METH_NOARGS },
    { "set_host_max_mine_radius", (PyCFunction)_wrap_gwp_game_state_set_host_max_mine_radius, METH_VARARGS|METH_KEYWORDS },
    { "get_host_isotope_tudr", (PyCFunction)_wrap_gwp_game_state_get_host_isotope_tudr, METH_NOARGS },
    { "set_host_isotope_tudr", (PyCFunction)_wrap_gwp_game_state_set_host_isotope_tudr, METH_VARARGS|METH_KEYWORDS },
    { "get_host_structure_decay", (PyCFunction)_wrap_gwp_game_state_get_host_structure_decay, METH_NOARGS },
    { "set_host_structure_decay", (PyCFunction)_wrap_gwp_game_state_set_host_structure_decay, METH_VARARGS|METH_KEYWORDS },
    { "get_host_mining_rate", (PyCFunction)_wrap_gwp_game_state_get_host_mining_rate, METH_VARARGS|METH_KEYWORDS },
    { "set_host_mining_rate", (PyCFunction)_wrap_gwp_game_state_set_host_mining_rate, METH_VARARGS|METH_KEYWORDS },
    { "get_host_colonists_eat_supplies", (PyCFunction)_wrap_gwp_game_state_get_host_colonists_eat_supplies, METH_NOARGS },
    { "set_host_colonists_eat_supplies", (PyCFunction)_wrap_gwp_game_state_set_host_colonists_eat_supplies, METH_VARARGS|METH_KEYWORDS },
    { "get_host_zero_fuel_ships_move", (PyCFunction)_wrap_gwp_game_state_get_host_zero_fuel_ships_move, METH_NOARGS },
    { "set_host_zero_fuel_ships_move", (PyCFunction)_wrap_gwp_game_state_set_host_zero_fuel_ships_move, METH_VARARGS|METH_KEYWORDS },
    { "get_host_mine_hit_odds", (PyCFunction)_wrap_gwp_game_state_get_host_mine_hit_odds, METH_NOARGS },
    { "set_host_mine_hit_odds", (PyCFunction)_wrap_gwp_game_state_set_host_mine_hit_odds, METH_VARARGS|METH_KEYWORDS },
    { "get_host_webmine_hit_odds", (PyCFunction)_wrap_gwp_game_state_get_host_webmine_hit_odds, METH_NOARGS },
    { "set_host_webmine_hit_odds", (PyCFunction)_wrap_gwp_game_state_set_host_webmine_hit_odds, METH_VARARGS|METH_KEYWORDS },
    { "get_host_mine_detect_range", (PyCFunction)_wrap_gwp_game_state_get_host_mine_detect_range, METH_NOARGS },
    { "set_host_mine_detect_range", (PyCFunction)_wrap_gwp_game_state_set_host_mine_detect_range, METH_VARARGS|METH_KEYWORDS },
    { "get_host_tax_rate", (PyCFunction)_wrap_gwp_game_state_get_host_tax_rate, METH_VARARGS|METH_KEYWORDS },
    { "set_host_tax_rate", (PyCFunction)_wrap_gwp_game_state_set_host_tax_rate, METH_VARARGS|METH_KEYWORDS },
    { "get_host_mines_destroy_mines", (PyCFunction)_wrap_gwp_game_state_get_host_mines_destroy_mines, METH_NOARGS },
    { "set_host_mines_destroy_mines", (PyCFunction)_wrap_gwp_game_state_set_host_mines_destroy_mines, METH_VARARGS|METH_KEYWORDS },
    { "get_host_es_bonus", (PyCFunction)_wrap_gwp_game_state_get_host_es_bonus, METH_NOARGS },
    { "set_host_es_bonus", (PyCFunction)_wrap_gwp_game_state_set_host_es_bonus, METH_VARARGS|METH_KEYWORDS },
    { "get_host_es_bonus_rate", (PyCFunction)_wrap_gwp_game_state_get_host_es_bonus_rate, METH_NOARGS },
    { "set_host_es_bonus_rate", (PyCFunction)_wrap_gwp_game_state_set_host_es_bonus_rate, METH_VARARGS|METH_KEYWORDS },
    { "get_host_colonial_sweep_rate", (PyCFunction)_wrap_gwp_game_state_get_host_colonial_sweep_rate, METH_NOARGS },
    { "set_host_colonial_sweep_rate", (PyCFunction)_wrap_gwp_game_state_set_host_colonial_sweep_rate, METH_VARARGS|METH_KEYWORDS },
    { "get_host_colonial_sweep_webs", (PyCFunction)_wrap_gwp_game_state_get_host_colonial_sweep_webs, METH_NOARGS },
    { "set_host_colonial_sweep_webs", (PyCFunction)_wrap_gwp_game_state_set_host_colonial_sweep_webs, METH_VARARGS|METH_KEYWORDS },
    { "get_host_mine_sweep_rate", (PyCFunction)_wrap_gwp_game_state_get_host_mine_sweep_rate, METH_NOARGS },
    { "set_host_mine_sweep_rate", (PyCFunction)_wrap_gwp_game_state_set_host_mine_sweep_rate, METH_VARARGS|METH_KEYWORDS },
    { "get_host_webmine_sweep_rate", (PyCFunction)_wrap_gwp_game_state_get_host_webmine_sweep_rate, METH_NOARGS },
    { "set_host_webmine_sweep_rate", (PyCFunction)_wrap_gwp_game_state_set_host_webmine_sweep_rate, METH_VARARGS|METH_KEYWORDS },
    { "get_host_hiss_mission_effect", (PyCFunction)_wrap_gwp_game_state_get_host_hiss_mission_effect, METH_NOARGS },
    { "set_host_hiss_mission_effect", (PyCFunction)_wrap_gwp_game_state_set_host_hiss_mission_effect, METH_VARARGS|METH_KEYWORDS },
    { "get_host_rob_mission_failure", (PyCFunction)_wrap_gwp_game_state_get_host_rob_mission_failure, METH_NOARGS },
    { "set_host_rob_mission_failure", (PyCFunction)_wrap_gwp_game_state_set_host_rob_mission_failure, METH_VARARGS|METH_KEYWORDS },
    { "get_host_planet_attack_rebel", (PyCFunction)_wrap_gwp_game_state_get_host_planet_attack_rebel, METH_NOARGS },
    { "set_host_planet_attack_rebel", (PyCFunction)_wrap_gwp_game_state_set_host_planet_attack_rebel, METH_VARARGS|METH_KEYWORDS },
    { "get_host_planet_attack_fascist", (PyCFunction)_wrap_gwp_game_state_get_host_planet_attack_fascist, METH_NOARGS },
    { "set_host_planet_attack_fascist", (PyCFunction)_wrap_gwp_game_state_set_host_planet_attack_fascist, METH_VARARGS|METH_KEYWORDS },
    { "get_host_mine_sweep_range", (PyCFunction)_wrap_gwp_game_state_get_host_mine_sweep_range, METH_NOARGS },
    { "set_host_mine_sweep_range", (PyCFunction)_wrap_gwp_game_state_set_host_mine_sweep_range, METH_VARARGS|METH_KEYWORDS },
    { "get_host_webmine_sweep_range", (PyCFunction)_wrap_gwp_game_state_get_host_webmine_sweep_range, METH_NOARGS },
    { "set_host_webmine_sweep_range", (PyCFunction)_wrap_gwp_game_state_set_host_webmine_sweep_range, METH_VARARGS|METH_KEYWORDS },
    { "get_host_science_missions", (PyCFunction)_wrap_gwp_game_state_get_host_science_missions, METH_NOARGS },
    { "set_host_science_missions", (PyCFunction)_wrap_gwp_game_state_set_host_science_missions, METH_VARARGS|METH_KEYWORDS },
    { "get_host_cloaked_mine_hit", (PyCFunction)_wrap_gwp_game_state_get_host_cloaked_mine_hit, METH_NOARGS },
    { "set_host_cloaked_mine_hit", (PyCFunction)_wrap_gwp_game_state_set_host_cloaked_mine_hit, METH_VARARGS|METH_KEYWORDS },
    { "get_host_cloak_prevent_damage", (PyCFunction)_wrap_gwp_game_state_get_host_cloak_prevent_damage, METH_NOARGS },
    { "set_host_cloak_prevent_damage", (PyCFunction)_wrap_gwp_game_state_set_host_cloak_prevent_damage, METH_VARARGS|METH_KEYWORDS },
    { "get_host_fed_crew_bonus", (PyCFunction)_wrap_gwp_game_state_get_host_fed_crew_bonus, METH_NOARGS },
    { "set_host_fed_crew_bonus", (PyCFunction)_wrap_gwp_game_state_set_host_fed_crew_bonus, METH_VARARGS|METH_KEYWORDS },
    { "get_host_one_engine_tow", (PyCFunction)_wrap_gwp_game_state_get_host_one_engine_tow, METH_NOARGS },
    { "set_host_one_engine_tow", (PyCFunction)_wrap_gwp_game_state_set_host_one_engine_tow, METH_VARARGS|METH_KEYWORDS },
    { "get_host_hyperdrive_ships", (PyCFunction)_wrap_gwp_game_state_get_host_hyperdrive_ships, METH_NOARGS },
    { "set_host_hyperdrive_ships", (PyCFunction)_wrap_gwp_game_state_set_host_hyperdrive_ships, METH_VARARGS|METH_KEYWORDS },
    { "get_host_climate_death_rate", (PyCFunction)_wrap_gwp_game_state_get_host_climate_death_rate, METH_NOARGS },
    { "set_host_climate_death_rate", (PyCFunction)_wrap_gwp_game_state_set_host_climate_death_rate, METH_VARARGS|METH_KEYWORDS },
    { "get_host_gravity_well", (PyCFunction)_wrap_gwp_game_state_get_host_gravity_well, METH_NOARGS },
    { "set_host_gravity_well", (PyCFunction)_wrap_gwp_game_state_set_host_gravity_well, METH_VARARGS|METH_KEYWORDS },
    { "get_host_crystal_desert_adv", (PyCFunction)_wrap_gwp_game_state_get_host_crystal_desert_adv, METH_NOARGS },
    { "set_host_crystal_desert_adv", (PyCFunction)_wrap_gwp_game_state_set_host_crystal_desert_adv, METH_VARARGS|METH_KEYWORDS },
    { "get_host_mines_destroy_webs", (PyCFunction)_wrap_gwp_game_state_get_host_mines_destroy_webs, METH_NOARGS },
    { "set_host_mines_destroy_webs", (PyCFunction)_wrap_gwp_game_state_set_host_mines_destroy_webs, METH_VARARGS|METH_KEYWORDS },
    { "get_host_climate_limit_pop", (PyCFunction)_wrap_gwp_game_state_get_host_climate_limit_pop, METH_NOARGS },
    { "set_host_climate_limit_pop", (PyCFunction)_wrap_gwp_game_state_set_host_climate_limit_pop, METH_VARARGS|METH_KEYWORDS },
    { "get_host_max_planet_income", (PyCFunction)_wrap_gwp_game_state_get_host_max_planet_income, METH_NOARGS },
    { "set_host_max_planet_income", (PyCFunction)_wrap_gwp_game_state_set_host_max_planet_income, METH_VARARGS|METH_KEYWORDS },
    { "get_host_ion_storms", (PyCFunction)_wrap_gwp_game_state_get_host_ion_storms, METH_NOARGS },
    { "set_host_ion_storms", (PyCFunction)_wrap_gwp_game_state_set_host_ion_storms, METH_VARARGS|METH_KEYWORDS },
    { "get_host_firecloud_chunnel", (PyCFunction)_wrap_gwp_game_state_get_host_firecloud_chunnel, METH_NOARGS },
    { "set_host_firecloud_chunnel", (PyCFunction)_wrap_gwp_game_state_set_host_firecloud_chunnel, METH_VARARGS|METH_KEYWORDS },
    { "get_host_superspy_deluxe", (PyCFunction)_wrap_gwp_game_state_get_host_superspy_deluxe, METH_NOARGS },
    { "set_host_superspy_deluxe", (PyCFunction)_wrap_gwp_game_state_set_host_superspy_deluxe, METH_VARARGS|METH_KEYWORDS },
    { "get_host_storms_hide_mines", (PyCFunction)_wrap_gwp_game_state_get_host_storms_hide_mines, METH_NOARGS },
    { "set_host_storms_hide_mines", (PyCFunction)_wrap_gwp_game_state_set_host_storms_hide_mines, METH_VARARGS|METH_KEYWORDS },
    { "get_host_fascist_glory_device", (PyCFunction)_wrap_gwp_game_state_get_host_fascist_glory_device, METH_NOARGS },
    { "set_host_fascist_glory_device", (PyCFunction)_wrap_gwp_game_state_set_host_fascist_glory_device, METH_VARARGS|METH_KEYWORDS },
    { "get_host_loki_anticloak", (PyCFunction)_wrap_gwp_game_state_get_host_loki_anticloak, METH_NOARGS },
    { "set_host_loki_anticloak", (PyCFunction)_wrap_gwp_game_state_set_host_loki_anticloak, METH_VARARGS|METH_KEYWORDS },
    { "get_host_ladyroyale_gambling", (PyCFunction)_wrap_gwp_game_state_get_host_ladyroyale_gambling, METH_NOARGS },
    { "set_host_ladyroyale_gambling", (PyCFunction)_wrap_gwp_game_state_set_host_ladyroyale_gambling, METH_VARARGS|METH_KEYWORDS },
    { "get_host_cloaked_ships_attack", (PyCFunction)_wrap_gwp_game_state_get_host_cloaked_ships_attack, METH_NOARGS },
    { "set_host_cloaked_ships_attack", (PyCFunction)_wrap_gwp_game_state_set_host_cloaked_ships_attack, METH_VARARGS|METH_KEYWORDS },
    { "get_host_ship_cloning", (PyCFunction)_wrap_gwp_game_state_get_host_ship_cloning, METH_NOARGS },
    { "set_host_ship_cloning", (PyCFunction)_wrap_gwp_game_state_set_host_ship_cloning, METH_VARARGS|METH_KEYWORDS },
    { "get_host_boarding_party", (PyCFunction)_wrap_gwp_game_state_get_host_boarding_party, METH_NOARGS },
    { "set_host_boarding_party", (PyCFunction)_wrap_gwp_game_state_set_host_boarding_party, METH_VARARGS|METH_KEYWORDS },
    { "get_host_imperial_assault", (PyCFunction)_wrap_gwp_game_state_get_host_imperial_assault, METH_NOARGS },
    { "set_host_imperial_assault", (PyCFunction)_wrap_gwp_game_state_set_host_imperial_assault, METH_VARARGS|METH_KEYWORDS },
    { "get_host_cobol_fuel", (PyCFunction)_wrap_gwp_game_state_get_host_cobol_fuel, METH_NOARGS },
    { "set_host_cobol_fuel", (PyCFunction)_wrap_gwp_game_state_set_host_cobol_fuel, METH_VARARGS|METH_KEYWORDS },
    { "get_host_hulltech_slowed_minehits", (PyCFunction)_wrap_gwp_game_state_get_host_hulltech_slowed_minehits, METH_NOARGS },
    { "set_host_hulltech_slowed_minehits", (PyCFunction)_wrap_gwp_game_state_set_host_hulltech_slowed_minehits, METH_VARARGS|METH_KEYWORDS },
    { "get_host_aries_makes_fuel", (PyCFunction)_wrap_gwp_game_state_get_host_aries_makes_fuel, METH_NOARGS },
    { "set_host_aries_makes_fuel", (PyCFunction)_wrap_gwp_game_state_set_host_aries_makes_fuel, METH_VARARGS|METH_KEYWORDS },
    { "get_host_bioscanners", (PyCFunction)_wrap_gwp_game_state_get_host_bioscanners, METH_NOARGS },
    { "set_host_bioscanners", (PyCFunction)_wrap_gwp_game_state_set_host_bioscanners, METH_VARARGS|METH_KEYWORDS },
    { "get_host_loki_decloak_birds", (PyCFunction)_wrap_gwp_game_state_get_host_loki_decloak_birds, METH_NOARGS },
    { "set_host_loki_decloak_birds", (PyCFunction)_wrap_gwp_game_state_set_host_loki_decloak_birds, METH_VARARGS|METH_KEYWORDS },
    { "get_host_vpa_extras", (PyCFunction)_wrap_gwp_game_state_get_host_vpa_extras, METH_NOARGS },
    { "set_host_vpa_extras", (PyCFunction)_wrap_gwp_game_state_set_host_vpa_extras, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpGameState_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.GameState",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpGameState_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_game_state_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpHullSpec ----------- */

static PyObject *
_wrap_gwp_hullspec_get_name_trunc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "len", NULL };
    int len;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.get_name_trunc", kwlist, &len))
        return NULL;
    ret = gwp_hullspec_get_name_trunc(GWP_HULL_SPEC(self->obj), len);
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_id(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_id(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_id", kwlist, &id))
        return NULL;
    gwp_hullspec_set_id(GWP_HULL_SPEC(self->obj), id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_hullspec_get_name(GWP_HULL_SPEC(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_set_name(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpHullSpec.set_name", kwlist, &name))
        return NULL;
    gwp_hullspec_set_name(GWP_HULL_SPEC(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_picture(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_picture(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_picture(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "pic", NULL };
    int pic;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_picture", kwlist, &pic))
        return NULL;
    gwp_hullspec_set_picture(GWP_HULL_SPEC(self->obj), pic);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_tritanium(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "m", NULL };
    int m;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_tritanium", kwlist, &m))
        return NULL;
    gwp_hullspec_set_tritanium(GWP_HULL_SPEC(self->obj), m);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_duranium(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "m", NULL };
    int m;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_duranium", kwlist, &m))
        return NULL;
    gwp_hullspec_set_duranium(GWP_HULL_SPEC(self->obj), m);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_molybdenum(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "m", NULL };
    int m;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_molybdenum", kwlist, &m))
        return NULL;
    gwp_hullspec_set_molybdenum(GWP_HULL_SPEC(self->obj), m);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_fuel_tank(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_fuel_tank(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_fuel_tank(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ft", NULL };
    int ft;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_fuel_tank", kwlist, &ft))
        return NULL;
    gwp_hullspec_set_fuel_tank(GWP_HULL_SPEC(self->obj), ft);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_crew(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_crew(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_crew(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "crew", NULL };
    int crew;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_crew", kwlist, &crew))
        return NULL;
    gwp_hullspec_set_crew(GWP_HULL_SPEC(self->obj), crew);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_engines(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_engines(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_engines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "eng", NULL };
    int eng;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_engines", kwlist, &eng))
        return NULL;
    gwp_hullspec_set_engines(GWP_HULL_SPEC(self->obj), eng);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_mass(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_mass(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_mass(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mass", NULL };
    int mass;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_mass", kwlist, &mass))
        return NULL;
    gwp_hullspec_set_mass(GWP_HULL_SPEC(self->obj), mass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_tech_level(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_tech_level(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_tech_level(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tl", NULL };
    int tl;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_tech_level", kwlist, &tl))
        return NULL;
    gwp_hullspec_set_tech_level(GWP_HULL_SPEC(self->obj), tl);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_cargo(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_cargo(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_cargo(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "cargo", NULL };
    int cargo;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_cargo", kwlist, &cargo))
        return NULL;
    gwp_hullspec_set_cargo(GWP_HULL_SPEC(self->obj), cargo);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_fighter_bays(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_fighter_bays(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_fighter_bays(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "fb", NULL };
    int fb;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_fighter_bays", kwlist, &fb))
        return NULL;
    gwp_hullspec_set_fighter_bays(GWP_HULL_SPEC(self->obj), fb);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_torp_launchers(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_torp_launchers(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_torp_launchers(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tl", NULL };
    int tl;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_torp_launchers", kwlist, &tl))
        return NULL;
    gwp_hullspec_set_torp_launchers(GWP_HULL_SPEC(self->obj), tl);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_beam_weapons(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_beam_weapons(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_beam_weapons(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bw", NULL };
    int bw;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_beam_weapons", kwlist, &bw))
        return NULL;
    gwp_hullspec_set_beam_weapons(GWP_HULL_SPEC(self->obj), bw);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_hullspec_get_cost(PyGObject *self)
{
    int ret;

    ret = gwp_hullspec_get_cost(GWP_HULL_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_hullspec_set_cost(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "cost", NULL };
    int cost;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpHullSpec.set_cost", kwlist, &cost))
        return NULL;
    gwp_hullspec_set_cost(GWP_HULL_SPEC(self->obj), cost);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpHullSpec_methods[] = {
    { "get_name_trunc", (PyCFunction)_wrap_gwp_hullspec_get_name_trunc, METH_VARARGS|METH_KEYWORDS },
    { "get_id", (PyCFunction)_wrap_gwp_hullspec_get_id, METH_NOARGS },
    { "set_id", (PyCFunction)_wrap_gwp_hullspec_set_id, METH_VARARGS|METH_KEYWORDS },
    { "get_name", (PyCFunction)_wrap_gwp_hullspec_get_name, METH_NOARGS },
    { "set_name", (PyCFunction)_wrap_gwp_hullspec_set_name, METH_VARARGS|METH_KEYWORDS },
    { "get_picture", (PyCFunction)_wrap_gwp_hullspec_get_picture, METH_NOARGS },
    { "set_picture", (PyCFunction)_wrap_gwp_hullspec_set_picture, METH_VARARGS|METH_KEYWORDS },
    { "get_tritanium", (PyCFunction)_wrap_gwp_hullspec_get_tritanium, METH_NOARGS },
    { "set_tritanium", (PyCFunction)_wrap_gwp_hullspec_set_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_duranium", (PyCFunction)_wrap_gwp_hullspec_get_duranium, METH_NOARGS },
    { "set_duranium", (PyCFunction)_wrap_gwp_hullspec_set_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_molybdenum", (PyCFunction)_wrap_gwp_hullspec_get_molybdenum, METH_NOARGS },
    { "set_molybdenum", (PyCFunction)_wrap_gwp_hullspec_set_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_fuel_tank", (PyCFunction)_wrap_gwp_hullspec_get_fuel_tank, METH_NOARGS },
    { "set_fuel_tank", (PyCFunction)_wrap_gwp_hullspec_set_fuel_tank, METH_VARARGS|METH_KEYWORDS },
    { "get_crew", (PyCFunction)_wrap_gwp_hullspec_get_crew, METH_NOARGS },
    { "set_crew", (PyCFunction)_wrap_gwp_hullspec_set_crew, METH_VARARGS|METH_KEYWORDS },
    { "get_engines", (PyCFunction)_wrap_gwp_hullspec_get_engines, METH_NOARGS },
    { "set_engines", (PyCFunction)_wrap_gwp_hullspec_set_engines, METH_VARARGS|METH_KEYWORDS },
    { "get_mass", (PyCFunction)_wrap_gwp_hullspec_get_mass, METH_NOARGS },
    { "set_mass", (PyCFunction)_wrap_gwp_hullspec_set_mass, METH_VARARGS|METH_KEYWORDS },
    { "get_tech_level", (PyCFunction)_wrap_gwp_hullspec_get_tech_level, METH_NOARGS },
    { "set_tech_level", (PyCFunction)_wrap_gwp_hullspec_set_tech_level, METH_VARARGS|METH_KEYWORDS },
    { "get_cargo", (PyCFunction)_wrap_gwp_hullspec_get_cargo, METH_NOARGS },
    { "set_cargo", (PyCFunction)_wrap_gwp_hullspec_set_cargo, METH_VARARGS|METH_KEYWORDS },
    { "get_fighter_bays", (PyCFunction)_wrap_gwp_hullspec_get_fighter_bays, METH_NOARGS },
    { "set_fighter_bays", (PyCFunction)_wrap_gwp_hullspec_set_fighter_bays, METH_VARARGS|METH_KEYWORDS },
    { "get_torp_launchers", (PyCFunction)_wrap_gwp_hullspec_get_torp_launchers, METH_NOARGS },
    { "set_torp_launchers", (PyCFunction)_wrap_gwp_hullspec_set_torp_launchers, METH_VARARGS|METH_KEYWORDS },
    { "get_beam_weapons", (PyCFunction)_wrap_gwp_hullspec_get_beam_weapons, METH_NOARGS },
    { "set_beam_weapons", (PyCFunction)_wrap_gwp_hullspec_set_beam_weapons, METH_VARARGS|METH_KEYWORDS },
    { "get_cost", (PyCFunction)_wrap_gwp_hullspec_get_cost, METH_NOARGS },
    { "set_cost", (PyCFunction)_wrap_gwp_hullspec_set_cost, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpHullSpec_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.HullSpec",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpHullSpec_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpObject ----------- */

static int
_wrap_gwp_object_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.Object.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_object_valid_coords(PyGObject *self)
{
    int ret;

    ret = gwp_object_valid_coords(GWP_OBJECT(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_object_get_name_trunc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "len", NULL };
    int len;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpObject.get_name_trunc", kwlist, &len))
        return NULL;
    ret = gwp_object_get_name_trunc(GWP_OBJECT(self->obj), len);
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_object_get_x_coord(PyGObject *self)
{
    int ret;

    ret = gwp_object_get_x_coord(GWP_OBJECT(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_object_set_x_coord(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", NULL };
    int x;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpObject.set_x_coord", kwlist, &x))
        return NULL;
    gwp_object_set_x_coord(GWP_OBJECT(self->obj), x);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_object_get_y_coord(PyGObject *self)
{
    int ret;

    ret = gwp_object_get_y_coord(GWP_OBJECT(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_object_set_y_coord(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "y", NULL };
    int y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpObject.set_y_coord", kwlist, &y))
        return NULL;
    gwp_object_set_y_coord(GWP_OBJECT(self->obj), y);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_object_get_id(PyGObject *self)
{
    int ret;

    ret = gwp_object_get_id(GWP_OBJECT(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_object_set_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpObject.set_id", kwlist, &id))
        return NULL;
    gwp_object_set_id(GWP_OBJECT(self->obj), id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_object_get_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_object_get_name(GWP_OBJECT(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_object_set_name(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpObject.set_name", kwlist, &name))
        return NULL;
    gwp_object_set_name(GWP_OBJECT(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpObject_methods[] = {
    { "valid_coords", (PyCFunction)_wrap_gwp_object_valid_coords, METH_NOARGS },
    { "get_name_trunc", (PyCFunction)_wrap_gwp_object_get_name_trunc, METH_VARARGS|METH_KEYWORDS },
    { "get_x_coord", (PyCFunction)_wrap_gwp_object_get_x_coord, METH_NOARGS },
    { "set_x_coord", (PyCFunction)_wrap_gwp_object_set_x_coord, METH_VARARGS|METH_KEYWORDS },
    { "get_y_coord", (PyCFunction)_wrap_gwp_object_get_y_coord, METH_NOARGS },
    { "set_y_coord", (PyCFunction)_wrap_gwp_object_set_y_coord, METH_VARARGS|METH_KEYWORDS },
    { "get_id", (PyCFunction)_wrap_gwp_object_get_id, METH_NOARGS },
    { "set_id", (PyCFunction)_wrap_gwp_object_set_id, METH_VARARGS|METH_KEYWORDS },
    { "get_name", (PyCFunction)_wrap_gwp_object_get_name, METH_NOARGS },
    { "set_name", (PyCFunction)_wrap_gwp_object_set_name, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpObject_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Object",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpObject_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_object_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpMinefield ----------- */

static int
_wrap_gwp_minefield_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.Minefield.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_minefield_is_valid(PyGObject *self)
{
    int ret;

    ret = gwp_minefield_is_valid(GWP_MINEFIELD(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_minefield_is_mine(PyGObject *self)
{
    int ret;

    ret = gwp_minefield_is_mine(GWP_MINEFIELD(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_minefield_is_web(PyGObject *self)
{
    int ret;

    ret = gwp_minefield_is_web(GWP_MINEFIELD(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_minefield_get_radius(PyGObject *self)
{
    int ret;

    ret = gwp_minefield_get_radius(GWP_MINEFIELD(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_minefield_set_radius(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "r", NULL };
    int r;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpMinefield.set_radius", kwlist, &r))
        return NULL;
    gwp_minefield_set_radius(GWP_MINEFIELD(self->obj), r);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_minefield_get_owner(PyGObject *self)
{
    int ret;

    ret = gwp_minefield_get_owner(GWP_MINEFIELD(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_minefield_set_owner(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "owner", NULL };
    int owner;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpMinefield.set_owner", kwlist, &owner))
        return NULL;
    gwp_minefield_set_owner(GWP_MINEFIELD(self->obj), owner);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpMinefield_methods[] = {
    { "is_valid", (PyCFunction)_wrap_gwp_minefield_is_valid, METH_NOARGS },
    { "is_mine", (PyCFunction)_wrap_gwp_minefield_is_mine, METH_NOARGS },
    { "is_web", (PyCFunction)_wrap_gwp_minefield_is_web, METH_NOARGS },
    { "get_radius", (PyCFunction)_wrap_gwp_minefield_get_radius, METH_NOARGS },
    { "set_radius", (PyCFunction)_wrap_gwp_minefield_set_radius, METH_VARARGS|METH_KEYWORDS },
    { "get_owner", (PyCFunction)_wrap_gwp_minefield_get_owner, METH_NOARGS },
    { "set_owner", (PyCFunction)_wrap_gwp_minefield_set_owner, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpMinefield_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Minefield",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpMinefield_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_minefield_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpMarker ----------- */

static int
_wrap_gwp_marker_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "starchart", NULL };
    PyGObject *starchart;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpMarker.__init__", kwlist, &PyGwpStarchart_Type, &starchart))
        return -1;
    self->obj = (GObject *)gwp_marker_new(GWP_STARCHART(starchart->obj));

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create GwpMarker object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_gwp_marker_draw(PyGObject *self)
{
    gwp_marker_draw(GWP_MARKER(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_marker_delete(PyGObject *self)
{
    gwp_marker_delete(GWP_MARKER(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_marker_update(PyGObject *self)
{
    gwp_marker_update(GWP_MARKER(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpMarker_methods[] = {
    { "draw", (PyCFunction)_wrap_gwp_marker_draw, METH_NOARGS },
    { "delete", (PyCFunction)_wrap_gwp_marker_delete, METH_NOARGS },
    { "update", (PyCFunction)_wrap_gwp_marker_update, METH_NOARGS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpMarker_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Marker",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpMarker_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_marker_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpLocation ----------- */

static int
_wrap_gwp_location_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.Location.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_location_add_object(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "obj", NULL };
    PyGObject *obj;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpLocation.add_object", kwlist, &PyGwpObject_Type, &obj))
        return NULL;
    gwp_location_add_object(GWP_LOCATION(self->obj), GWP_OBJECT(obj->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_location_objects_nr(PyGObject *self)
{
    guint ret;

    ret = gwp_location_objects_nr(GWP_LOCATION(self->obj));
    return PyLong_FromUnsignedLong(ret);

}

static PyObject *
_wrap_gwp_location_get_object(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "obj_nr", NULL };
    GwpObject *ret;
    guint obj_nr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "I:GwpLocation.get_object", kwlist, &obj_nr))
        return NULL;
    ret = gwp_location_get_object(GWP_LOCATION(self->obj), obj_nr);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyMethodDef _PyGwpLocation_methods[] = {
    { "add_object", (PyCFunction)_wrap_gwp_location_add_object, METH_VARARGS|METH_KEYWORDS },
    { "objects_nr", (PyCFunction)_wrap_gwp_location_objects_nr, METH_NOARGS },
    { "get_object", (PyCFunction)_wrap_gwp_location_get_object, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpLocation_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Location",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpLocation_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_location_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpFlyingObject ----------- */

static int
_wrap_gwp_flying_object_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.FlyingObject.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_flying_object_get_heading_str(PyGObject *self)
{
    gchar *ret;

    ret = gwp_flying_object_get_heading_str(GWP_FLYING_OBJECT(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_flying_object_get_heading(PyGObject *self)
{
    int ret;

    ret = gwp_flying_object_get_heading(GWP_FLYING_OBJECT(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_flying_object_set_heading(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "heading", NULL };
    int heading;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpFlyingObject.set_heading", kwlist, &heading))
        return NULL;
    gwp_flying_object_set_heading(GWP_FLYING_OBJECT(self->obj), heading);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_flying_object_get_speed(PyGObject *self)
{
    int ret;

    ret = gwp_flying_object_get_speed(GWP_FLYING_OBJECT(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_flying_object_set_speed(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "speed", NULL };
    int speed;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpFlyingObject.set_speed", kwlist, &speed))
        return NULL;
    gwp_flying_object_set_speed(GWP_FLYING_OBJECT(self->obj), speed);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpFlyingObject_methods[] = {
    { "get_heading_str", (PyCFunction)_wrap_gwp_flying_object_get_heading_str, METH_NOARGS },
    { "get_heading", (PyCFunction)_wrap_gwp_flying_object_get_heading, METH_NOARGS },
    { "set_heading", (PyCFunction)_wrap_gwp_flying_object_set_heading, METH_VARARGS|METH_KEYWORDS },
    { "get_speed", (PyCFunction)_wrap_gwp_flying_object_get_speed, METH_NOARGS },
    { "set_speed", (PyCFunction)_wrap_gwp_flying_object_set_speed, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpFlyingObject_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.FlyingObject",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpFlyingObject_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_flying_object_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpIonStorm ----------- */

static int
_wrap_gwp_ion_storm_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.IonStorm.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_ion_storm_get_class(PyGObject *self)
{
    int ret;

    ret = gwp_ion_storm_get_class(GWP_ION_STORM(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ion_storm_get_class_str(PyGObject *self)
{
    gchar *ret;

    ret = gwp_ion_storm_get_class_str(GWP_ION_STORM(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ion_storm_is_valid(PyGObject *self)
{
    int ret;

    ret = gwp_ion_storm_is_valid(GWP_ION_STORM(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_ion_storm_get_radius(PyGObject *self)
{
    int ret;

    ret = gwp_ion_storm_get_radius(GWP_ION_STORM(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ion_storm_set_radius(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "r", NULL };
    int r;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpIonStorm.set_radius", kwlist, &r))
        return NULL;
    gwp_ion_storm_set_radius(GWP_ION_STORM(self->obj), r);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ion_storm_get_voltage(PyGObject *self)
{
    int ret;

    ret = gwp_ion_storm_get_voltage(GWP_ION_STORM(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ion_storm_set_voltage(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "v", NULL };
    int v;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpIonStorm.set_voltage", kwlist, &v))
        return NULL;
    gwp_ion_storm_set_voltage(GWP_ION_STORM(self->obj), v);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpIonStorm_methods[] = {
    { "get_class", (PyCFunction)_wrap_gwp_ion_storm_get_class, METH_NOARGS },
    { "get_class_str", (PyCFunction)_wrap_gwp_ion_storm_get_class_str, METH_NOARGS },
    { "is_valid", (PyCFunction)_wrap_gwp_ion_storm_is_valid, METH_NOARGS },
    { "get_radius", (PyCFunction)_wrap_gwp_ion_storm_get_radius, METH_NOARGS },
    { "set_radius", (PyCFunction)_wrap_gwp_ion_storm_set_radius, METH_VARARGS|METH_KEYWORDS },
    { "get_voltage", (PyCFunction)_wrap_gwp_ion_storm_get_voltage, METH_NOARGS },
    { "set_voltage", (PyCFunction)_wrap_gwp_ion_storm_set_voltage, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpIonStorm_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.IonStorm",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpIonStorm_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_ion_storm_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpPlanet ----------- */

static int
_wrap_gwp_planet_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.Planet.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_planet_get_def_sys_beams_type_str(PyGObject *self)
{
    gchar *ret;

    ret = gwp_planet_get_def_sys_beams_type_str(GWP_PLANET(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_def_sys_beams_type(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_def_sys_beams_type(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_def_sys_beams_nr(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_def_sys_beams_nr(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_def_sys_fighters_nr(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_def_sys_fighters_nr(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_def_sys_fighter_bays(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_def_sys_fighter_bays(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_def_sys_battle_mass(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_def_sys_battle_mass(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_col_growth_limit(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_col_growth_limit(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_nat_growth_limit(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_nat_growth_limit(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_copy(PyGObject *self)
{
    GwpPlanet *ret;

    ret = gwp_planet_copy(GWP_PLANET(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gwp_planet_is_mine(PyGObject *self)
{
    int ret;

    ret = gwp_planet_is_mine(GWP_PLANET(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_planet_is_unowned(PyGObject *self)
{
    int ret;

    ret = gwp_planet_is_unowned(GWP_PLANET(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_planet_what_is(PyGObject *self)
{
    int ret;

    ret = gwp_planet_what_is(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_temperature_f(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_temperature_f(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_temperature_str(PyGObject *self)
{
    gchar *ret;

    ret = gwp_planet_get_temperature_str(GWP_PLANET(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_visibility(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_visibility(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_happiness_col_change(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_happiness_col_change(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_happiness_nat_change(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_happiness_nat_change(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_natives_race_chars(PyGObject *self)
{
    gchar *ret;

    ret = gwp_planet_get_natives_race_chars(GWP_PLANET(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_natives_spi_chars(PyGObject *self)
{
    gchar *ret;

    ret = gwp_planet_get_natives_spi_chars(GWP_PLANET(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_has_starbase(PyGObject *self)
{
    int ret;

    ret = gwp_planet_has_starbase(GWP_PLANET(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_planet_neutronium_extraction_rate(PyGObject *self)
{
    int ret;

    ret = gwp_planet_neutronium_extraction_rate(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_neutronium_turns_left(PyGObject *self)
{
    int ret;

    ret = gwp_planet_neutronium_turns_left(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_tritanium_extraction_rate(PyGObject *self)
{
    int ret;

    ret = gwp_planet_tritanium_extraction_rate(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_tritanium_turns_left(PyGObject *self)
{
    int ret;

    ret = gwp_planet_tritanium_turns_left(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_molybdenum_extraction_rate(PyGObject *self)
{
    int ret;

    ret = gwp_planet_molybdenum_extraction_rate(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_molybdenum_turns_left(PyGObject *self)
{
    int ret;

    ret = gwp_planet_molybdenum_turns_left(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_duranium_extraction_rate(PyGObject *self)
{
    int ret;

    ret = gwp_planet_duranium_extraction_rate(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_duranium_turns_left(PyGObject *self)
{
    int ret;

    ret = gwp_planet_duranium_turns_left(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_tax_collected_colonists(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_tax_collected_colonists(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_tax_collected_natives(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_tax_collected_natives(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_tax_collected_natives_max(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_tax_collected_natives_max(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_calculate_allowed_factories(PyGObject *self)
{
    int ret;

    ret = gwp_planet_calculate_allowed_factories(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_calculate_allowed_mines(PyGObject *self)
{
    int ret;

    ret = gwp_planet_calculate_allowed_mines(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_calculate_allowed_defenses(PyGObject *self)
{
    int ret;

    ret = gwp_planet_calculate_allowed_defenses(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_is_known(PyGObject *self)
{
    int ret;

    ret = gwp_planet_is_known(GWP_PLANET(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_planet_set_is_known(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "is_known", NULL };
    int is_known;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_is_known", kwlist, &is_known))
        return NULL;
    gwp_planet_set_is_known(GWP_PLANET(self->obj), is_known);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_set_starbase(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "sb", NULL };
    PyGObject *sb;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpPlanet.set_starbase", kwlist, &PyGwpStarbase_Type, &sb))
        return NULL;
    gwp_planet_set_starbase(GWP_PLANET(self->obj), GWP_STARBASE(sb->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_starbase(PyGObject *self)
{
    GwpStarbase *ret;

    ret = gwp_planet_get_starbase(GWP_PLANET(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gwp_planet_get_owner(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_owner(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_owner(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "o", NULL };
    int o;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_owner", kwlist, &o))
        return NULL;
    gwp_planet_set_owner(GWP_PLANET(self->obj), o);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_fcode(PyGObject *self)
{
    gchar *ret;

    ret = gwp_planet_get_fcode(GWP_PLANET(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_set_fcode(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "fcode", NULL };
    char *fcode;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpPlanet.set_fcode", kwlist, &fcode))
        return NULL;
    gwp_planet_set_fcode(GWP_PLANET(self->obj), fcode);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_mines(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_mines(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_mines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "m", NULL };
    int m;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_mines", kwlist, &m))
        return NULL;
    gwp_planet_set_mines(GWP_PLANET(self->obj), m);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_factories(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_factories(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_factories(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "f", NULL };
    int f;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_factories", kwlist, &f))
        return NULL;
    gwp_planet_set_factories(GWP_PLANET(self->obj), f);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_defense_posts(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_defense_posts(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_defense_posts(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "d", NULL };
    int d;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_defense_posts", kwlist, &d))
        return NULL;
    gwp_planet_set_defense_posts(GWP_PLANET(self->obj), d);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_mined_neutronium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_mined_neutronium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_mined_neutronium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mn", NULL };
    int mn;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_mined_neutronium", kwlist, &mn))
        return NULL;
    gwp_planet_set_mined_neutronium(GWP_PLANET(self->obj), mn);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_mined_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_mined_tritanium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_mined_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mt", NULL };
    int mt;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_mined_tritanium", kwlist, &mt))
        return NULL;
    gwp_planet_set_mined_tritanium(GWP_PLANET(self->obj), mt);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_mined_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_mined_duranium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_mined_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "md", NULL };
    int md;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_mined_duranium", kwlist, &md))
        return NULL;
    gwp_planet_set_mined_duranium(GWP_PLANET(self->obj), md);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_mined_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_mined_molybdenum(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_mined_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mm", NULL };
    int mm;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_mined_molybdenum", kwlist, &mm))
        return NULL;
    gwp_planet_set_mined_molybdenum(GWP_PLANET(self->obj), mm);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_colonists(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_colonists(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_colonists(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "col", NULL };
    int col;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_colonists", kwlist, &col))
        return NULL;
    gwp_planet_set_colonists(GWP_PLANET(self->obj), col);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_supplies(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_supplies(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_supplies(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "sup", NULL };
    int sup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_supplies", kwlist, &sup))
        return NULL;
    gwp_planet_set_supplies(GWP_PLANET(self->obj), sup);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_megacredits(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_megacredits(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_megacredits(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mc", NULL };
    int mc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_megacredits", kwlist, &mc))
        return NULL;
    gwp_planet_set_megacredits(GWP_PLANET(self->obj), mc);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_ground_neutronium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_ground_neutronium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_ground_neutronium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "gn", NULL };
    int gn;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_ground_neutronium", kwlist, &gn))
        return NULL;
    gwp_planet_set_ground_neutronium(GWP_PLANET(self->obj), gn);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_ground_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_ground_tritanium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_ground_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "gt", NULL };
    int gt;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_ground_tritanium", kwlist, &gt))
        return NULL;
    gwp_planet_set_ground_tritanium(GWP_PLANET(self->obj), gt);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_ground_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_ground_duranium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_ground_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "gd", NULL };
    int gd;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_ground_duranium", kwlist, &gd))
        return NULL;
    gwp_planet_set_ground_duranium(GWP_PLANET(self->obj), gd);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_ground_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_ground_molybdenum(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_ground_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "gm", NULL };
    int gm;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_ground_molybdenum", kwlist, &gm))
        return NULL;
    gwp_planet_set_ground_molybdenum(GWP_PLANET(self->obj), gm);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_dens_neutronium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_dens_neutronium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_dens_neutronium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dn", NULL };
    int dn;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_dens_neutronium", kwlist, &dn))
        return NULL;
    gwp_planet_set_dens_neutronium(GWP_PLANET(self->obj), dn);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_dens_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_dens_tritanium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_dens_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dt", NULL };
    int dt;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_dens_tritanium", kwlist, &dt))
        return NULL;
    gwp_planet_set_dens_tritanium(GWP_PLANET(self->obj), dt);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_dens_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_dens_duranium(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_dens_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dd", NULL };
    int dd;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_dens_duranium", kwlist, &dd))
        return NULL;
    gwp_planet_set_dens_duranium(GWP_PLANET(self->obj), dd);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_dens_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_dens_molybdenum(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_dens_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dm", NULL };
    int dm;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_dens_molybdenum", kwlist, &dm))
        return NULL;
    gwp_planet_set_dens_molybdenum(GWP_PLANET(self->obj), dm);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_tax_colonists(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_tax_colonists(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_tax_colonists(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tc", NULL };
    int tc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_tax_colonists", kwlist, &tc))
        return NULL;
    gwp_planet_set_tax_colonists(GWP_PLANET(self->obj), tc);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_tax_natives(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_tax_natives(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_tax_natives(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tn", NULL };
    int tn;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_tax_natives", kwlist, &tn))
        return NULL;
    gwp_planet_set_tax_natives(GWP_PLANET(self->obj), tn);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_happiness_colonists(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_happiness_colonists(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_happiness_colonists(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tc", NULL };
    int tc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_happiness_colonists", kwlist, &tc))
        return NULL;
    gwp_planet_set_happiness_colonists(GWP_PLANET(self->obj), tc);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_happiness_natives(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_happiness_natives(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_happiness_natives(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tn", NULL };
    int tn;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_happiness_natives", kwlist, &tn))
        return NULL;
    gwp_planet_set_happiness_natives(GWP_PLANET(self->obj), tn);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_natives_spi(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_natives_spi(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_natives_spi(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "spi", NULL };
    int spi;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_natives_spi", kwlist, &spi))
        return NULL;
    gwp_planet_set_natives_spi(GWP_PLANET(self->obj), spi);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_natives(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_natives(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_natives(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "nat", NULL };
    int nat;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_natives", kwlist, &nat))
        return NULL;
    gwp_planet_set_natives(GWP_PLANET(self->obj), nat);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_natives_race(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_natives_race(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_natives_race(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "nr", NULL };
    int nr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_natives_race", kwlist, &nr))
        return NULL;
    gwp_planet_set_natives_race(GWP_PLANET(self->obj), nr);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_temperature(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_temperature(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_temperature(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "temp", NULL };
    int temp;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_temperature", kwlist, &temp))
        return NULL;
    gwp_planet_set_temperature(GWP_PLANET(self->obj), temp);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_build_base(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_build_base(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_set_build_base(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bb", NULL };
    int bb;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpPlanet.set_build_base", kwlist, &bb))
        return NULL;
    gwp_planet_set_build_base(GWP_PLANET(self->obj), bb);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_planet_get_mining_rate(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_mining_rate(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_tax_rate_colonists(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_tax_rate_colonists(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_planet_get_tax_rate_natives(PyGObject *self)
{
    int ret;

    ret = gwp_planet_get_tax_rate_natives(GWP_PLANET(self->obj));
    return PyInt_FromLong(ret);
}

static PyMethodDef _PyGwpPlanet_methods[] = {
    { "get_def_sys_beams_type_str", (PyCFunction)_wrap_gwp_planet_get_def_sys_beams_type_str, METH_NOARGS },
    { "get_def_sys_beams_type", (PyCFunction)_wrap_gwp_planet_get_def_sys_beams_type, METH_NOARGS },
    { "get_def_sys_beams_nr", (PyCFunction)_wrap_gwp_planet_get_def_sys_beams_nr, METH_NOARGS },
    { "get_def_sys_fighters_nr", (PyCFunction)_wrap_gwp_planet_get_def_sys_fighters_nr, METH_NOARGS },
    { "get_def_sys_fighter_bays", (PyCFunction)_wrap_gwp_planet_get_def_sys_fighter_bays, METH_NOARGS },
    { "get_def_sys_battle_mass", (PyCFunction)_wrap_gwp_planet_get_def_sys_battle_mass, METH_NOARGS },
    { "get_col_growth_limit", (PyCFunction)_wrap_gwp_planet_get_col_growth_limit, METH_NOARGS },
    { "get_nat_growth_limit", (PyCFunction)_wrap_gwp_planet_get_nat_growth_limit, METH_NOARGS },
    { "copy", (PyCFunction)_wrap_gwp_planet_copy, METH_NOARGS },
    { "is_mine", (PyCFunction)_wrap_gwp_planet_is_mine, METH_NOARGS },
    { "is_unowned", (PyCFunction)_wrap_gwp_planet_is_unowned, METH_NOARGS },
    { "what_is", (PyCFunction)_wrap_gwp_planet_what_is, METH_NOARGS },
    { "get_temperature_f", (PyCFunction)_wrap_gwp_planet_get_temperature_f, METH_NOARGS },
    { "get_temperature_str", (PyCFunction)_wrap_gwp_planet_get_temperature_str, METH_NOARGS },
    { "get_visibility", (PyCFunction)_wrap_gwp_planet_get_visibility, METH_NOARGS },
    { "get_happiness_col_change", (PyCFunction)_wrap_gwp_planet_get_happiness_col_change, METH_NOARGS },
    { "get_happiness_nat_change", (PyCFunction)_wrap_gwp_planet_get_happiness_nat_change, METH_NOARGS },
    { "get_natives_race_chars", (PyCFunction)_wrap_gwp_planet_get_natives_race_chars, METH_NOARGS },
    { "get_natives_spi_chars", (PyCFunction)_wrap_gwp_planet_get_natives_spi_chars, METH_NOARGS },
    { "has_starbase", (PyCFunction)_wrap_gwp_planet_has_starbase, METH_NOARGS },
    { "neutronium_extraction_rate", (PyCFunction)_wrap_gwp_planet_neutronium_extraction_rate, METH_NOARGS },
    { "neutronium_turns_left", (PyCFunction)_wrap_gwp_planet_neutronium_turns_left, METH_NOARGS },
    { "tritanium_extraction_rate", (PyCFunction)_wrap_gwp_planet_tritanium_extraction_rate, METH_NOARGS },
    { "tritanium_turns_left", (PyCFunction)_wrap_gwp_planet_tritanium_turns_left, METH_NOARGS },
    { "molybdenum_extraction_rate", (PyCFunction)_wrap_gwp_planet_molybdenum_extraction_rate, METH_NOARGS },
    { "molybdenum_turns_left", (PyCFunction)_wrap_gwp_planet_molybdenum_turns_left, METH_NOARGS },
    { "duranium_extraction_rate", (PyCFunction)_wrap_gwp_planet_duranium_extraction_rate, METH_NOARGS },
    { "duranium_turns_left", (PyCFunction)_wrap_gwp_planet_duranium_turns_left, METH_NOARGS },
    { "get_tax_collected_colonists", (PyCFunction)_wrap_gwp_planet_get_tax_collected_colonists, METH_NOARGS },
    { "get_tax_collected_natives", (PyCFunction)_wrap_gwp_planet_get_tax_collected_natives, METH_NOARGS },
    { "get_tax_collected_natives_max", (PyCFunction)_wrap_gwp_planet_get_tax_collected_natives_max, METH_NOARGS },
    { "calculate_allowed_factories", (PyCFunction)_wrap_gwp_planet_calculate_allowed_factories, METH_NOARGS },
    { "calculate_allowed_mines", (PyCFunction)_wrap_gwp_planet_calculate_allowed_mines, METH_NOARGS },
    { "calculate_allowed_defenses", (PyCFunction)_wrap_gwp_planet_calculate_allowed_defenses, METH_NOARGS },
    { "is_known", (PyCFunction)_wrap_gwp_planet_is_known, METH_NOARGS },
    { "set_is_known", (PyCFunction)_wrap_gwp_planet_set_is_known, METH_VARARGS|METH_KEYWORDS },
    { "set_starbase", (PyCFunction)_wrap_gwp_planet_set_starbase, METH_VARARGS|METH_KEYWORDS },
    { "get_starbase", (PyCFunction)_wrap_gwp_planet_get_starbase, METH_NOARGS },
    { "get_owner", (PyCFunction)_wrap_gwp_planet_get_owner, METH_NOARGS },
    { "set_owner", (PyCFunction)_wrap_gwp_planet_set_owner, METH_VARARGS|METH_KEYWORDS },
    { "get_fcode", (PyCFunction)_wrap_gwp_planet_get_fcode, METH_NOARGS },
    { "set_fcode", (PyCFunction)_wrap_gwp_planet_set_fcode, METH_VARARGS|METH_KEYWORDS },
    { "get_mines", (PyCFunction)_wrap_gwp_planet_get_mines, METH_NOARGS },
    { "set_mines", (PyCFunction)_wrap_gwp_planet_set_mines, METH_VARARGS|METH_KEYWORDS },
    { "get_factories", (PyCFunction)_wrap_gwp_planet_get_factories, METH_NOARGS },
    { "set_factories", (PyCFunction)_wrap_gwp_planet_set_factories, METH_VARARGS|METH_KEYWORDS },
    { "get_defense_posts", (PyCFunction)_wrap_gwp_planet_get_defense_posts, METH_NOARGS },
    { "set_defense_posts", (PyCFunction)_wrap_gwp_planet_set_defense_posts, METH_VARARGS|METH_KEYWORDS },
    { "get_mined_neutronium", (PyCFunction)_wrap_gwp_planet_get_mined_neutronium, METH_NOARGS },
    { "set_mined_neutronium", (PyCFunction)_wrap_gwp_planet_set_mined_neutronium, METH_VARARGS|METH_KEYWORDS },
    { "get_mined_tritanium", (PyCFunction)_wrap_gwp_planet_get_mined_tritanium, METH_NOARGS },
    { "set_mined_tritanium", (PyCFunction)_wrap_gwp_planet_set_mined_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_mined_duranium", (PyCFunction)_wrap_gwp_planet_get_mined_duranium, METH_NOARGS },
    { "set_mined_duranium", (PyCFunction)_wrap_gwp_planet_set_mined_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_mined_molybdenum", (PyCFunction)_wrap_gwp_planet_get_mined_molybdenum, METH_NOARGS },
    { "set_mined_molybdenum", (PyCFunction)_wrap_gwp_planet_set_mined_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_colonists", (PyCFunction)_wrap_gwp_planet_get_colonists, METH_NOARGS },
    { "set_colonists", (PyCFunction)_wrap_gwp_planet_set_colonists, METH_VARARGS|METH_KEYWORDS },
    { "get_supplies", (PyCFunction)_wrap_gwp_planet_get_supplies, METH_NOARGS },
    { "set_supplies", (PyCFunction)_wrap_gwp_planet_set_supplies, METH_VARARGS|METH_KEYWORDS },
    { "get_megacredits", (PyCFunction)_wrap_gwp_planet_get_megacredits, METH_NOARGS },
    { "set_megacredits", (PyCFunction)_wrap_gwp_planet_set_megacredits, METH_VARARGS|METH_KEYWORDS },
    { "get_ground_neutronium", (PyCFunction)_wrap_gwp_planet_get_ground_neutronium, METH_NOARGS },
    { "set_ground_neutronium", (PyCFunction)_wrap_gwp_planet_set_ground_neutronium, METH_VARARGS|METH_KEYWORDS },
    { "get_ground_tritanium", (PyCFunction)_wrap_gwp_planet_get_ground_tritanium, METH_NOARGS },
    { "set_ground_tritanium", (PyCFunction)_wrap_gwp_planet_set_ground_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_ground_duranium", (PyCFunction)_wrap_gwp_planet_get_ground_duranium, METH_NOARGS },
    { "set_ground_duranium", (PyCFunction)_wrap_gwp_planet_set_ground_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_ground_molybdenum", (PyCFunction)_wrap_gwp_planet_get_ground_molybdenum, METH_NOARGS },
    { "set_ground_molybdenum", (PyCFunction)_wrap_gwp_planet_set_ground_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_dens_neutronium", (PyCFunction)_wrap_gwp_planet_get_dens_neutronium, METH_NOARGS },
    { "set_dens_neutronium", (PyCFunction)_wrap_gwp_planet_set_dens_neutronium, METH_VARARGS|METH_KEYWORDS },
    { "get_dens_tritanium", (PyCFunction)_wrap_gwp_planet_get_dens_tritanium, METH_NOARGS },
    { "set_dens_tritanium", (PyCFunction)_wrap_gwp_planet_set_dens_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_dens_duranium", (PyCFunction)_wrap_gwp_planet_get_dens_duranium, METH_NOARGS },
    { "set_dens_duranium", (PyCFunction)_wrap_gwp_planet_set_dens_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_dens_molybdenum", (PyCFunction)_wrap_gwp_planet_get_dens_molybdenum, METH_NOARGS },
    { "set_dens_molybdenum", (PyCFunction)_wrap_gwp_planet_set_dens_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_tax_colonists", (PyCFunction)_wrap_gwp_planet_get_tax_colonists, METH_NOARGS },
    { "set_tax_colonists", (PyCFunction)_wrap_gwp_planet_set_tax_colonists, METH_VARARGS|METH_KEYWORDS },
    { "get_tax_natives", (PyCFunction)_wrap_gwp_planet_get_tax_natives, METH_NOARGS },
    { "set_tax_natives", (PyCFunction)_wrap_gwp_planet_set_tax_natives, METH_VARARGS|METH_KEYWORDS },
    { "get_happiness_colonists", (PyCFunction)_wrap_gwp_planet_get_happiness_colonists, METH_NOARGS },
    { "set_happiness_colonists", (PyCFunction)_wrap_gwp_planet_set_happiness_colonists, METH_VARARGS|METH_KEYWORDS },
    { "get_happiness_natives", (PyCFunction)_wrap_gwp_planet_get_happiness_natives, METH_NOARGS },
    { "set_happiness_natives", (PyCFunction)_wrap_gwp_planet_set_happiness_natives, METH_VARARGS|METH_KEYWORDS },
    { "get_natives_spi", (PyCFunction)_wrap_gwp_planet_get_natives_spi, METH_NOARGS },
    { "set_natives_spi", (PyCFunction)_wrap_gwp_planet_set_natives_spi, METH_VARARGS|METH_KEYWORDS },
    { "get_natives", (PyCFunction)_wrap_gwp_planet_get_natives, METH_NOARGS },
    { "set_natives", (PyCFunction)_wrap_gwp_planet_set_natives, METH_VARARGS|METH_KEYWORDS },
    { "get_natives_race", (PyCFunction)_wrap_gwp_planet_get_natives_race, METH_NOARGS },
    { "set_natives_race", (PyCFunction)_wrap_gwp_planet_set_natives_race, METH_VARARGS|METH_KEYWORDS },
    { "get_temperature", (PyCFunction)_wrap_gwp_planet_get_temperature, METH_NOARGS },
    { "set_temperature", (PyCFunction)_wrap_gwp_planet_set_temperature, METH_VARARGS|METH_KEYWORDS },
    { "get_build_base", (PyCFunction)_wrap_gwp_planet_get_build_base, METH_NOARGS },
    { "set_build_base", (PyCFunction)_wrap_gwp_planet_set_build_base, METH_VARARGS|METH_KEYWORDS },
    { "get_mining_rate", (PyCFunction)_wrap_gwp_planet_get_mining_rate, METH_NOARGS },
    { "get_tax_rate_colonists", (PyCFunction)_wrap_gwp_planet_get_tax_rate_colonists, METH_NOARGS },
    { "get_tax_rate_natives", (PyCFunction)_wrap_gwp_planet_get_tax_rate_natives, METH_NOARGS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpPlanet_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Planet",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpPlanet_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_planet_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpRace ----------- */

static int
_wrap_gwp_race_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.Race.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_race_set_long_desc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpRace.set_long_desc", kwlist, &name))
        return NULL;
    gwp_race_set_long_desc(GWP_RACE(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_race_get_long_desc(PyGObject *self)
{
    gchar *ret;

    ret = gwp_race_get_long_desc(GWP_RACE(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_race_set_short_desc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpRace.set_short_desc", kwlist, &name))
        return NULL;
    gwp_race_set_short_desc(GWP_RACE(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_race_get_short_desc(PyGObject *self)
{
    gchar *ret;

    ret = gwp_race_get_short_desc(GWP_RACE(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_race_set_adjective(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpRace.set_adjective", kwlist, &name))
        return NULL;
    gwp_race_set_adjective(GWP_RACE(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_race_get_adjective(PyGObject *self)
{
    gchar *ret;

    ret = gwp_race_get_adjective(GWP_RACE(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpRace_methods[] = {
    { "set_long_desc", (PyCFunction)_wrap_gwp_race_set_long_desc, METH_VARARGS|METH_KEYWORDS },
    { "get_long_desc", (PyCFunction)_wrap_gwp_race_get_long_desc, METH_NOARGS },
    { "set_short_desc", (PyCFunction)_wrap_gwp_race_set_short_desc, METH_VARARGS|METH_KEYWORDS },
    { "get_short_desc", (PyCFunction)_wrap_gwp_race_get_short_desc, METH_NOARGS },
    { "set_adjective", (PyCFunction)_wrap_gwp_race_set_adjective, METH_VARARGS|METH_KEYWORDS },
    { "get_adjective", (PyCFunction)_wrap_gwp_race_get_adjective, METH_NOARGS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpRace_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Race",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpRace_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_race_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpShip ----------- */

static int
_wrap_gwp_ship_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.Ship.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_ship_has_beam_weapons(PyGObject *self)
{
    int ret;

    ret = gwp_ship_has_beam_weapons(GWP_SHIP(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_ship_has_torp_weapons(PyGObject *self)
{
    int ret;

    ret = gwp_ship_has_torp_weapons(GWP_SHIP(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_ship_get_primary_enemy_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_ship_get_primary_enemy_name(GWP_SHIP(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_mission_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_ship_get_mission_name(GWP_SHIP(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_owner_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_ship_get_owner_name(GWP_SHIP(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_hull_name_trunc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "len", NULL };
    int len;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.get_hull_name_trunc", kwlist, &len))
        return NULL;
    ret = gwp_ship_get_hull_name_trunc(GWP_SHIP(self->obj), len);
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_hull_cargo(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_cargo(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_hull_fuel_tank(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_fuel_tank(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_hull_crew(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_crew(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_hull_engines(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_engines(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_hull_beam_weapons(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_beam_weapons(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_hull_torp_launchers(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_torp_launchers(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_hull_fighter_bays(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_fighter_bays(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_hull_picture(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_picture(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_engine_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_ship_get_engine_name(GWP_SHIP(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_beams_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_ship_get_beams_name(GWP_SHIP(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_torps_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_ship_get_torps_name(GWP_SHIP(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_calculate_heading(PyGObject *self)
{
    int ret;

    ret = gwp_ship_calculate_heading(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_valid_coords(PyGObject *self)
{
    int ret;

    ret = gwp_ship_valid_coords(GWP_SHIP(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_ship_is_mine(PyGObject *self)
{
    int ret;

    ret = gwp_ship_is_mine(GWP_SHIP(self->obj));
    return PyBool_FromLong(ret);

}

#line 32 "src/gwp-py-mappings.override"
static PyObject *
_wrap_gwp_ship_get_waypoint (PyGObject *self)
{
  int wp_x, wp_y;
  
  gwp_ship_get_waypoint (GWP_SHIP (self->obj), &wp_x, &wp_y);
  
  return Py_BuildValue("(ii)", wp_x, wp_y); 
}
#line 6158 "src/gwp-py-mappings.c"


static PyObject *
_wrap_gwp_ship_calculate_waypoint_distance(PyGObject *self)
{
    double ret;

    ret = gwp_ship_calculate_waypoint_distance(GWP_SHIP(self->obj));
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_gwp_ship_calculate_eta(PyGObject *self)
{
    int ret;

    ret = gwp_ship_calculate_eta(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_calculate_fuel_usage(PyGObject *self)
{
    int ret;

    ret = gwp_ship_calculate_fuel_usage(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_calculate_cargo(PyGObject *self)
{
    int ret;

    ret = gwp_ship_calculate_cargo(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_calculate_mass(PyGObject *self)
{
    int ret;

    ret = gwp_ship_calculate_mass(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_calculate_lay_mines_torps(PyGObject *self)
{
    int ret;

    ret = gwp_ship_calculate_lay_mines_torps(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_is_known(PyGObject *self)
{
    int ret;

    ret = gwp_ship_is_known(GWP_SHIP(self->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_ship_set_known(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "is_known", NULL };
    int is_known;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_known", kwlist, &is_known))
        return NULL;
    gwp_ship_set_known(GWP_SHIP(self->obj), is_known);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_owner(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_owner(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_owner(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "owner", NULL };
    int owner;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_owner", kwlist, &owner))
        return NULL;
    gwp_ship_set_owner(GWP_SHIP(self->obj), owner);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_mass_if_unknown(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_mass_if_unknown(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_mass_if_unknown(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mass", NULL };
    int mass;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_mass_if_unknown", kwlist, &mass))
        return NULL;
    gwp_ship_set_mass_if_unknown(GWP_SHIP(self->obj), mass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_fcode(PyGObject *self)
{
    gchar *ret;

    ret = gwp_ship_get_fcode(GWP_SHIP(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_set_fcode(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "fcode", NULL };
    char *fcode;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpShip.set_fcode", kwlist, &fcode))
        return NULL;
    gwp_ship_set_fcode(GWP_SHIP(self->obj), fcode);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_x_to_waypoint(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_x_to_waypoint(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_x_to_waypoint(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xw", NULL };
    int xw;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_x_to_waypoint", kwlist, &xw))
        return NULL;
    gwp_ship_set_x_to_waypoint(GWP_SHIP(self->obj), xw);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_y_to_waypoint(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_y_to_waypoint(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_y_to_waypoint(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "yw", NULL };
    int yw;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_y_to_waypoint", kwlist, &yw))
        return NULL;
    gwp_ship_set_y_to_waypoint(GWP_SHIP(self->obj), yw);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_engines_type(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_engines_type(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_engines_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "et", NULL };
    int et;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_engines_type", kwlist, &et))
        return NULL;
    gwp_ship_set_engines_type(GWP_SHIP(self->obj), et);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_hull_type(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_hull_type(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_hull_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ht", NULL };
    int ht;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_hull_type", kwlist, &ht))
        return NULL;
    gwp_ship_set_hull_type(GWP_SHIP(self->obj), ht);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_beams_type(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_beams_type(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_beams_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bt", NULL };
    int bt;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_beams_type", kwlist, &bt))
        return NULL;
    gwp_ship_set_beams_type(GWP_SHIP(self->obj), bt);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_beams(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_beams(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_beams(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "beams", NULL };
    int beams;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_beams", kwlist, &beams))
        return NULL;
    gwp_ship_set_beams(GWP_SHIP(self->obj), beams);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_fighter_bays(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_fighter_bays(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_fighter_bays(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "f_bays", NULL };
    int f_bays;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_fighter_bays", kwlist, &f_bays))
        return NULL;
    gwp_ship_set_fighter_bays(GWP_SHIP(self->obj), f_bays);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_torps_type(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_torps_type(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_torps_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tt", NULL };
    int tt;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_torps_type", kwlist, &tt))
        return NULL;
    gwp_ship_set_torps_type(GWP_SHIP(self->obj), tt);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_torps(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_torps(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_torps(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "torps", NULL };
    int torps;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_torps", kwlist, &torps))
        return NULL;
    gwp_ship_set_torps(GWP_SHIP(self->obj), torps);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_fighters(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_fighters(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_fighters(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "fighters", NULL };
    int fighters;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_fighters", kwlist, &fighters))
        return NULL;
    gwp_ship_set_fighters(GWP_SHIP(self->obj), fighters);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_torps_launchers(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_torps_launchers(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_torps_launchers(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tl", NULL };
    int tl;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_torps_launchers", kwlist, &tl))
        return NULL;
    gwp_ship_set_torps_launchers(GWP_SHIP(self->obj), tl);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_mission(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_mission(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_mission(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mission", NULL };
    int mission;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_mission", kwlist, &mission))
        return NULL;
    gwp_ship_set_mission(GWP_SHIP(self->obj), mission);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_primary_enemy(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_primary_enemy(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_primary_enemy(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "pe", NULL };
    int pe;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_primary_enemy", kwlist, &pe))
        return NULL;
    gwp_ship_set_primary_enemy(GWP_SHIP(self->obj), pe);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_tow_ship_id(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_tow_ship_id(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_tow_ship_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_tow_ship_id", kwlist, &id))
        return NULL;
    gwp_ship_set_tow_ship_id(GWP_SHIP(self->obj), id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_damage(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_damage(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_damage(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dmg", NULL };
    int dmg;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_damage", kwlist, &dmg))
        return NULL;
    gwp_ship_set_damage(GWP_SHIP(self->obj), dmg);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_crew(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_crew(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_crew(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "crew", NULL };
    int crew;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_crew", kwlist, &crew))
        return NULL;
    gwp_ship_set_crew(GWP_SHIP(self->obj), crew);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_colonists(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_colonists(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_colonists(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "col", NULL };
    int col;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_colonists", kwlist, &col))
        return NULL;
    gwp_ship_set_colonists(GWP_SHIP(self->obj), col);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_neutronium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_neutronium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_neutronium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "neu", NULL };
    int neu;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_neutronium", kwlist, &neu))
        return NULL;
    gwp_ship_set_neutronium(GWP_SHIP(self->obj), neu);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_tritanium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tri", NULL };
    int tri;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_tritanium", kwlist, &tri))
        return NULL;
    gwp_ship_set_tritanium(GWP_SHIP(self->obj), tri);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_duranium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dur", NULL };
    int dur;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_duranium", kwlist, &dur))
        return NULL;
    gwp_ship_set_duranium(GWP_SHIP(self->obj), dur);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_molybdenum(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mol", NULL };
    int mol;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_molybdenum", kwlist, &mol))
        return NULL;
    gwp_ship_set_molybdenum(GWP_SHIP(self->obj), mol);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_supplies(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_supplies(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_supplies(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "sup", NULL };
    int sup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_supplies", kwlist, &sup))
        return NULL;
    gwp_ship_set_supplies(GWP_SHIP(self->obj), sup);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_unload_neutronium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_unload_neutronium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_unload_neutronium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "neu", NULL };
    int neu;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_unload_neutronium", kwlist, &neu))
        return NULL;
    gwp_ship_set_unload_neutronium(GWP_SHIP(self->obj), neu);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_unload_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_unload_tritanium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_unload_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tri", NULL };
    int tri;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_unload_tritanium", kwlist, &tri))
        return NULL;
    gwp_ship_set_unload_tritanium(GWP_SHIP(self->obj), tri);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_unload_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_unload_duranium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_unload_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dur", NULL };
    int dur;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_unload_duranium", kwlist, &dur))
        return NULL;
    gwp_ship_set_unload_duranium(GWP_SHIP(self->obj), dur);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_unload_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_unload_molybdenum(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_unload_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mol", NULL };
    int mol;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_unload_molybdenum", kwlist, &mol))
        return NULL;
    gwp_ship_set_unload_molybdenum(GWP_SHIP(self->obj), mol);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_unload_supplies(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_unload_supplies(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_unload_supplies(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "sup", NULL };
    int sup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_unload_supplies", kwlist, &sup))
        return NULL;
    gwp_ship_set_unload_supplies(GWP_SHIP(self->obj), sup);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_set_unload_colonists(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "col", NULL };
    int col;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_unload_colonists", kwlist, &col))
        return NULL;
    gwp_ship_set_unload_colonists(GWP_SHIP(self->obj), col);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_unload_colonists(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_unload_colonists(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_unload_planet_id(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_unload_planet_id(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_unload_planet_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "pid", NULL };
    int pid;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_unload_planet_id", kwlist, &pid))
        return NULL;
    gwp_ship_set_unload_planet_id(GWP_SHIP(self->obj), pid);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_transfer_neutronium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_transfer_neutronium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_transfer_neutronium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "neu", NULL };
    int neu;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_transfer_neutronium", kwlist, &neu))
        return NULL;
    gwp_ship_set_transfer_neutronium(GWP_SHIP(self->obj), neu);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_transfer_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_transfer_tritanium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_transfer_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tri", NULL };
    int tri;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_transfer_tritanium", kwlist, &tri))
        return NULL;
    gwp_ship_set_transfer_tritanium(GWP_SHIP(self->obj), tri);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_transfer_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_transfer_duranium(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_transfer_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dur", NULL };
    int dur;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_transfer_duranium", kwlist, &dur))
        return NULL;
    gwp_ship_set_transfer_duranium(GWP_SHIP(self->obj), dur);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_transfer_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_transfer_molybdenum(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_transfer_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mol", NULL };
    int mol;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_transfer_molybdenum", kwlist, &mol))
        return NULL;
    gwp_ship_set_transfer_molybdenum(GWP_SHIP(self->obj), mol);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_transfer_supplies(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_transfer_supplies(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_transfer_supplies(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "sup", NULL };
    int sup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_transfer_supplies", kwlist, &sup))
        return NULL;
    gwp_ship_set_transfer_supplies(GWP_SHIP(self->obj), sup);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_set_transfer_colonists(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "col", NULL };
    int col;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_transfer_colonists", kwlist, &col))
        return NULL;
    gwp_ship_set_transfer_colonists(GWP_SHIP(self->obj), col);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_transfer_colonists(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_transfer_colonists(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_get_transfer_ship_id(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_transfer_ship_id(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_transfer_ship_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "sid", NULL };
    int sid;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_transfer_ship_id", kwlist, &sid))
        return NULL;
    gwp_ship_set_transfer_ship_id(GWP_SHIP(self->obj), sid);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_intercept_ship_id(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_intercept_ship_id(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_intercept_ship_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "sid", NULL };
    int sid;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_intercept_ship_id", kwlist, &sid))
        return NULL;
    gwp_ship_set_intercept_ship_id(GWP_SHIP(self->obj), sid);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_ship_get_megacredits(PyGObject *self)
{
    int ret;

    ret = gwp_ship_get_megacredits(GWP_SHIP(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_ship_set_megacredits(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "m", NULL };
    int m;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpShip.set_megacredits", kwlist, &m))
        return NULL;
    gwp_ship_set_megacredits(GWP_SHIP(self->obj), m);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpShip_methods[] = {
    { "has_beam_weapons", (PyCFunction)_wrap_gwp_ship_has_beam_weapons, METH_NOARGS },
    { "has_torp_weapons", (PyCFunction)_wrap_gwp_ship_has_torp_weapons, METH_NOARGS },
    { "get_primary_enemy_name", (PyCFunction)_wrap_gwp_ship_get_primary_enemy_name, METH_NOARGS },
    { "get_mission_name", (PyCFunction)_wrap_gwp_ship_get_mission_name, METH_NOARGS },
    { "get_owner_name", (PyCFunction)_wrap_gwp_ship_get_owner_name, METH_NOARGS },
    { "get_hull_name_trunc", (PyCFunction)_wrap_gwp_ship_get_hull_name_trunc, METH_VARARGS|METH_KEYWORDS },
    { "get_hull_cargo", (PyCFunction)_wrap_gwp_ship_get_hull_cargo, METH_NOARGS },
    { "get_hull_fuel_tank", (PyCFunction)_wrap_gwp_ship_get_hull_fuel_tank, METH_NOARGS },
    { "get_hull_crew", (PyCFunction)_wrap_gwp_ship_get_hull_crew, METH_NOARGS },
    { "get_hull_engines", (PyCFunction)_wrap_gwp_ship_get_hull_engines, METH_NOARGS },
    { "get_hull_beam_weapons", (PyCFunction)_wrap_gwp_ship_get_hull_beam_weapons, METH_NOARGS },
    { "get_hull_torp_launchers", (PyCFunction)_wrap_gwp_ship_get_hull_torp_launchers, METH_NOARGS },
    { "get_hull_fighter_bays", (PyCFunction)_wrap_gwp_ship_get_hull_fighter_bays, METH_NOARGS },
    { "get_hull_picture", (PyCFunction)_wrap_gwp_ship_get_hull_picture, METH_NOARGS },
    { "get_engine_name", (PyCFunction)_wrap_gwp_ship_get_engine_name, METH_NOARGS },
    { "get_beams_name", (PyCFunction)_wrap_gwp_ship_get_beams_name, METH_NOARGS },
    { "get_torps_name", (PyCFunction)_wrap_gwp_ship_get_torps_name, METH_NOARGS },
    { "calculate_heading", (PyCFunction)_wrap_gwp_ship_calculate_heading, METH_NOARGS },
    { "valid_coords", (PyCFunction)_wrap_gwp_ship_valid_coords, METH_NOARGS },
    { "is_mine", (PyCFunction)_wrap_gwp_ship_is_mine, METH_NOARGS },
    { "get_waypoint", (PyCFunction)_wrap_gwp_ship_get_waypoint, METH_NOARGS },
    { "calculate_waypoint_distance", (PyCFunction)_wrap_gwp_ship_calculate_waypoint_distance, METH_NOARGS },
    { "calculate_eta", (PyCFunction)_wrap_gwp_ship_calculate_eta, METH_NOARGS },
    { "calculate_fuel_usage", (PyCFunction)_wrap_gwp_ship_calculate_fuel_usage, METH_NOARGS },
    { "calculate_cargo", (PyCFunction)_wrap_gwp_ship_calculate_cargo, METH_NOARGS },
    { "calculate_mass", (PyCFunction)_wrap_gwp_ship_calculate_mass, METH_NOARGS },
    { "calculate_lay_mines_torps", (PyCFunction)_wrap_gwp_ship_calculate_lay_mines_torps, METH_NOARGS },
    { "is_known", (PyCFunction)_wrap_gwp_ship_is_known, METH_NOARGS },
    { "set_known", (PyCFunction)_wrap_gwp_ship_set_known, METH_VARARGS|METH_KEYWORDS },
    { "get_owner", (PyCFunction)_wrap_gwp_ship_get_owner, METH_NOARGS },
    { "set_owner", (PyCFunction)_wrap_gwp_ship_set_owner, METH_VARARGS|METH_KEYWORDS },
    { "get_mass_if_unknown", (PyCFunction)_wrap_gwp_ship_get_mass_if_unknown, METH_NOARGS },
    { "set_mass_if_unknown", (PyCFunction)_wrap_gwp_ship_set_mass_if_unknown, METH_VARARGS|METH_KEYWORDS },
    { "get_fcode", (PyCFunction)_wrap_gwp_ship_get_fcode, METH_NOARGS },
    { "set_fcode", (PyCFunction)_wrap_gwp_ship_set_fcode, METH_VARARGS|METH_KEYWORDS },
    { "get_x_to_waypoint", (PyCFunction)_wrap_gwp_ship_get_x_to_waypoint, METH_NOARGS },
    { "set_x_to_waypoint", (PyCFunction)_wrap_gwp_ship_set_x_to_waypoint, METH_VARARGS|METH_KEYWORDS },
    { "get_y_to_waypoint", (PyCFunction)_wrap_gwp_ship_get_y_to_waypoint, METH_NOARGS },
    { "set_y_to_waypoint", (PyCFunction)_wrap_gwp_ship_set_y_to_waypoint, METH_VARARGS|METH_KEYWORDS },
    { "get_engines_type", (PyCFunction)_wrap_gwp_ship_get_engines_type, METH_NOARGS },
    { "set_engines_type", (PyCFunction)_wrap_gwp_ship_set_engines_type, METH_VARARGS|METH_KEYWORDS },
    { "get_hull_type", (PyCFunction)_wrap_gwp_ship_get_hull_type, METH_NOARGS },
    { "set_hull_type", (PyCFunction)_wrap_gwp_ship_set_hull_type, METH_VARARGS|METH_KEYWORDS },
    { "get_beams_type", (PyCFunction)_wrap_gwp_ship_get_beams_type, METH_NOARGS },
    { "set_beams_type", (PyCFunction)_wrap_gwp_ship_set_beams_type, METH_VARARGS|METH_KEYWORDS },
    { "get_beams", (PyCFunction)_wrap_gwp_ship_get_beams, METH_NOARGS },
    { "set_beams", (PyCFunction)_wrap_gwp_ship_set_beams, METH_VARARGS|METH_KEYWORDS },
    { "get_fighter_bays", (PyCFunction)_wrap_gwp_ship_get_fighter_bays, METH_NOARGS },
    { "set_fighter_bays", (PyCFunction)_wrap_gwp_ship_set_fighter_bays, METH_VARARGS|METH_KEYWORDS },
    { "get_torps_type", (PyCFunction)_wrap_gwp_ship_get_torps_type, METH_NOARGS },
    { "set_torps_type", (PyCFunction)_wrap_gwp_ship_set_torps_type, METH_VARARGS|METH_KEYWORDS },
    { "get_torps", (PyCFunction)_wrap_gwp_ship_get_torps, METH_NOARGS },
    { "set_torps", (PyCFunction)_wrap_gwp_ship_set_torps, METH_VARARGS|METH_KEYWORDS },
    { "get_fighters", (PyCFunction)_wrap_gwp_ship_get_fighters, METH_NOARGS },
    { "set_fighters", (PyCFunction)_wrap_gwp_ship_set_fighters, METH_VARARGS|METH_KEYWORDS },
    { "get_torps_launchers", (PyCFunction)_wrap_gwp_ship_get_torps_launchers, METH_NOARGS },
    { "set_torps_launchers", (PyCFunction)_wrap_gwp_ship_set_torps_launchers, METH_VARARGS|METH_KEYWORDS },
    { "get_mission", (PyCFunction)_wrap_gwp_ship_get_mission, METH_NOARGS },
    { "set_mission", (PyCFunction)_wrap_gwp_ship_set_mission, METH_VARARGS|METH_KEYWORDS },
    { "get_primary_enemy", (PyCFunction)_wrap_gwp_ship_get_primary_enemy, METH_NOARGS },
    { "set_primary_enemy", (PyCFunction)_wrap_gwp_ship_set_primary_enemy, METH_VARARGS|METH_KEYWORDS },
    { "get_tow_ship_id", (PyCFunction)_wrap_gwp_ship_get_tow_ship_id, METH_NOARGS },
    { "set_tow_ship_id", (PyCFunction)_wrap_gwp_ship_set_tow_ship_id, METH_VARARGS|METH_KEYWORDS },
    { "get_damage", (PyCFunction)_wrap_gwp_ship_get_damage, METH_NOARGS },
    { "set_damage", (PyCFunction)_wrap_gwp_ship_set_damage, METH_VARARGS|METH_KEYWORDS },
    { "get_crew", (PyCFunction)_wrap_gwp_ship_get_crew, METH_NOARGS },
    { "set_crew", (PyCFunction)_wrap_gwp_ship_set_crew, METH_VARARGS|METH_KEYWORDS },
    { "get_colonists", (PyCFunction)_wrap_gwp_ship_get_colonists, METH_NOARGS },
    { "set_colonists", (PyCFunction)_wrap_gwp_ship_set_colonists, METH_VARARGS|METH_KEYWORDS },
    { "get_neutronium", (PyCFunction)_wrap_gwp_ship_get_neutronium, METH_NOARGS },
    { "set_neutronium", (PyCFunction)_wrap_gwp_ship_set_neutronium, METH_VARARGS|METH_KEYWORDS },
    { "get_tritanium", (PyCFunction)_wrap_gwp_ship_get_tritanium, METH_NOARGS },
    { "set_tritanium", (PyCFunction)_wrap_gwp_ship_set_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_duranium", (PyCFunction)_wrap_gwp_ship_get_duranium, METH_NOARGS },
    { "set_duranium", (PyCFunction)_wrap_gwp_ship_set_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_molybdenum", (PyCFunction)_wrap_gwp_ship_get_molybdenum, METH_NOARGS },
    { "set_molybdenum", (PyCFunction)_wrap_gwp_ship_set_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_supplies", (PyCFunction)_wrap_gwp_ship_get_supplies, METH_NOARGS },
    { "set_supplies", (PyCFunction)_wrap_gwp_ship_set_supplies, METH_VARARGS|METH_KEYWORDS },
    { "get_unload_neutronium", (PyCFunction)_wrap_gwp_ship_get_unload_neutronium, METH_NOARGS },
    { "set_unload_neutronium", (PyCFunction)_wrap_gwp_ship_set_unload_neutronium, METH_VARARGS|METH_KEYWORDS },
    { "get_unload_tritanium", (PyCFunction)_wrap_gwp_ship_get_unload_tritanium, METH_NOARGS },
    { "set_unload_tritanium", (PyCFunction)_wrap_gwp_ship_set_unload_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_unload_duranium", (PyCFunction)_wrap_gwp_ship_get_unload_duranium, METH_NOARGS },
    { "set_unload_duranium", (PyCFunction)_wrap_gwp_ship_set_unload_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_unload_molybdenum", (PyCFunction)_wrap_gwp_ship_get_unload_molybdenum, METH_NOARGS },
    { "set_unload_molybdenum", (PyCFunction)_wrap_gwp_ship_set_unload_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_unload_supplies", (PyCFunction)_wrap_gwp_ship_get_unload_supplies, METH_NOARGS },
    { "set_unload_supplies", (PyCFunction)_wrap_gwp_ship_set_unload_supplies, METH_VARARGS|METH_KEYWORDS },
    { "set_unload_colonists", (PyCFunction)_wrap_gwp_ship_set_unload_colonists, METH_VARARGS|METH_KEYWORDS },
    { "get_unload_colonists", (PyCFunction)_wrap_gwp_ship_get_unload_colonists, METH_NOARGS },
    { "get_unload_planet_id", (PyCFunction)_wrap_gwp_ship_get_unload_planet_id, METH_NOARGS },
    { "set_unload_planet_id", (PyCFunction)_wrap_gwp_ship_set_unload_planet_id, METH_VARARGS|METH_KEYWORDS },
    { "get_transfer_neutronium", (PyCFunction)_wrap_gwp_ship_get_transfer_neutronium, METH_NOARGS },
    { "set_transfer_neutronium", (PyCFunction)_wrap_gwp_ship_set_transfer_neutronium, METH_VARARGS|METH_KEYWORDS },
    { "get_transfer_tritanium", (PyCFunction)_wrap_gwp_ship_get_transfer_tritanium, METH_NOARGS },
    { "set_transfer_tritanium", (PyCFunction)_wrap_gwp_ship_set_transfer_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_transfer_duranium", (PyCFunction)_wrap_gwp_ship_get_transfer_duranium, METH_NOARGS },
    { "set_transfer_duranium", (PyCFunction)_wrap_gwp_ship_set_transfer_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_transfer_molybdenum", (PyCFunction)_wrap_gwp_ship_get_transfer_molybdenum, METH_NOARGS },
    { "set_transfer_molybdenum", (PyCFunction)_wrap_gwp_ship_set_transfer_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_transfer_supplies", (PyCFunction)_wrap_gwp_ship_get_transfer_supplies, METH_NOARGS },
    { "set_transfer_supplies", (PyCFunction)_wrap_gwp_ship_set_transfer_supplies, METH_VARARGS|METH_KEYWORDS },
    { "set_transfer_colonists", (PyCFunction)_wrap_gwp_ship_set_transfer_colonists, METH_VARARGS|METH_KEYWORDS },
    { "get_transfer_colonists", (PyCFunction)_wrap_gwp_ship_get_transfer_colonists, METH_NOARGS },
    { "get_transfer_ship_id", (PyCFunction)_wrap_gwp_ship_get_transfer_ship_id, METH_NOARGS },
    { "set_transfer_ship_id", (PyCFunction)_wrap_gwp_ship_set_transfer_ship_id, METH_VARARGS|METH_KEYWORDS },
    { "get_intercept_ship_id", (PyCFunction)_wrap_gwp_ship_get_intercept_ship_id, METH_NOARGS },
    { "set_intercept_ship_id", (PyCFunction)_wrap_gwp_ship_set_intercept_ship_id, METH_VARARGS|METH_KEYWORDS },
    { "get_megacredits", (PyCFunction)_wrap_gwp_ship_get_megacredits, METH_NOARGS },
    { "set_megacredits", (PyCFunction)_wrap_gwp_ship_set_megacredits, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpShip_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Ship",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpShip_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_ship_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpStarbase ----------- */

static int
_wrap_gwp_starbase_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.Starbase.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_starbase_copy(PyGObject *self)
{
    GwpStarbase *ret;

    ret = gwp_starbase_copy(GWP_STARBASE(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gwp_starbase_get_id(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_id(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_get_defense(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_defense(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_defense(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "def_", NULL };
    int def;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_defense", kwlist, &def))
        return NULL;
    gwp_starbase_set_defense(GWP_STARBASE(self->obj), def);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_damage(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_damage(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_damage(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dam", NULL };
    int dam;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_damage", kwlist, &dam))
        return NULL;
    gwp_starbase_set_damage(GWP_STARBASE(self->obj), dam);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_engines_tech(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_engines_tech(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_engines_tech(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tech", NULL };
    int tech;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_engines_tech", kwlist, &tech))
        return NULL;
    gwp_starbase_set_engines_tech(GWP_STARBASE(self->obj), tech);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_hulls_tech(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_hulls_tech(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_hulls_tech(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tech", NULL };
    int tech;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_hulls_tech", kwlist, &tech))
        return NULL;
    gwp_starbase_set_hulls_tech(GWP_STARBASE(self->obj), tech);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_beams_tech(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_beams_tech(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_beams_tech(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tech", NULL };
    int tech;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_beams_tech", kwlist, &tech))
        return NULL;
    gwp_starbase_set_beams_tech(GWP_STARBASE(self->obj), tech);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_torps_tech(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_torps_tech(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_torps_tech(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tech", NULL };
    int tech;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_torps_tech", kwlist, &tech))
        return NULL;
    gwp_starbase_set_torps_tech(GWP_STARBASE(self->obj), tech);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_storage_engines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", NULL };
    int storage_nr, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.get_storage_engines", kwlist, &storage_nr))
        return NULL;
    ret = gwp_starbase_get_storage_engines(GWP_STARBASE(self->obj), storage_nr);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_storage_engines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", "engine", NULL };
    int storage_nr, engine;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpStarbase.set_storage_engines", kwlist, &storage_nr, &engine))
        return NULL;
    gwp_starbase_set_storage_engines(GWP_STARBASE(self->obj), storage_nr, engine);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_storage_hulls(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", NULL };
    int storage_nr, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.get_storage_hulls", kwlist, &storage_nr))
        return NULL;
    ret = gwp_starbase_get_storage_hulls(GWP_STARBASE(self->obj), storage_nr);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_storage_hulls(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", "hull", NULL };
    int storage_nr, hull;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpStarbase.set_storage_hulls", kwlist, &storage_nr, &hull))
        return NULL;
    gwp_starbase_set_storage_hulls(GWP_STARBASE(self->obj), storage_nr, hull);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_storage_beams(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", NULL };
    int storage_nr, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.get_storage_beams", kwlist, &storage_nr))
        return NULL;
    ret = gwp_starbase_get_storage_beams(GWP_STARBASE(self->obj), storage_nr);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_storage_beams(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", "beam", NULL };
    int storage_nr, beam;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpStarbase.set_storage_beams", kwlist, &storage_nr, &beam))
        return NULL;
    gwp_starbase_set_storage_beams(GWP_STARBASE(self->obj), storage_nr, beam);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_storage_torp_launchers(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", NULL };
    int storage_nr, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.get_storage_torp_launchers", kwlist, &storage_nr))
        return NULL;
    ret = gwp_starbase_get_storage_torp_launchers(GWP_STARBASE(self->obj), storage_nr);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_storage_torp_launchers(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", "t_launcher", NULL };
    int storage_nr, t_launcher;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpStarbase.set_storage_torp_launchers", kwlist, &storage_nr, &t_launcher))
        return NULL;
    gwp_starbase_set_storage_torp_launchers(GWP_STARBASE(self->obj), storage_nr, t_launcher);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_storage_torps(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", NULL };
    int storage_nr, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.get_storage_torps", kwlist, &storage_nr))
        return NULL;
    ret = gwp_starbase_get_storage_torps(GWP_STARBASE(self->obj), storage_nr);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_storage_torps(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "storage_nr", "torp", NULL };
    int storage_nr, torp;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpStarbase.set_storage_torps", kwlist, &storage_nr, &torp))
        return NULL;
    gwp_starbase_set_storage_torps(GWP_STARBASE(self->obj), storage_nr, torp);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_fighters(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_fighters(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_fighters(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "f", NULL };
    int f;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_fighters", kwlist, &f))
        return NULL;
    gwp_starbase_set_fighters(GWP_STARBASE(self->obj), f);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_id_ship(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_id_ship(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_id_ship(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_id_ship", kwlist, &id))
        return NULL;
    gwp_starbase_set_id_ship(GWP_STARBASE(self->obj), id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_ship_action(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_ship_action(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_ship_action(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "action", NULL };
    int action;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_ship_action", kwlist, &action))
        return NULL;
    gwp_starbase_set_ship_action(GWP_STARBASE(self->obj), action);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_mission(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_mission(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_mission(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mission", NULL };
    int mission;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_mission", kwlist, &mission))
        return NULL;
    gwp_starbase_set_mission(GWP_STARBASE(self->obj), mission);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_build_ship_type(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_build_ship_type(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_build_ship_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "type", NULL };
    int type;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_build_ship_type", kwlist, &type))
        return NULL;
    gwp_starbase_set_build_ship_type(GWP_STARBASE(self->obj), type);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_build_engine_type(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_build_engine_type(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_build_engine_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "type", NULL };
    int type;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_build_engine_type", kwlist, &type))
        return NULL;
    gwp_starbase_set_build_engine_type(GWP_STARBASE(self->obj), type);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_build_beam_type(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_build_beam_type(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_build_beam_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "type", NULL };
    int type;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_build_beam_type", kwlist, &type))
        return NULL;
    gwp_starbase_set_build_beam_type(GWP_STARBASE(self->obj), type);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_build_beam_count(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_build_beam_count(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_build_beam_count(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "count", NULL };
    int count;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_build_beam_count", kwlist, &count))
        return NULL;
    gwp_starbase_set_build_beam_count(GWP_STARBASE(self->obj), count);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_build_torp_type(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_build_torp_type(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_build_torp_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "type", NULL };
    int type;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_build_torp_type", kwlist, &type))
        return NULL;
    gwp_starbase_set_build_torp_type(GWP_STARBASE(self->obj), type);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_build_torp_count(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_build_torp_count(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_build_torp_count(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "count", NULL };
    int count;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_build_torp_count", kwlist, &count))
        return NULL;
    gwp_starbase_set_build_torp_count(GWP_STARBASE(self->obj), count);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_fighter_count(PyGObject *self)
{
    int ret;

    ret = gwp_starbase_get_fighter_count(GWP_STARBASE(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starbase_set_fighter_count(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "count", NULL };
    int count;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarbase.set_fighter_count", kwlist, &count))
        return NULL;
    gwp_starbase_set_fighter_count(GWP_STARBASE(self->obj), count);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_set_planet(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "p", NULL };
    PyGObject *p;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpStarbase.set_planet", kwlist, &PyGwpPlanet_Type, &p))
        return NULL;
    gwp_starbase_set_planet(GWP_STARBASE(self->obj), GWP_PLANET(p->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starbase_get_planet(PyGObject *self)
{
    GwpPlanet *ret;

    ret = gwp_starbase_get_planet(GWP_STARBASE(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyMethodDef _PyGwpStarbase_methods[] = {
    { "copy", (PyCFunction)_wrap_gwp_starbase_copy, METH_NOARGS },
    { "get_id", (PyCFunction)_wrap_gwp_starbase_get_id, METH_NOARGS },
    { "get_defense", (PyCFunction)_wrap_gwp_starbase_get_defense, METH_NOARGS },
    { "set_defense", (PyCFunction)_wrap_gwp_starbase_set_defense, METH_VARARGS|METH_KEYWORDS },
    { "get_damage", (PyCFunction)_wrap_gwp_starbase_get_damage, METH_NOARGS },
    { "set_damage", (PyCFunction)_wrap_gwp_starbase_set_damage, METH_VARARGS|METH_KEYWORDS },
    { "get_engines_tech", (PyCFunction)_wrap_gwp_starbase_get_engines_tech, METH_NOARGS },
    { "set_engines_tech", (PyCFunction)_wrap_gwp_starbase_set_engines_tech, METH_VARARGS|METH_KEYWORDS },
    { "get_hulls_tech", (PyCFunction)_wrap_gwp_starbase_get_hulls_tech, METH_NOARGS },
    { "set_hulls_tech", (PyCFunction)_wrap_gwp_starbase_set_hulls_tech, METH_VARARGS|METH_KEYWORDS },
    { "get_beams_tech", (PyCFunction)_wrap_gwp_starbase_get_beams_tech, METH_NOARGS },
    { "set_beams_tech", (PyCFunction)_wrap_gwp_starbase_set_beams_tech, METH_VARARGS|METH_KEYWORDS },
    { "get_torps_tech", (PyCFunction)_wrap_gwp_starbase_get_torps_tech, METH_NOARGS },
    { "set_torps_tech", (PyCFunction)_wrap_gwp_starbase_set_torps_tech, METH_VARARGS|METH_KEYWORDS },
    { "get_storage_engines", (PyCFunction)_wrap_gwp_starbase_get_storage_engines, METH_VARARGS|METH_KEYWORDS },
    { "set_storage_engines", (PyCFunction)_wrap_gwp_starbase_set_storage_engines, METH_VARARGS|METH_KEYWORDS },
    { "get_storage_hulls", (PyCFunction)_wrap_gwp_starbase_get_storage_hulls, METH_VARARGS|METH_KEYWORDS },
    { "set_storage_hulls", (PyCFunction)_wrap_gwp_starbase_set_storage_hulls, METH_VARARGS|METH_KEYWORDS },
    { "get_storage_beams", (PyCFunction)_wrap_gwp_starbase_get_storage_beams, METH_VARARGS|METH_KEYWORDS },
    { "set_storage_beams", (PyCFunction)_wrap_gwp_starbase_set_storage_beams, METH_VARARGS|METH_KEYWORDS },
    { "get_storage_torp_launchers", (PyCFunction)_wrap_gwp_starbase_get_storage_torp_launchers, METH_VARARGS|METH_KEYWORDS },
    { "set_storage_torp_launchers", (PyCFunction)_wrap_gwp_starbase_set_storage_torp_launchers, METH_VARARGS|METH_KEYWORDS },
    { "get_storage_torps", (PyCFunction)_wrap_gwp_starbase_get_storage_torps, METH_VARARGS|METH_KEYWORDS },
    { "set_storage_torps", (PyCFunction)_wrap_gwp_starbase_set_storage_torps, METH_VARARGS|METH_KEYWORDS },
    { "get_fighters", (PyCFunction)_wrap_gwp_starbase_get_fighters, METH_NOARGS },
    { "set_fighters", (PyCFunction)_wrap_gwp_starbase_set_fighters, METH_VARARGS|METH_KEYWORDS },
    { "get_id_ship", (PyCFunction)_wrap_gwp_starbase_get_id_ship, METH_NOARGS },
    { "set_id_ship", (PyCFunction)_wrap_gwp_starbase_set_id_ship, METH_VARARGS|METH_KEYWORDS },
    { "get_ship_action", (PyCFunction)_wrap_gwp_starbase_get_ship_action, METH_NOARGS },
    { "set_ship_action", (PyCFunction)_wrap_gwp_starbase_set_ship_action, METH_VARARGS|METH_KEYWORDS },
    { "get_mission", (PyCFunction)_wrap_gwp_starbase_get_mission, METH_NOARGS },
    { "set_mission", (PyCFunction)_wrap_gwp_starbase_set_mission, METH_VARARGS|METH_KEYWORDS },
    { "get_build_ship_type", (PyCFunction)_wrap_gwp_starbase_get_build_ship_type, METH_NOARGS },
    { "set_build_ship_type", (PyCFunction)_wrap_gwp_starbase_set_build_ship_type, METH_VARARGS|METH_KEYWORDS },
    { "get_build_engine_type", (PyCFunction)_wrap_gwp_starbase_get_build_engine_type, METH_NOARGS },
    { "set_build_engine_type", (PyCFunction)_wrap_gwp_starbase_set_build_engine_type, METH_VARARGS|METH_KEYWORDS },
    { "get_build_beam_type", (PyCFunction)_wrap_gwp_starbase_get_build_beam_type, METH_NOARGS },
    { "set_build_beam_type", (PyCFunction)_wrap_gwp_starbase_set_build_beam_type, METH_VARARGS|METH_KEYWORDS },
    { "get_build_beam_count", (PyCFunction)_wrap_gwp_starbase_get_build_beam_count, METH_NOARGS },
    { "set_build_beam_count", (PyCFunction)_wrap_gwp_starbase_set_build_beam_count, METH_VARARGS|METH_KEYWORDS },
    { "get_build_torp_type", (PyCFunction)_wrap_gwp_starbase_get_build_torp_type, METH_NOARGS },
    { "set_build_torp_type", (PyCFunction)_wrap_gwp_starbase_set_build_torp_type, METH_VARARGS|METH_KEYWORDS },
    { "get_build_torp_count", (PyCFunction)_wrap_gwp_starbase_get_build_torp_count, METH_NOARGS },
    { "set_build_torp_count", (PyCFunction)_wrap_gwp_starbase_set_build_torp_count, METH_VARARGS|METH_KEYWORDS },
    { "get_fighter_count", (PyCFunction)_wrap_gwp_starbase_get_fighter_count, METH_NOARGS },
    { "set_fighter_count", (PyCFunction)_wrap_gwp_starbase_set_fighter_count, METH_VARARGS|METH_KEYWORDS },
    { "set_planet", (PyCFunction)_wrap_gwp_starbase_set_planet, METH_VARARGS|METH_KEYWORDS },
    { "get_planet", (PyCFunction)_wrap_gwp_starbase_get_planet, METH_NOARGS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpStarbase_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Starbase",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpStarbase_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_starbase_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpStarchart ----------- */

static int
_wrap_gwp_starchart_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, ":gwp.Starchart.__init__", kwlist))
        return -1;

    self->obj = g_object_newv(obj_type, 0, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}


static PyObject *
_wrap_gwp_starchart_calculate_width(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_calculate_width(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_calculate_canvas_width(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_calculate_canvas_width(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_calculate_quads_per_line(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_calculate_quads_per_line(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_calculate_total_quads(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_calculate_total_quads(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_has_valid_coords(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "obj", NULL };
    PyGObject *obj;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpStarchart.has_valid_coords", kwlist, &PyGwpObject_Type, &obj))
        return NULL;
    ret = gwp_starchart_has_valid_coords(GWP_STARCHART(self->obj), GWP_OBJECT(obj->obj));
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_gwp_starchart_calculate_obj_quadrant(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "obj", NULL };
    PyGObject *obj;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpStarchart.calculate_obj_quadrant", kwlist, &PyGwpObject_Type, &obj))
        return NULL;
    ret = gwp_starchart_calculate_obj_quadrant(GWP_STARCHART(self->obj), GWP_OBJECT(obj->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_calculate_quadrant(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    int ret;
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:GwpStarchart.calculate_quadrant", kwlist, &x, &y))
        return NULL;
    ret = gwp_starchart_calculate_quadrant(GWP_STARCHART(self->obj), x, y);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_get_x_max(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_get_x_max(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_set_x_max(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", NULL };
    int x;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.set_x_max", kwlist, &x))
        return NULL;
    gwp_starchart_set_x_max(GWP_STARCHART(self->obj), x);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_get_x_min(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_get_x_min(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_set_x_min(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", NULL };
    int x;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.set_x_min", kwlist, &x))
        return NULL;
    gwp_starchart_set_x_min(GWP_STARCHART(self->obj), x);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_get_y_max(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_get_y_max(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_set_y_max(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "y", NULL };
    int y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.set_y_max", kwlist, &y))
        return NULL;
    gwp_starchart_set_y_max(GWP_STARCHART(self->obj), y);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_get_y_min(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_get_y_min(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_set_y_min(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "y", NULL };
    int y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.set_y_min", kwlist, &y))
        return NULL;
    gwp_starchart_set_y_min(GWP_STARCHART(self->obj), y);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_get_valid_margin(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_get_valid_margin(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_set_valid_margin(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "margin", NULL };
    int margin;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.set_valid_margin", kwlist, &margin))
        return NULL;
    gwp_starchart_set_valid_margin(GWP_STARCHART(self->obj), margin);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_get_canvas_margin(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_get_canvas_margin(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_set_canvas_margin(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "margin", NULL };
    int margin;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.set_canvas_margin", kwlist, &margin))
        return NULL;
    gwp_starchart_set_canvas_margin(GWP_STARCHART(self->obj), margin);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_get_quad_width(PyGObject *self)
{
    int ret;

    ret = gwp_starchart_get_quad_width(GWP_STARCHART(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_set_quad_width(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "width", NULL };
    int width;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.set_quad_width", kwlist, &width))
        return NULL;
    gwp_starchart_set_quad_width(GWP_STARCHART(self->obj), width);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_set_planets_per_quad(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "planet", NULL };
    PyGObject *planet;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpStarchart.set_planets_per_quad", kwlist, &PyGwpPlanet_Type, &planet))
        return NULL;
    gwp_starchart_set_planets_per_quad(GWP_STARCHART(self->obj), GWP_PLANET(planet->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_set_ships_per_quad(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ship", NULL };
    PyGObject *ship;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpStarchart.set_ships_per_quad", kwlist, &PyGwpShip_Type, &ship))
        return NULL;
    gwp_starchart_set_ships_per_quad(GWP_STARCHART(self->obj), GWP_SHIP(ship->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_set_locations_per_quad(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "loc", NULL };
    PyGObject *loc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpStarchart.set_locations_per_quad", kwlist, &PyGwpLocation_Type, &loc))
        return NULL;
    gwp_starchart_set_locations_per_quad(GWP_STARCHART(self->obj), GWP_LOCATION(loc->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_select_nearest_planet(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    int x, y;
    GwpPlanet *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpStarchart.select_nearest_planet", kwlist, &x, &y))
        return NULL;
    ret = gwp_starchart_select_nearest_planet(GWP_STARCHART(self->obj), x, y);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gwp_starchart_select_planet(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "planet_id", NULL };
    int planet_id;
    GwpPlanet *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.select_planet", kwlist, &planet_id))
        return NULL;
    ret = gwp_starchart_select_planet(GWP_STARCHART(self->obj), planet_id);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_gwp_starchart_center_around(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "obj", NULL };
    PyGObject *obj;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:GwpStarchart.center_around", kwlist, &PyGwpObject_Type, &obj))
        return NULL;
    gwp_starchart_center_around(GWP_STARCHART(self->obj), GWP_OBJECT(obj->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_draw_line(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "from_x", "from_y", "to_x", "to_y", "color", NULL };
    int from_x, from_y, to_x, to_y, ret;
    char *color;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiiis:GwpStarchart.draw_line", kwlist, &from_x, &from_y, &to_x, &to_y, &color))
        return NULL;
    ret = gwp_starchart_draw_line(GWP_STARCHART(self->obj), from_x, from_y, to_x, to_y, color);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_draw_line_on_marker(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "marker", "from_x", "from_y", "to_x", "to_y", "color", NULL };
    int marker, from_x, from_y, to_x, to_y;
    char *color;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiiiis:GwpStarchart.draw_line_on_marker", kwlist, &marker, &from_x, &from_y, &to_x, &to_y, &color))
        return NULL;
    gwp_starchart_draw_line_on_marker(GWP_STARCHART(self->obj), marker, from_x, from_y, to_x, to_y, color);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_starchart_draw_group(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    int x, y, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:GwpStarchart.draw_group", kwlist, &x, &y))
        return NULL;
    ret = gwp_starchart_draw_group(GWP_STARCHART(self->obj), x, y);
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_starchart_delete_draw(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "idx", NULL };
    int idx;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpStarchart.delete_draw", kwlist, &idx))
        return NULL;
    gwp_starchart_delete_draw(GWP_STARCHART(self->obj), idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpStarchart_methods[] = {
    { "calculate_width", (PyCFunction)_wrap_gwp_starchart_calculate_width, METH_NOARGS },
    { "calculate_canvas_width", (PyCFunction)_wrap_gwp_starchart_calculate_canvas_width, METH_NOARGS },
    { "calculate_quads_per_line", (PyCFunction)_wrap_gwp_starchart_calculate_quads_per_line, METH_NOARGS },
    { "calculate_total_quads", (PyCFunction)_wrap_gwp_starchart_calculate_total_quads, METH_NOARGS },
    { "has_valid_coords", (PyCFunction)_wrap_gwp_starchart_has_valid_coords, METH_VARARGS|METH_KEYWORDS },
    { "calculate_obj_quadrant", (PyCFunction)_wrap_gwp_starchart_calculate_obj_quadrant, METH_VARARGS|METH_KEYWORDS },
    { "calculate_quadrant", (PyCFunction)_wrap_gwp_starchart_calculate_quadrant, METH_VARARGS|METH_KEYWORDS },
    { "get_x_max", (PyCFunction)_wrap_gwp_starchart_get_x_max, METH_NOARGS },
    { "set_x_max", (PyCFunction)_wrap_gwp_starchart_set_x_max, METH_VARARGS|METH_KEYWORDS },
    { "get_x_min", (PyCFunction)_wrap_gwp_starchart_get_x_min, METH_NOARGS },
    { "set_x_min", (PyCFunction)_wrap_gwp_starchart_set_x_min, METH_VARARGS|METH_KEYWORDS },
    { "get_y_max", (PyCFunction)_wrap_gwp_starchart_get_y_max, METH_NOARGS },
    { "set_y_max", (PyCFunction)_wrap_gwp_starchart_set_y_max, METH_VARARGS|METH_KEYWORDS },
    { "get_y_min", (PyCFunction)_wrap_gwp_starchart_get_y_min, METH_NOARGS },
    { "set_y_min", (PyCFunction)_wrap_gwp_starchart_set_y_min, METH_VARARGS|METH_KEYWORDS },
    { "get_valid_margin", (PyCFunction)_wrap_gwp_starchart_get_valid_margin, METH_NOARGS },
    { "set_valid_margin", (PyCFunction)_wrap_gwp_starchart_set_valid_margin, METH_VARARGS|METH_KEYWORDS },
    { "get_canvas_margin", (PyCFunction)_wrap_gwp_starchart_get_canvas_margin, METH_NOARGS },
    { "set_canvas_margin", (PyCFunction)_wrap_gwp_starchart_set_canvas_margin, METH_VARARGS|METH_KEYWORDS },
    { "get_quad_width", (PyCFunction)_wrap_gwp_starchart_get_quad_width, METH_NOARGS },
    { "set_quad_width", (PyCFunction)_wrap_gwp_starchart_set_quad_width, METH_VARARGS|METH_KEYWORDS },
    { "set_planets_per_quad", (PyCFunction)_wrap_gwp_starchart_set_planets_per_quad, METH_VARARGS|METH_KEYWORDS },
    { "set_ships_per_quad", (PyCFunction)_wrap_gwp_starchart_set_ships_per_quad, METH_VARARGS|METH_KEYWORDS },
    { "set_locations_per_quad", (PyCFunction)_wrap_gwp_starchart_set_locations_per_quad, METH_VARARGS|METH_KEYWORDS },
    { "select_nearest_planet", (PyCFunction)_wrap_gwp_starchart_select_nearest_planet, METH_VARARGS|METH_KEYWORDS },
    { "select_planet", (PyCFunction)_wrap_gwp_starchart_select_planet, METH_VARARGS|METH_KEYWORDS },
    { "center_around", (PyCFunction)_wrap_gwp_starchart_center_around, METH_VARARGS|METH_KEYWORDS },
    { "draw_line", (PyCFunction)_wrap_gwp_starchart_draw_line, METH_VARARGS|METH_KEYWORDS },
    { "draw_line_on_marker", (PyCFunction)_wrap_gwp_starchart_draw_line_on_marker, METH_VARARGS|METH_KEYWORDS },
    { "draw_group", (PyCFunction)_wrap_gwp_starchart_draw_group, METH_VARARGS|METH_KEYWORDS },
    { "delete_draw", (PyCFunction)_wrap_gwp_starchart_delete_draw, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpStarchart_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.Starchart",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpStarchart_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_gwp_starchart_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- GwpTorpSpec ----------- */

static PyObject *
_wrap_gwp_torpspec_get_id(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_id(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_id", kwlist, &id))
        return NULL;
    gwp_torpspec_set_id(GWP_TORP_SPEC(self->obj), id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_name(PyGObject *self)
{
    gchar *ret;

    ret = gwp_torpspec_get_name(GWP_TORP_SPEC(self->obj));
    if (ret) {
        PyObject *py_ret = PyString_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_set_name(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "name", NULL };
    char *name;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:GwpTorpSpec.set_name", kwlist, &name))
        return NULL;
    gwp_torpspec_set_name(GWP_TORP_SPEC(self->obj), name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_ammo_cost(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_ammo_cost(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_ammo_cost(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tc", NULL };
    int tc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_ammo_cost", kwlist, &tc))
        return NULL;
    gwp_torpspec_set_ammo_cost(GWP_TORP_SPEC(self->obj), tc);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_cost(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_cost(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_cost(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "lc", NULL };
    int lc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_cost", kwlist, &lc))
        return NULL;
    gwp_torpspec_set_cost(GWP_TORP_SPEC(self->obj), lc);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_tritanium(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_tritanium(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_tritanium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tri", NULL };
    int tri;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_tritanium", kwlist, &tri))
        return NULL;
    gwp_torpspec_set_tritanium(GWP_TORP_SPEC(self->obj), tri);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_duranium(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_duranium(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_duranium(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dur", NULL };
    int dur;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_duranium", kwlist, &dur))
        return NULL;
    gwp_torpspec_set_duranium(GWP_TORP_SPEC(self->obj), dur);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_molybdenum(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_molybdenum(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_molybdenum(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mol", NULL };
    int mol;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_molybdenum", kwlist, &mol))
        return NULL;
    gwp_torpspec_set_molybdenum(GWP_TORP_SPEC(self->obj), mol);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_mass(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_mass(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_mass(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mass", NULL };
    int mass;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_mass", kwlist, &mass))
        return NULL;
    gwp_torpspec_set_mass(GWP_TORP_SPEC(self->obj), mass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_tech_level(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_tech_level(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_tech_level(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "tl", NULL };
    int tl;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_tech_level", kwlist, &tl))
        return NULL;
    gwp_torpspec_set_tech_level(GWP_TORP_SPEC(self->obj), tl);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_kill_value(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_kill_value(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_kill_value(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "kv", NULL };
    int kv;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_kill_value", kwlist, &kv))
        return NULL;
    gwp_torpspec_set_kill_value(GWP_TORP_SPEC(self->obj), kv);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gwp_torpspec_get_damage_value(PyGObject *self)
{
    int ret;

    ret = gwp_torpspec_get_damage_value(GWP_TORP_SPEC(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_gwp_torpspec_set_damage_value(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dv", NULL };
    int dv;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:GwpTorpSpec.set_damage_value", kwlist, &dv))
        return NULL;
    gwp_torpspec_set_damage_value(GWP_TORP_SPEC(self->obj), dv);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyGwpTorpSpec_methods[] = {
    { "get_id", (PyCFunction)_wrap_gwp_torpspec_get_id, METH_NOARGS },
    { "set_id", (PyCFunction)_wrap_gwp_torpspec_set_id, METH_VARARGS|METH_KEYWORDS },
    { "get_name", (PyCFunction)_wrap_gwp_torpspec_get_name, METH_NOARGS },
    { "set_name", (PyCFunction)_wrap_gwp_torpspec_set_name, METH_VARARGS|METH_KEYWORDS },
    { "get_ammo_cost", (PyCFunction)_wrap_gwp_torpspec_get_ammo_cost, METH_NOARGS },
    { "set_ammo_cost", (PyCFunction)_wrap_gwp_torpspec_set_ammo_cost, METH_VARARGS|METH_KEYWORDS },
    { "get_cost", (PyCFunction)_wrap_gwp_torpspec_get_cost, METH_NOARGS },
    { "set_cost", (PyCFunction)_wrap_gwp_torpspec_set_cost, METH_VARARGS|METH_KEYWORDS },
    { "get_tritanium", (PyCFunction)_wrap_gwp_torpspec_get_tritanium, METH_NOARGS },
    { "set_tritanium", (PyCFunction)_wrap_gwp_torpspec_set_tritanium, METH_VARARGS|METH_KEYWORDS },
    { "get_duranium", (PyCFunction)_wrap_gwp_torpspec_get_duranium, METH_NOARGS },
    { "set_duranium", (PyCFunction)_wrap_gwp_torpspec_set_duranium, METH_VARARGS|METH_KEYWORDS },
    { "get_molybdenum", (PyCFunction)_wrap_gwp_torpspec_get_molybdenum, METH_NOARGS },
    { "set_molybdenum", (PyCFunction)_wrap_gwp_torpspec_set_molybdenum, METH_VARARGS|METH_KEYWORDS },
    { "get_mass", (PyCFunction)_wrap_gwp_torpspec_get_mass, METH_NOARGS },
    { "set_mass", (PyCFunction)_wrap_gwp_torpspec_set_mass, METH_VARARGS|METH_KEYWORDS },
    { "get_tech_level", (PyCFunction)_wrap_gwp_torpspec_get_tech_level, METH_NOARGS },
    { "set_tech_level", (PyCFunction)_wrap_gwp_torpspec_set_tech_level, METH_VARARGS|METH_KEYWORDS },
    { "get_kill_value", (PyCFunction)_wrap_gwp_torpspec_get_kill_value, METH_NOARGS },
    { "set_kill_value", (PyCFunction)_wrap_gwp_torpspec_set_kill_value, METH_VARARGS|METH_KEYWORDS },
    { "get_damage_value", (PyCFunction)_wrap_gwp_torpspec_get_damage_value, METH_NOARGS },
    { "set_damage_value", (PyCFunction)_wrap_gwp_torpspec_set_damage_value, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyGwpTorpSpec_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "gwp.TorpSpec",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyGwpTorpSpec_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- functions ----------- */

static PyObject *
_wrap_gwp_planet_get_ground_percent(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mineral", NULL };
    int mineral;
    double ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:gwp_planet_get_ground_percent", kwlist, &mineral))
        return NULL;
    ret = gwp_planet_get_ground_percent(mineral);
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_ship_get_by_id(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;
    GwpShip *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:ship_get_by_id", kwlist, &id))
        return NULL;
    ret = ship_get_by_id(id);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_planet_get_by_id(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;
    GwpPlanet *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:planet_get_by_id", kwlist, &id))
        return NULL;
    ret = planet_get_by_id(id);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_get_game_state(PyObject *self)
{
    GwpGameState *ret;

    ret = get_game_state();
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

#line 43 "src/gwp-py-mappings.override"
static PyObject *
_wrap_ship_get_list (PyObject *self)
{
  PyObject *ret = PyDict_New();

  void add_ship (gpointer key, gpointer value, gpointer user_data) {
    PyObject *dict = (PyObject *)user_data;
    GwpShip *ship = GWP_SHIP(value);

    PyDict_SetItem (dict, 
		    PyInt_FromLong(gwp_object_get_id(GWP_OBJECT(ship))),
		    pygobject_new((GObject *)ship));
  }
  
  g_hash_table_foreach (ship_list, (GHFunc)add_ship, (gpointer)ret);

  return ret;
}
#line 8831 "src/gwp-py-mappings.c"


#line 63 "src/gwp-py-mappings.override"
static PyObject *
_wrap_planet_get_list (PyObject *self)
{
  PyObject *ret = PyDict_New();

  void add_planet (gpointer key, gpointer value, gpointer user_data) {
    PyObject *dict = (PyObject *)user_data;
    GwpPlanet *planet = GWP_PLANET(value);

    PyDict_SetItem (dict, 
		    PyInt_FromLong(gwp_object_get_id(GWP_OBJECT(planet))),
		    pygobject_new((GObject *)planet));
  }
  
  g_hash_table_foreach (planet_list, (GHFunc)add_planet, (gpointer)ret);

  return ret;
}
#line 8853 "src/gwp-py-mappings.c"


#line 111 "src/gwp-py-mappings.override"
static PyObject *
_wrap_hullspec_get_list (PyObject *self)
{
  PyObject *ret = PyDict_New();

  void add_hullspec (gpointer value, gpointer user_data) {
    PyObject *dict = (PyObject *)user_data;
    GwpHullSpec *hullspec = GWP_HULLSPEC(value);

    PyDict_SetItem (dict, 
		    PyInt_FromLong(gwp_hullspec_get_id(hullspec)),
		    pygobject_new((GObject *)hullspec));
  }
  
  g_slist_foreach (hullspec_list, (GFunc)add_hullspec, (gpointer)ret);

  return ret;
}
#line 8875 "src/gwp-py-mappings.c"


#line 131 "src/gwp-py-mappings.override"
static PyObject *
_wrap_engspec_get_list (PyObject *self)
{
  PyObject *ret = PyDict_New();

  void add_engspec (gpointer value, gpointer user_data) {
    PyObject *dict = (PyObject *)user_data;
    GwpEngSpec *engspec = GWP_ENGSPEC(value);

    PyDict_SetItem (dict, 
		    PyInt_FromLong(gwp_engspec_get_id(engspec)),
		    pygobject_new((GObject *)engspec));
  }
  
  g_slist_foreach (engspec_list, (GFunc)add_engspec, (gpointer)ret);

  return ret;
}
#line 8897 "src/gwp-py-mappings.c"


#line 151 "src/gwp-py-mappings.override"
static PyObject *
_wrap_beamspec_get_list (PyObject *self)
{
  PyObject *ret = PyDict_New();

  void add_beamspec (gpointer value, gpointer user_data) {
    PyObject *dict = (PyObject *)user_data;
    GwpBeamSpec *beamspec = GWP_BEAMSPEC(value);

    PyDict_SetItem (dict, 
		    PyInt_FromLong(gwp_beamspec_get_id(beamspec)),
		    pygobject_new((GObject *)beamspec));
  }
  
  g_slist_foreach (beamspec_list, (GFunc)add_beamspec, (gpointer)ret);

  return ret;
}
#line 8919 "src/gwp-py-mappings.c"


#line 171 "src/gwp-py-mappings.override"
static PyObject *
_wrap_torpspec_get_list (PyObject *self)
{
  PyObject *ret = PyDict_New();

  void add_torpspec (gpointer value, gpointer user_data) {
    PyObject *dict = (PyObject *)user_data;
    GwpTorpSpec *torpspec = GWP_TORPSPEC(value);

    PyDict_SetItem (dict, 
		    PyInt_FromLong(gwp_torpspec_get_id(torpspec)),
		    pygobject_new((GObject *)torpspec));
  }
  
  g_slist_foreach (torpspec_list, (GFunc)add_torpspec, (gpointer)ret);

  return ret;
}
#line 8941 "src/gwp-py-mappings.c"


#line 90 "src/gwp-py-mappings.override"
PyObject *
_wrap_set_plugin_mgr (PyObject *self, PyObject *args)
{
  PyObject *obj = NULL;  
  PyArg_ParseTuple (args, "O", &obj);

  gwp_game_state_set_plugin_mgr (game_state, obj);

  Py_INCREF (obj);
  Py_INCREF (Py_None);
  return Py_None;
}
#line 8957 "src/gwp-py-mappings.c"


#line 104 "src/gwp-py-mappings.override"
PyObject *
_wrap_get_plugin_mgr (PyObject *self)
{
  return (PyObject *)gwp_game_state_get_plugin_mgr (game_state);
}
#line 8966 "src/gwp-py-mappings.c"


#line 224 "src/gwp-py-mappings.override"
static PyObject *
_wrap_get_path_pic_hull (PyObject *self, PyObject *args)
{
  gint ship_nr;
  gchar *path = NULL;

  PyArg_ParseTuple (args, "i", &ship_nr);
  path = g_strdup_printf ("%s/vpl%d.jpg",
			  DATADIR"/pixmaps/gwp/ships", ship_nr);
  return PyString_FromString (path);
}

#line 8982 "src/gwp-py-mappings.c"


#line 191 "src/gwp-py-mappings.override"
static PyObject *
_wrap_get_truehull (PyObject *self)
{
  int i, j;
  PyObject *th = PyDict_New ();
  PyObject *dict;

  for (i=1; i <= 11; i++) {
    dict = PyDict_New ();
    for (j=1; j <= 20; j++) {
      PyDict_SetItem (dict, 
		      PyInt_FromLong(j), 
		      PyInt_FromLong(truehull[i-1][j-1]));
    }
    PyDict_SetItem (th, 
		    PyInt_FromLong(i), 
		    dict);
    Py_INCREF(dict);
  }
  Py_INCREF(th);
  return th;
}
#line 9008 "src/gwp-py-mappings.c"


#line 215 "src/gwp-py-mappings.override"
static PyObject *
_wrap_get_race_name (PyObject *self, PyObject *args)
{
  gint race;
  PyArg_ParseTuple (args, "i", &race);
  return PyString_FromString (race_get_name(race));
}
#line 9019 "src/gwp-py-mappings.c"


#line 83 "src/gwp-py-mappings.override"
static PyObject *
_wrap_get_system_plugins_dir (PyObject *self)
{
  return PyString_FromString (GWP_SCRIPTS_DIR"/plugins/");
}
#line 9028 "src/gwp-py-mappings.c"


PyMethodDef gwp_functions[] = {
    { "gwp_planet_get_ground_percent", (PyCFunction)_wrap_gwp_planet_get_ground_percent, METH_VARARGS|METH_KEYWORDS },
    { "ship_get_by_id", (PyCFunction)_wrap_ship_get_by_id, METH_VARARGS|METH_KEYWORDS },
    { "planet_get_by_id", (PyCFunction)_wrap_planet_get_by_id, METH_VARARGS|METH_KEYWORDS },
    { "get_game_state", (PyCFunction)_wrap_get_game_state, METH_NOARGS },
    { "ship_get_list", (PyCFunction)_wrap_ship_get_list, METH_NOARGS },
    { "planet_get_list", (PyCFunction)_wrap_planet_get_list, METH_NOARGS },
    { "hullspec_get_list", (PyCFunction)_wrap_hullspec_get_list, METH_NOARGS },
    { "engspec_get_list", (PyCFunction)_wrap_engspec_get_list, METH_NOARGS },
    { "beamspec_get_list", (PyCFunction)_wrap_beamspec_get_list, METH_NOARGS },
    { "torpspec_get_list", (PyCFunction)_wrap_torpspec_get_list, METH_NOARGS },
    { "set_plugin_mgr", (PyCFunction)_wrap_set_plugin_mgr, METH_VARARGS },
    { "get_plugin_mgr", (PyCFunction)_wrap_get_plugin_mgr, METH_NOARGS },
    { "get_path_pic_hull", (PyCFunction)_wrap_get_path_pic_hull, METH_VARARGS },
    { "get_truehull", (PyCFunction)_wrap_get_truehull, METH_NOARGS },
    { "get_race_name", (PyCFunction)_wrap_get_race_name, METH_VARARGS },
    { "get_system_plugins_dir", (PyCFunction)_wrap_get_system_plugins_dir, METH_NOARGS },
    { NULL, NULL, 0 }
};

/* initialise stuff extension classes */
void
gwp_register_classes(PyObject *d)
{
    PyObject *module;

    if ((module = PyImport_ImportModule("gobject")) != NULL) {
        PyObject *moddict = PyModule_GetDict(module);

        _PyGObject_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "GObject");
        if (_PyGObject_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name GObject from gobject");
            return;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gobject");
        return;
    }


#line 9073 "src/gwp-py-mappings.c"
    pygobject_register_class(d, "GwpBeamSpec", GWP_TYPE_BEAM_SPEC, &PyGwpBeamSpec_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "GwpEngSpec", GWP_TYPE_ENG_SPEC, &PyGwpEngSpec_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "GwpGameState", GWP_TYPE_GAME_STATE, &PyGwpGameState_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "GwpHullSpec", GWP_TYPE_HULL_SPEC, &PyGwpHullSpec_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "GwpObject", GWP_TYPE_OBJECT, &PyGwpObject_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "GwpMinefield", GWP_TYPE_MINEFIELD, &PyGwpMinefield_Type, Py_BuildValue("(O)", &PyGwpObject_Type));
    pygobject_register_class(d, "GwpMarker", GWP_TYPE_MARKER, &PyGwpMarker_Type, Py_BuildValue("(O)", &PyGwpObject_Type));
    pygobject_register_class(d, "GwpLocation", GWP_TYPE_LOCATION, &PyGwpLocation_Type, Py_BuildValue("(O)", &PyGwpObject_Type));
    pygobject_register_class(d, "GwpFlyingObject", GWP_TYPE_FLYING_OBJECT, &PyGwpFlyingObject_Type, Py_BuildValue("(O)", &PyGwpObject_Type));
    pygobject_register_class(d, "GwpIonStorm", GWP_TYPE_ION_STORM, &PyGwpIonStorm_Type, Py_BuildValue("(O)", &PyGwpFlyingObject_Type));
    pygobject_register_class(d, "GwpPlanet", GWP_TYPE_PLANET, &PyGwpPlanet_Type, Py_BuildValue("(O)", &PyGwpObject_Type));
    pygobject_register_class(d, "GwpRace", GWP_TYPE_RACE, &PyGwpRace_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "GwpShip", GWP_TYPE_SHIP, &PyGwpShip_Type, Py_BuildValue("(O)", &PyGwpFlyingObject_Type));
    pygobject_register_class(d, "GwpStarbase", GWP_TYPE_STARBASE, &PyGwpStarbase_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "GwpStarchart", GWP_TYPE_STARCHART, &PyGwpStarchart_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "GwpTorpSpec", GWP_TYPE_TORP_SPEC, &PyGwpTorpSpec_Type, Py_BuildValue("(O)", &PyGObject_Type));
}
