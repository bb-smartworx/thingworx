// **************************************************************************
//
// Functions for generating HTML code
//
// **************************************************************************

#ifndef _HTML_H_
#define _HTML_H_

// item of select element
typedef struct {
  const char            *text;
  const char            *value;
} option_str_t;

// item of select element
typedef struct {
  const char            *text;
  unsigned int          value;
} option_int_t;

// item of main menu
typedef struct {
  const char            *label;
  const char            *url;
} menu_item_t;  

// send HTML code of beginning of page
extern void html_page_begin(const char *title);

// send HTML code of end of page
extern void html_page_end(void);

// send HTML code of info box
extern void html_info_box(int ok, const char *title, const char *text, const char *url, const char *button);

// send HTML code of info box
extern void html_config_info_box(int ok, int input_ok, const char *url);

// send HTML code of begining of form
extern void html_form_begin(const char *heading, const char *title, const char *action, int multipart, const char *javascript, const menu_item_t *menu);

// send HTML code of end of form
extern void html_form_end(const char *javascript);

// send HTML code of horizontal line in form
extern void html_form_break(void);

// define structure of table
extern void html_table(unsigned int cols, unsigned int align);

// define ID for next cell in table
extern void html_id(const char *name);

// define style for next cell in table
extern void html_style(const char *style);

// send HTML code of simple text
extern void html_text(const char *text);

// send HTML code of link
extern void html_link(const char *url, const char *text);

// send HTML code of input box (string)
extern void html_input_str(const char *name, const char *value);

// send HTML code of input box (readonly string)
extern void html_input_str_ro(const char *name, const char *value);

// send HTML code of input box (integer)
extern void html_input_int(const char *name, unsigned int value, int show_zero, const char *unit);

// send HTML code of input box (IP address)
extern void html_input_ip(const char *name, unsigned int value);

// send HTML code of input box (password)
extern void html_input_pwd(const char *name);

// send HTML code of input box (file)
extern void html_input_file(const char *name);

// send HTML code of select box (string)
extern void html_select_str(const char *name, const char *value, const option_str_t *option_ptr);

// send HTML code of select box (integer)
extern void html_select_int(const char *name, unsigned int value, const option_int_t *option_ptr);

// send HTML code of check box
extern void html_check_box(const char *name, int checked);

// send HTML code of text area
extern void html_area_text(const char *name, const char *value, unsigned int cols, unsigned int rows);

// send HTML code of text area
extern void html_area_file(const char *name, const char *filename, unsigned int cols, unsigned int rows);

// send HTML code of submit button
extern void html_submit(const char *name, const char *value);

// send HTML code of header of preformatted block
extern void html_pre_head(const char *text);

// send HTML code of preformatted block (text)
extern void html_pre_text(const char *text);

// send HTML code of preformatted block (file)
extern void html_pre_file(const char *filename, const char *error);

// send HTML code of preformatted block (program output)
extern void html_pre_proc(const char *program, int no_lf);

// send HTML code of page with system log
extern void html_slog(const char *title, const menu_item_t *menu);

#endif

