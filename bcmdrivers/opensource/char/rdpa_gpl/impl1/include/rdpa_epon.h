/*
* <:copyright-BRCM:2013:DUAL/GPL:standard
* 
*    Copyright (c) 2013 Broadcom Corporation
*    All Rights Reserved
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License, version 2, as published by
* the Free Software Foundation (the "GPL").
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* 
* A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
* writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
* 
* :> 
*/

#ifndef _RDPA_EPON_H
#define _RDPA_EPON_H

#include <bdmf_data_types.h>

/** \defgroup eponmanagement EPON Management
 * Objects in this group control EPON-related configuration
 */

/**
 * \defgroup epon EPON MAC Management
 * \ingroup eponmanagement
 * Epon object represent the EPON MAC. By setting its attributes EPON MAC
 * functionality can be controlled. 
 * @{
 */

/**
 * Each unicast link has to be associated with a mcast link. In the BCM OAM
 * mode, each unicast link may have its own multicast link. In other mode, all
 * unicast link will share the same multicast link. This function is called by
 * OAM stack for each unicast link in the system. The EPON MAC gets configured
 * only when "enable" will set to "yes". 
 */
typedef struct
{
    uint32_t llid;
    uint32_t flow_idx;
    bdmf_boolean enable;
} rdpa_epon_mcast_link_t;

/**
 * Enable EPON MAC FEC in ds and/or us
 */
typedef struct
{
    bdmf_boolean ds;
    bdmf_boolean us;
} rdpa_epon_fec_enable_t;

/**
  * Tx Laser mode
  */
typedef enum
{
    rdpa_epon_laser_tx_off,
    rdpa_epon_laser_tx_burst,
    rdpa_epon_laser_tx_continuous
} rdpa_epon_laser_tx_mode;

/** Epon link MPCP regitration state */
typedef enum
{
    rdpa_epon_link_unregistered,
    rdpa_epon_link_registering,
    rdpa_epon_link_awaiting_register,
    rdpa_epon_link_in_service,
    rdpa_epon_link_awaiting_gate
} rdpa_epon_link_mpcp_state;

/** Epon holdover flags */
typedef enum
{
    rdpa_epon_holdover_noflags = 0,
    rdpa_epon_holdover_rerange = 1
} rdpa_epon_holdover_flags;

/**
 * EPON Holdover
 */
typedef struct 
{
    uint16_t time;
    rdpa_epon_holdover_flags flags;
} rdpa_epon_holdover_t;

/** EPON Speed */
typedef enum
{
    rdpa_epon_speed_1g1g,       /**< epon normal speed (1/1)*/
    rdpa_epon_speed_2g1g,       /**< epon turbo speed  (2/1)*/
}rdpa_epon_speed_mode;


typedef struct
{
    uint16_t pon;
    uint16_t gate;
} rdpa_epon_los_t;

/**
 * a burst cap for each transmission priority
 */
typedef struct
{
    uint16_t priority_0;
    uint16_t priority_1;
    uint16_t priority_2;
    uint16_t priority_3;
    uint16_t priority_4;
    uint16_t priority_5;
    uint16_t priority_6;
    uint16_t priority_7;
} rdpa_epon_burst_cap_per_priority_t;


/** @} end of epon Doxygen group */

/** @} end of eponmanagement Doxygen group */


#endif //_RDPA_EPON_H

