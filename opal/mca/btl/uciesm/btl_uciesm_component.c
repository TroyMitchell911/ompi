
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
#include "opal_config.h"

#include "opal/mca/btl/base/btl_base_error.h"
#include "opal/mca/threads/mutex.h"
#include "opal/util/bit_ops.h"
#include "opal/util/output.h"
#include "opal/util/printf.h"

#include "opal/mca/btl/uciesm/btl_uciesm.h"
#include "opal/mca/btl/uciesm/btl_uciesm_frag.h"
#include "opal/mca/smsc/smsc.h"

#ifdef HAVE_SYS_STAT_H
#    include <sys/stat.h>
#endif

#include <fcntl.h>
#include <sys/mman.h>

#ifdef HAVE_SYS_PRCTL_H
#    include <sys/prctl.h>
#endif

/* NTH: OS X does not define MAP_ANONYMOUS */
#if !defined(MAP_ANONYMOUS)
#    define MAP_ANONYMOUS MAP_ANON
#endif

static int mca_btl_uciesm_component_progress(void);
static int mca_btl_uciesm_component_open(void);
static int mca_btl_uciesm_component_close(void);
static int mca_btl_uciesm_component_register(void);
static mca_btl_base_module_t **
mca_btl_uciesm_component_init(int *num_btls, bool enable_progress_threads, bool enable_mpi_threads);

/*
 * Shared Memory (SM) component instance.
 */
mca_btl_uciesm_component_t mca_btl_uciesm_component = {
    .super =
        {
            /* First, the mca_base_component_t struct containing meta information
               about the component itself */
            .btl_version =
                {
                    MCA_BTL_DEFAULT_VERSION("uciesm"),
                    .mca_open_component = mca_btl_uciesm_component_open,
                    .mca_close_component = mca_btl_uciesm_component_close,
                    .mca_register_component_params = mca_btl_uciesm_component_register,
                },
            .btl_data =
                {/* The component is checkpoint ready */
                 .param_field = MCA_BASE_METADATA_PARAM_CHECKPOINT},

            .btl_init = mca_btl_uciesm_component_init,
            /*.btl_progress = mca_btl_uciesm_component_progress,*/
        } /* end super */
};
MCA_BASE_COMPONENT_INIT(opal, btl, uciesm)

static int mca_btl_uciesm_component_register(void)
{
    (void) mca_base_var_group_component_register(&mca_btl_uciesm_component.super.btl_version,
                                                 "Enhanced ucie shared memory byte transport later");

    mca_btl_uciesm.btl_exclusivity = MCA_BTL_EXCLUSIVITY_HIGH;

    mca_btl_uciesm.btl_eager_limit = 4 * 1024;
    mca_btl_uciesm.btl_rndv_eager_limit = 32 * 1024;
    mca_btl_uciesm.btl_max_send_size = 32 * 1024;
    mca_btl_uciesm.btl_min_rdma_pipeline_size = INT_MAX;

    mca_btl_uciesm.btl_rdma_pipeline_send_length = mca_btl_uciesm.btl_eager_limit;
    mca_btl_uciesm.btl_rdma_pipeline_frag_size = mca_btl_uciesm.btl_eager_limit;

    mca_btl_uciesm.btl_flags = MCA_BTL_FLAGS_SEND_INPLACE | MCA_BTL_FLAGS_SEND;

    mca_btl_uciesm.btl_bandwidth = 20000; /* Mbs */
    mca_btl_uciesm.btl_latency = 1; /* Microsecs */

    /* Call the BTL based to register its MCA params */
    mca_btl_base_param_register(&mca_btl_uciesm_component.super.btl_version, &mca_btl_uciesm);

    return OPAL_SUCCESS;
}

/*
 *  UCIE SM component initialization
 */
static mca_btl_base_module_t **
mca_btl_uciesm_component_init(int *num_btls, bool enable_progress_threads, bool enable_mpi_threads)
{
    mca_btl_base_module_t **btls = NULL;

	/* get pointer to the btls */
    btls = (mca_btl_base_module_t **) malloc(sizeof(mca_btl_base_module_t *));
    if (NULL == btls) {
        return NULL;
    }

    btls[0] = &mca_btl_uciesm;
    *num_btls = 1;

	opal_output_verbose(9999, opal_btl_base_framework.framework_output,   
						"My BTL debug message: test");

    return btls;
}

/*
 *  Called by MCA framework to open the component, registers
 *  component parameters.
 */

static int mca_btl_uciesm_component_open(void)
{
    /* initialize objects */

    return OPAL_SUCCESS;
}

/*
 * component cleanup - sanity checking of queue lengths
 */

static int mca_btl_uciesm_component_close(void)
{
    return OPAL_SUCCESS;
}
