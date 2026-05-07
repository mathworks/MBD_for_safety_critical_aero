/*
 * File: ModeLogic_types.h
 *
 * Code generated for Simulink model 'ModeLogic'.
 *
 * Model version                  : 9.0
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Wed Oct 16 13:47:43 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Custom Processor->Custom Processor
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef ModeLogic_types_h_
#define ModeLogic_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_GCSCommands_
#define DEFINED_TYPEDEF_FOR_GCSCommands_

typedef struct {
  boolean_T EMERGENCY_OFF;
  boolean_T WIFIconnected;
  boolean_T BTconnected;
  boolean_T CalibrateCmd;
  uint8_T GCS_MissionMode;
  real32_T GCS_HeadingCmd;
} GCSCommands;

#endif

#ifndef DEFINED_TYPEDEF_FOR_State_
#define DEFINED_TYPEDEF_FOR_State_

typedef struct {
  boolean_T CalibrationDone;
  real32_T Pos_BODY[3];
  real32_T Pos_FSD[3];
  real32_T V_BODY[3];
  real32_T V_FSD[3];
  real32_T Acc_BODY[3];
  real32_T Acc_FSD[3];
  real32_T AngRate[3];
  real32_T Angles[3];
  real32_T Heading;
  real32_T Altitude;
  real32_T BatteryVolts;
} State;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Logic_
#define DEFINED_TYPEDEF_FOR_Logic_

typedef struct {
  boolean_T CalibrateSensors;
  uint8_T Mode;
} Logic;

#endif
#endif                                 /* ModeLogic_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
