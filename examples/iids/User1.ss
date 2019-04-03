	.file	"User1.cpp"
	.intel_syntax noprefix
	.text
	.globl	Love<unsigned int>::x
	.data
	.align 4
	.type	Love<unsigned int>::x, @object
	.size	Love<unsigned int>::x, 4
Love<unsigned int>::x:
	.long	1068827777
	.text
	.globl	User1()
	.type	User1(), @function
User1():
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	movss	xmm0, DWORD PTR Love<unsigned int>::x[rip]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	User1(), .-User1()
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
