#!/bin/env node
/**
 * Created by trichner on 6/11/15.
 */

var ffi = require('ffi')
var ref = require('ref')
var consts = require('./dogma-const')

var typeId = ref.types.uint32;
var attributeId = ref.types.uint16;
var effectId = ref.types.int32;

var dogmaCtx = ref.types.void
var ctxPtr = ref.refType(dogmaCtx)
var ctxPtrPtr = ref.refType(ctxPtr)
var doublePtr = ref.refType(ref.types.double);

var lib = ffi.Library('libdogma.so.0.1.0', {
    'dogma_init':               ['int', []],
    'dogma_init_context':       ['int', [ctxPtrPtr]],
    'dogma_set_ship':           ['int', [ctxPtr, typeId]],
    'dogma_get_ship_attribute': ['int', [ctxPtr, attributeId, doublePtr]],
    'dogma_free_context' :      ['int', [ctxPtr]]
})

/* -------- Return codes -------- */
var ctxref = ref.alloc(ctxPtrPtr)
var ret;
ret = lib.dogma_init()
ret = lib.dogma_init_context(ctxref)

var ctxHandle = ctxref.deref();
ret = lib.dogma_set_ship(ctxHandle, consts.TYPE.Vindicator)

var value = ref.alloc('double')
ret = lib.dogma_get_ship_attribute(ctxHandle, consts.ATT.HiSlots, value)

console.log('A Vindicator has ' + value.deref() + ' high slots.')

ret = lib.dogma_free_context(ctxHandle)

/* -------- Data types -------- */
/*
 typedef Pvoid_t dogma_array_t;
 typedef Word_t dogma_key_t;
 */
