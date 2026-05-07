/*
 * File: ModeLogic.c
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

#include "ModeLogic.h"
#include "rtwtypes.h"
#include <math.h>
#include "ModeLogic_types.h"
#include <string.h>

/* Named constants for Chart: '<Root>/ModeLogic' */
#define ModeLogic_CALL_EVENT           (-1)
#define ModeLogic_IN_Calibration       ((uint8_T)1U)
#define ModeLogic_IN_Crash             ((uint8_T)2U)
#define ModeLogic_IN_Init              ((uint8_T)3U)
#define ModeLogic_IN_Land              ((uint8_T)4U)
#define ModeLogic_IN_LostBall          ((uint8_T)5U)
#define ModeLogic_IN_NO_ACTIVE_CHILD   ((uint8_T)0U)
#define ModeLogic_IN_NO_ACTIVE_LEAF    ((uint8_T)0U)
#define ModeLogic_IN_ReadyForTO        ((uint8_T)6U)
#define ModeLogic_IN_Track3D           ((uint8_T)7U)
#define ModeLogic_IN_TrackAlt          ((uint8_T)8U)
#define ModeLogic_IN_WaitForComms      ((uint8_T)9U)

/* Block signals (default storage) */
B_ModeLogic_T ModeLogic_B;

/* Block states (default storage) */
DW_ModeLogic_T ModeLogic_DW;

/* External inputs (root inport signals with default storage) */
ExtU_ModeLogic_T ModeLogic_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_ModeLogic_T ModeLogic_Y;
const Logic ModeLogic_rtZLogic = { false,/* CalibrateSensors */
  0U                                   /* Mode */
};

