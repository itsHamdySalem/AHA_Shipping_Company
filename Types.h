#pragma once
#ifndef TYPES_H
#define TYPES_H

// The Modes of the UI
enum MODE
{
    interactive,
    step_by_step,
    silent
};

// The types of cargos
enum CargoType
{
    NORMAL_CARGO,
    SPECIAL_CARGO,
    VIP_CARGO
};

// the types of trucks
enum TruckType
{
    NORMAL_TRUCK,
    SPECIAL_TRUCK,
    VIP_TRUCK
};

// Truck Status
enum TruckStatus {
    AVAILABLE_TRUCK,
    LOADING_TRUCK,
    MOVING_TRUCK,
    CHECKUP_TRUCK
};

// Cargo Status
enum CargoStatus {
    WAITING_CARGO,
    LOADING_CARGO,
    MOVING_CARGO,
    DELIVERED_CARGO
};

#endif