#! /usr/bin/env bash

export CPATH="$(realpath ../include):$CPATH"
export LIBRARY_PATH="$(realpath ../lib):$LIBRARY_PATH"
export LD_LIBRARY_PATH="$(realpath ../lib):$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="$(realpath ../lib):$DYLD_LIBRARY_PATH"

export LIBDXP_SANDBOX_MKENV=1
