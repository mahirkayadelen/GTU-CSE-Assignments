
#include <multitasking.h>

using namespace myos;
using namespace myos::common;

void printfHex32(uint32_t key);
void printfHex16(uint32_t key);
void printfHex(uint8_t key);
void printf(char *);

Task::Task(GlobalDescriptorTable *gdt, void entrypoint())
{
	cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
	
	cpustate -> eax = 0;
	cpustate -> ebx = 0;
	cpustate -> ecx = 0;
	cpustate -> edx = 0;

	cpustate -> esi = 0;
	cpustate -> edi = 0;
	cpustate -> ebp = 0;
	
	/*
	cpustate -> gs = 0;
	cpustate -> fs = 0;
	cpustate -> es = 0;
	cpustate -> ds = 0;
	*/
	
	// cpustate -> error = 0;    
   
	// cpustate -> esp = ;
	cpustate -> eip = (uint32_t)entrypoint;
	cpustate -> cs = gdt->CodeSegmentSelector();
	// cpustate -> ss = ;
	cpustate -> eflags = 0x202;
    taskState = FINISHED;
	
}

Task::Task(GlobalDescriptorTable *gdt, void entrypoint(),TaskManager * manager){

	cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState)); 
	cpustate -> eax = 0;
	cpustate -> ebx = 0;
	cpustate -> ecx = 0;
	cpustate -> edx = 0;
	cpustate -> esi = 0;
	cpustate -> edi = 0;
	cpustate -> ebp = 0;
	cpustate -> eip = (uint32_t)entrypoint;
	cpustate -> cs = gdt->CodeSegmentSelector();
	cpustate -> eflags = 0x202;


	
	taskState = FINISHED;
}
	
Task::~Task()
{
}



void idle(){
    while(true);
}
		
TaskManager::TaskManager()
{
	numTasks = 0;
	currentTask = -1;

	this->gdt = gdt;

    idleTask=new Task(gdt, idle);
    idleTask->waitPid = -1;
    idleTask->taskState = READY;
}

TaskManager::~TaskManager()
{
}

bool TaskManager::AddTask(Task* task)
{
	if(numTasks >= 256)
		return false;
	tasks[numTasks++] = task;

    task->taskState = READY;
	task->pId = numTasks;
	return true;
}

CPUState* TaskManager::Schedule(CPUState* cpustate)
{
	if(numTasks <= 0)
		return cpustate;
	

    // idleprocess

	static int idleTime = 0;

	if(idleTask->taskState == RUNNING)
	{
		idleTask->cpustate = cpustate;
	}
	else if(idleTask->taskState == READY)
	{
		idleTask->taskState = RUNNING;
		if(currentTask >= 0)
			tasks[currentTask]->cpustate = cpustate;
	}

	if(++idleTime % IDLE != 0)
	{
		return idleTask->cpustate;
	}
	else
	{
		idleTime = 0;
		idleTask->taskState = READY;
	}
	
	// idleprocess



	int start = currentTask == -1 ? 0 : currentTask;
	
    do{
        if(++currentTask >= numTasks)
		    currentTask %= numTasks;
        if(tasks[currentTask]->taskState == WAITING )
        {
            if(tasks[tasks[currentTask]->waitPid -1]->taskState == FINISHED)
                tasks[currentTask]->taskState = READY;
        }
    }
    while(tasks[currentTask]->taskState != READY);


    if(tasks[start]->taskState == RUNNING)
        tasks[start]->taskState = READY; 

    tasks[currentTask]->taskState = RUNNING;
    printTasks();
	return tasks[currentTask]->cpustate;
}


bool TaskManager::Waitpid(uint32_t esp){

    CPUState *cpustate = (CPUState *) esp;
    uint32_t pid = cpustate->ebx;
    
    if(tasks[currentTask]->pId == pid || pid == 0){ // for self waiting
        return false;
    }

    int index = -1; // default value of non found
    for(int i =0 ; i < numTasks;i++){ // iterates through tasks and finds if waiting Process exist
        if(tasks[i]->pId == pid){
            index = i;
            break;
        }
    }

    if(index == -1) // process doesnt exist
        return false;

    if(numTasks<= index || tasks[index]->taskState == FINISHED){
        printf("returned \n");
        return false;
    }

    tasks[currentTask]->cpustate=cpustate;
    tasks[currentTask]->waitPid = pid;
    tasks[currentTask]->taskState = WAITING;
    return true;
}



uint32_t TaskManager::Fork(CPUState* cpustate) {
	Task* cur_Task = tasks[currentTask];

	Task* child = new Task(gdt, 0, this);

    // copy parent stack to the child stack
	for(int i = 0; i < sizeof(cur_Task->stack); i++){ 
		child->stack[i] = cur_Task->stack[i];
	}
	
	// calculating offset of current esp(cpustate)
	uint32_t parentEspRelativeToStackStart = (uint32_t)cpustate - (uint32_t)cur_Task->stack;
    
    // calculating childs current esp(cpustate) with calculating  parent esp offset
    child->cpustate = (CPUState *) (child->stack + parentEspRelativeToStackStart);


    uint32_t parentEbpRelativeToStackStart = (uint32_t)cpustate->ebp - (uint32_t)cur_Task->stack ;
    child->cpustate->ebp = (uint32_t) (child->stack + parentEbpRelativeToStackStart);
    



	child->pPid = cur_Task->pId;
	child->cpustate->ecx = 0;

	AddTask(child);

	printf("\n");

	return child->pId;
}

void TaskManager::printTasks() 
{
    for (int i = 0; i < numTasks; ++i)
    {
        printf("Task ID: ");
        printfHex(tasks[i]->pId);
        printf("\n");
        printf("Parent Task ID: ");
        printfHex(tasks[i]->pPid);
        printf("\n");
        printf("Task State: ");
        if(tasks[i]->taskState==READY)
            printf("READY\n");
        else if(tasks[i]->taskState==WAITING)
            printf("WAITING\n");
        else if(tasks[i]->taskState==RUNNING)
            printf("RUNNING\n");
        else
            printf("FINISHED\n");

        printf("-------------------------\n");
    }
}


bool TaskManager::Exit(){
    tasks[currentTask]->taskState = FINISHED;

    return true;
}

CPUState * Task::getCpuState(){
    return this->cpustate;
}


Task* TaskManager::getCurrentTask(){
    return tasks[currentTask];
}


int TaskManager::Execve(void (*entrypoint)()){

    tasks[currentTask]->cpustate = (CPUState*) (tasks[currentTask]->stack + 4096 - sizeof(CPUState));

    tasks[currentTask]->cpustate->eip = (uint32_t) entrypoint; // move instructor pointer to the function

    tasks[currentTask]->cpustate->cs = gdt->CodeSegmentSelector(); // for kernel

    tasks[currentTask]->cpustate->ebp = 0; // for make sure there will be no problem 
    tasks[currentTask]->cpustate->eflags = 0x202;

    return 0;
}


