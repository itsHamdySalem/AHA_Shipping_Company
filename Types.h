#ifndef TYPES_H
#define TYPES_H

// Modes
enum MODE
{
    interactive,
    step_by_step,
    silent
};

// Cargo Type
enum CargoType
{
    NORMAL_CARGO,
    SPECIAL_CARGO,
    VIP_CARGO
};

// Truck Types
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
