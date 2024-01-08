/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : Atmega32_Drivers
// File          : ssd_interface.h
// Date          : 6 Aug 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/
#ifndef HAL_SSD_SSD_INTERFACE_H_
#define HAL_SSD_SSD_INTERFACE_H_

#include "../../COMMON/std_types.h"
#include "../../HAL/ssd/ssd_config.h"

EN_SSD_systemState_t SSD_int(ST_SSD_cfg_t const *ST_ptrSsdCfgInstamce);

EN_SSD_systemState_t
SSD_setNumberOnSsd(ST_SSD_cfg_t const *ST_ptrSsdCfgInstamce,
                   EN_SSD_numbers_t valueOfNumber);

EN_SSD_systemState_t SSD_enableDot(ST_SSD_cfg_t const *ST_ptrSsdCfgInstamce);
EN_SSD_systemState_t SSD_disableDot(ST_SSD_cfg_t const *ST_ptrSsdCfgInstamce);

EN_SSD_systemState_t
SSD_dualInit(ST_SSD_DualCfg_t const *ST_ptrSsdDualCfgInstance);
EN_SSD_systemState_t SSD_dualSetCurrentSegmentComPin(
    ST_SSD_DualCfg_t const *ST_ptrSsdDualCfgInstance);
EN_SSD_systemState_t
SSD_dualSwitchSegment(ST_SSD_DualCfg_t *ST_ptrSsdDualCfgInstance,
                      EN_SSD_index_t indexOfTheDisplay);
EN_SSD_systemState_t
SSD_dualSetNumberOnSsd(ST_SSD_DualCfg_t const *ST_ptrSsdDualCfgInstance,
                       EN_SSD_numbers_t valueOfNumber);

#endif /* HAL_SSD_SSD_INTERFACE_H_ */
