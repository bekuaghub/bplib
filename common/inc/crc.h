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

#ifndef CRC_H
#define CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 INCLUDES
 ******************************************************************************/

#include "bplib.h"

/******************************************************************************
 DEFINES
 ******************************************************************************/

/******************************************************************************
 TYPEDEFS
 ******************************************************************************/

/* Standard parameters for calculating a CRC. */
struct bplib_crc_parameters;
typedef const struct bplib_crc_parameters bplib_crc_parameters_t;

/*
 * CRC algorithms that are implemented in BPLIB
 * These definitions are always fixed/const
 */
extern bplib_crc_parameters_t BPLIB_CRC_NONE;
extern bplib_crc_parameters_t BPLIB_CRC16_X25;
extern bplib_crc_parameters_t BPLIB_CRC32_CASTAGNOLI;

/******************************************************************************
 PROTOTYPES
 ******************************************************************************/

void bplib_crc_init(void);

const char *bplib_crc_get_name(bplib_crc_parameters_t *params);
uint8_t     bplib_crc_get_width(bplib_crc_parameters_t *params);
bp_crcval_t bplib_crc_initial_value(bplib_crc_parameters_t *params);
bp_crcval_t bplib_crc_update(bplib_crc_parameters_t *params, bp_crcval_t crc, const void *data, size_t size);
bp_crcval_t bplib_crc_finalize(bplib_crc_parameters_t *params, bp_crcval_t crc);

bp_crcval_t bplib_crc_get(const void *data, const uint32_t length, bplib_crc_parameters_t *params);

#ifdef __cplusplus
}
#endif

#endif /* CRC_H */
