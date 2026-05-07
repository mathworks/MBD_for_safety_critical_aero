# Model-Based Design for Safety-Critical Aerospace Systems Workshop

[![Open in MATLAB Online](https://www.mathworks.com/images/responsive/global/open-in-matlab-online.svg)](https://matlab.mathworks.com/open/github/v1?repo=mathworks/MBD_for_safety_critical_aero​&project=AeroVnV.prj)

## Overview and Motivation

This repository contains a hands-on workshop for aerospace engineers who want to build robust verification and validation practices into their Model-Based Design workflow using Simulink&reg; and Stateflow&reg;. You'll learn how to check models against high-integrity standards, link tests to requirements, and measure structural coverage — practices that improve software quality whether or not you're pursuing formal certification. The workshop follows a DO-178C verification workflow using MathWorks&reg; tools, so the skills you learn translate directly to certification readiness.

### Who is this for?

- **Teams pursuing DO-178C (or similar) certification** who want a practical introduction to the MathWorks V&V toolchain. **Note:** The workflows described are not limited to DO-178C compliance and can be applied to similar standards.
- **Teams adopting high-integrity practices** who want to build rigorous V&V into their workflow now so they're ready if certification requirements come later

**Workshop scenario:** Your team is working on an autonomous quadcopter mission. As a lead software engineer, your current priority is to ensure that the mission mode logic is robust and fully verified, a key requirement for airborne software in commercial aerospace systems. Your project centers around building and certifying a system where the quadcopter tracks a moving ball and operates across different flight modes.

In this workshop, you will learn how to:

1. check your model for compliance with high-integrity standards
2. create test cases and link them to requirements
3. run a test suite and resolve missing model test coverage

**Note**: most standards (e.g., DO-178C) require independence between design and verification activities. In other words, "you should not test your own design." We recommend you follow that practice.

## Prerequisites

- MATLAB R2025b or newer with all [products listed below](#products-used) installed
- Familiarity with Simulink (no prior DO-178C experience required)

## Getting Started

This workshop takes approximately 2 hours to complete.

1. Clone this repo
2. Open the MATLAB project: `openProject("AeroVnV.prj");`
3. Follow instructions in **Instructions.mlx**

**OR**

[![Open in MATLAB Online](https://www.mathworks.com/images/responsive/global/open-in-matlab-online.svg)](https://matlab.mathworks.com/open/github/v1?repo=mathworks/MBD_for_safety_critical_aero​&project=AeroVnV.prj)

## Products Used

1. MATLAB&reg;
2. Simulink&reg;
3. Stateflow&trade;
4. Simulink Check&trade;
5. Requirements Toolbox&trade;
6. Simulink Test&trade;
7. Simulink Coverage&trade;
8. Simulink Design Verifier&trade;

---

## Workshop Summary

Participants work through a complete DO-178C verification workflow using a quadcopter mode logic example. The workshop covers model compliance checking, requirements-based testing, coverage analysis, and traceability.


Copyright 2026, The MathWorks Inc.