﻿// SmartRoom.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include "Scheduler.h"
//#include "getC2Dms.h"
//#include "../Assignment-03/pc_vs2/SmartRoom/test/TestTask.h"
#include "IotTask.h"
#include "LightTask.h"
#include "RollerTask.h"
#include "SerialPort.h"


using namespace std;

Timer* timer;
Scheduler* sched;

void init_system() {
    sched = new Scheduler;
    timer = new Timer;
    sched->init(100);
    Task* t0 = new IotTask();
    Task* t1 = new LightTask();
    //Task* t2 = new RollerTask();
    t0->init(100);
    sched->addTask(t0);
    t1->init(100);
    sched->addTask(t1);
    // t2->init(100);
    // sched->addTask(t2);
    timer->setupPeriod(50);
}

int main()
{
    init_system();
    while(1){
        timer->waitForNextTick();
        sched->schedule();
    }

    return 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
