	.file	"pipeit.c"
	.section	.rodata
.LC0:
	.string	"Error\n"
.LC1:
	.string	"ls"
.LC2:
	.string	"outfile"
.LC3:
	.string	"-r"
.LC4:
	.string	"sort"
.LC5:
	.string	"Error"
	.text
.globl PipeIt
	.type	PipeIt, @function
PipeIt:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	pipe
	movl	$0, -12(%rbp)
	jmp	.L2
.L7:
	call	fork
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jns	.L3
	movq	stderr(%rip), %rax
	movq	%rax, %rdx
	movl	$.LC0, %eax
	movq	%rdx, %rcx
	movl	$6, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite
	jmp	.L4
.L3:
	cmpl	$0, -4(%rbp)
	je	.L5
	cmpl	$0, -12(%rbp)
	je	.L4
	movl	-64(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	-60(%rbp), %eax
	movl	%eax, %edi
	call	close
	jmp	.L4
.L5:
	cmpl	$0, -12(%rbp)
	jne	.L6
	movl	-64(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	-60(%rbp), %eax
	movl	$1, %esi
	movl	%eax, %edi
	call	dup2
	movl	-60(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	$0, %edx
	movl	$.LC1, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	execlp
	jmp	.L4
.L6:
	movl	-60(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	-64(%rbp), %eax
	movl	$0, %esi
	movl	%eax, %edi
	call	dup2
	movl	-64(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	$420, %edx
	movl	$577, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	open
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	$1, %esi
	movl	%eax, %edi
	call	dup2
	movl	-8(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	$0, %ecx
	movl	$.LC3, %edx
	movl	$.LC4, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	execlp
.L4:
	addl	$1, -12(%rbp)
.L2:
	cmpl	$1, -12(%rbp)
	jle	.L7
	movl	$0, -12(%rbp)
	jmp	.L8
.L9:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, %edx
	movq	%rax, %rdx
	movq	%rdx, %rdi
	call	wait
	addl	$1, -12(%rbp)
.L8:
	cmpl	$1, -12(%rbp)
	jle	.L9
	movl	-48(%rbp), %eax
	movl	$0, -32(%rbp)
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L10
	movl	-44(%rbp), %eax
	movl	$0, -16(%rbp)
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L10
	movl	$0, %edi
	call	exit
.L10:
	movl	$.LC5, %edi
	call	perror
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE0:
	.size	PipeIt, .-PipeIt
.globl main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	PipeIt
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-16)"
	.section	.note.GNU-stack,"",@progbits
