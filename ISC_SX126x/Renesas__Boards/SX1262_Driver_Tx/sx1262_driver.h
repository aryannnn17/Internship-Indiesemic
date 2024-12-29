/**
 * @file      sx126x_hal.h
 *
 * @brief     Hardware Abstraction Layer for SX126x
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2021. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SX126X_HAL_H
#define SX126X_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>
#include <stdbool.h>

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/**
 * @brief Write this to SPI bus while reading data, or as a dummy/placeholder
 */
#define SX126X_NOP ( 0x00 )

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

typedef enum sx126x_hal_status_e
{
    SX126X_HAL_STATUS_OK    = 0,
    SX126X_HAL_STATUS_ERROR = 3,
} sx126x_hal_status_t;
typedef enum sx126x_sleep_cfgs_e
{
    SX126X_SLEEP_CFG_COLD_START = ( 0 << 2 ),
    SX126X_SLEEP_CFG_WARM_START = ( 1 << 2 ),
} sx126x_sleep_cfgs_t;
typedef enum sx126x_standby_cfgs_e
{
    SX126X_STANDBY_CFG_RC   = 0x00,
    SX126X_STANDBY_CFG_XOSC = 0x01,
} sx126x_standby_cfgs_t;

typedef uint8_t sx126x_standby_cfg_t;

sx126x_hal_status_t sx126x_set_sleep( const void* context, const sx126x_sleep_cfgs_t cfg );
sx126x_hal_status_t sx126x_set_standby( const void* context, const sx126x_standby_cfg_t cfg );
sx126x_hal_status_t sx126x_set_fs( const void* context );

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */


#ifdef __cplusplus
}
#endif

#endif  // SX126X_HAL_H

/* --- EOF ------------------------------------------------------------------ */
