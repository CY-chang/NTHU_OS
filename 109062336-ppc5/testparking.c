#include <8051.h>
#include "preemptive.h"

__data __at (0x24) char empty_slots_cnt;
__data __at (0x25) char spot1;
__data __at (0x26) char spot2;
__data __at (0x27) char spots_mutex;
__data __at (0x28) char print_mutex;

#define print(a, b)\
        TMOD |= 0x20;\
        TH1 = -6;\
        SCON = 0x50;\
        TR1 = 1;\
        SBUF = a + '0';\
        while (!TI){}\
        TI = 0;\
        SBUF = b;\
        while (!TI){}\
        TI = 0;\
        SBUF = '\n';\
        while (!TI){}\
        TI = 0;\

void Park(void) {
        SemaphoreWait(empty_slots_cnt);
        if (spot1 == 0) {
            SemaphoreWait(spots_mutex);

            EA = 0;    
            spot1 = idx_for_threads[current_thread_ID];
            EA = 1;

            SemaphoreWait(print_mutex);
            EA = 0;
            print(spot1,'i');
            EA = 1;   
            SemaphoreSignal(print_mutex);
            
            
            SemaphoreSignal(spots_mutex);

            if (idx_for_threads[current_thread_ID] == 1) 
            {
            delay(2);
            }
            else if (idx_for_threads[current_thread_ID] == 2) 
            {
            delay(2);
            }    
            else if (idx_for_threads[current_thread_ID] == 3) 
            {
            delay(5);
            }    
            else if (idx_for_threads[current_thread_ID] == 4) 
            {
            delay(2);
            }
            else if (idx_for_threads[current_thread_ID] == 5) 
            {
            delay(1);
            }
            //124260
              

            SemaphoreWait(spots_mutex);

            SemaphoreWait(print_mutex);
            EA = 0;
            print(spot1, 'o');
            EA = 1;
            SemaphoreSignal(print_mutex);  
            
            EA = 0;
            spot1 = 0;
            EA = 1;
            
            SemaphoreSignal(spots_mutex);
        }
        else if (spot2 == 0) {
            SemaphoreWait(spots_mutex);

            EA = 0;
            spot2 = idx_for_threads[current_thread_ID];
            EA = 1;

            SemaphoreWait(print_mutex); 
            EA = 0;
            print(spot2, 'i');    
            EA = 1;    
            SemaphoreSignal(print_mutex);

            SemaphoreSignal(spots_mutex);


            //delay(2);

            if (idx_for_threads[current_thread_ID] == 1) 
            {
            delay(2);
            }
            else if (idx_for_threads[current_thread_ID] == 2) 
            {
            delay(2);
            }    
            else if (idx_for_threads[current_thread_ID] == 3) 
            {
            delay(5);
            }    
            else if (idx_for_threads[current_thread_ID] == 4) 
            {
            delay(2);
            }
            else if (idx_for_threads[current_thread_ID] == 5) 
            {
            delay(1);
            }
            //124324
            SemaphoreWait(spots_mutex);

            SemaphoreWait(print_mutex);
            EA = 0;
            print(spot2, 'o');
            EA = 1;
            SemaphoreSignal(print_mutex);

            EA = 0;
            spot2 = 0;
            EA = 1;

            SemaphoreSignal(spots_mutex);
        }
        

        SemaphoreSignal(empty_slots_cnt);
        ThreadExit();
}

void main(void) {

        SemaphoreCreate(empty_slots_cnt, 2);
        SemaphoreCreate(spots_mutex, 1);
        SemaphoreCreate(print_mutex, 1);

        
        SemaphoreWait(unused_thread_count);
        ThreadCreate(Park);  
        SemaphoreWait(unused_thread_count);
        ThreadCreate(Park);  
        SemaphoreWait(unused_thread_count);
        ThreadCreate(Park);  
        SemaphoreWait(unused_thread_count);
        ThreadCreate(Park);  
        SemaphoreWait(unused_thread_count);
        ThreadCreate(Park);  
        

        ThreadExit();
        
}

void _sdcc_gsinit_startup(void) {
        __asm
                ljmp  _Bootstrap
        __endasm;
}

void _mcs51_genRAMCLEAR(void) {}
void _mcs51_genXINIT(void) {}
void _mcs51_genXRAMCLEAR(void) {}
void timer0_ISR(void) __interrupt(1) {
        __asm
                ljmp _myTimer0Handler
        __endasm;
}