/* Model step function */
void ModeLogic_step(void)
{
  int32_T tmp_1;
  real32_T tmp;
  real32_T tmp_0;

  /* Chart: '<Root>/ModeLogic' incorporates:
   *  Inport: '<Root>/GCSCmds'
   *  Inport: '<Root>/IsBall'
   *  Inport: '<Root>/State'
   *
   * Block requirements for '<Root>/ModeLogic':
   *  1. 3 Modes of Operation
   */
  /* Gateway: ModeLogic
   * Requirements for Gateway: ModeLogic:
   *  1. 3 Modes of Operation
   */
  /* During: ModeLogic
   * Requirements for During: ModeLogic:
   *  1. 3 Modes of Operation
   */
  switch (ModeLogic_DW.is_c2_ModeLogic) {
   case ModeLogic_IN_Calibration:
    /* During 'Calibration': '<S1>:74':
     *  1. 3 Modes of Operation
     *  2. 26 Enter Calibrate Sensors from Initialization
     *  3. 27 Enter Calibrate Sensors from Ready for Flight
     */
    if ((ModeLogic_U.GCSCmds.GCS_MissionMode == 1U) &&
        (ModeLogic_U.State_femo.CalibrationDone)) {
      /* Transition: '<S1>:77':
       *  1. 30 Enter Ready for Flight from Calibration
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_ReadyForTO;

      /* Entry 'ReadyForTO': '<S1>:5':
       *  1. 3 Modes of Operation
       *  2. 30 Enter Ready for Flight from Calibration
       */
      ModeLogic_B.Logic_l1kg.Mode = 4;
    } else {
      ModeLogic_B.Logic_l1kg.CalibrateSensors = false;
    }
    break;

   case ModeLogic_IN_Crash:
    /* During 'Crash': '<S1>:23':
     *  1. 3 Modes of Operation
     *  2. 51 Enter Crash
     */
    /* Transition: '<S1>:24':
     *  1. 18 Enter Establish Communications from Crash
     */
    /* Transition: '<S1>:96':
     *  1. 18 Enter Establish Communications from Crash
     *  2. 19 Enter Establish Communications from Land
     */
    ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_WaitForComms;

    /* Entry 'WaitForComms': '<S1>:1':
     *  1. 3 Modes of Operation
     *  2. 17 Enter Establish Communications at Power Up
     *  3. 18 Enter Establish Communications from Crash
     *  4. 19 Enter Establish Communications from Land
     */
    ModeLogic_B.Logic_l1kg.Mode = 1;
    break;

   case ModeLogic_IN_Init:
    /* During 'Init': '<S1>:3':
     *  1. 3 Modes of Operation
     *  2. 22 Enter Initialization from Establish Communications
     */
    if (ModeLogic_U.GCSCmds.CalibrateCmd) {
      /* Transition: '<S1>:76':
       *  1. 26 Enter Calibrate Sensors from Initialization
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Calibration;

      /* Entry 'Calibration': '<S1>:74':
       *  1. 3 Modes of Operation
       *  2. 26 Enter Calibrate Sensors from Initialization
       *  3. 27 Enter Calibrate Sensors from Ready for Flight
       */
      ModeLogic_B.Logic_l1kg.Mode = 3;
      ModeLogic_B.Logic_l1kg.CalibrateSensors = true;
    }
    break;

   case ModeLogic_IN_Land:
    /* During 'Land': '<S1>:16':
     *  1. 3 Modes of Operation
     *  2. 43 Enter Land from Lost Ball
     *  3. 47 Enter Land from Track Altitude
     *  4. 47 Enter Land from Track Altitude and Position
     */
    tmp = (real32_T)fabs((real_T)ModeLogic_U.State_femo.Angles[0]);
    tmp_0 = (real32_T)fabs((real_T)ModeLogic_U.State_femo.Angles[1]);
    if (((((tmp * 180.0F) / 3.1415F) < 5.0F) && (((tmp_0 * 180.0F) / 3.1415F) <
          5.0F)) && (((real32_T)fabs((real_T)ModeLogic_U.State_femo.V_BODY[2])) <
                     0.1F)) {
      /* Transition: '<S1>:88':
       *  1. 19 Enter Establish Communications from Land
       */
      /* Transition: '<S1>:96':
       *  1. 18 Enter Establish Communications from Crash
       *  2. 19 Enter Establish Communications from Land
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_WaitForComms;

      /* Entry 'WaitForComms': '<S1>:1':
       *  1. 3 Modes of Operation
       *  2. 17 Enter Establish Communications at Power Up
       *  3. 18 Enter Establish Communications from Crash
       *  4. 19 Enter Establish Communications from Land
       */
      ModeLogic_B.Logic_l1kg.Mode = 1;

      /* Transition: '<S1>:93':
       *  1. 51 Enter Crash
       */
      /* 1.39626 rad ~= 80 deg  */
    } else if (((ModeLogic_U.GCSCmds.EMERGENCY_OFF) || (tmp > 1.39626F)) ||
               (tmp_0 > 1.39626F)) {
      /* Transition: '<S1>:25':
       *  1. 51 Enter Crash
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Crash;

      /* Entry 'Crash': '<S1>:23':
       *  1. 3 Modes of Operation
       *  2. 51 Enter Crash
       */
      ModeLogic_B.Logic_l1kg.Mode = 9;
    } else {
      /* no actions */
    }
    break;

   case ModeLogic_IN_LostBall:
    /* During 'LostBall': '<S1>:97':
     *  1. 3 Modes of Operation
     *  2. 42 Enter Lost Ball from Track Altitude
     *  3. 42 Enter Lost Ball from Track Altitude and Position
     */
    if (ModeLogic_DW.count >= 29U) {
      /* Transition: '<S1>:100':
       *  1. 43 Enter Land from Lost Ball
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Land;

      /* Entry 'Land': '<S1>:16':
       *  1. 3 Modes of Operation
       *  2. 43 Enter Land from Lost Ball
       *  3. 47 Enter Land from Track Altitude
       *  4. 47 Enter Land from Track Altitude and Position
       */
      ModeLogic_B.Logic_l1kg.Mode = 8;
    } else if (ModeLogic_U.IsBall) {
      /* Transition: '<S1>:102':
       *  1. 35 Enter Track Altitude from Lost Ball
       *  2. 39 The Track Altitude and Position mode shall be entered only from th*/
      if (ModeLogic_U.State_femo.Altitude >= 0.1F) {
        /* Transition: '<S1>:104':
         *  1. 39 The Track Altitude and Position mode shall be entered only from th*/
        ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Track3D;

        /* Entry 'Track3D': '<S1>:29':
         *  1. 3 Modes of Operation
         *  2. 38 The Track Altitude and Position mode shall be entered only from th*  3. 39 The Track Altitude and Position mode shall be entered only from th*/
        ModeLogic_B.Logic_l1kg.Mode = 6;
      } else {
        /* Transition: '<S1>:103':
         *  1. 35 Enter Track Altitude from Lost Ball
         */
        ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_TrackAlt;

        /* Entry 'TrackAlt': '<S1>:7':
         *  1. 3 Modes of Operation
         *  2. 34 Enter Track Altitude from Ready for Flight
         *  3. 35 Enter Track Altitude from Lost Ball
         */
        ModeLogic_B.Logic_l1kg.Mode = 5;
      }

      /* Transition: '<S1>:106':
       *  1. 51 Enter Crash
       */
      /* 1.39626 rad ~= 80 deg  */
    } else if (((ModeLogic_U.GCSCmds.EMERGENCY_OFF) || (((real32_T)fabs((real_T)
        ModeLogic_U.State_femo.Angles[0])) > 1.39626F)) || (((real32_T)fabs
                 ((real_T)ModeLogic_U.State_femo.Angles[1])) > 1.39626F)) {
      /* Transition: '<S1>:25':
       *  1. 51 Enter Crash
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Crash;

      /* Entry 'Crash': '<S1>:23':
       *  1. 3 Modes of Operation
       *  2. 51 Enter Crash
       */
      ModeLogic_B.Logic_l1kg.Mode = 9;
    } else {
      /* Transition: '<S1>:99':
       *  1. 43 Enter Land from Lost Ball
       */
      tmp_1 = ((int32_T)ModeLogic_DW.count) + 1;
      if ((((int32_T)ModeLogic_DW.count) + 1) < 0) {
        tmp_1 = 0;
      } else if ((((int32_T)ModeLogic_DW.count) + 1) > 255) {
        tmp_1 = 255;
      } else {
        /* no actions */
      }

      ModeLogic_DW.count = (uint8_T)tmp_1;
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_LostBall;

      /* Entry 'LostBall': '<S1>:97':
       *  1. 3 Modes of Operation
       *  2. 42 Enter Lost Ball from Track Altitude
       *  3. 42 Enter Lost Ball from Track Altitude and Position
       */
      ModeLogic_B.Logic_l1kg.Mode = 7;
    }
    break;

   case ModeLogic_IN_ReadyForTO:
    /* During 'ReadyForTO': '<S1>:5':
     *  1. 3 Modes of Operation
     *  2. 30 Enter Ready for Flight from Calibration
     */
    if (ModeLogic_U.IsBall) {
      /* Transition: '<S1>:8':
       *  1. 34 Enter Track Altitude from Ready for Flight
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_TrackAlt;

      /* Entry 'TrackAlt': '<S1>:7':
       *  1. 3 Modes of Operation
       *  2. 34 Enter Track Altitude from Ready for Flight
       *  3. 35 Enter Track Altitude from Lost Ball
       */
      ModeLogic_B.Logic_l1kg.Mode = 5;
    } else if (ModeLogic_U.GCSCmds.CalibrateCmd) {
      /* Transition: '<S1>:78':
       *  1. 27 Enter Calibrate Sensors from Ready for Flight
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Calibration;

      /* Entry 'Calibration': '<S1>:74':
       *  1. 3 Modes of Operation
       *  2. 26 Enter Calibrate Sensors from Initialization
       *  3. 27 Enter Calibrate Sensors from Ready for Flight
       */
      ModeLogic_B.Logic_l1kg.Mode = 3;
      ModeLogic_B.Logic_l1kg.CalibrateSensors = true;
    } else {
      /* no actions */
    }
    break;

   case ModeLogic_IN_Track3D:
    /* During 'Track3D': '<S1>:29':
     *  1. 3 Modes of Operation
     *  2. 38 The Track Altitude and Position mode shall be entered only from th*  3. 39 The Track Altitude and Position mode shall be entered only from th*/
    /* Transition: '<S1>:50':
     *  1. 42 Enter Lost Ball from Track Altitude and Position
     *  2. 47 Enter Land from Track Altitude and Position
     */
    if ((ModeLogic_U.GCSCmds.GCS_MissionMode == 2U) ||
        (ModeLogic_U.State_femo.BatteryVolts <= 3.0F)) {
      /* Transition: '<S1>:79':
       *  1. 47 Enter Land from Track Altitude
       *  2. 47 Enter Land from Track Altitude and Position
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Land;

      /* Entry 'Land': '<S1>:16':
       *  1. 3 Modes of Operation
       *  2. 43 Enter Land from Lost Ball
       *  3. 47 Enter Land from Track Altitude
       *  4. 47 Enter Land from Track Altitude and Position
       */
      ModeLogic_B.Logic_l1kg.Mode = 8;
    } else if (!ModeLogic_U.IsBall) {
      /* Transition: '<S1>:98':
       *  1. 42 Enter Lost Ball from Track Altitude
       *  2. 42 Enter Lost Ball from Track Altitude and Position
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_LostBall;

      /* Entry 'LostBall': '<S1>:97':
       *  1. 3 Modes of Operation
       *  2. 42 Enter Lost Ball from Track Altitude
       *  3. 42 Enter Lost Ball from Track Altitude and Position
       */
      ModeLogic_B.Logic_l1kg.Mode = 7;

      /* Transition: '<S1>:85':
       *  1. 51 Enter Crash
       */
      /* 1.39626 rad ~= 80 deg  */
    } else if (((ModeLogic_U.GCSCmds.EMERGENCY_OFF) || (((real32_T)fabs((real_T)
        ModeLogic_U.State_femo.Angles[0])) > 1.39626F)) || (((real32_T)fabs
                 ((real_T)ModeLogic_U.State_femo.Angles[1])) > 1.39626F)) {
      /* Transition: '<S1>:25':
       *  1. 51 Enter Crash
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Crash;

      /* Entry 'Crash': '<S1>:23':
       *  1. 3 Modes of Operation
       *  2. 51 Enter Crash
       */
      ModeLogic_B.Logic_l1kg.Mode = 9;
    } else {
      /* no actions */
    }
    break;

   case ModeLogic_IN_TrackAlt:
    /* During 'TrackAlt': '<S1>:7':
     *  1. 3 Modes of Operation
     *  2. 34 Enter Track Altitude from Ready for Flight
     *  3. 35 Enter Track Altitude from Lost Ball
     */
    /* Transition: '<S1>:84':
     *  1. 51 Enter Crash
     */
    /* 1.39626 rad ~= 80 deg  */
    if (((ModeLogic_U.GCSCmds.EMERGENCY_OFF) || (((real32_T)fabs((real_T)
            ModeLogic_U.State_femo.Angles[0])) > 1.39626F)) || (((real32_T)fabs
          ((real_T)ModeLogic_U.State_femo.Angles[1])) > 1.39626F)) {
      /* Transition: '<S1>:25':
       *  1. 51 Enter Crash
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Crash;

      /* Entry 'Crash': '<S1>:23':
       *  1. 3 Modes of Operation
       *  2. 51 Enter Crash
       */
      ModeLogic_B.Logic_l1kg.Mode = 9;
    } else if (ModeLogic_U.State_femo.Altitude >= 0.1F) {
      /* Transition: '<S1>:30':
       *  1. 38 The Track Altitude and Position mode shall be entered only from th*/
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Track3D;

      /* Entry 'Track3D': '<S1>:29':
       *  1. 3 Modes of Operation
       *  2. 38 The Track Altitude and Position mode shall be entered only from th*  3. 39 The Track Altitude and Position mode shall be entered only from th*/
      ModeLogic_B.Logic_l1kg.Mode = 6;

      /* Transition: '<S1>:81':
       *  1. 42 Enter Lost Ball from Track Altitude
       *  2. 47 Enter Land from Track Altitude
       */
    } else if ((ModeLogic_U.GCSCmds.GCS_MissionMode == 2U) ||
               (ModeLogic_U.State_femo.BatteryVolts <= 3.0F)) {
      /* Transition: '<S1>:79':
       *  1. 47 Enter Land from Track Altitude
       *  2. 47 Enter Land from Track Altitude and Position
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Land;

      /* Entry 'Land': '<S1>:16':
       *  1. 3 Modes of Operation
       *  2. 43 Enter Land from Lost Ball
       *  3. 47 Enter Land from Track Altitude
       *  4. 47 Enter Land from Track Altitude and Position
       */
      ModeLogic_B.Logic_l1kg.Mode = 8;
    } else if (!ModeLogic_U.IsBall) {
      /* Transition: '<S1>:98':
       *  1. 42 Enter Lost Ball from Track Altitude
       *  2. 42 Enter Lost Ball from Track Altitude and Position
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_LostBall;

      /* Entry 'LostBall': '<S1>:97':
       *  1. 3 Modes of Operation
       *  2. 42 Enter Lost Ball from Track Altitude
       *  3. 42 Enter Lost Ball from Track Altitude and Position
       */
      ModeLogic_B.Logic_l1kg.Mode = 7;
    } else {
      /* no actions */
    }
    break;

   default:
    /* During 'WaitForComms': '<S1>:1':
     *  1. 3 Modes of Operation
     *  2. 17 Enter Establish Communications at Power Up
     *  3. 18 Enter Establish Communications from Crash
     *  4. 19 Enter Establish Communications from Land
     */
    if ((ModeLogic_U.GCSCmds.WIFIconnected) && (ModeLogic_U.GCSCmds.BTconnected))
    {
      /* Transition: '<S1>:4':
       *  1. 22 Enter Initialization from Establish Communications
       */
      ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_Init;

      /* Entry 'Init': '<S1>:3':
       *  1. 3 Modes of Operation
       *  2. 22 Enter Initialization from Establish Communications
       */
      ModeLogic_B.Logic_l1kg.Mode = 2;
    }
    break;
  }

  /* End of Chart: '<Root>/ModeLogic' */

  /* Outport: '<Root>/Logic' */
  ModeLogic_Y.Logic_dzei = ModeLogic_B.Logic_l1kg;
}

