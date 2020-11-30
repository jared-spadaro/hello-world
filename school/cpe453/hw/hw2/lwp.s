	.file	"lwp.c"
	.local	global_tid
	.comm	global_tid,8,8
	.local	global_head
	.comm	global_head,8,8
	.local	global_current
	.comm	global_current,8,8
	.local	global_maincontext
	.comm	global_maincontext,8,8
	.local	global_safestack
	.comm	global_safestack,8,8
	.data
	.align 32
	.type	rr_publish, @object
	.size	rr_publish, 40
rr_publish:
	.quad	0
	.quad	0
	.quad	rr_admit
	.quad	rr_remove
	.quad	rr_next
	.local	global_current_scheduler
	.comm	global_current_scheduler,8,8
	.section	.rodata
.LC0:
	.string	"goto start"
	.text
.globl goto_start
	.type	goto_start, @function
goto_start:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$.LC0, %edi
	call	puts
	movq	global_current(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	movq	680(%rax), %rax
	movq	%rax, -8(%rbp)
.L2:
	movq	-8(%rbp), %rax
	movq	680(%rax), %rax
	testq	%rax, %rax
	jne	.L3
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	goto_start, .-goto_start
	.section	.rodata
.LC1:
	.string	"admitting thread"
	.text
.globl rr_admit
	.type	rr_admit, @function
rr_admit:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$.LC1, %edi
	call	puts
	movq	global_head(%rip), %rax
	testq	%rax, %rax
	jne	.L6
	movq	-8(%rbp), %rax
	movq	$0, 672(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 680(%rax)
	jmp	.L7
.L6:
	movq	global_head(%rip), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 672(%rax)
	movq	global_head(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 680(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 672(%rax)
.L7:
	movq	-8(%rbp), %rax
	movq	%rax, global_head(%rip)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	rr_admit, .-rr_admit
	.section	.rodata
.LC2:
	.string	"removing thread"
	.text
.globl rr_remove
	.type	rr_remove, @function
rr_remove:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$.LC2, %edi
	call	puts
	movq	-8(%rbp), %rax
	movq	672(%rax), %rax
	testq	%rax, %rax
	je	.L10
	movq	-8(%rbp), %rax
	movq	680(%rax), %rax
	testq	%rax, %rax
	je	.L10
	movq	-8(%rbp), %rax
	movq	680(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	672(%rdx), %rdx
	movq	%rdx, 672(%rax)
	movq	-8(%rbp), %rax
	movq	672(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	680(%rdx), %rdx
	movq	%rdx, 680(%rax)
	jmp	.L13
.L10:
	movq	-8(%rbp), %rax
	movq	672(%rax), %rax
	testq	%rax, %rax
	je	.L12
	movq	-8(%rbp), %rax
	movq	672(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	680(%rdx), %rdx
	movq	%rdx, 680(%rax)
	jmp	.L13
.L12:
	movq	-8(%rbp), %rax
	movq	680(%rax), %rax
	testq	%rax, %rax
	je	.L13
	movq	-8(%rbp), %rax
	movq	680(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	672(%rdx), %rdx
	movq	%rdx, 672(%rax)
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	rr_remove, .-rr_remove
.globl rr_next
	.type	rr_next, @function
rr_next:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	global_current(%rip), %rax
	movq	680(%rax), %rax
	testq	%rax, %rax
	jne	.L15
	movq	global_current(%rip), %rax
	movq	%rax, -16(%rbp)
	jmp	.L16
.L15:
	movq	global_current(%rip), %rax
	movq	672(%rax), %rax
	movq	%rax, -8(%rbp)
.L16:
	cmpq	$0, -16(%rbp)
	jne	.L17
	movl	$0, %eax
	call	goto_start
	movq	%rax, -16(%rbp)
.L17:
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	rr_next, .-rr_next
	.section	.rodata
.LC3:
	.string	"creating thread"
.LC4:
	.string	"location of lwpfun = %lu\n"
.LC5:
	.string	"location of lwp_exit = %lu\n"
.LC6:
	.string	"location of stack = %lu\n"
.LC7:
	.string	"end of stack = %lu\n"
	.text
.globl lwp_create
	.type	lwp_create, @function
lwp_create:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$568, %rsp
	movq	%rdi, -552(%rbp)
	movq	%rsi, -560(%rbp)
	movq	%rdx, -568(%rbp)
	movl	$.LC3, %edi
	.cfi_offset 3, -24
	call	puts
	movl	$704, %edi
	call	malloc
	movq	%rax, -32(%rbp)
	movq	global_current_scheduler(%rip), %rax
	testq	%rax, %rax
	jne	.L20
	movq	$rr_publish, global_current_scheduler(%rip)
.L20:
	movq	global_current_scheduler(%rip), %rax
	movq	16(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
	movq	global_current(%rip), %rax
	testq	%rax, %rax
	jne	.L21
	movq	-32(%rbp), %rax
	movq	%rax, global_current(%rip)
.L21:
	movq	global_tid(%rip), %rax
	addq	$1, %rax
	movq	%rax, global_tid(%rip)
	movq	global_tid(%rip), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-568(%rbp), %rax
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-32(%rbp), %rax
	movq	-568(%rbp), %rdx
	movq	%rdx, 16(%rax)
	leaq	-544(%rbp), %rbx
	movl	$0, %eax
	movl	$64, %edx
	movq	%rbx, %rdi
	movq	%rdx, %rcx
	rep stosq
	movb	$127, -544(%rbp)
	movb	$3, -543(%rbp)
	movb	$-128, -520(%rbp)
	movb	$31, -519(%rbp)
	movb	$-1, -516(%rbp)
	movb	$-1, -515(%rbp)
	movb	$37, -368(%rbp)
	movb	$37, -367(%rbp)
	movb	$37, -366(%rbp)
	movb	$37, -365(%rbp)
	movb	$37, -364(%rbp)
	movb	$37, -363(%rbp)
	movb	$37, -362(%rbp)
	movb	$37, -361(%rbp)
	movb	$37, -360(%rbp)
	movb	$37, -359(%rbp)
	movb	$37, -358(%rbp)
	movb	$37, -357(%rbp)
	movb	$37, -356(%rbp)
	movb	$37, -355(%rbp)
	movb	$37, -354(%rbp)
	movb	$37, -353(%rbp)
	movb	$-1, -328(%rbp)
	movb	$-1, -323(%rbp)
	movq	-32(%rbp), %rax
	leaq	160(%rax), %rbx
	leaq	-544(%rbp), %rdx
	movl	$64, %eax
	movq	%rbx, %rdi
	movq	%rdx, %rsi
	movq	%rax, %rcx
	rep movsq
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	-568(%rbp), %rdx
	subq	$2, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movq	-552(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, 88(%rax)
	addq	$8, -24(%rbp)
	movl	$lwp_exit, %edx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-560(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, 72(%rax)
	movq	-552(%rbp), %rdx
	movl	$.LC4, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$lwp_exit, %edx
	movl	$.LC5, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdx
	movl	$.LC6, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-32(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	salq	$3, %rax
	leaq	(%rdx,%rax), %rax
	movq	%rax, %rdx
	movl	$.LC7, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addq	$568, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	lwp_create, .-lwp_create
.globl freeThread
	.type	freeThread, @function
freeThread:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	global_current_scheduler(%rip), %rax
	movq	32(%rax), %rax
	call	*%rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L24
	call	lwp_stop
.L24:
	movq	global_current_scheduler(%rip), %rax
	movq	24(%rax), %rdx
	movq	global_current(%rip), %rax
	movq	%rax, %rdi
	call	*%rdx
	movq	global_current(%rip), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	free
	movq	global_current(%rip), %rax
	movq	%rax, %rdi
	call	free
	movq	-8(%rbp), %rax
	movq	%rax, global_current(%rip)
	movq	global_current(%rip), %rax
	addq	$32, %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	swap_rfiles
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	freeThread, .-freeThread
	.section	.rodata
.LC8:
	.string	"exiting thread"
	.text
.globl lwp_exit
	.type	lwp_exit, @function
lwp_exit:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC8, %edi
	call	puts
	movq	global_safestack(%rip), %rax
	testq	%rax, %rax
	jne	.L27
	movl	$1024, %edi
	call	malloc
	movq	%rax, global_safestack(%rip)
.L27:
	movq	global_safestack(%rip), %rax
	addq	$1024, %rax
#APP
# 167 "lwp.c" 1
	movq  %rax,%rsp
# 0 "" 2
#NO_APP
	movl	$0, %eax
	call	freeThread
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	lwp_exit, .-lwp_exit
	.section	.rodata
.LC9:
	.string	"getting current tid"
	.text
.globl lwp_gettid
	.type	lwp_gettid, @function
lwp_gettid:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC9, %edi
	call	puts
	movq	global_current(%rip), %rax
	movq	(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	lwp_gettid, .-lwp_gettid
	.section	.rodata
.LC10:
	.string	"yielding thread"
	.text
.globl lwp_yield
	.type	lwp_yield, @function
lwp_yield:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$.LC10, %edi
	call	puts
	movq	global_current(%rip), %rax
	addq	$32, %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	swap_rfiles
	movq	global_current_scheduler(%rip), %rax
	movq	32(%rax), %rax
	call	*%rax
	movq	%rax, global_current(%rip)
	movq	global_current(%rip), %rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L32
	call	lwp_stop
.L32:
	movq	-8(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	swap_rfiles
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	lwp_yield, .-lwp_yield
	.section	.rodata
.LC11:
	.string	"starting lwp system"
.LC12:
	.string	"rsp = %lu\n"
.LC13:
	.string	"rdi = %lu\n"
.LC14:
	.string	"rsp value = %lu\n"
.LC15:
	.string	"(one below rsp) value = %lu\n"
	.text
.globl lwp_start
	.type	lwp_start, @function
lwp_start:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$.LC11, %edi
	call	puts
	movq	global_maincontext(%rip), %rax
	testq	%rax, %rax
	jne	.L35
	movl	$704, %edi
	call	malloc
	movq	%rax, global_maincontext(%rip)
.L35:
	movq	global_current_scheduler(%rip), %rax
	testq	%rax, %rax
	jne	.L36
	movq	$rr_publish, global_current_scheduler(%rip)
.L36:
	movq	global_current_scheduler(%rip), %rax
	movq	32(%rax), %rax
	call	*%rax
	movq	%rax, global_current(%rip)
	movq	global_current(%rip), %rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L37
	movq	global_maincontext(%rip), %rax
	addq	$32, %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	swap_rfiles
	call	lwp_stop
.L37:
	movq	-8(%rbp), %rax
	movq	88(%rax), %rdx
	movl	$.LC12, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rax
	movq	72(%rax), %rdx
	movl	$.LC13, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	subq	$2, %rax
	salq	$3, %rax
	leaq	(%rdx,%rax), %rax
	movq	(%rax), %rdx
	movl	$.LC14, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	subq	$1, %rax
	salq	$3, %rax
	leaq	(%rdx,%rax), %rax
	movq	(%rax), %rdx
	movl	$.LC15, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	global_maincontext(%rip), %rax
	addq	$32, %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	swap_rfiles
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	lwp_start, .-lwp_start
	.section	.rodata
.LC16:
	.string	"stopping lwp system"
	.text
.globl lwp_stop
	.type	lwp_stop, @function
lwp_stop:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC16, %edi
	call	puts
	movq	global_maincontext(%rip), %rax
	addq	$32, %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	swap_rfiles
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	lwp_stop, .-lwp_stop
	.section	.rodata
.LC17:
	.string	"setting scheduler"
	.text
.globl lwp_set_scheduler
	.type	lwp_set_scheduler, @function
lwp_set_scheduler:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$.LC17, %edi
	call	puts
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L42
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	call	*%rax
.L42:
	movl	$0, %eax
	call	goto_start
	movq	%rax, -8(%rbp)
	jmp	.L43
.L44:
	movq	-24(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
	movq	global_current_scheduler(%rip), %rax
	movq	24(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
	movq	-8(%rbp), %rax
	movq	672(%rax), %rax
	movq	%rax, -8(%rbp)
.L43:
	movq	-8(%rbp), %rax
	movq	672(%rax), %rax
	testq	%rax, %rax
	jne	.L44
	movq	global_current_scheduler(%rip), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L45
	movq	global_current_scheduler(%rip), %rax
	movq	8(%rax), %rax
	call	*%rax
.L45:
	movq	-24(%rbp), %rax
	movq	%rax, global_current_scheduler(%rip)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	lwp_set_scheduler, .-lwp_set_scheduler
	.section	.rodata
.LC18:
	.string	"getting scheduler"
	.text
.globl lwp_get_scheduler
	.type	lwp_get_scheduler, @function
lwp_get_scheduler:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC18, %edi
	call	puts
	movq	global_current_scheduler(%rip), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	lwp_get_scheduler, .-lwp_get_scheduler
	.section	.rodata
.LC19:
	.string	"running tid2thread"
	.text
.globl lwp_tid2thread
	.type	lwp_tid2thread, @function
lwp_tid2thread:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$.LC19, %edi
	call	puts
	movq	global_head(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L50
.L53:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	-24(%rbp), %rax
	jne	.L51
	movq	-8(%rbp), %rax
	jmp	.L52
.L51:
	movq	-8(%rbp), %rax
	movq	680(%rax), %rax
	movq	%rax, -8(%rbp)
.L50:
	movq	-8(%rbp), %rax
	movq	680(%rax), %rax
	testq	%rax, %rax
	jne	.L53
	movl	$0, %eax
.L52:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	lwp_tid2thread, .-lwp_tid2thread
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-16)"
	.section	.note.GNU-stack,"",@progbits
