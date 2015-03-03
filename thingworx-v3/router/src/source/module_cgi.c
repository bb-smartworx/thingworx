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

#define _GNU_SOURCE

#include <stdio.h>          // snprintf, NULL
#include <string.h>         // basename, strcmp

#include "cgi.h"            // cgi_...
#include "html.h"           // html_...
#include "run.h"            // run

#include "module.h"
#include "module_cfg.h"

// **************************************************************************

// JavaScript stranky
const char *JAVASCRIPT_BEGIN =
  "function CheckForm() {\n"
  "  if (!IsValidIP(document.f.gateway, !document.f.enabled.checked)) {\n"
  "  return Error(\"Missing or invalid Server address.\", document.f.addr);\n"
  "  }\n"
  "  if (IsEmpty(document.f.name) && document.f.enabled.checked) {\n"
  "  return Error(\"Missing Thing Name.\", document.f.name);\n"
  "  }\n"
  "  if (IsEmpty(document.f.key) && document.f.enabled.checked) {\n"
  "  return Error(\"Missing Application Key.\", document.f.key);\n"
  "  }\n"
  "  return true;\n"
  "}\n";

// JavaScript stranky
const char *JAVASCRIPT_END =
  "document.f.onsubmit = CheckForm;\n"
  "document.f.enabled.focus();\n";

// **************************************************************************
// hlavni funkce CGI skriptu index.cgi
static void main_index(void)
{
  module_cfg_t          cfg;

  module_cfg_load(&cfg);

  html_page_begin(MODULE_TITLE);

  html_form_begin(MODULE_TITLE, MODULE_TITLE " Configuration", "set.cgi", 0, JAVASCRIPT_BEGIN, NULL);

  html_table(2, 0);

  html_check_box("enabled", cfg.enabled);
  html_text("Enable Thingworx Client");

  html_form_break();

  html_table(2, 0);

  html_text("Server Address");
  html_input_str("addr", cfg.addr);

  html_text("Thing Name");
  html_input_str("name", cfg.name);

  html_text("Application key");
  html_input_str("key", cfg.key);

  html_form_break();

  html_table(1, 0);

  html_submit("button", "Apply");

  html_form_end(JAVASCRIPT_END);

  html_page_end();
}

// **************************************************************************
// hlavni funkce CGI skriptu set.cgi
static void main_set(void)
{
  module_cfg_t          cfg;
  int                   ok, input_ok;

  cgi_begin();

  html_page_begin(MODULE_TITLE);

  ok       = 0;
  input_ok = cgi_query_ok()                        &&
             cgi_get_bool("enabled", &cfg.enabled) &&
             cgi_get_str ("addr"   , &cfg.addr, 1) &&
             cgi_get_str ("name"   , &cfg.name, 1) &&
             cgi_get_str ("key"    , &cfg.key,  1);
  if (input_ok) {
    if (module_cfg_save(&cfg)) {
      ok = !run(MODULE_INIT, "restart", NULL, 1);
    }
  }

  html_config_info_box(ok, input_ok, "index.cgi");

  html_page_end();

  cgi_end();
}

// **************************************************************************
// hlavni funkce
int main(int argc, char *argv[])
{
  const char            *name;

  if (argc > 0) {
    name = basename(argv[0]);
    if (!strcmp(name, "index.cgi")) {
      main_index();
    } else if (!strcmp(name, "set.cgi")) {
      main_set();
    }
  }

  return 0;
}