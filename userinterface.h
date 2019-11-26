//
//  userinterface.h
//  practice
//
//  Created by Jungwoo Chang on 8/21/18.
//  Copyright © 2018 Jungwoo Chang. All rights reserved.
//

#ifndef userinterface_h
#define userinterface_h

#include <iostream>
#include <cassert>
#include <vector>

#include "Time.h"

using namespace std;

//REQUIRES:
//MODIFIES:
//EFFECTS: returns the inputed current time
Time current_time_prompt();

//REQUIRES:
//MODIFIES:
//EFFECTS: returns the inputed desired time
Time desired_time_prompt();

//REQUIRES:
//MODIFIES:
//EFFECTS: returns the desired od
double desired_od_prompt();

//REQUIRES:
//MODIFIES:
//EFFECTS: returns the end volume
double end_volume_prompt();

double doubling_time_prompt();

double current_od_prompt();

bool is_double(string& double_in) {
    try {
        stod(double_in);
    }
    catch(...) {
        return false;
    }
    return true;
}

class OD_Calculator {
public:
    OD_Calculator() : current_time("0:00AM"), desired_time("0:00AM"), current_OD(0),
    desired_OD(0), final_volume(0), doubling_time(0), num_cultures(0),
                                                                    menu_prompt(-1) { }
    
    void set_current_time() {
        current_time = current_time_prompt();
    }
    
    Time get_current_time() {
        return current_time;
    }
    
    void set_desired_time() {
        desired_time = desired_time_prompt();
    }
    
    Time get_desired_time() {
        return desired_time;
    }
    
    void set_current_od() {
        current_OD = current_od_prompt();
    }
    
    void set_double_time() {
        doubling_time = doubling_time_prompt();
    }
    
    void set_desired_od() {
        desired_OD = desired_od_prompt();
    }
    
    void set_final_volume() {
        final_volume = end_volume_prompt();
    }
    
    int get_menu_prompt() {
        return menu_prompt;
    }
    
    void mLs_for_new_od() {
        pair<double, double> return_double;
        // figure out number of doubling times
        int doubling_time_min = 60 * doubling_time;
        int minutes_between = current_time.time_until(desired_time);
        int num_doubling_times = minutes_between / doubling_time_min;
        
        // divide target OD by 2 * #doubleing times to get current needed OD
        double current_needed_od = desired_OD / pow(2, num_doubling_times);
        return_double.first = (current_needed_od / current_OD);
        return_double.second = final_volume - return_double.first;
        final_storage.push_back(return_double);
    }

    
    void run_initial() {
        set_current_time();
        set_desired_time();
        set_double_time();
        set_current_od();
        set_desired_od();
        set_final_volume();
        mLs_for_new_od();
    }
    
    void run_another_culture() {
        set_current_od();
        mLs_for_new_od();
    }
    
    void run_diff_culture() {
        
    }
    
    void list_all_ods() {
        cout << endl;
        for (int i = 0; i < num_cultures; ++i) {
            cout << (i + 1) << ". " << final_storage[i].first << "mLs of cells and "
            << final_storage[i].second << "mLs of media" << endl;
        }
        cout << endl;
    }
    
private:
    Time current_time;
    Time desired_time;
    double current_OD;
    double desired_OD;
    double current_volume;
    double final_volume;
    double doubling_time;
    vector<pair<double, double>> final_storage;
    int num_cultures;
    int menu_prompt;
};

Time current_time_prompt() {
    bool correct_time = false;
    string time_in_string;
    while (!correct_time) {
        cout << "\nEnter the current time." << endl;
        cin >> time_in_string;
        if (proper_time_string(time_in_string)) {
            correct_time = true;
        }
        else {
            correct_time = false;
            time_in_string = "";
            cout << "\nThe correct format for time looks like '12:24PM' or '6:02AM'";
        }
    }
    Time time_in(time_in_string);
    return time_in;
}

Time desired_time_prompt() {
    bool correct_time = false;
    string desired_time_string;
    while (!correct_time) {
        cout << "\nEnter the time at which you want your new OD:" << endl;
        cin >> desired_time_string;
        if (proper_time_string(desired_time_string)) {
            correct_time = true;
        }
        else {
            correct_time = false;
            desired_time_string = "";
            cout << "\nThe correct format for time looks like '12:24PM' or '6:02AM'";
        }
    }
    Time desired_time(desired_time_string);
    return desired_time;
}

double desired_od_prompt() {
    double desired_OD;
    cout << "\nEnter the desired OD:" << endl;
    string desired_OD_string;
    cin >> desired_OD_string;
    desired_OD = atof(desired_OD_string.c_str());
    return desired_OD;
}

double current_volume_prompt() {
    string begin_volume_string;
    while (!is_double(begin_volume_string)) {
        begin_volume_string = "";
        cout << "\nEnter the current total volume of your cells and media in mLs:" << endl;
        cin >> begin_volume_string;
    }
    double begin_volume = atof(begin_volume_string.c_str());
    return begin_volume;
}

double end_volume_prompt() {
    string end_volume_string;
    while (!is_double(end_volume_string)) {
        end_volume_string = "";
        cout << "\nEnter the total volume that you want to dilute to in mLs:" << endl;
        cin >> end_volume_string;
    }
    double end_volume = atof(end_volume_string.c_str());
    return end_volume;
}

double doubling_time_prompt() {
    string doubling_time_string;
    while (!is_double(doubling_time_string)) {
        doubling_time_string = "";
        cout << "\nEnter the doubling time of your cells in hours, such as '2.5':" << endl;
        cin >> doubling_time_string;
    }
    double doubling_time = atof(doubling_time_string.c_str());
    return doubling_time;
}

double current_od_prompt() {
    string current_OD_string;
    while (!is_double(current_OD_string)) {
        current_OD_string = "";
        cout << "\nEnter the current OD:" << endl;
        cin >> current_OD_string;
    }
    double current_OD = atof(current_OD_string.c_str());
    return current_OD;
}

#endif /* userinterface_h */
