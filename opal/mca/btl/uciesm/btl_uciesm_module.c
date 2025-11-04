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

#include "opal/mca/btl/uciesm/btl_uciesm.h"
#include "opal/mca/smsc/smsc.h"

#include <string.h>


/**
 * PML->BTL notification of change in the process list.
 * PML->BTL Notification that a receive fragment has been matched.
 * Called for message that is send from process with the virtual
 * address of the shared memory segment being different than that of
 * the receiver.
 *
 * @param btl (IN)
 * @param proc (IN)
 * @param peer (OUT)
 * @return     OPAL_SUCCESS or error status on failure.
 *
 */

static int uciesm_add_procs(struct mca_btl_base_module_t *btl, size_t nprocs,
							struct opal_proc_t **procs, struct mca_btl_base_endpoint_t **peers,
							opal_bitmap_t *reachability)
{
    mca_btl_uciesm_component_t *component = (mca_btl_uciesm_component_t *)btl->btl_component;
    const opal_proc_t *my_proc;
    int rc = OPAL_SUCCESS;

    /* initializion */

    /* get pointer to my proc structure */
    if (NULL == (my_proc = opal_proc_local_get())) {
        return OPAL_ERR_OUT_OF_RESOURCE;
    }

	if (!component->is_a)
		component->is_a = true;

	/* TODO: switch it from sm to tcp-like */
    for (int32_t proc = 0; proc < (int32_t) nprocs; ++proc) {
        /* check to see if this proc can be reached via shmem (i.e.,
           if they're on my local host and in my job) */
        if (procs[proc]->proc_name.jobid != my_proc->proc_name.jobid
            || !OPAL_PROC_ON_LOCAL_NODE(procs[proc]->proc_flags)) {
            peers[proc] = NULL;
            continue;
        }

        if (my_proc != procs[proc] && NULL != reachability) {
            /* add this proc to shared memory accessibility list */
            rc = opal_bitmap_set_bit(reachability, proc);
            if (OPAL_SUCCESS != rc) {
                return rc;
            }
        }
    }

	return rc;
}

/* btl uciesm module */
mca_btl_base_module_t mca_btl_uciesm = {.btl_component = &mca_btl_uciesm_component.super,
										.btl_add_procs = uciesm_add_procs,
                                      	.btl_dump = mca_btl_base_dump};

