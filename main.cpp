//
//  main.cpp
//  practice
//
//  Created by Jungwoo Chang on 8/7/18.
//  Copyright © 2018 Jungwoo Chang. All rights reserved.
//

#include <iostream>

#include "Time.h"
#include "userinterface.h"

using namespace std;

// To do: implement a memory feature, and maybe a display all current ODs mode
// names of strains? probably too extra
// implement diluting to different volumes

int main(int argc, const char * argv[]) {
    OD_Calculator main_calculator;
    main_calculator.run_initial();

    return 0;
}

