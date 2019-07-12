/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   overcurrent_controller.h
 * Author: root
 *
 * Created on July 12, 2019, 1:57 PM
 */

#ifndef OVERCURRENT_CONTROLLER_H
#define OVERCURRENT_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "linked_list.h"
#include "prot_controller.h"
#include "meas_controller.h"
#include "ctrl_controller.h"

    bool is_overcurrent();
    void store_sampled_value(float current, float voltage);
    void overcurrent_controller_main();

#ifdef __cplusplus
}
#endif

#endif /* OVERCURRENT_CONTROLLER_H */

