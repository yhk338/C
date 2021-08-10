
        # LEAVE THIS PART ALONE
	.text
	.globl	add_array
	.def	add_array;	.scl	2;	.type	32;	.endef

	# See the declaration in add_array.h
	# This function takes two parameters:
	#   -- an array (i.e. a 64-bit pointer in the %rcx register)
	#   -- the size of the array (i.e. a 32-bit integer in
	#      the %edx register.
	# It returns the sum of the elements of the array. The return
	# value, being 32 bits, must be placed in the %eax register.

add_array:

	# Note: You can overwrite the 64-bit registers %rax, %rcx, %rdx, %r8,
	# %r9, %r10, %r11 (as well as their 32-bit halves, %eax, %ecx,
	# %edx, %r8d, %r9d, %r10d, %r11d) as you like. These are the
	# "caller-saved" registers.

	# hint: to access a[i], use scaled indexed addressing
	# mode: "(base_reg,index_reg,scale)" -- see page 180 of Bryant & O'Hallaron
	# If the base_reg is a 64-bit register (e.g. %rcx holding the address of
	# the array), then the index_reg (e.g. holding i) must also be a 64-bit
	# register.

	pushq	%rbp		# LEAVE THIS ALONE
	movq	%rsp, %rbp	# LEAVE THIS ALONE

	movl $0, %eax  # sum = 0
	movq $0, %r8  # i = 0 (use a 64-bit register, see hint above)

/* THIS IS THE TOP OF THE LOOP, NEED A LABEL */
TOP:
	cmpl %edx, %r8d  # compare i to size
	jge DONE          #  if i is not less than size, jump out of loop

	addl (%rcx, %r8, 4), %eax  # sum += a[i]
	incq %r8  # i++
	jmp TOP  # jump to top of loop

/* THIS IS OUTSIDE THE LOOP, NEED A LABEL */
DONE:
	/* Make sure result is in %eax */

	popq	%rbp	# LEAVE THIS ALONE
	retq		# LEAVE THIS ALONE
