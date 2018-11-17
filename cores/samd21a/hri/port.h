#ifndef ECLAY_PROCESSOR_PORT_H
#define ECLAY_PROCESSOR_PORT_H

#include "hri/sam.h"

#include <stdbool.h>
#include <stdint.h>

#include "utils/utils_repeat_macro.h"


#ifdef __cplusplus
extern "C" {
#endif

// Values of processor_port_group_t must match PORT group values so that
// they can be used directly in accessing PORT registers.
// e.g. Port pins PAxx are accessed through PORT->Group[0]
typedef enum
{
  PROCESSOR_PORT_GROUP_PA = 0,
  PROCESSOR_PORT_GROUP_PB = 1,
  NUM_PROCESSOR_PORT_GROUP,
  NOT_A_PROCESSOR_PORT_GROUP = NUM_PROCESSOR_PORT_GROUP
} processor_port_group_t;

typedef uint8_t processor_port_pin_t;
#define NUM_PROCESSOR_PORT_PINS           32

typedef bool processor_port_direction_t;
#define PROCESSOR_PORT_DIRECTION_INPUT    false
#define PROCESSOR_PORT_DIRECTION_OUTPUT   true

typedef bool processor_port_pinstate_t;
#define PROCESSOR_PORT_PINSTATE_LOW       false
#define PROCESSOR_PORT_PINSTATE_HIGH      true

typedef enum
{
  PROCESSOR_PORT_PULL_OFF = 0,
  PROCESSOR_PORT_PULL_UP,
  PROCESSOR_PORT_PULL_DOWN,
  NUM_PROCESSOR_PORT_PULL,
  PROCESSOR_PORT_PULL_INVALID = NUM_PROCESSOR_PORT_PULL
} processor_port_pull_t;

typedef enum
{
  PROCESSOR_PORT_STRENGTH_NORMAL = 0,
  PROCESSOR_PORT_STRENGTH_HIGH,
  NUM_PROCESSOR_PORT_STRENGTH,
  PROCESSOR_PORT_STRENGTH_INVALID = NUM_PROCESSOR_PORT_STRENGTH
} processor_port_strength_t;

typedef enum
{
  PROCESSOR_PORT_PINMUX_A = PORT_PMUX_PMUXE_A_Val,
  PROCESSOR_PORT_PINMUX_B = PORT_PMUX_PMUXE_B_Val,
  PROCESSOR_PORT_PINMUX_C = PORT_PMUX_PMUXE_C_Val,
  PROCESSOR_PORT_PINMUX_D = PORT_PMUX_PMUXE_D_Val,
  PROCESSOR_PORT_PINMUX_E = PORT_PMUX_PMUXE_E_Val,
  PROCESSOR_PORT_PINMUX_F = PORT_PMUX_PMUXE_F_Val,
  PROCESSOR_PORT_PINMUX_G = PORT_PMUX_PMUXE_G_Val,
  PROCESSOR_PORT_PINMUX_H = PORT_PMUX_PMUXE_H_Val,
  NUM_PROCESSOR_PORT_PINMUX,
  PROCESSOR_PORT_PINMUX_DISABLED = NUM_PROCESSOR_PORT_PINMUX,
  PROCESSOR_PORT_PINMUX_INVALID
} processor_port_pinmux_t;


void PROCESSOR_PORT_Initialize( void );


static inline void PROCESSOR_PORT_DirectionSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_direction_t  direction
  );

static inline processor_port_direction_t PROCESSOR_PORT_DirectionGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  );

static inline void PROCESSOR_PORT_OutputSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_pinstate_t   state
  );

static inline void PROCESSOR_PORT_OutputToggle(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  );

static inline processor_port_pinstate_t PROCESSOR_PORT_OutputGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  );

static inline processor_port_pinstate_t PROCESSOR_PORT_InputGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  );


static inline void PROCESSOR_PORT_InputEnableSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    bool                        enable
  );

static inline bool PROCESSOR_PORT_InputEnableGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  );


void PROCESSOR_PORT_PullSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_pull_t       pull
  );

processor_port_pull_t PROCESSOR_PORT_PullGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  );


void PROCESSOR_PORT_DriveStrengthSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_strength_t   strength
  );

processor_port_strength_t PROCESSOR_PORT_DriveStrengthGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  );


void PROCESSOR_PORT_PinMuxSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_pinmux_t     mux
  );

processor_port_pinmux_t PROCESSOR_PORT_PinMuxGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  );


#define INCLUDE_HRI_PORT_INLINE_H
#include "src/hri_port_inline.h"
#undef INCLUDE_HRI_PORT_INLINE_H


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_PROCESSOR_PORT_H