/* Model initialize function */
void ModeLogic_initialize(void)
{
  /* Registration code */

  /* block I/O */
  (void) memset(((void *) &ModeLogic_B), 0,
                sizeof(B_ModeLogic_T));

  /* states (dwork) */
  (void) memset((void *)&ModeLogic_DW, 0,
                sizeof(DW_ModeLogic_T));

  /* external inputs */
  (void)memset((void *)(&ModeLogic_U), 0, sizeof(ExtU_ModeLogic_T));

  /* external outputs */
  ModeLogic_Y.Logic_dzei = ModeLogic_rtZLogic;

  /* SystemInitialize for Chart: '<Root>/ModeLogic'
   *
   * Block requirements for '<Root>/ModeLogic':
   *  1. 3 Modes of Operation
   */
  ModeLogic_B.Logic_l1kg.CalibrateSensors = false;
  ModeLogic_DW.count = 0;

  /* Chart: '<Root>/ModeLogic'
   *
   * Block requirements for '<Root>/ModeLogic':
   *  1. 3 Modes of Operation
   */
  /* Entry: ModeLogic
   * Requirements for Entry: ModeLogic:
   *  1. 3 Modes of Operation
   */
  /* Entry Internal: ModeLogic
   * Requirements for Entry Internal: ModeLogic:
   *  1. 3 Modes of Operation
   */
  /* Transition: '<S1>:2':
   *  1. 17 Enter Establish Communications at Power Up
   */
  ModeLogic_DW.is_c2_ModeLogic = ModeLogic_IN_WaitForComms;

  /* Entry 'WaitForComms': '<S1>:1':
   *  1. 3 Modes of Operation
   *  2. 17 Enter Establish Communications at Power Up
   *  3. 18 Enter Establish Communications from Crash
   *  4. 19 Enter Establish Communications from Land
   */
  ModeLogic_B.Logic_l1kg.Mode = 1;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
