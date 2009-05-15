#ifndef CSC_AP_LINK_H
#define CSC_AP_LINK_H

#include "std.h"
#include "string.h"

#define CSC_SERVO_CMD_ID    0
#define CSC_MOTOR_CMD_ID    1
#define CSC_MOTOR_STATUS_ID 2
#define CSC_BOARD_STATUS_ID 3

#include "csc_can.h"

/* Received from the autopilot */
struct CscServoCmd {
  uint16_t servo_1;
  uint16_t servo_2;
  uint16_t servo_3;
  uint16_t servo_4;
} __attribute__((packed));

/* Send and Received between autopilot and csc */
struct CscMotorMsg {
  uint8_t  cmd_id;
  uint16_t arg1;
  uint16_t arg2;
} __attribute__((packed));

struct CscStatusMsg {
  uint32_t loop_count;
  uint32_t msg_count;
} __attribute__((packed));


extern struct CscServoCmd    csc_servo_cmd;
extern struct CscMotorMsg    csc_motor_msg;

extern int32_t csc_ap_link_error_cnt;

extern void csc_ap_link_init(void);
void csc_ap_send_msg(uint8_t msg_id, const uint8_t *buf, uint8_t len);
void csc_ap_link_send_status(uint32_t loops, uint32_t msgs);

#include "csc_can.h"

#define CscApLinkEvent(_on_servo_msg, _on_motor_msg) {		\
    Can1Event(CscApLinkOnCanMsg(_on_servo_msg, _on_motor_msg));	\
  }

#define CscApLinkOnCanMsg(_on_servo_msg, _on_motor_msg) {		\
    uint32_t msg_id = MSGID_OF_CANMSG_ID(can1_rx_msg.id);		\
    switch (msg_id) {							\
    case CSC_SERVO_CMD_ID:						\
      if (CAN_MSG_LENGH_OF_FRAME(can1_rx_msg.frame) != sizeof(csc_servo_cmd)) { \
	LED_ON(ERROR_LED);							\
	csc_ap_link_error_cnt++;					\
      }									\
      else {								\
	memcpy(&csc_servo_cmd, &can1_rx_msg.dat_a, sizeof(csc_servo_cmd));\
	_on_servo_msg();						\
      }									\
      break;								\
    case CSC_MOTOR_CMD_ID:						\
      if (CAN_MSG_LENGH_OF_FRAME(can1_rx_msg.frame) != sizeof(csc_motor_msg)) { \
	LED_ON(ERROR_LED);							\
	csc_ap_link_error_cnt++;					\
      }									\
      else {								\
	memcpy(&csc_motor_msg, &can1_rx_msg.dat_a, sizeof(csc_motor_msg));\
	_on_motor_msg();						\
      }									\
      break;								\
    }									\
  }


#endif /* CSC_AP_LINK_H */
