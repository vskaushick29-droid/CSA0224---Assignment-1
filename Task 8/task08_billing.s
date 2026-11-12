	.file	"task08_billing.c"
	.text
	.type	consumption, @function
consumption:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -4(%rbp)
	movw	%ax, -8(%rbp)
	movzwl	-8(%rbp), %eax
	subw	-4(%rbp), %ax
	movzwl	%ax, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	consumption, .-consumption
	.type	compute_bill, @function
compute_bill:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	$0, -8(%rbp)
	cmpl	$100, -20(%rbp)
	jbe	.L4
	movl	-20(%rbp), %eax
	subl	$100, %eax
	movl	%eax, -12(%rbp)
	cmpl	$100, -12(%rbp)
	jbe	.L5
	movl	$100, -12(%rbp)
.L5:
	movl	-12(%rbp), %eax
	imulq	$225, %rax, %rax
	addq	%rax, -8(%rbp)
.L4:
	cmpl	$200, -20(%rbp)
	jbe	.L6
	movl	-20(%rbp), %eax
	subl	$200, %eax
	movl	%eax, %eax
	imulq	$450, %rax, %rax
	addq	%rax, -8(%rbp)
.L6:
	movq	-8(%rbp), %rax
	addq	$5000, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	compute_bill, .-compute_bill
	.section	.rodata
.LC0:
	.string	"Previous reading : %u\n"
.LC1:
	.string	"Current reading  : %u\n"
.LC2:
	.string	"Units consumed   : %u\n"
	.align 8
.LC3:
	.string	"Total bill       : Rs %lld.%02lld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movw	$-136, -2(%rbp)
	movw	$120, -4(%rbp)
	movzwl	-4(%rbp), %edx
	movzwl	-2(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	consumption
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %edi
	call	compute_bill
	movq	%rax, -16(%rbp)
	movzwl	-2(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movzwl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rcx
	movabsq	$-6640827866535438581, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	leaq	(%rdx,%rcx), %rax
	sarq	$6, %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	movq	%rdx, %rsi
	subq	%rax, %rsi
	movq	%rsi, %rax
	salq	$2, %rax
	addq	%rsi, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	subq	%rax, %rcx
	movq	%rcx, %rsi
	movq	-16(%rbp), %rcx
	movabsq	$-6640827866535438581, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	leaq	(%rdx,%rcx), %rax
	sarq	$6, %rax
	sarq	$63, %rcx
	movq	%rcx, %rdx
	subq	%rdx, %rax
	movq	%rsi, %rdx
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
