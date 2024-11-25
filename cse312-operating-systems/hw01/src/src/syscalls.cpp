
#include <syscalls.h>
 
using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;
 
SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber, TaskManager* taskmanager)
:    InterruptHandler(interruptManager, InterruptNumber  + interruptManager->HardwareInterruptOffset())
{
    this->taskmanager = taskmanager;
}

SyscallHandler::~SyscallHandler()
{
}


void printf(char*);

enum SYSCALLS{EXIT,WAITPID,FORK,EXECVE,PRINTF};




void myos::waitpid(common::uint8_t wPid){
    asm("int $0x80" : : "a" (SYSCALLS::WAITPID), "b" (wPid));
}

void myos::exit(){
    asm("int $0x80" : : "a" (SYSCALLS::EXIT));
}


uint8_t myos::fork(){
    uint8_t childPid;
    asm("int $0x80" : "=c" (childPid) : "a" (SYSCALLS::FORK));
    return childPid;
}

int myos::execve(void entrypoint()){
    int result;

    asm("int $0x80" : "=c" (result) : "a" (SYSCALLS::EXECVE), "b" ((uint32_t)entrypoint));

    return result;
}



uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState* cpu = (CPUState*)esp;

    switch(cpu->eax)
    {
        case SYSCALLS::PRINTF:
            printf((char*)cpu->ebx);
            break;

        case SYSCALLS::FORK:
        {
            cpu->ecx = taskmanager->Fork(cpu);
            break;
        }

        case SYSCALLS::WAITPID:
        {
            if(taskmanager->Waitpid(esp)){ // if its succesfully wait
                esp = (uint32_t) taskmanager->Schedule(cpu);
            }
            break;
        }

        case SYSCALLS::EXIT:
        {
            taskmanager->Exit();
            esp = (uint32_t) taskmanager->Schedule(cpu);
            break;
        }

        case SYSCALLS::EXECVE:
        {
            cpu-> ecx = taskmanager->Execve((void (*)())cpu->ebx);
            esp = (uint32_t) this->taskmanager->getCurrentTask()->getCpuState();
            break;
        }

        default:
            break;
    }

    return esp;
}


