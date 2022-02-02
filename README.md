# Embedded Systems Bare-Metal Programming Ground Up™ (STM32): Program 14

[Code Development follows this Udemy Course](https://www.udemy.com/course/embedded-systems-bare-metal-programming/)

## Specs

Host

* MS Windows 10.0.19042
* STM32CubeIDE 1.8.0

Device

* STM32F401RE chip
* STM32 Nucleo-64 development board

## Description

This program demonstrates how one pin on the nucleo board can capture the output of another pin.

In this case, PA6 (D12) is capturing the output of PA5 (D13).

## Design

Nucleo-64 Board Layout Guide

![Layout Guide](Design/STM32F4-14_input_capture-board-layout-guide.png)

Nucleo-64 Board Layout 

![Layout](Design/STM32F4-14_input_capture-board-layout.png)

## Output

### Video of Debugger

![Debugger shows changing timestamp being captured](Output/STM32F4-14_input_capture-debugging.mp4)

### Video of Board

![LED flashing in unison with timestamp change](Output/STM32F4-14_input_capture-running.mp4)


