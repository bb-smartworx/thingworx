// **************************************************************************
//
// Function for work with GPIO
//
// **************************************************************************

#ifndef _GPIO_H_
#define _GPIO_H_

// types of expansion ports
#define GPIO_PORT_TYPE_EMPTY            0x00
#define GPIO_PORT_TYPE_RS232            0x02
#define GPIO_PORT_TYPE_RS485            0x03
#define GPIO_PORT_TYPE_MBUS             0x04
#define GPIO_PORT_TYPE_CNT              0x05
#define GPIO_PORT_TYPE_ETH              0x08
#define GPIO_PORT_TYPE_WMBUS            0x0A
#define GPIO_PORT_TYPE_RS422            0x0B
#define GPIO_PORT_TYPE_NONE             0x0F
#define GPIO_PORT_TYPE_WIFI             0x11

// types of modules
#define GPIO_MODULE_TYPE_EES3           0x00
#define GPIO_MODULE_TYPE_EU3            0x01
#define GPIO_MODULE_TYPE_MCXXXX_VWM10   0x02
#define GPIO_MODULE_TYPE_PHS8           0x03
#define GPIO_MODULE_TYPE_MCXXXX         0x04
#define GPIO_MODULE_TYPE_VWM10          0x05
#define GPIO_MODULE_TYPE_GOBI3K         0x06
#define GPIO_MODULE_TYPE_NONE           0x0F

// set state of LED USR
extern void gpio_set_led_usr(unsigned int state);

// set state of output OUT0
extern void gpio_set_out0(unsigned int state);

// get state of output OUT0
extern int gpio_get_out0(void);

// get state of input BIN0
extern int gpio_get_bin0(void);

// get type of expansion port
extern int gpio_get_port_type(int port);

// get information about overload on MBUS bus
extern int gpio_get_mbus_overload(int port);

// get type of module
extern int gpio_get_module_type(void);

// get internal temperature
extern int gpio_get_temperature(void);

// get supply voltage
extern int gpio_get_voltage(void);

#endif

