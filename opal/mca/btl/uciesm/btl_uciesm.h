/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2025 Troy Mitchell <troy.mitchell@linux.spacemit.com>
 *
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */
/**
 * @file
 */
#ifndef MCA_BTL_UCIESM_H
#define MCA_BTL_UCIESM_H

#include <stdlib.h>
#ifdef HAVE_SYS_TYPES_H
#    include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */

#include "opal/mca/btl/base/base.h"
#include "opal/mca/btl/btl.h"

#include "opal/mca/btl/uciesm/btl_uciesm_type.h"

OPAL_DECLSPEC extern mca_btl_uciesm_component_t mca_btl_uciesm_component;
OPAL_DECLSPEC extern mca_btl_base_module_t mca_btl_uciesm;

BEGIN_C_DECLS

END_C_DECLS

#endif
