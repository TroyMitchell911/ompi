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

#ifndef MCA_BTL_UCIESM_TYPES_H
#define MCA_BTL_UCIESM_TYPES_H

#include "opal_config.h"
#include "opal/class/opal_free_list.h"
#include "opal/mca/btl/btl.h"
#include "opal/mca/smsc/smsc.h"
/**
 * Shared Memory (SM) BTL module.
 */
struct mca_btl_uciesm_component_t {
    mca_btl_base_component_3_0_0_t super; /**< base BTL component */
	bool is_a;
};
typedef struct mca_btl_uciesm_component_t mca_btl_uciesm_component_t;

#endif
