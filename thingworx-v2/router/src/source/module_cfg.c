/* LICENSE AND DISCLAIMER
 * ----------------------
 * This material contains sample programming source code ("Sample Code").
 * B+B Smartworx grants you a nonexclusive license to compile, link, run,
 * display, reproduce, distribute and prepare derivative works of 
 * this Sample Code.  The Sample Code has not been thoroughly
 * tested under all conditions.  B+B Smartworx, therefore, does not guarantee
 * or imply its reliability, serviceability, or function. B+B Smartworx
 * provides no program services for the Sample Code.
 *
 * All Sample Code contained herein is provided to you "AS IS" without
 * any warranties of any kind. THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGMENT ARE EXPRESSLY
 * DISCLAIMED.  SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OF IMPLIED
 * WARRANTIES, SO THE ABOVE EXCLUSIONS MAY NOT APPLY TO YOU.  IN NO 
 * EVENT WILL IBM BE LIABLE TO ANY PARTY FOR ANY DIRECT, INDIRECT, 
 * SPECIAL OR OTHER CONSEQUENTIAL DAMAGES FOR ANY USE OF THE SAMPLE CODE
 * INCLUDING, WITHOUT LIMITATION, ANY LOST PROFITS, BUSINESS 
 * INTERRUPTION, LOSS OF PROGRAMS OR OTHER DATA ON YOUR INFORMATION
 * HANDLING SYSTEM OR OTHERWISE, EVEN IF WE ARE EXPRESSLY ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 *
 * COPYRIGHT
 * ---------
 * (C) Copyright B+B Smartworx. 2015
 * All rights reserved.
 * Licensed Material - Property of B+B Smartworx
*/

#include <stdio.h>          // snprintf, FILE

#include "cfg.h"            // cfg_...

#include "module.h"
#include "module_cfg.h"

// **************************************************************************
// precteni konfigurace modulu
void module_cfg_load(module_cfg_t *cfg_ptr)
{
  FILE                  *file_ptr;

  file_ptr          = cfg_open(MODULE_SETTINGS, "r");
  cfg_ptr->enabled  = cfg_get_int(file_ptr, MODULE_PREFIX "ENABLED" );
  cfg_ptr->addr     = cfg_get_str(file_ptr, MODULE_PREFIX "ADDR"    );
  cfg_ptr->name     = cfg_get_str(file_ptr, MODULE_PREFIX "NAME"    );
  cfg_ptr->key      = cfg_get_str(file_ptr, MODULE_PREFIX "KEY"     );
  cfg_ptr->device   = cfg_get_str(file_ptr, MODULE_PREFIX "DEVICE"  );
  cfg_ptr->baudrate = cfg_get_int(file_ptr, MODULE_PREFIX "BAUDRATE");
  cfg_ptr->databits = cfg_get_int(file_ptr, MODULE_PREFIX "DATABITS");
  cfg_ptr->parity   = cfg_get_str(file_ptr, MODULE_PREFIX "PARITY"  );
  cfg_ptr->stopbits = cfg_get_int(file_ptr, MODULE_PREFIX "STOPBITS");
  cfg_close(file_ptr);
}

// **************************************************************************
// ulozeni konfigurace modulu
int module_cfg_save(module_cfg_t *cfg_ptr)
{
  FILE                  *file_ptr;

  if ((file_ptr = cfg_open(MODULE_SETTINGS, "w"))) {
    cfg_put_bool(file_ptr, MODULE_PREFIX "ENABLED" , cfg_ptr->enabled);
    cfg_put_str (file_ptr, MODULE_PREFIX "ADDR"    , cfg_ptr->addr       );
    cfg_put_str (file_ptr, MODULE_PREFIX "NAME"    , cfg_ptr->name       );
    cfg_put_str (file_ptr, MODULE_PREFIX "KEY"     , cfg_ptr->key        );
    cfg_put_str (file_ptr, MODULE_PREFIX "DEVICE"  , cfg_ptr->device     );
    cfg_put_int (file_ptr, MODULE_PREFIX "BAUDRATE", cfg_ptr->baudrate, 1);
    cfg_put_int (file_ptr, MODULE_PREFIX "DATABITS", cfg_ptr->databits, 1);
    cfg_put_str (file_ptr, MODULE_PREFIX "PARITY"  , cfg_ptr->parity     );
    cfg_put_int (file_ptr, MODULE_PREFIX "STOPBITS", cfg_ptr->stopbits, 1);
    cfg_close(file_ptr);
    return 1;
  }

  return 0;
}


