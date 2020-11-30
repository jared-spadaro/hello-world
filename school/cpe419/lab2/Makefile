CC = nvcc
CFLAGS = -x cu -Xcompiler -rdynamic -lineinfo -Wno-deprecated-gpu-targets

mult: mult.cu 
	@$(CC) $(CFLAGS) -o mult mult.cu

create: create.c
	@$(CC) -Wno-deprecated-gpu-targets -o create create.c

clean:
	@rm -f hello mult matrix1 matrix2
