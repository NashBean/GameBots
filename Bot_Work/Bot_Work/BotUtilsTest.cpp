//
//  BotUtilsTest.cpp
//
//
//  Created by nash on 11/24/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

#include "BotUtls.h"

struct Student
{
    int age;
    int standard;
    std::string first_name, last_name;
    Student():age(-1), first_name (""), last_name (""), standard(-1){};
    ~Student(){};
    void in()
    {
        std::cin >> age >> first_name >> last_name >> standard;
    };
    void out()
    {
        std::cout << age << " " << first_name << " " << last_name << " " << standard;
    };
};
