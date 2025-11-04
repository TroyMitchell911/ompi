#
# Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
#                         University Research and Technology
#                         Corporation.  All rights reserved.
# Copyright (c) 2004-2009 The University of Tennessee and The University
#                         of Tennessee Research Foundation.  All rights
#                         reserved.
# Copyright (c) 2004-2009 High Performance Computing Center Stuttgart,
#                         University of Stuttgart.  All rights reserved.
# Copyright (c) 2004-2005 The Regents of the University of California.
#                         All rights reserved.
# Copyright (c) 2009-2022 Cisco Systems, Inc.  All rights reserved.
# Copyright (c) 2011-2014 Los Alamos National Security, LLC. All rights
#                         reserved.
# Copyright (c) 2017      IBM Corporation.  All rights reserved.
# Copyright (c) 2020-2021 Google, LLC. All rights reserved.
# Copyright (c) 2022      Amazon.com, Inc. or its affiliates.  All Rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#

libmca_btl_uciesm_la_sources = \
    btl_uciesm_module.c \
    btl_uciesm.h \
    btl_uciesm_component.c \
		btl_uciesm_frag.c \
		btl_uciesm_frag.h


# Make the output library in this directory, and name it either
# mca_<type>_<name>.la (for DSO builds) or libmca_<type>_<name>.la
# (for static builds).

if MCA_BUILD_opal_btl_uciesm_DSO
component_noinst =
component_install = mca_btl_uciesm.la
else
component_noinst = libmca_btl_uciesm.la
component_install =
endif

mcacomponentdir = $(opallibdir)
mcacomponent_LTLIBRARIES = $(component_install)
mca_btl_uciesm_la_SOURCES = $(libmca_btl_uciesm_la_sources)
mca_btl_uciesm_la_LDFLAGS = -module -avoid-version
mca_btl_uciesm_la_LIBADD = $(top_builddir)/opal/lib@OPAL_LIB_NAME@.la

noinst_LTLIBRARIES = $(component_noinst)
libmca_btl_uciesm_la_SOURCES = $(libmca_btl_uciesm_la_sources)
libmca_btl_uciesm_la_LIBADD =
libmca_btl_uciesm_la_LDFLAGS = -module -avoid-version
