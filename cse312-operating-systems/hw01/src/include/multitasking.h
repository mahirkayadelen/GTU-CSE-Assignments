 
#ifndef __MYOS__MULTITASKING_H
#define __MYOS__MULTITASKING_H

#include <common/types.h>
#include <gdt.h>

#define IDLE 20

namespace myos
{
    
    struct CPUState
    {
        common::uint32_t eax;
        common::uint32_t ebx;
        common::uint32_t ecx;
        common::uint32_t edx;

        common::uint32_t esi;
        common::uint32_t edi;
        common::uint32_t ebp;

        /*
        common::uint32_t gs;
        common::uint32_t fs;
        common::uint32_t es;
        common::uint32_t ds;
        */
        common::uint32_t error;

        common::uint32_t eip;
        common::uint32_t cs;
        common::uint32_t eflags;
        common::uint32_t esp;
        common::uint32_t ss;        
    } __attribute__((packed));
    
    enum TaskState {READY,WAITING,FINISHED,RUNNING};

    class TaskManager;

    class Task
    {
        friend class TaskManager;
        private:
            common::uint8_t stack[4096]; // 4 KiB
            CPUState* cpustate;
            TaskState taskState; // keeps status of task(READY,WAITING,FINISHED,RUNNING)
            common::uint8_t pId = 0; // holds Process ID
            common::uint8_t pPid = 0; // holds Parent Process ID
            common::uint8_t waitPid; // need for waitPid function

            
        public:
            Task(GlobalDescriptorTable *gdt, void entrypoint());
            ~Task();

            CPUState * getCpuState(); // for using cpustate in execve
            Task(GlobalDescriptorTable *gdt, void entrypoint(),TaskManager * manager);
    };
    
    
    class TaskManager
    {
    private:
        Task* tasks[256];
        int numTasks;
        int currentTask;

        Task* idleTask; // idle task for demonstration purposes for

        GlobalDescriptorTable *gdt; 
    public:
        TaskManager();
        ~TaskManager();
        bool AddTask(Task* task);
        CPUState* Schedule(CPUState* cpustate);


        bool Waitpid(common::uint32_t esp); // waitpid system call
        common::uint32_t Fork(CPUState* cpustate); // fork system call

        bool Exit(); // exit system call
        Task* getCurrentTask(); // for using in execve
        int Execve(void (*entrypoint)()); // execve system call

        void printTasks(); // print all tasks with their attributes
    };
    
}


#endif