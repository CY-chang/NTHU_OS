/*
 * file: preemptive.h
 *
 * this is the include file for the cooperative multithreading
 * package.  It is to be compiled by SDCC and targets the EdSim51 as
 * the target architecture.
 *
 * CS 3423 Fall 2018
 */

#ifndef __PREEMPTIVE_H__
#define __PREEMPTIVE_H__

typedef char ThreadID;
typedef void (*FunctionPtr)(void);

#define MAXTHREADS 4  /* not including the scheduler */
/* the scheduler does not take up a thread of its own */

#define delay(n) {\
    available_time[current_thread_ID] = time_units_elapsed + n;\
    while (1) {\
        if (time_units_elapsed == available_time[current_thread_ID]) break;\
    }\
}

__data __at (0x37) ThreadID current_thread_ID;
__data __at (0x38) unsigned char available_time[MAXTHREADS];
__data __at (0x3C) char idx_for_threads[MAXTHREADS];
__data __at (0x20) char unused_thread_count; // 23949 unused 會變 FF(solved)
__data __at (0x21) char car_idx_counter;
__data __at (0x22) char time_counter;
__data __at (0x23) unsigned char time_units_elapsed;


// used to convert a C name into an assembly name
// ##: concatenate two symbols together
#define CNAME(s) _ ## s
#define _CONCAT(a, b) a ## b
#define CONCAT(a, b) _CONCAT(a, b)
#define tmp_label CONCAT(__COUNTER__, $)


// create a counting semaphore s 
// that is initialized to n
#define SemaphoreCreate(s, n)\
    {\
        s = n;\
    }


// signal() semaphore s
#define SemaphoreSignal(s)\
    {\
        __asm\
        INC CNAME(s)\
        __endasm;\
    }


// do (busy-)wait() on semaphore s



#define SemaphoreWaitBody(s, label)\
    {\
        __asm\
        label:\
        MOV A, CNAME(s)\
        JB ACC.7, label\
        JZ label\
        DEC CNAME(s)\
        __endasm;\
    }


// parentheses outside __COUNTER ## $ is needed 
#define SemaphoreWait(s)\
    {\
        SemaphoreWaitBody(s, tmp_label);\
    }

                                 




ThreadID ThreadCreate(FunctionPtr);
void ThreadYield(void);
void ThreadExit(void);
void myTimer0Handler();


unsigned char now(void);
void Park(void);


#endif // __PREEMPTIVE_H__
