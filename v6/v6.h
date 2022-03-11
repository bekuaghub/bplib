/*
 * NASA Docket No. GSC-18,587-1 and identified as “The Bundle Protocol Core Flight
 * System Application (BP) v6.5”
 *
 * Copyright © 2020 United States Government as represented by the Administrator of
 * the National Aeronautics and Space Administration. All Rights Reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef V6_H
#define V6_H

/******************************************************************************
 INCLUDES
 ******************************************************************************/

#include "bundle_types.h"
#include "rb_tree.h"

/******************************************************************************
 DEFINES
 ******************************************************************************/

#define BP_PRI_VERSION 0x06

/* Block Processing Control Flags */
#define BP_BLK_REPALL_MASK        0x000001 /* block must be replicated in every fragment */
#define BP_BLK_NOTIFYNOPROC_MASK  0x000002 /* transmit status report if block cannot be processed */
#define BP_BLK_DELETENOPROC_MASK  0x000004 /* delete bundle if block cannot be processed */
#define BP_BLK_LASTBLOCK_MASK     0x000008 /* last block in bundle */
#define BP_BLK_DROPNOPROC_MASK    0x000010 /* drop block if block cannot be processed */
#define BP_BLK_FORWARDNOPROC_MASK 0x000020 /* block was forwarded without being processed */
#define BP_BLK_EIDREF_MASK        0x000040 /* block contains an EID reference field */

/* Block Type Definitions */
#define BP_PAY_BLK_TYPE  0x1
#define BP_CTEB_BLK_TYPE 0xA
#define BP_BIB_BLK_TYPE  0x3

/* BIB Definitions */
#define BP_BIB_INTEGRITY_SIGNATURE 5

/* Bundle Creation Time Handling */
#define BP_TTL_CREATION_TIME     0 /* time-to-live extension block may be used */
#define BP_UNKNOWN_CREATION_TIME 1 /* unreliable time source */
#define BP_BEST_EFFORT_LIFETIME \
    1576800000 /* 50 years; ground systems using 'int' type for time have maximum of 68 years */

/* Record Type Definitions */
#define BP_STAT_REC_TYPE 0x10 /* Status Report */
#define BP_CS_REC_TYPE   0x20 /* Custody Signal */
#define BP_ACS_REC_TYPE  0x40 /* Aggregate Custody Signal */

/* Aggregate Custody Signal Definitions */
#define BP_ACS_REC_TYPE_INDEX   0
#define BP_ACS_REC_STATUS_INDEX 1
#define BP_ACS_ACK_MASK         0x80 /* if set, then custody successfully transferred */

/* Processing Control Flags */
#define BP_PCF_FRAGMENT_MASK  0x000001 /* bundle is a fragement */
#define BP_PCF_ADMIN_MASK     0x000002 /* bundle is an administrative record */
#define BP_PCF_NOFRAG_MASK    0x000004 /* bundle must not be fragmented */
#define BP_PCF_CSTRQST_MASK   0x000008 /* custody transfer is requested */
#define BP_PCF_SINGLETON_MASK 0x000010 /* destination endpoint is a singleton */
#define BP_PCF_ACKRQST_MASK   0x000020 /* acknowledgement is requested from application */
#define BP_PCF_COS_MASK       0x000180 /* class of service */
#define BP_PCF_COS_SHIFT      7
#define BP_PCF_RPTRCV_MASK    0x004000 /* report reception */
#define BP_PCF_RPTACT_MASK    0x008000 /* report acceptance */
#define BP_PCF_RPTFRW_MASK    0x010000 /* report forwarding */
#define BP_PCF_RPTDLV_MASK    0x020000 /* report delivery */
#define BP_PCF_RPTDLT_MASK    0x040000 /* report deletion */

/******************************************************************************
 EXPORTED FUNCTIONS
 ******************************************************************************/

int v6_initialize(void);
int v6_create(bp_bundle_t *bundle, bp_route_t route, bp_attr_t attributes);
int v6_destroy(bp_bundle_t *bundle);
int v6_populate_bundle(bp_bundle_t *bundle, uint32_t *flags);
int v6_send_bundle(bp_bundle_t *bundle, const uint8_t *buffer, int size, bp_create_func_t create, void *parm,
                   int timeout, uint32_t *flags);
int v6_receive_bundle(bp_bundle_t *bundle, const uint8_t *buffer, int size, bp_payload_t *payload, uint32_t *flags);
int v6_update_bundle(bp_bundle_data_t *data, bp_val_t cid, uint32_t *flags);
int v6_populate_acknowledgment(uint8_t *rec, int size, int max_fills, rb_tree_t *tree, uint32_t *flags);
int v6_receive_acknowledgment(const uint8_t *rec, int size, int *num_acks, bp_delete_func_t remove, void *parm,
                              uint32_t *flags);
int v6_is_expired(bp_bundle_t *bundle, unsigned long sysnow, unsigned long exprtime, bool unrelt);
int v6_routeinfo(const void *bundle, int size, bp_route_t *route);
int v6_display(const void *bundle, int size, uint32_t *flags);

#endif /* V6_H */
