#include <inc/lib.h>
#define num_of_pages  (USER_HEAP_MAX - USER_HEAP_START) / PAGE_SIZE
struct heapinfo {
	uint32 va;
	int si;
	int ind;
};

int itrate = 0;
struct heapinfo pages[num_of_pages];
bool status_of_page[num_of_pages] = { 0 };



void* find_add(uint32 req_pages);
void* malloc(uint32 size) {
	uint32* target_address;
	target_address = find_add(size);
	if (target_address != NULL){
		sys_allocateMem((uint32) target_address, size);
			  itrate++;
	}
		return (void*) target_address;
}




//Best Fit
void* find_add(uint32 req_pages) {
int number_of_pages = (USER_HEAP_MAX - USER_HEAP_START) / PAGE_SIZE;
	req_pages = ROUNDUP(req_pages, PAGE_SIZE);
	req_pages/= PAGE_SIZE;
	uint32 c = 0, start_index = 0, min = 1000000, isempty = 1,target_index = 0;
	for (int i = 0; i < number_of_pages; i++) {
		if (status_of_page[i] == 0 )
			if(status_of_page[i - 1] == 1)
			start_index = i;
		if (status_of_page[i] == 0)
			c++;
		else if (status_of_page[i] == 1) {
			if (c < min && c >= req_pages) {
				target_index = start_index;
				min = c;
				isempty = 0;
			}
			c = 0;
		}
		if (isempty&&c<min&&c==req_pages) {
			int j;
			for ( j = i; j < number_of_pages; j++) {
				if (status_of_page[j] == 1) {
					break;
				}
			}
			if (j==number_of_pages) {
				target_index = start_index;
				isempty = 0;
				break;
			}
		}
	}
	if (isempty==0) {
		for (int i = 0; i < req_pages; i++) {
			status_of_page[i + target_index] = 1;
		}
		pages[itrate].ind=target_index;
		pages[itrate].si = req_pages*PAGE_SIZE;
		pages[itrate].va = (target_index* PAGE_SIZE) + USER_HEAP_START;
		return (void*) pages[itrate].va;
	}
	return NULL;
}










void free(void* virtual_address) {
	for (int i = 0; i < itrate; i++) {
		if (pages[i].va == (uint32) virtual_address) {
			int siz = ROUNDUP(pages[i].si, PAGE_SIZE) / PAGE_SIZE;
			sys_freeMem((uint32) virtual_address,pages[i].si);
			pages[i].va =pages[itrate - 1].va;
			pages[i].si =pages[itrate - 1].si;
			itrate--;
			for (int i = 0; i < siz; i++) {
				int indx=i +((uint32) virtual_address - USER_HEAP_START) / PAGE_SIZE;
				status_of_page[indx] = 0;
			}
			return;
		}
	}


}
//==================================================================================//
//================================ OTHER FUNCTIONS =================================//
//==================================================================================//

void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable) {
	panic("this function is not required...!!");
	return 0;
}

void* sget(int32 ownerEnvID, char *sharedVarName) {
	panic("this function is not required...!!");
	return 0;
}

void sfree(void* virtual_address) {
	panic("this function is not required...!!");
}

void *realloc(void *virtual_address, uint32 new_size) {
	panic("this function is not required...!!");
	return 0;
}

void expand(uint32 newSize) {
	panic("this function is not required...!!");
}
void shrink(uint32 newSize) {
	panic("this function is not required...!!");
}

void freeHeap(void* virtual_address) {
	panic("this function is not required...!!");
}
