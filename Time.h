//
//  Time.h
//  practice
//
//  Created by Jungwoo Chang on 8/7/18.
//  Copyright © 2018 Jungwoo Chang. All rights reserved.
//

#ifndef Time_h
#define Time_h

#include <cassert>  //assert
#include <iostream>
#include <functional>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

const int MAX_MIN = 1440;

class Time {
    string time;
    string hrs;
    string min;
    string am_pm;
    int minutes = 0;
    
  public:
    Time(string time_in) : time(time_in) {
        if (time_in.length() == 7) {
            hrs = time[0];
            hrs += time[1];
            min = time[3];
            min += time[4];
            am_pm = time[5];
            am_pm += time[6];
        }
        else if (time_in.length() == 6) {
            hrs += time[0];
            min = time[2];
            min += time[3];
            am_pm = time[4];
            am_pm += time[5];
        }
        convert_time_to_minutes();
        assert(check_invariant());
    }
    
    bool check_invariant() const {
        bool proper_time = atoi(hrs.c_str()) <= 12 && atoi(min.c_str()) <= 59;
        bool proper_minutes = minutes <= MAX_MIN;
        return proper_time && proper_minutes;
    }
    
    string get_time() const {
        return time;
    }
    
    int get_minutes() const {
        return minutes;
    }
    
    // REQUIRES: Time variable is a valid time
    // MODIFIES: minutes
    // EFFECTS:  converts string format time to minutes for easy calculation of time
    void print_time()const {
        assert(check_invariant());
        cout << time;
    }
    
    // REQUIRES: Time variable is a valid time
    // MODIFIES: minutes
    // EFFECTS:  converts string format time to minutes for easy calculation of time
    void convert_time_to_minutes() {
        // multiply hrs by minutes
        // special case for 12AM
        if (hrs == "12" && am_pm == "AM") {
                minutes = 0;
        }
        else {
            minutes += atoi(hrs.c_str()) * 60;
            if (am_pm == "PM" && hrs != "12") {
                minutes += MAX_MIN/2;
            }
        }
        // add normal minutes
        minutes += atoi(min.c_str());
        assert(check_invariant());
    }
    
    // REQUIRES: Time variable is a valid time
    // MODIFIES: minutes
    // EFFECTS:  adds time to minutes
    void add_time(int time_to_add) {
        minutes += time_to_add;
        if (minutes > MAX_MIN) {
            minutes %= MAX_MIN;
        }
        assert(check_invariant());
    }
    
    // REQUIRES: Time variable is a valid time
    // MODIFIES: minutes
    // EFFECTS:  subtracts time from minutes
    void subtract_time(int time_to_subtract) {
        minutes -= time_to_subtract;
        if (minutes < MAX_MIN) {
            minutes = abs(minutes)%MAX_MIN;
        }
        assert(check_invariant());
    }
    
    // REQUIRES: Time variable is a valid time
    // MODIFIES:
    // EFFECTS:  returns minutes between current time and desired time
    int time_until(Time time_desired) {
        return (time_desired.get_minutes() + (MAX_MIN - minutes));
    }
};

bool proper_time_string(string time_string_in) {
    if (time_string_in.length() == 7) {
        if (time_string_in[0] == '0') {
            return false;
        }
        if (time_string_in[2] != ':') {
            return false;
        }
        if (!(isdigit(time_string_in[0]) && isdigit(time_string_in[1]))) {
            return false;
        }
        if (time_string_in[0] == '1') {
            if (time_string_in[1] != '1' && time_string_in[1] != '2'
                                        && time_string_in[1] != '0') {
                return false;
            }
        }
        else {
            return false;
        }
        if (!(isdigit(time_string_in[3]) && isdigit(time_string_in[4]))) {
            return false;
        }
        if (time_string_in[5] != 'P' && time_string_in[5] != 'A') {
            return false;
        }
        if (time_string_in[6] != 'M') {
            return false;
        }
        return true;
    }
    else if (time_string_in.length() == 6) {
        if (time_string_in[0] == '0') {
            return false;
        }
        if (time_string_in[1] != ':') {
            return false;
        }
        if (!(isdigit(time_string_in[0]))) {
            return false;
        }
        if (!(isdigit(time_string_in[2]) && isdigit(time_string_in[3]))) {
            return false;
        }
        if (time_string_in[4] != 'P' && time_string_in[4] != 'A') {
            return false;
        }
        if (time_string_in[5] != 'M') {
            return false;
        }
        return true;
    }
    return false;
}

#endif /* Time_h */


