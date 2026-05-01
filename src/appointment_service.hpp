#include<iostream>

#include"storage.hpp"
#include"appointment.hpp"
#include "char_array_functions.hpp"
#include "slot_unavailable_exception.hpp"

#pragma once

bool is_slot_available(const Storage<Appointment>& appointments, int doctor_id, const char* date, const char* time);
void book_appointment(Storage<Appointment>& appointments, const Appointment& new_appt);


bool is_slot_available(const Storage<Appointment>& appointments, int doctor_id, const char* ptr_date, const char* ptr_time)
{
    const Appointment* data = appointments.get_data();

    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& appt = data[i];

        if (appt.get_doctor_id() == doctor_id)
        {
            if (is_char_arrays_equal(appt.get_date(), ptr_date) &&
                is_char_arrays_equal(appt.get_time(), ptr_time))
            {
                return false;
            }
        }
    }

    return true;
}

void book_appointment(Storage<Appointment>& appointments, const Appointment& new_appt)
{
    if (!is_slot_available(appointments, new_appt.get_doctor_id(), new_appt.get_date(), new_appt.get_time()))
    {
        throw SlotUnavailableException();
    }

    appointments.add(new_appt);
}