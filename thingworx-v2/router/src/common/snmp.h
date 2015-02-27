// **************************************************************************
//
// Functions from Net-SNMP library
//
// **************************************************************************

#ifndef _SNMP_H_
#define _SNMP_H_

#include <sys/types.h>

#define ASN_UNIVERSAL                   ((u_char)0x00)
#define ASN_APPLICATION                 ((u_char)0x40)
#define ASN_CONTEXT                     ((u_char)0x80)
#define ASN_PRIVATE                     ((u_char)0xC0)

#define ASN_PRIMITIVE                   ((u_char)0x00)
#define ASN_CONSTRUCTOR                 ((u_char)0x20)

#define ASN_BOOLEAN                     (ASN_UNIVERSAL | 0x01)
#define ASN_INTEGER                     (ASN_UNIVERSAL | 0x02)
#define ASN_BIT_STR                     (ASN_UNIVERSAL | 0x03)
#define ASN_OCTET_STR                   (ASN_UNIVERSAL | 0x04)
#define ASN_NULL                        (ASN_UNIVERSAL | 0x05)
#define ASN_OBJECT_ID                   (ASN_UNIVERSAL | 0x06)

#define ASN_IPADDRESS                   (ASN_APPLICATION | 0x00)
#define ASN_COUNTER                     (ASN_APPLICATION | 0x01)
#define ASN_GAUGE                       (ASN_APPLICATION | 0x02)
#define ASN_TIMETICKS                   (ASN_APPLICATION | 0x03)
#define ASN_OPAQUE                      (ASN_APPLICATION | 0x04)

#define MODE_GET                        (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x00)

#define MODE_SET_BEGIN                  -1
#define MODE_SET_RESERVE1               0
#define MODE_SET_RESERVE2               1
#define MODE_SET_ACTION                 2
#define MODE_SET_COMMIT                 3
#define MODE_SET_FREE                   4
#define MODE_SET_UNDO                   5

#define HANDLER_CAN_RONLY               0x01
#define HANDLER_CAN_RWRITE              0x03

#define SNMP_ERR_NOERROR                0
#define SNMP_ERR_TOOBIG                 1
#define SNMP_ERR_NOSUCHNAME             2
#define SNMP_ERR_BADVALUE               3
#define SNMP_ERR_READONLY               4
#define SNMP_ERR_GENERR                 5
#define SNMP_ERR_NOACCESS               6
#define SNMP_ERR_WRONGTYPE              7
#define SNMP_ERR_WRONGLENGTH            8
#define SNMP_ERR_WRONGENCODING          9
#define SNMP_ERR_WRONGVALUE             10
#define SNMP_ERR_NOCREATION             11
#define SNMP_ERR_INCONSISTENTVALUE      12
#define SNMP_ERR_RESOURCEUNAVAILABLE    13
#define SNMP_ERR_COMMITFAILED           14
#define SNMP_ERR_UNDOFAILED             15
#define SNMP_ERR_AUTHORIZATIONERROR     16
#define SNMP_ERR_NOTWRITABLE            17

#define MAX_OID_LEN                     128

#define OID_LENGTH(x)                   (sizeof(x)/sizeof(oid))

typedef u_long                          oid;

typedef union {
  int                                   value;
  long                                  *integer;
  u_char                                *string;
  oid                                   *objid;
  u_char                                *bitstring;
  struct counter64                      *counter64;
  float                                 *floatVal;
  double                                *doubleVal;
} netsnmp_vardata;

typedef struct variable_list {
  struct variable_list                  *next_variable;
  oid                                   *name;
  size_t                                name_length;
  u_char                                type;
  netsnmp_vardata                       val;
  size_t                                val_len;
  oid                                   name_loc[MAX_OID_LEN];
  u_char                                buf[40];
  void                                  *data;
  void                                  (*dataFreeHook)(void *);
  int                                   index;
} netsnmp_variable_list;

typedef struct netsnmp_data_list_s {
  struct netsnmp_data_list_s            *next;
  char                                  *name;
  void                                  *data;
  void                                  (*free_func)(void *);
} netsnmp_data_list;

typedef struct netsnmp_request_info_s {
  netsnmp_variable_list                 *requestvb;
  netsnmp_data_list                     *parent_data;
  struct netsnmp_agent_request_info_s   *agent_req_info;
  oid                                   *range_end;
  size_t                                range_end_len;
  int                                   delegated;
  int                                   processed;
  int                                   inclusive;
  int                                   status;
  int                                   index;
  int                                   repeat;
  int                                   orig_repeat;
  netsnmp_variable_list                 *requestvb_start;
  struct netsnmp_request_info_s         *next;
  struct netsnmp_request_info_s         *prev;
  struct netsnmp_subtree_s              *subtree;
} netsnmp_request_info;

typedef struct netsnmp_agent_request_info_s {
  int                                   mode;
  struct netsnmp_agent_session_s        *asp;
  netsnmp_data_list                     *agent_data;
} netsnmp_agent_request_info;

struct netsnmp_mib_handler_s;
struct netsnmp_handler_registration_s;

typedef int (Netsnmp_Node_Handler)(
  struct netsnmp_mib_handler_s          *handler,
  struct netsnmp_handler_registration_s *reginfo,
  struct netsnmp_agent_request_info_s   *reqinfo,
  struct netsnmp_request_info_s         *requests
);

typedef struct netsnmp_mib_handler_s {
  char                                  *handler_name;
  void                                  *myvoid;
  int                                   flags;
  Netsnmp_Node_Handler                  *access_method;
  void                                  *(*data_clone)(void *myvoid);
  void                                  (*data_free)(void *myvoid);
  struct netsnmp_mib_handler_s          *next;
  struct netsnmp_mib_handler_s          *prev;
} netsnmp_mib_handler;

typedef struct netsnmp_handler_registration_s {
  char                                  *handlerName;
  char                                  *contextName;
  oid                                   *rootoid;
  size_t                                rootoid_len;
  netsnmp_mib_handler                   *handler;
  int                                   modes;
  int                                   priority;
  int                                   range_subid;
  oid                                   range_ubound;
  int                                   timeout;
  int                                   global_cacheid;
  void                                  *my_reg_void;
} netsnmp_handler_registration;

extern int netsnmp_register_scalar_group(netsnmp_handler_registration *reginfo, oid first, oid last);

extern netsnmp_handler_registration *netsnmp_create_handler_registration(const char *name, Netsnmp_Node_Handler *handler_access_method, const oid *reg_oid, size_t reg_oid_len, int modes);

extern int snmp_set_var_typed_value(netsnmp_variable_list *var, u_char type, const void *value, size_t len);

extern int snmp_set_var_typed_integer(netsnmp_variable_list *var, u_char type, long val);

#endif

