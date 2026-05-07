/*
 * File: ModeLogic.h
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

#ifndef ModeLogic_h_
#define ModeLogic_h_
#ifndef ModeLogic_COMMON_INCLUDES_
#define ModeLogic_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ModeLogic_COMMON_INCLUDES_ */

#include "ModeLogic_types.h"
#include <string.h>

/* Block signals (default storage) */
typedef struct {
  Logic Logic_l1kg;                    /* '<Root>/ModeLogic' (Output 1) */
} B_ModeLogic_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T count;                   /* '<Root>/ModeLogic' (Local data 'count') */
  uint8_T is_c2_ModeLogic;
                         /* '<Root>/ModeLogic' (Active substate of the chart) */
} DW_ModeLogic_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  GCSCommands GCSCmds;                 /* '<Root>/GCSCmds' */
  boolean_T IsBall;                    /* '<Root>/IsBall' */
  State State_femo;                    /* '<Root>/State' */
} ExtU_ModeLogic_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  Logic Logic_dzei;                    /* '<Root>/Logic' */
} ExtY_ModeLogic_T;

/* Block signals (default storage) */
extern B_ModeLogic_T ModeLogic_B;

/* Block states (default storage) */
extern DW_ModeLogic_T ModeLogic_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_ModeLogic_T ModeLogic_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_ModeLogic_T ModeLogic_Y;

/* External data declarations for dependent source files */
extern const Logic ModeLogic_rtZLogic; /* Logic ground */

/* Model entry point functions */
extern void ModeLogic_initialize(void);
extern void ModeLogic_step(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ModeLogic'
 * '<S1>'   : 'ModeLogic/ModeLogic'
 */

/*-
 * Requirements for '<Root>': ModeLogic

 *
 * Inherited requirements for '<Root>/ModeLogic':
 *  1. 3 Modes of Operation

 */
#endif                                 /* ModeLogic_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
