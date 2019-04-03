	.file	"User1.cpp"
	.intel_syntax noprefix
	.text
	.globl	_ZN4LoveIjE1xE
	.data
	.align 4
	.type	_ZN4LoveIjE1xE, @object
	.size	_ZN4LoveIjE1xE, 4
_ZN4LoveIjE1xE:
	.long	1068827777
	.text
	.globl	_Z5User1v
	.type	_Z5User1v, @function
_Z5User1v:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	movss	xmm0, DWORD PTR _ZN4LoveIjE1xE[rip]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z5User1v, .-_Z5User1v
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
