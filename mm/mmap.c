// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	void *result = (void *)syscall(9, addr, length, prot, flags, fd, offset);
	if(result < 0){
		return MAP_FAILED;
	}
	return result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	/* TODO: Implement mremap(). */
	void *result = (void *)syscall(25, old_address, old_size, new_size, flags);
	if(result < 0){
		return MAP_FAILED;
	}
	return result;
}

int munmap(void *addr, size_t length)
{
	/* TODO: Implement munmap(). */
	int result = syscall(11, addr, length);
	if(result < 0){
		errno = -result;
		return -1;
	}
	return 0;
}
