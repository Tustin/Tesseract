#define TOC							( 0x1C85330 )

int write_process(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	return_to_user_prog(int);
}

int32_t sys_dbg_write_process_memory(uint64_t ea, const void * data, uint32_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
void PatchInJump(uint64_t Address, int Destination, bool Linked)
{
	int FuncBytes[4];
	Destination = *(int*)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000) FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	if (Linked)
		FuncBytes[3] += 1;
	//memcpy((void*)Address, FuncBytes, 4 * 4); Use for cex
	write_process((void*)Address, FuncBytes, 4 * 4);
}
void HookFunctionStart(int Address, int saveStub, int Destination, int addr_type)
{
	saveStub = *(int*)saveStub;
	int BranchtoAddress = Address + (4 * 4);
	int StubData[8];
	StubData[0] = 0x3D600000 + ((BranchtoAddress >> 16) & 0xFFFF);
	if (BranchtoAddress & 0x8000) StubData[0] += 1;
	StubData[1] = 0x396B0000 + (BranchtoAddress & 0xFFFF);
	StubData[2] = 0x7D6903A6;
	write_process(&StubData[3], (void*)Address, 4 * 4);
	StubData[7] = 0x4E800420;
	write_process((void*)saveStub, StubData, 8 * 4);
	PatchInJump(Address, Destination, false);
}
void HookNative(int native, int dest)
{
	int FuncBytes[1];
	FuncBytes[0] = *(int*)dest;
	_sys_memcpy((void*)native, FuncBytes, 4);
}
void is_player_online()
{
	__asm("li %r3, 0x3");
}

int sys_ppu_thread_exit()
{
	system_call_1(41, 0);
	return_to_user_prog(int);
}

sys_ppu_thread_t id;
sys_ppu_thread_t create_thread(void(*entry)(uint64_t), int priority, size_t stacksize, const char* threadname)
{
	if (sys_ppu_thread_create(&id, entry, 0, priority, stacksize, 0, threadname) != CELL_OK)
	{
	}
	else
	{
	}
	return id;
}

void Sleep(usecond_t time)  //1 second = 1000
{
	sys_timer_usleep(time * 1000);
}