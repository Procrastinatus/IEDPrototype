/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "overcurrent_controller.h"

/* This is a scenario-specific controller */

/* No. of samples to take */
int N = 100;
int current_index = 0;

/* TODO Sample values must be based on last 20ms instead of fixed N */
float sampled_voltages[100];
float sampled_currents[100];

/* Note that v_rms and its threshold are in units of KILO volts (10.0f = 10,000V) */
float i_rms, v_rms;
float i_rms_threshold = 505.0f, v_rms_threshold = 10.0f;
float total_current_squared,total_voltage_squared;
int no_of_readings = 0;

bool is_overcurrent() {
    /* Determine if OC has occurred given sampled values */
    /* no_of_readings should increase to N after a while and not increase further */
    /* Note that it's KILO-volts */
    total_current_squared = 0.0f;
    total_voltage_squared = 0.0f;
    for (int i = 0; i < no_of_readings; i++) {
        total_voltage_squared += powf(sampled_voltages[i], 2.0f);
        total_current_squared += powf(sampled_currents[i], 2.0f);
    }
    i_rms = sqrt(total_current_squared / no_of_readings);
    v_rms = sqrt(total_voltage_squared / no_of_readings);
    //printf("i_rms is %f and v_rms is %f \n ", i_rms, v_rms);
    if ((v_rms > v_rms_threshold) && (i_rms > i_rms_threshold)) {
        return true;
    } else {       
        return false;
    }
}

void store_sampled_value(float current, float voltage) {
    /* This method stores the latest N sampled values (TODO: Sample from last 20ms instead of N) */
    /* Values can be sampled from any one phase, so we take phsA's current and voltage */
    sampled_currents[current_index] = current;
    sampled_voltages[current_index] = voltage;

    if (current_index == 99) {
        current_index = 0;
    } else {
        current_index += 1;
    }
    /* Stop increasing the no. of readings after N samples */
    if (no_of_readings < N) {
        no_of_readings++;
    }
}

void overcurrent_controller_main() {
    /* This method should be called continuously by the SV listener to have the latest sampled values
       to determine if an over-current has occurred. */
    if (is_overcurrent()) {
        set_alarm(true);
        update_cb_status(0);
        printf("OC DETECTED!============OC DETECTED!============OC DETECTED!OC DETECTED!============OC DETECTED!============OC DETECTED!\n");
    } else {
        set_alarm(false);
        update_cb_status(1);
        printf("-----------NO OVERCURRENT.----------------------NO OVERCURRENT.-----------\n");
    }
}