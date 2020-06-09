	.arch armv7-a
	.eabi_attribute 27, 3
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"glserver.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.rodata
	.align	2
	.type	in6addr_any, %object
	.size	in6addr_any, 16
in6addr_any:
	.space	16
	.align	2
	.type	in6addr_loopback, %object
	.size	in6addr_loopback, 16
in6addr_loopback:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.section	.text.next_ptr,"ax",%progbits
	.align	2
	.type	next_ptr, %function
next_ptr:
	.fnstart
.LFB3:
	.file 1 "jni/../../gl_server/../common/gls_command.h"
	.loc 1 853 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	.save {fp}
	.cfi_def_cfa_offset 4
	.cfi_offset 11, -4
	.setfp fp, sp, #0
	add	fp, sp, #0
	.cfi_def_cfa_register 11
	.pad #28
	sub	sp, sp, #28
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	.loc 1 854 0
	ldr	r3, [fp, #-24]
	mov	r2, #1
	mov	r3, r2, asl r3
	sub	r3, r3, #1
	str	r3, [fp, #-8]
	.loc 1 855 0
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-20]
	add	r2, r2, r3
	ldr	r3, [fp, #-8]
	add	r2, r2, r3
	ldr	r3, [fp, #-8]
	mvn	r3, r3
	and	r3, r3, r2
	.loc 1 856 0
	mov	r0, r3
	sub	sp, fp, #0
	.cfi_def_cfa_register 13
	@ sp needed
	ldr	fp, [sp], #4
	.cfi_restore 11
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE3:
	.fnend
	.size	next_ptr, .-next_ptr
	.section	.text.gls_sleep,"ax",%progbits
	.align	2
	.type	gls_sleep, %function
gls_sleep:
	.fnstart
.LFB4:
	.loc 1 860 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #16
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	.loc 1 862 0
	ldr	r3, [fp, #-16]
	fmsr	s15, r3	@ int
	fuitos	s15, s15
	flds	s14, .L4
	fdivs	s15, s14, s15
	fconsts	s14, #112
	fadds	s15, s15, s14
	ftouizs	s15, s15
	fmrs	r3, s15	@ int
	str	r3, [fp, #-8]
	.loc 1 863 0
	ldr	r0, [fp, #-8]
	bl	usleep(PLT)
	.loc 1 864 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L5:
	.align	2
.L4:
	.word	1177735262
	.cfi_endproc
.LFE4:
	.fnend
	.size	gls_sleep, .-gls_sleep
	.comm	glsurfaceview_width,4,4
	.comm	glsurfaceview_height,4,4
	.comm	jstrclient_addr,4,4
	.comm	var_server_port,4,4
	.comm	var_client_port,4,4
	.comm	var_client_addr,4,4
	.comm	glsurfaceview_window,4,4
	.section	.text.fifo_pop_ptr_get,"ax",%progbits
	.align	2
	.type	fifo_pop_ptr_get, %function
fifo_pop_ptr_get:
	.fnstart
.LFB7:
	.file 2 "jni/../../gl_server/../common/fifo.h"
	.loc 2 65 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	.save {fp}
	.cfi_def_cfa_offset 4
	.cfi_offset 11, -4
	.setfp fp, sp, #0
	add	fp, sp, #0
	.cfi_def_cfa_register 11
	.pad #12
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	.loc 2 66 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	bne	.L7
	.loc 2 68 0
	mov	r3, #0
	b	.L8
.L7:
	.loc 2 70 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r1, r3
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #20]
	mul	r3, r3, r1
	add	r3, r2, r3
.L8:
	.loc 2 71 0
	mov	r0, r3
	sub	sp, fp, #0
	.cfi_def_cfa_register 13
	@ sp needed
	ldr	fp, [sp], #4
	.cfi_restore 11
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE7:
	.fnend
	.size	fifo_pop_ptr_get, .-fifo_pop_ptr_get
	.section	.text.fifo_pop_ptr_next,"ax",%progbits
	.align	2
	.type	fifo_pop_ptr_next, %function
fifo_pop_ptr_next:
	.fnstart
.LFB8:
	.loc 2 74 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	.save {fp}
	.cfi_def_cfa_offset 4
	.cfi_offset 11, -4
	.setfp fp, sp, #0
	add	fp, sp, #0
	.cfi_def_cfa_register 11
	.pad #20
	sub	sp, sp, #20
	str	r0, [fp, #-16]
	.loc 2 75 0
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #8]
	add	r3, r3, #1
	mov	r2, r3
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #16]
	sub	r3, r3, #1
	and	r3, r3, r2
	str	r3, [fp, #-8]
	.loc 2 76 0
	ldr	r3, [fp, #-16]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	beq	.L9
	.loc 2 78 0
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-8]
	str	r2, [r3, #8]
.L9:
	.loc 2 80 0
	sub	sp, fp, #0
	.cfi_def_cfa_register 13
	@ sp needed
	ldr	fp, [sp], #4
	.cfi_restore 11
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE8:
	.fnend
	.size	fifo_pop_ptr_next, .-fifo_pop_ptr_next
	.comm	glsec_global,36,4
	.section	.text.pop_batch_command,"ax",%progbits
	.align	2
	.type	pop_batch_command, %function
pop_batch_command:
	.fnstart
.LFB9:
	.file 3 "jni/../../gl_server/glserver.c"
	.loc 3 55 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	str	r0, [fp, #-16]
	ldr	r4, .L12
.LPIC0:
	add	r4, pc, r4
	.loc 3 56 0
	ldr	r3, .L12+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #8]
	mov	r0, r3
	ldr	r1, [fp, #-16]
	mov	r2, #3
	bl	next_ptr(PLT)
	mov	r2, r0
	ldr	r3, .L12+4
	ldr	r3, [r4, r3]
	str	r2, [r3, #8]
	.loc 3 57 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L13:
	.align	2
.L12:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC0+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE9:
	.fnend
	.size	pop_batch_command, .-pop_batch_command
	.section	.text.send_packet,"ax",%progbits
	.align	2
	.global	send_packet
	.type	send_packet, %function
send_packet:
	.fnstart
.LFB10:
	.loc 3 61 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #24
	sub	sp, sp, #24
	str	r0, [fp, #-16]
	ldr	r3, .L17
.LPIC1:
	add	r3, pc, r3
	.loc 3 62 0
	ldr	r2, .L17+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #24]
	str	r2, [fp, #-8]
	.loc 3 63 0
	ldr	r2, [fp, #-8]
	ldr	r1, [r2, #16]
	ldr	r2, .L17+4
	ldr	r3, [r3, r2]
	ldr	r2, [r3, #12]
	ldr	r3, [fp, #-8]
	str	r3, [sp]
	mov	r3, #16
	str	r3, [sp, #4]
	mov	r0, r1
	mov	r1, r2
	ldr	r2, [fp, #-16]
	mov	r3, #0
	bl	sendto(PLT)
	mov	r3, r0
	cmn	r3, #1
	bne	.L15
	.loc 3 65 0
	mov	r3, #0
	b	.L16
.L15:
	.loc 3 67 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #292]
	mov	r0, r3
	ldr	r1, [fp, #-16]
	bl	gls_sleep(PLT)
	.loc 3 68 0
	mov	r3, #1
.L16:
	.loc 3 69 0
	mov	r0, r3
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L18:
	.align	2
.L17:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC1+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE10:
	.fnend
	.size	send_packet, .-send_packet
	.section	.text.glse_cmd_send_data,"ax",%progbits
	.align	2
	.global	glse_cmd_send_data
	.type	glse_cmd_send_data, %function
glse_cmd_send_data:
	.fnstart
.LFB11:
	.loc 3 73 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #48
	sub	sp, sp, #48
	str	r0, [fp, #-40]
	str	r1, [fp, #-44]
	str	r2, [fp, #-48]
	ldr	r2, .L24
.LPIC2:
	add	r2, pc, r2
	.loc 3 74 0
	ldr	r3, .L24+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #12]
	str	r3, [fp, #-20]
	.loc 3 75 0
	ldr	r3, [fp, #-20]
	mov	r2, #2
	str	r2, [r3]
	.loc 3 77 0
	mov	r3, #1
	str	r3, [fp, #-32]
	.loc 3 78 0
	mov	r3, #1424
	str	r3, [fp, #-16]
	.loc 3 79 0
	ldr	r3, [fp, #-48]
	str	r3, [fp, #-28]
	.loc 3 81 0
	mov	r3, #0
	str	r3, [fp, #-24]
	b	.L20
.L22:
.LBB2:
	.loc 3 83 0
	ldr	r2, [fp, #-44]
	ldr	r3, [fp, #-24]
	rsb	r3, r3, r2
	str	r3, [fp, #-12]
	.loc 3 84 0
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-16]
	cmp	r2, r3
	movls	r3, #1
	movhi	r3, #0
	uxtb	r3, r3
	mov	r2, r3
	ldr	r3, [fp, #-20]
	str	r2, [r3, #12]
	.loc 3 85 0
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-16]
	cmp	r2, r3
	movcc	r3, r2
	movcs	r3, r3
	str	r3, [fp, #-12]
	.loc 3 86 0
	ldr	r3, [fp, #-20]
	add	r3, r3, #16
	mov	r0, r3
	ldr	r1, [fp, #-28]
	ldr	r2, [fp, #-12]
	bl	memcpy(PLT)
	.loc 3 87 0
	ldr	r3, [fp, #-12]
	add	r3, r3, #16
	ldr	r2, [fp, #-20]
	add	r3, r2, r3
	mov	r2, r3
	ldr	r3, [fp, #-20]
	rsb	r3, r3, r2
	str	r3, [fp, #-8]
	.loc 3 88 0
	ldr	r2, [fp, #-40]
	ldr	r3, [fp, #-24]
	add	r2, r2, r3
	ldr	r3, [fp, #-20]
	str	r2, [r3, #4]
	.loc 3 89 0
	ldr	r3, [fp, #-20]
	ldr	r2, [fp, #-12]
	str	r2, [r3, #8]
	.loc 3 90 0
	ldr	r0, [fp, #-8]
	bl	send_packet(PLT)
	mov	r3, r0
	cmp	r3, #0
	bne	.L21
	.loc 3 92 0
	mov	r3, #0
	str	r3, [fp, #-32]
.L21:
	.loc 3 94 0
	ldr	r2, [fp, #-28]
	ldr	r3, [fp, #-16]
	add	r3, r2, r3
	str	r3, [fp, #-28]
.LBE2:
	.loc 3 81 0 discriminator 2
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-16]
	add	r3, r2, r3
	str	r3, [fp, #-24]
.L20:
	.loc 3 81 0 is_stmt 0 discriminator 1
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-44]
	cmp	r2, r3
	bcc	.L22
	.loc 3 96 0 is_stmt 1
	ldr	r3, [fp, #-32]
	.loc 3 97 0
	mov	r0, r3
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L25:
	.align	2
.L24:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC2+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE11:
	.fnend
	.size	glse_cmd_send_data, .-glse_cmd_send_data
	.section	.text.glse_cmd_get_context,"ax",%progbits
	.align	2
	.global	glse_cmd_get_context
	.type	glse_cmd_get_context, %function
glse_cmd_get_context:
	.fnstart
.LFB12:
	.loc 3 101 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #16
	sub	sp, sp, #16
	ldr	r3, .L27
.LPIC3:
	add	r3, pc, r3
	.loc 3 102 0
	ldr	r2, .L27+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #32]
	str	r2, [fp, #-20]
	.loc 3 103 0
	ldr	r2, .L27+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #28]
	str	r2, [fp, #-16]
	.loc 3 105 0
	ldr	r2, .L27+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2]
	str	r2, [fp, #-12]
	.loc 3 106 0
	ldr	r2, [fp, #-20]
	ldr	r1, [r2]
	ldr	r2, [fp, #-12]
	str	r1, [r2]
	.loc 3 107 0
	ldr	r2, .L27+8
	ldr	r2, [r3, r2]
	ldr	r2, [r2]
	mov	r1, r2
	ldr	r2, [fp, #-16]
	str	r1, [r2]
	ldr	r2, [fp, #-16]
	ldr	r1, [r2]
	ldr	r2, [fp, #-12]
	str	r1, [r2, #8]
	.loc 3 108 0
	ldr	r2, .L27+12
	ldr	r2, [r3, r2]
	ldr	r2, [r2]
	mov	r1, r2
	ldr	r2, [fp, #-16]
	str	r1, [r2, #4]
	ldr	r2, [fp, #-16]
	ldr	r1, [r2, #4]
	ldr	r2, [fp, #-12]
	str	r1, [r2, #12]
	.loc 3 109 0
	ldr	r2, [fp, #-12]
	mov	r1, #7
	str	r1, [r2, #4]
	.loc 3 110 0
	mov	r2, #16
	str	r2, [fp, #-8]
	.loc 3 111 0
	ldr	r2, .L27+4
	ldr	r3, [r3, r2]
	ldr	r3, [r3]
	mov	r0, #0
	ldr	r1, [fp, #-8]
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 112 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L28:
	.align	2
.L27:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC3+8)
	.word	glsec_global(GOT)
	.word	glsurfaceview_width(GOT)
	.word	glsurfaceview_height(GOT)
	.cfi_endproc
.LFE12:
	.fnend
	.size	glse_cmd_get_context, .-glse_cmd_get_context
	.section	.text.glse_cmd_flip,"ax",%progbits
	.align	2
	.global	glse_cmd_flip
	.type	glse_cmd_flip, %function
glse_cmd_flip:
	.fnstart
.LFB13:
	.loc 3 116 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #20
	sub	sp, sp, #20
	ldr	r4, .L30
.LPIC4:
	add	r4, pc, r4
	.loc 3 117 0
	ldr	r3, .L30+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-28]
	.loc 3 118 0
	ldr	r3, .L30+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #28]
	str	r3, [fp, #-24]
	.loc 3 119 0
	ldr	r3, [fp, #-24]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-24]
	ldr	r3, [r3, #12]
	mov	r0, r2
	mov	r1, r3
	bl	eglSwapBuffers(PLT)
	.loc 3 121 0
	ldr	r3, .L30+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-20]
	.loc 3 122 0
	ldr	r3, [fp, #-28]
	ldr	r2, [r3]
	ldr	r3, [fp, #-20]
	str	r2, [r3]
	.loc 3 123 0
	ldr	r3, [fp, #-28]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-20]
	str	r2, [r3, #4]
	.loc 3 124 0
	mov	r3, #8
	str	r3, [fp, #-16]
	.loc 3 125 0
	ldr	r3, .L30+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	ldr	r1, [fp, #-16]
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 126 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L31:
	.align	2
.L30:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC4+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE13:
	.fnend
	.size	glse_cmd_flip, .-glse_cmd_flip
	.section	.text.glse_cmd_recv_data,"ax",%progbits
	.align	2
	.global	glse_cmd_recv_data
	.type	glse_cmd_recv_data, %function
glse_cmd_recv_data:
	.fnstart
.LFB14:
	.loc 3 130 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r3, .L36
.LPIC5:
	add	r3, pc, r3
	.loc 3 131 0
	ldr	r2, .L36+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #32]
	str	r2, [fp, #-8]
	.loc 3 132 0
	ldr	r2, [fp, #-8]
	ldr	r1, [r2, #4]
	ldr	r2, [fp, #-8]
	ldr	r2, [r2, #8]
	add	r1, r1, r2
	ldr	r2, .L36+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #4]
	cmp	r1, r2
	bhi	.L33
	.loc 3 132 0 is_stmt 0 discriminator 1
	ldr	r2, .L36+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #4]
	cmp	r2, #0
	bne	.L34
.L33:
	.loc 3 134 0 is_stmt 1
	mov	r3, #0
	b	.L35
.L34:
	.loc 3 136 0
	ldr	r2, .L36+4
	ldr	r3, [r3, r2]
	ldr	r2, [r3]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	add	r1, r2, r3
	ldr	r3, [fp, #-8]
	add	r2, r3, #16
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	memcpy(PLT)
	.loc 3 137 0
	mov	r3, #1
.L35:
	.loc 3 138 0
	mov	r0, r3
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L37:
	.align	2
.L36:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC5+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE14:
	.fnend
	.size	glse_cmd_recv_data, .-glse_cmd_recv_data
	.section	.text.glse_glBindBuffer,"ax",%progbits
	.align	2
	.global	glse_glBindBuffer
	.type	glse_glBindBuffer, %function
glse_glBindBuffer:
	.fnstart
.LFB15:
	.loc 3 142 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L39
.LPIC6:
	add	r2, pc, r2
	.loc 3 143 0
	ldr	r3, .L39+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 144 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r2
	mov	r1, r3
	bl	glBindBuffer(PLT)
	.loc 3 146 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L40:
	.align	2
.L39:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC6+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE15:
	.fnend
	.size	glse_glBindBuffer, .-glse_glBindBuffer
	.section	.text.glse_glBindTexture,"ax",%progbits
	.align	2
	.global	glse_glBindTexture
	.type	glse_glBindTexture, %function
glse_glBindTexture:
	.fnstart
.LFB16:
	.loc 3 150 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L42
.LPIC7:
	add	r2, pc, r2
	.loc 3 151 0
	ldr	r3, .L42+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 152 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r2
	mov	r1, r3
	bl	glBindTexture(PLT)
	.loc 3 154 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L43:
	.align	2
.L42:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC7+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE16:
	.fnend
	.size	glse_glBindTexture, .-glse_glBindTexture
	.section	.text.glse_glBlendEquationSeparate,"ax",%progbits
	.align	2
	.global	glse_glBlendEquationSeparate
	.type	glse_glBlendEquationSeparate, %function
glse_glBlendEquationSeparate:
	.fnstart
.LFB17:
	.loc 3 158 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L45
.LPIC8:
	add	r2, pc, r2
	.loc 3 159 0
	ldr	r3, .L45+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 160 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r2
	mov	r1, r3
	bl	glBlendEquationSeparate(PLT)
	.loc 3 162 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L46:
	.align	2
.L45:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC8+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE17:
	.fnend
	.size	glse_glBlendEquationSeparate, .-glse_glBlendEquationSeparate
	.section	.text.glse_glBlendFuncSeparate,"ax",%progbits
	.align	2
	.global	glse_glBlendFuncSeparate
	.type	glse_glBlendFuncSeparate, %function
glse_glBlendFuncSeparate:
	.fnstart
.LFB18:
	.loc 3 166 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L48
.LPIC9:
	add	r2, pc, r2
	.loc 3 167 0
	ldr	r3, .L48+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 168 0
	ldr	r3, [fp, #-8]
	ldr	r0, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #12]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #16]
	bl	glBlendFuncSeparate(PLT)
	.loc 3 170 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L49:
	.align	2
.L48:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC9+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE18:
	.fnend
	.size	glse_glBlendFuncSeparate, .-glse_glBlendFuncSeparate
	.section	.text.glse_glBufferData,"ax",%progbits
	.align	2
	.global	glse_glBufferData
	.type	glse_glBufferData, %function
glse_glBufferData:
	.fnstart
.LFB19:
	.loc 3 174 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r3, .L51
.LPIC10:
	add	r3, pc, r3
	.loc 3 175 0
	ldr	r2, .L51+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #32]
	str	r2, [fp, #-8]
	.loc 3 176 0
	ldr	r2, [fp, #-8]
	ldr	r0, [r2, #4]
	ldr	r2, [fp, #-8]
	ldr	r1, [r2, #8]
	ldr	r2, .L51+4
	ldr	r3, [r3, r2]
	ldr	r2, [r3]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	bl	glBufferData(PLT)
	.loc 3 178 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L52:
	.align	2
.L51:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC10+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE19:
	.fnend
	.size	glse_glBufferData, .-glse_glBufferData
	.section	.text.glse_glBufferSubData,"ax",%progbits
	.align	2
	.global	glse_glBufferSubData
	.type	glse_glBufferSubData, %function
glse_glBufferSubData:
	.fnstart
.LFB20:
	.loc 3 182 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r3, .L54
.LPIC11:
	add	r3, pc, r3
	.loc 3 183 0
	ldr	r2, .L54+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #32]
	str	r2, [fp, #-8]
	.loc 3 184 0
	ldr	r2, [fp, #-8]
	ldr	r0, [r2, #4]
	ldr	r2, [fp, #-8]
	ldr	r1, [r2, #8]
	ldr	r2, [fp, #-8]
	ldr	ip, [r2, #12]
	ldr	r2, .L54+4
	ldr	r3, [r3, r2]
	ldr	r3, [r3]
	mov	r2, ip
	bl	glBufferSubData(PLT)
	.loc 3 186 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L55:
	.align	2
.L54:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC11+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE20:
	.fnend
	.size	glse_glBufferSubData, .-glse_glBufferSubData
	.section	.text.glse_glClear,"ax",%progbits
	.align	2
	.global	glse_glClear
	.type	glse_glClear, %function
glse_glClear:
	.fnstart
.LFB21:
	.loc 3 190 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L57
.LPIC12:
	add	r2, pc, r2
	.loc 3 191 0
	ldr	r3, .L57+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 192 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glClear(PLT)
	.loc 3 194 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L58:
	.align	2
.L57:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC12+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE21:
	.fnend
	.size	glse_glClear, .-glse_glClear
	.section	.text.glse_glClearColor,"ax",%progbits
	.align	2
	.global	glse_glClearColor
	.type	glse_glClearColor, %function
glse_glClearColor:
	.fnstart
.LFB22:
	.loc 3 198 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L60
.LPIC13:
	add	r2, pc, r2
	.loc 3 199 0
	ldr	r3, .L60+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 200 0
	ldr	r3, [fp, #-8]
	ldr	r0, [r3, #4]	@ float
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #8]	@ float
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #12]	@ float
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #16]	@ float
	bl	glClearColor(PLT)
	.loc 3 202 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L61:
	.align	2
.L60:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC13+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE22:
	.fnend
	.size	glse_glClearColor, .-glse_glClearColor
	.section	.text.glse_glDeleteBuffers,"ax",%progbits
	.align	2
	.global	glse_glDeleteBuffers
	.type	glse_glDeleteBuffers, %function
glse_glDeleteBuffers:
	.fnstart
.LFB23:
	.loc 3 206 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r3, .L63
.LPIC14:
	add	r3, pc, r3
	.loc 3 207 0
	ldr	r2, .L63+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #32]
	str	r2, [fp, #-8]
	.loc 3 208 0
	ldr	r2, [fp, #-8]
	ldr	r1, [r2, #4]
	ldr	r2, .L63+4
	ldr	r3, [r3, r2]
	ldr	r3, [r3]
	mov	r0, r1
	mov	r1, r3
	bl	glDeleteBuffers(PLT)
	.loc 3 210 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L64:
	.align	2
.L63:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC14+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE23:
	.fnend
	.size	glse_glDeleteBuffers, .-glse_glDeleteBuffers
	.section	.text.glse_glDepthFunc,"ax",%progbits
	.align	2
	.global	glse_glDepthFunc
	.type	glse_glDepthFunc, %function
glse_glDepthFunc:
	.fnstart
.LFB24:
	.loc 3 214 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L66
.LPIC15:
	add	r2, pc, r2
	.loc 3 215 0
	ldr	r3, .L66+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 216 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glDepthFunc(PLT)
	.loc 3 218 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L67:
	.align	2
.L66:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC15+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE24:
	.fnend
	.size	glse_glDepthFunc, .-glse_glDepthFunc
	.section	.text.glse_glDrawArrays,"ax",%progbits
	.align	2
	.global	glse_glDrawArrays
	.type	glse_glDrawArrays, %function
glse_glDrawArrays:
	.fnstart
.LFB25:
	.loc 3 222 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L69
.LPIC16:
	add	r2, pc, r2
	.loc 3 223 0
	ldr	r3, .L69+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 224 0
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	glDrawArrays(PLT)
	.loc 3 226 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L70:
	.align	2
.L69:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC16+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE25:
	.fnend
	.size	glse_glDrawArrays, .-glse_glDrawArrays
	.section	.text.glse_glEnable,"ax",%progbits
	.align	2
	.global	glse_glEnable
	.type	glse_glEnable, %function
glse_glEnable:
	.fnstart
.LFB26:
	.loc 3 230 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L72
.LPIC17:
	add	r2, pc, r2
	.loc 3 231 0
	ldr	r3, .L72+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 232 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glEnable(PLT)
	.loc 3 234 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L73:
	.align	2
.L72:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC17+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE26:
	.fnend
	.size	glse_glEnable, .-glse_glEnable
	.section	.text.glse_glGenBuffers,"ax",%progbits
	.align	2
	.global	glse_glGenBuffers
	.type	glse_glGenBuffers, %function
glse_glGenBuffers:
	.fnstart
.LFB27:
	.loc 3 238 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L75
.LPIC18:
	add	r4, pc, r4
	.loc 3 239 0
	ldr	r3, .L75+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-20]
	.loc 3 240 0
	ldr	r3, [fp, #-20]
	ldr	r2, [r3, #4]
	ldr	r3, .L75+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, r2
	mov	r1, r3
	bl	glGenBuffers(PLT)
	.loc 3 242 0
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #4]
	mov	r3, r3, asl #2
	str	r3, [fp, #-16]
	.loc 3 243 0
	ldr	r3, .L75+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	ldr	r1, [fp, #-16]
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 244 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L76:
	.align	2
.L75:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC18+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE27:
	.fnend
	.size	glse_glGenBuffers, .-glse_glGenBuffers
	.section	.text.glse_glGenTextures,"ax",%progbits
	.align	2
	.global	glse_glGenTextures
	.type	glse_glGenTextures, %function
glse_glGenTextures:
	.fnstart
.LFB28:
	.loc 3 248 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L78
.LPIC19:
	add	r4, pc, r4
	.loc 3 249 0
	ldr	r3, .L78+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-20]
	.loc 3 250 0
	ldr	r3, [fp, #-20]
	ldr	r2, [r3, #4]
	ldr	r3, .L78+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, r2
	mov	r1, r3
	bl	glGenTextures(PLT)
	.loc 3 252 0
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #4]
	mov	r3, r3, asl #2
	str	r3, [fp, #-16]
	.loc 3 253 0
	ldr	r3, .L78+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	ldr	r1, [fp, #-16]
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 254 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L79:
	.align	2
.L78:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC19+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE28:
	.fnend
	.size	glse_glGenTextures, .-glse_glGenTextures
	.section	.text.glse_glGetAttribLocation,"ax",%progbits
	.align	2
	.global	glse_glGetAttribLocation
	.type	glse_glGetAttribLocation, %function
glse_glGetAttribLocation:
	.fnstart
.LFB29:
	.loc 3 258 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #20
	sub	sp, sp, #20
	ldr	r4, .L81
.LPIC20:
	add	r4, pc, r4
	.loc 3 259 0
	ldr	r3, .L81+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-24]
	.loc 3 260 0
	ldr	r3, [fp, #-24]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-24]
	add	r3, r3, #8
	mov	r0, r2
	mov	r1, r3
	bl	glGetAttribLocation(PLT)
	str	r0, [fp, #-20]
	.loc 3 262 0
	ldr	r3, .L81+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 263 0
	ldr	r3, [fp, #-16]
	mov	r2, #42
	str	r2, [r3]
	.loc 3 264 0
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-20]
	str	r2, [r3, #4]
	.loc 3 265 0
	ldr	r3, .L81+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 266 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L82:
	.align	2
.L81:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC20+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE29:
	.fnend
	.size	glse_glGetAttribLocation, .-glse_glGetAttribLocation
	.section	.text.glse_glGetError,"ax",%progbits
	.align	2
	.global	glse_glGetError
	.type	glse_glGetError, %function
glse_glGetError:
	.fnstart
.LFB30:
	.loc 3 270 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L84
.LPIC21:
	add	r4, pc, r4
	.loc 3 271 0
	bl	glGetError(PLT)
	str	r0, [fp, #-20]
	.loc 3 274 0
	ldr	r3, .L84+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 275 0
	ldr	r3, [fp, #-16]
	mov	r2, #43
	str	r2, [r3]
	.loc 3 276 0
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-20]
	str	r2, [r3, #4]
	.loc 3 277 0
	ldr	r3, .L84+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 278 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L85:
	.align	2
.L84:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC21+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE30:
	.fnend
	.size	glse_glGetError, .-glse_glGetError
	.section	.text.glse_glGetFloatv,"ax",%progbits
	.align	2
	.global	glse_glGetFloatv
	.type	glse_glGetFloatv, %function
glse_glGetFloatv:
	.fnstart
.LFB31:
	.loc 3 282 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L87
.LPIC22:
	add	r4, pc, r4
	.loc 3 283 0
	ldr	r3, .L87+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-20]
	.loc 3 284 0
	ldr	r3, .L87+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 285 0
	ldr	r3, [fp, #-20]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-16]
	add	r3, r3, #4
	mov	r0, r2
	mov	r1, r3
	bl	glGetFloatv(PLT)
	.loc 3 286 0
	ldr	r3, [fp, #-16]
	mov	r2, #44
	str	r2, [r3]
	.loc 3 287 0
	ldr	r3, .L87+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 288 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L88:
	.align	2
.L87:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC22+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE31:
	.fnend
	.size	glse_glGetFloatv, .-glse_glGetFloatv
	.section	.text.glse_glGetIntegerv,"ax",%progbits
	.align	2
	.global	glse_glGetIntegerv
	.type	glse_glGetIntegerv, %function
glse_glGetIntegerv:
	.fnstart
.LFB32:
	.loc 3 292 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L90
.LPIC23:
	add	r4, pc, r4
	.loc 3 293 0
	ldr	r3, .L90+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-20]
	.loc 3 294 0
	ldr	r3, .L90+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 295 0
	ldr	r3, [fp, #-20]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-16]
	add	r3, r3, #4
	mov	r0, r2
	mov	r1, r3
	bl	glGetIntegerv(PLT)
	.loc 3 296 0
	ldr	r3, [fp, #-16]
	mov	r2, #46
	str	r2, [r3]
	.loc 3 297 0
	ldr	r3, .L90+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 298 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L91:
	.align	2
.L90:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC23+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE32:
	.fnend
	.size	glse_glGetIntegerv, .-glse_glGetIntegerv
	.section	.text.glse_glGetProgramInfoLog,"ax",%progbits
	.align	2
	.global	glse_glGetProgramInfoLog
	.type	glse_glGetProgramInfoLog, %function
glse_glGetProgramInfoLog:
	.fnstart
.LFB33:
	.loc 3 302 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #20
	sub	sp, sp, #20
	ldr	r4, .L94
.LPIC24:
	add	r4, pc, r4
	.loc 3 303 0
	ldr	r3, .L94+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-28]
	.loc 3 304 0
	ldr	r3, .L94+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-24]
	.loc 3 305 0
	movw	r3, #65272
	movt	r3, 31
	str	r3, [fp, #-20]
	.loc 3 306 0
	ldr	r3, [fp, #-28]
	ldr	r3, [r3, #8]
	mov	r2, r3
	ldr	r3, [fp, #-20]
	cmp	r2, r3
	bls	.L93
	.loc 3 308 0
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-28]
	str	r2, [r3, #8]
.L93:
	.loc 3 310 0
	ldr	r3, [fp, #-28]
	ldr	r0, [r3, #4]
	ldr	r3, [fp, #-28]
	ldr	r1, [r3, #8]
	ldr	r3, [fp, #-24]
	add	r2, r3, #4
	ldr	r3, [fp, #-24]
	add	r3, r3, #8
	bl	glGetProgramInfoLog(PLT)
	.loc 3 312 0
	ldr	r3, [fp, #-24]
	mov	r2, #47
	str	r2, [r3]
	.loc 3 313 0
	ldr	r3, [fp, #-24]
	ldr	r3, [r3, #4]
	add	r3, r3, #9
	str	r3, [fp, #-16]
	.loc 3 314 0
	ldr	r3, .L94+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	ldr	r1, [fp, #-16]
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 315 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L95:
	.align	2
.L94:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC24+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE33:
	.fnend
	.size	glse_glGetProgramInfoLog, .-glse_glGetProgramInfoLog
	.section	.text.glse_glGetProgramiv,"ax",%progbits
	.align	2
	.global	glse_glGetProgramiv
	.type	glse_glGetProgramiv, %function
glse_glGetProgramiv:
	.fnstart
.LFB34:
	.loc 3 319 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L97
.LPIC25:
	add	r4, pc, r4
	.loc 3 320 0
	ldr	r3, .L97+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-20]
	.loc 3 321 0
	ldr	r3, .L97+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 322 0
	ldr	r3, [fp, #-20]
	ldr	r1, [r3, #4]
	ldr	r3, [fp, #-20]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-16]
	add	r3, r3, #4
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	glGetProgramiv(PLT)
	.loc 3 323 0
	ldr	r3, [fp, #-16]
	mov	r2, #45
	str	r2, [r3]
	.loc 3 324 0
	ldr	r3, .L97+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 325 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L98:
	.align	2
.L97:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC25+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE34:
	.fnend
	.size	glse_glGetProgramiv, .-glse_glGetProgramiv
	.section	.text.glse_glGetShaderiv,"ax",%progbits
	.align	2
	.global	glse_glGetShaderiv
	.type	glse_glGetShaderiv, %function
glse_glGetShaderiv:
	.fnstart
.LFB35:
	.loc 3 329 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L100
.LPIC26:
	add	r4, pc, r4
	.loc 3 330 0
	ldr	r3, .L100+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-20]
	.loc 3 331 0
	ldr	r3, .L100+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 332 0
	ldr	r3, [fp, #-20]
	ldr	r1, [r3, #4]
	ldr	r3, [fp, #-20]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-16]
	add	r3, r3, #4
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	glGetShaderiv(PLT)
	.loc 3 334 0
	ldr	r3, [fp, #-16]
	mov	r2, #49
	str	r2, [r3]
	.loc 3 335 0
	ldr	r3, .L100+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 336 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L101:
	.align	2
.L100:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC26+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE35:
	.fnend
	.size	glse_glGetShaderiv, .-glse_glGetShaderiv
	.section	.text.glse_glGetString,"ax",%progbits
	.align	2
	.global	glse_glGetString
	.type	glse_glGetString, %function
glse_glGetString:
	.fnstart
.LFB36:
	.loc 3 340 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #20
	sub	sp, sp, #20
	ldr	r4, .L103
.LPIC27:
	add	r4, pc, r4
	.loc 3 341 0
	ldr	r3, .L103+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-24]
	.loc 3 342 0
	ldr	r3, .L103+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-20]
	.loc 3 343 0
	ldr	r3, [fp, #-24]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glGetString(PLT)
	str	r0, [fp, #-16]
	.loc 3 344 0
	ldr	r3, [fp, #-20]
	mov	r2, #50
	str	r2, [r3]
	.loc 3 346 0
	ldr	r3, [fp, #-20]
	mov	r2, #0
	strb	r2, [r3, #259]
	.loc 3 347 0
	ldr	r3, [fp, #-20]
	add	r3, r3, #4
	mov	r0, r3
	ldr	r1, [fp, #-16]
	mov	r2, #254
	bl	strncpy(PLT)
	.loc 3 348 0
	ldr	r3, .L103+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	movw	r1, #10244
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 349 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L104:
	.align	2
.L103:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC27+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE36:
	.fnend
	.size	glse_glGetString, .-glse_glGetString
	.section	.text.glse_glGetUniformLocation,"ax",%progbits
	.align	2
	.global	glse_glGetUniformLocation
	.type	glse_glGetUniformLocation, %function
glse_glGetUniformLocation:
	.fnstart
.LFB37:
	.loc 3 353 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #20
	sub	sp, sp, #20
	ldr	r4, .L106
.LPIC28:
	add	r4, pc, r4
	.loc 3 354 0
	ldr	r3, .L106+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-24]
	.loc 3 355 0
	ldr	r3, [fp, #-24]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-24]
	add	r3, r3, #8
	mov	r0, r2
	mov	r1, r3
	bl	glGetUniformLocation(PLT)
	str	r0, [fp, #-20]
	.loc 3 357 0
	ldr	r3, .L106+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 358 0
	ldr	r3, [fp, #-16]
	mov	r2, #51
	str	r2, [r3]
	.loc 3 359 0
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-20]
	str	r2, [r3, #4]
	.loc 3 360 0
	ldr	r3, .L106+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 361 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L107:
	.align	2
.L106:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC28+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE37:
	.fnend
	.size	glse_glGetUniformLocation, .-glse_glGetUniformLocation
	.section	.text.glse_glEnableVertexAttribArray,"ax",%progbits
	.align	2
	.global	glse_glEnableVertexAttribArray
	.type	glse_glEnableVertexAttribArray, %function
glse_glEnableVertexAttribArray:
	.fnstart
.LFB38:
	.loc 3 365 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L109
.LPIC29:
	add	r2, pc, r2
	.loc 3 366 0
	ldr	r3, .L109+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 367 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glEnableVertexAttribArray(PLT)
	.loc 3 369 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L110:
	.align	2
.L109:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC29+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE38:
	.fnend
	.size	glse_glEnableVertexAttribArray, .-glse_glEnableVertexAttribArray
	.section	.text.glse_glVertexAttribPointer,"ax",%progbits
	.align	2
	.global	glse_glVertexAttribPointer
	.type	glse_glVertexAttribPointer, %function
glse_glVertexAttribPointer:
	.fnstart
.LFB39:
	.loc 3 374 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #16
	sub	sp, sp, #16
	ldr	r2, .L112
.LPIC30:
	add	r2, pc, r2
	.loc 3 375 0
	ldr	r3, .L112+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 376 0
	ldr	r3, [fp, #-8]
	ldr	r0, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	lr, [r3, #12]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #24]
	uxtb	ip, r3
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #16]
	ldr	r2, [fp, #-8]
	ldr	r2, [r2, #20]
	str	r3, [sp]
	str	r2, [sp, #4]
	mov	r2, lr
	mov	r3, ip
	bl	glVertexAttribPointer(PLT)
	.loc 3 378 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L113:
	.align	2
.L112:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC30+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE39:
	.fnend
	.size	glse_glVertexAttribPointer, .-glse_glVertexAttribPointer
	.section	.text.glse_glBindFramebuffer,"ax",%progbits
	.align	2
	.global	glse_glBindFramebuffer
	.type	glse_glBindFramebuffer, %function
glse_glBindFramebuffer:
	.fnstart
.LFB40:
	.loc 3 382 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L115
.LPIC31:
	add	r2, pc, r2
	.loc 3 383 0
	ldr	r3, .L115+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 384 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r2
	mov	r1, r3
	bl	glBindFramebuffer(PLT)
	.loc 3 386 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L116:
	.align	2
.L115:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC31+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE40:
	.fnend
	.size	glse_glBindFramebuffer, .-glse_glBindFramebuffer
	.section	.text.glse_glViewport,"ax",%progbits
	.align	2
	.global	glse_glViewport
	.type	glse_glViewport, %function
glse_glViewport:
	.fnstart
.LFB41:
	.loc 3 390 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L118
.LPIC32:
	add	r2, pc, r2
	.loc 3 391 0
	ldr	r3, .L118+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 392 0
	ldr	r3, [fp, #-8]
	ldr	r0, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #12]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #16]
	bl	glViewport(PLT)
	.loc 3 394 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L119:
	.align	2
.L118:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC32+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE41:
	.fnend
	.size	glse_glViewport, .-glse_glViewport
	.section	.text.glse_glUseProgram,"ax",%progbits
	.align	2
	.global	glse_glUseProgram
	.type	glse_glUseProgram, %function
glse_glUseProgram:
	.fnstart
.LFB42:
	.loc 3 399 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L121
.LPIC33:
	add	r2, pc, r2
	.loc 3 400 0
	ldr	r3, .L121+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 401 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glUseProgram(PLT)
	.loc 3 403 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L122:
	.align	2
.L121:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC33+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE42:
	.fnend
	.size	glse_glUseProgram, .-glse_glUseProgram
	.section	.text.glse_glCreateShader,"ax",%progbits
	.align	2
	.global	glse_glCreateShader
	.type	glse_glCreateShader, %function
glse_glCreateShader:
	.fnstart
.LFB43:
	.loc 3 407 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #20
	sub	sp, sp, #20
	ldr	r4, .L124
.LPIC34:
	add	r4, pc, r4
	.loc 3 408 0
	ldr	r3, .L124+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-24]
	.loc 3 409 0
	ldr	r3, [fp, #-24]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glCreateShader(PLT)
	str	r0, [fp, #-20]
	.loc 3 411 0
	ldr	r3, .L124+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 412 0
	ldr	r3, [fp, #-16]
	mov	r2, #22
	str	r2, [r3]
	.loc 3 413 0
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-20]
	str	r2, [r3, #4]
	.loc 3 414 0
	ldr	r3, .L124+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 415 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L125:
	.align	2
.L124:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC34+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE43:
	.fnend
	.size	glse_glCreateShader, .-glse_glCreateShader
	.section	.text.glse_glShaderSource,"ax",%progbits
	.align	2
	.global	glse_glShaderSource
	.type	glse_glShaderSource, %function
glse_glShaderSource:
	.fnstart
.LFB44:
	.loc 3 419 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #16
	sub	sp, sp, #16
	ldr	r3, .L129
.LPIC35:
	add	r3, pc, r3
	.loc 3 420 0
	ldr	r2, .L129+4
	ldr	r2, [r3, r2]
	ldr	r2, [r2, #32]
	str	r2, [fp, #-12]
	.loc 3 421 0
	ldr	r2, .L129+4
	ldr	r3, [r3, r2]
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	.loc 3 423 0
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L127
.L128:
	.loc 3 426 0
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-16]
	ldr	r3, [r3, r2, asl #2]
	add	r3, r3, #81920
	ldr	r2, [fp, #-8]
	add	r3, r2, r3
	mov	r1, r3
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-16]
	str	r1, [r3, r2, asl #2]
	.loc 3 423 0 discriminator 3
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L127:
	.loc 3 423 0 is_stmt 0 discriminator 1
	ldr	r3, [fp, #-12]
	ldr	r3, [r3, #8]
	mov	r2, r3
	ldr	r3, [fp, #-16]
	cmp	r2, r3
	bhi	.L128
	.loc 3 428 0 is_stmt 1
	ldr	r3, [fp, #-12]
	ldr	r0, [r3, #4]
	ldr	r3, [fp, #-12]
	ldr	r1, [r3, #8]
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-8]
	add	r3, r3, #40960
	bl	glShaderSource(PLT)
	.loc 3 430 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L130:
	.align	2
.L129:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC35+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE44:
	.fnend
	.size	glse_glShaderSource, .-glse_glShaderSource
	.section	.text.glse_glCompileShader,"ax",%progbits
	.align	2
	.global	glse_glCompileShader
	.type	glse_glCompileShader, %function
glse_glCompileShader:
	.fnstart
.LFB45:
	.loc 3 434 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L132
.LPIC36:
	add	r2, pc, r2
	.loc 3 435 0
	ldr	r3, .L132+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 436 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glCompileShader(PLT)
	.loc 3 438 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L133:
	.align	2
.L132:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC36+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE45:
	.fnend
	.size	glse_glCompileShader, .-glse_glCompileShader
	.section	.text.glse_glCreateProgram,"ax",%progbits
	.align	2
	.global	glse_glCreateProgram
	.type	glse_glCreateProgram, %function
glse_glCreateProgram:
	.fnstart
.LFB46:
	.loc 3 442 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L135
.LPIC37:
	add	r4, pc, r4
	.loc 3 443 0
	bl	glCreateProgram(PLT)
	str	r0, [fp, #-20]
	.loc 3 445 0
	ldr	r3, .L135+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 446 0
	ldr	r3, [fp, #-16]
	mov	r2, #21
	str	r2, [r3]
	.loc 3 447 0
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-20]
	str	r2, [r3, #4]
	.loc 3 448 0
	ldr	r3, .L135+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 449 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L136:
	.align	2
.L135:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC37+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE46:
	.fnend
	.size	glse_glCreateProgram, .-glse_glCreateProgram
	.section	.text.glse_glAttachShader,"ax",%progbits
	.align	2
	.global	glse_glAttachShader
	.type	glse_glAttachShader, %function
glse_glAttachShader:
	.fnstart
.LFB47:
	.loc 3 453 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L138
.LPIC38:
	add	r2, pc, r2
	.loc 3 454 0
	ldr	r3, .L138+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 455 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r2
	mov	r1, r3
	bl	glAttachShader(PLT)
	.loc 3 457 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L139:
	.align	2
.L138:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC38+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE47:
	.fnend
	.size	glse_glAttachShader, .-glse_glAttachShader
	.section	.text.glse_glLinkProgram,"ax",%progbits
	.align	2
	.global	glse_glLinkProgram
	.type	glse_glLinkProgram, %function
glse_glLinkProgram:
	.fnstart
.LFB48:
	.loc 3 461 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L141
.LPIC39:
	add	r2, pc, r2
	.loc 3 462 0
	ldr	r3, .L141+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 463 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glLinkProgram(PLT)
	.loc 3 465 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L142:
	.align	2
.L141:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC39+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE48:
	.fnend
	.size	glse_glLinkProgram, .-glse_glLinkProgram
	.section	.text.glse_glDeleteProgram,"ax",%progbits
	.align	2
	.global	glse_glDeleteProgram
	.type	glse_glDeleteProgram, %function
glse_glDeleteProgram:
	.fnstart
.LFB49:
	.loc 3 469 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L144
.LPIC40:
	add	r2, pc, r2
	.loc 3 470 0
	ldr	r3, .L144+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 471 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glDeleteProgram(PLT)
	.loc 3 473 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L145:
	.align	2
.L144:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC40+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE49:
	.fnend
	.size	glse_glDeleteProgram, .-glse_glDeleteProgram
	.section	.text.glse_glDeleteShader,"ax",%progbits
	.align	2
	.global	glse_glDeleteShader
	.type	glse_glDeleteShader, %function
glse_glDeleteShader:
	.fnstart
.LFB50:
	.loc 3 477 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L147
.LPIC41:
	add	r2, pc, r2
	.loc 3 478 0
	ldr	r3, .L147+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 479 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glDeleteShader(PLT)
	.loc 3 481 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L148:
	.align	2
.L147:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC41+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE50:
	.fnend
	.size	glse_glDeleteShader, .-glse_glDeleteShader
	.section	.text.glse_glUniform1f,"ax",%progbits
	.align	2
	.global	glse_glUniform1f
	.type	glse_glUniform1f, %function
glse_glUniform1f:
	.fnstart
.LFB51:
	.loc 3 485 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L150
.LPIC42:
	add	r2, pc, r2
	.loc 3 486 0
	ldr	r3, .L150+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 487 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]	@ float
	mov	r0, r2
	mov	r1, r3	@ float
	bl	glUniform1f(PLT)
	.loc 3 489 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L151:
	.align	2
.L150:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC42+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE51:
	.fnend
	.size	glse_glUniform1f, .-glse_glUniform1f
	.section	.text.glse_glDisableVertexAttribArray,"ax",%progbits
	.align	2
	.global	glse_glDisableVertexAttribArray
	.type	glse_glDisableVertexAttribArray, %function
glse_glDisableVertexAttribArray:
	.fnstart
.LFB52:
	.loc 3 493 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L153
.LPIC43:
	add	r2, pc, r2
	.loc 3 494 0
	ldr	r3, .L153+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 495 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glDisableVertexAttribArray(PLT)
	.loc 3 497 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L154:
	.align	2
.L153:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC43+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE52:
	.fnend
	.size	glse_glDisableVertexAttribArray, .-glse_glDisableVertexAttribArray
	.section	.text.glse_glDisable,"ax",%progbits
	.align	2
	.global	glse_glDisable
	.type	glse_glDisable, %function
glse_glDisable:
	.fnstart
.LFB53:
	.loc 3 501 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L156
.LPIC44:
	add	r2, pc, r2
	.loc 3 502 0
	ldr	r3, .L156+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 503 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glDisable(PLT)
	.loc 3 505 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L157:
	.align	2
.L156:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC44+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE53:
	.fnend
	.size	glse_glDisable, .-glse_glDisable
	.section	.text.glse_glDrawElements,"ax",%progbits
	.align	2
	.global	glse_glDrawElements
	.type	glse_glDrawElements, %function
glse_glDrawElements:
	.fnstart
.LFB54:
	.loc 3 509 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L159
.LPIC45:
	add	r2, pc, r2
	.loc 3 510 0
	ldr	r3, .L159+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 511 0
	ldr	r3, [fp, #-8]
	ldr	r0, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #12]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #16]
	bl	glDrawElements(PLT)
	.loc 3 513 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L160:
	.align	2
.L159:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC45+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE54:
	.fnend
	.size	glse_glDrawElements, .-glse_glDrawElements
	.section	.text.glse_glGetShaderInfoLog,"ax",%progbits
	.align	2
	.global	glse_glGetShaderInfoLog
	.type	glse_glGetShaderInfoLog, %function
glse_glGetShaderInfoLog:
	.fnstart
.LFB55:
	.loc 3 517 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #20
	sub	sp, sp, #20
	ldr	r4, .L163
.LPIC46:
	add	r4, pc, r4
	.loc 3 518 0
	ldr	r3, .L163+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-28]
	.loc 3 519 0
	ldr	r3, .L163+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-24]
	.loc 3 520 0
	movw	r3, #65272
	movt	r3, 31
	str	r3, [fp, #-20]
	.loc 3 521 0
	ldr	r3, [fp, #-28]
	ldr	r3, [r3, #8]
	mov	r2, r3
	ldr	r3, [fp, #-20]
	cmp	r2, r3
	bls	.L162
	.loc 3 523 0
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-28]
	str	r2, [r3, #8]
.L162:
	.loc 3 525 0
	ldr	r3, [fp, #-28]
	ldr	r0, [r3, #4]
	ldr	r3, [fp, #-28]
	ldr	r1, [r3, #8]
	ldr	r3, [fp, #-24]
	add	r2, r3, #4
	ldr	r3, [fp, #-24]
	add	r3, r3, #8
	bl	glGetShaderInfoLog(PLT)
	.loc 3 527 0
	ldr	r3, [fp, #-24]
	mov	r2, #48
	str	r2, [r3]
	.loc 3 528 0
	ldr	r3, [fp, #-24]
	ldr	r3, [r3, #4]
	add	r3, r3, #9
	str	r3, [fp, #-16]
	.loc 3 529 0
	ldr	r3, .L163+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	ldr	r1, [fp, #-16]
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 530 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L164:
	.align	2
.L163:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC46+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE55:
	.fnend
	.size	glse_glGetShaderInfoLog, .-glse_glGetShaderInfoLog
	.section	.text.glse_glBindAttribLocation,"ax",%progbits
	.align	2
	.global	glse_glBindAttribLocation
	.type	glse_glBindAttribLocation, %function
glse_glBindAttribLocation:
	.fnstart
.LFB56:
	.loc 3 534 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L166
.LPIC47:
	add	r2, pc, r2
	.loc 3 535 0
	ldr	r3, .L166+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 536 0
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-8]
	add	r3, r3, #12
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	glBindAttribLocation(PLT)
	.loc 3 538 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L167:
	.align	2
.L166:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC47+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE56:
	.fnend
	.size	glse_glBindAttribLocation, .-glse_glBindAttribLocation
	.section	.text.glse_glUniform4fv,"ax",%progbits
	.align	2
	.global	glse_glUniform4fv
	.type	glse_glUniform4fv, %function
glse_glUniform4fv:
	.fnstart
.LFB57:
	.loc 3 542 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L169
.LPIC48:
	add	r2, pc, r2
	.loc 3 543 0
	ldr	r3, .L169+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 544 0
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #12]
	ldr	r3, [fp, #-8]
	add	r3, r3, #16
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	glUniform4fv(PLT)
	.loc 3 546 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L170:
	.align	2
.L169:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC48+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE57:
	.fnend
	.size	glse_glUniform4fv, .-glse_glUniform4fv
	.section	.text.glse_glUniformMatrix4fv,"ax",%progbits
	.align	2
	.global	glse_glUniformMatrix4fv
	.type	glse_glUniformMatrix4fv, %function
glse_glUniformMatrix4fv:
	.fnstart
.LFB58:
	.loc 3 550 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L172
.LPIC49:
	add	r2, pc, r2
	.loc 3 551 0
	ldr	r3, .L172+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 552 0
	ldr	r3, [fp, #-8]
	ldr	r0, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #12]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #16]
	uxtb	r2, r3
	ldr	r3, [fp, #-8]
	add	r3, r3, #20
	bl	glUniformMatrix4fv(PLT)
	.loc 3 554 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L173:
	.align	2
.L172:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC49+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE58:
	.fnend
	.size	glse_glUniformMatrix4fv, .-glse_glUniformMatrix4fv
	.section	.text.glse_glFinish,"ax",%progbits
	.align	2
	.global	glse_glFinish
	.type	glse_glFinish, %function
glse_glFinish:
	.fnstart
.LFB59:
	.loc 3 558 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #20
	sub	sp, sp, #20
	ldr	r4, .L175
.LPIC50:
	add	r4, pc, r4
	.loc 3 559 0
	ldr	r3, .L175+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-24]
	.loc 3 560 0
	bl	glFinish(PLT)
	.loc 3 562 0
	ldr	r3, .L175+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-20]
	.loc 3 563 0
	ldr	r3, [fp, #-24]
	ldr	r2, [r3]
	ldr	r3, [fp, #-20]
	str	r2, [r3]
	.loc 3 564 0
	mov	r3, #4
	str	r3, [fp, #-16]
	.loc 3 565 0
	ldr	r3, .L175+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	ldr	r1, [fp, #-16]
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 566 0
	sub	sp, fp, #8
	.cfi_def_cfa 13, 12
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L176:
	.align	2
.L175:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC50+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE59:
	.fnend
	.size	glse_glFinish, .-glse_glFinish
	.section	.text.glse_glFlush,"ax",%progbits
	.align	2
	.global	glse_glFlush
	.type	glse_glFlush, %function
glse_glFlush:
	.fnstart
.LFB60:
	.loc 3 570 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.loc 3 571 0
	bl	glFlush(PLT)
	.loc 3 573 0
	ldmfd	sp!, {fp, pc}
	.cfi_endproc
.LFE60:
	.fnend
	.size	glse_glFlush, .-glse_glFlush
	.section	.text.glse_glTexParameteri,"ax",%progbits
	.align	2
	.global	glse_glTexParameteri
	.type	glse_glTexParameteri, %function
glse_glTexParameteri:
	.fnstart
.LFB61:
	.loc 3 577 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L179
.LPIC51:
	add	r2, pc, r2
	.loc 3 578 0
	ldr	r3, .L179+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 579 0
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	glTexParameteri(PLT)
	.loc 3 581 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L180:
	.align	2
.L179:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC51+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE61:
	.fnend
	.size	glse_glTexParameteri, .-glse_glTexParameteri
	.section	.text.glse_glTexImage2D,"ax",%progbits
	.align	2
	.global	glse_glTexImage2D
	.type	glse_glTexImage2D, %function
glse_glTexImage2D:
	.fnstart
.LFB62:
	.loc 3 585 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, fp, lr}
	.save {r4, r5, r6, fp, lr}
	.cfi_def_cfa_offset 20
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #16
	add	fp, sp, #16
	.cfi_def_cfa 11, 4
	.pad #36
	sub	sp, sp, #36
	ldr	r2, .L182
.LPIC52:
	add	r2, pc, r2
	.loc 3 586 0
	ldr	r3, .L182+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-24]
	.loc 3 587 0
	ldr	r3, [fp, #-24]
	ldr	r6, [r3, #8]
	ldr	r3, [fp, #-24]
	ldr	r5, [r3, #12]
	ldr	r3, [fp, #-24]
	ldr	r4, [r3, #16]
	ldr	r3, [fp, #-24]
	ldr	lr, [r3, #20]
	ldr	r3, [fp, #-24]
	ldr	ip, [r3, #24]
	ldr	r3, [fp, #-24]
	ldr	r0, [r3, #28]
	ldr	r3, [fp, #-24]
	ldr	r1, [r3, #32]
	ldr	r3, [fp, #-24]
	ldr	r2, [r3, #36]
	ldr	r3, [fp, #-24]
	add	r3, r3, #40
	str	ip, [sp]
	str	r0, [sp, #4]
	str	r1, [sp, #8]
	str	r2, [sp, #12]
	str	r3, [sp, #16]
	mov	r0, r6
	mov	r1, r5
	mov	r2, r4
	mov	r3, lr
	bl	glTexImage2D(PLT)
	.loc 3 589 0
	sub	sp, fp, #16
	.cfi_def_cfa 13, 20
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, fp, pc}
.L183:
	.align	2
.L182:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC52+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE62:
	.fnend
	.size	glse_glTexImage2D, .-glse_glTexImage2D
	.section	.text.glse_glTexSubImage2D,"ax",%progbits
	.align	2
	.global	glse_glTexSubImage2D
	.type	glse_glTexSubImage2D, %function
glse_glTexSubImage2D:
	.fnstart
.LFB63:
	.loc 3 594 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, fp, lr}
	.save {r4, r5, r6, fp, lr}
	.cfi_def_cfa_offset 20
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #16
	add	fp, sp, #16
	.cfi_def_cfa 11, 4
	.pad #36
	sub	sp, sp, #36
	ldr	r2, .L185
.LPIC53:
	add	r2, pc, r2
	.loc 3 595 0
	ldr	r3, .L185+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-24]
	.loc 3 596 0
	ldr	r3, [fp, #-24]
	ldr	r6, [r3, #8]
	ldr	r3, [fp, #-24]
	ldr	r5, [r3, #12]
	ldr	r3, [fp, #-24]
	ldr	r4, [r3, #16]
	ldr	r3, [fp, #-24]
	ldr	lr, [r3, #20]
	ldr	r3, [fp, #-24]
	ldr	ip, [r3, #24]
	ldr	r3, [fp, #-24]
	ldr	r0, [r3, #28]
	ldr	r3, [fp, #-24]
	ldr	r1, [r3, #32]
	ldr	r3, [fp, #-24]
	ldr	r2, [r3, #36]
	ldr	r3, [fp, #-24]
	add	r3, r3, #40
	str	ip, [sp]
	str	r0, [sp, #4]
	str	r1, [sp, #8]
	str	r2, [sp, #12]
	str	r3, [sp, #16]
	mov	r0, r6
	mov	r1, r5
	mov	r2, r4
	mov	r3, lr
	bl	glTexSubImage2D(PLT)
	.loc 3 598 0
	sub	sp, fp, #16
	.cfi_def_cfa 13, 20
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, fp, pc}
.L186:
	.align	2
.L185:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC53+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE63:
	.fnend
	.size	glse_glTexSubImage2D, .-glse_glTexSubImage2D
	.section	.text.glse_glDeleteTextures,"ax",%progbits
	.align	2
	.global	glse_glDeleteTextures
	.type	glse_glDeleteTextures, %function
glse_glDeleteTextures:
	.fnstart
.LFB64:
	.loc 3 602 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L188
.LPIC54:
	add	r2, pc, r2
	.loc 3 603 0
	ldr	r3, .L188+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 604 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-8]
	add	r3, r3, #12
	mov	r0, r2
	mov	r1, r3
	bl	glDeleteTextures(PLT)
	.loc 3 606 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L189:
	.align	2
.L188:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC54+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE64:
	.fnend
	.size	glse_glDeleteTextures, .-glse_glDeleteTextures
	.section	.text.glse_glPixelStorei,"ax",%progbits
	.align	2
	.global	glse_glPixelStorei
	.type	glse_glPixelStorei, %function
glse_glPixelStorei:
	.fnstart
.LFB65:
	.loc 3 610 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L191
.LPIC55:
	add	r2, pc, r2
	.loc 3 611 0
	ldr	r3, .L191+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 612 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r2
	mov	r1, r3
	bl	glPixelStorei(PLT)
	.loc 3 614 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L192:
	.align	2
.L191:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC55+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE65:
	.fnend
	.size	glse_glPixelStorei, .-glse_glPixelStorei
	.section	.text.glse_glActiveTexture,"ax",%progbits
	.align	2
	.global	glse_glActiveTexture
	.type	glse_glActiveTexture, %function
glse_glActiveTexture:
	.fnstart
.LFB66:
	.loc 3 618 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L194
.LPIC56:
	add	r2, pc, r2
	.loc 3 619 0
	ldr	r3, .L194+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 620 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glActiveTexture(PLT)
	.loc 3 622 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L195:
	.align	2
.L194:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC56+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE66:
	.fnend
	.size	glse_glActiveTexture, .-glse_glActiveTexture
	.section	.text.glse_glBlendFunc,"ax",%progbits
	.align	2
	.global	glse_glBlendFunc
	.type	glse_glBlendFunc, %function
glse_glBlendFunc:
	.fnstart
.LFB67:
	.loc 3 626 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L197
.LPIC57:
	add	r2, pc, r2
	.loc 3 627 0
	ldr	r3, .L197+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 628 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r2
	mov	r1, r3
	bl	glBlendFunc(PLT)
	.loc 3 630 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L198:
	.align	2
.L197:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC57+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE67:
	.fnend
	.size	glse_glBlendFunc, .-glse_glBlendFunc
	.section	.text.glse_glCullFace,"ax",%progbits
	.align	2
	.global	glse_glCullFace
	.type	glse_glCullFace, %function
glse_glCullFace:
	.fnstart
.LFB68:
	.loc 3 634 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L200
.LPIC58:
	add	r2, pc, r2
	.loc 3 635 0
	ldr	r3, .L200+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 636 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glActiveTexture(PLT)
	.loc 3 638 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L201:
	.align	2
.L200:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC58+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE68:
	.fnend
	.size	glse_glCullFace, .-glse_glCullFace
	.section	.text.glse_glDepthMask,"ax",%progbits
	.align	2
	.global	glse_glDepthMask
	.type	glse_glDepthMask, %function
glse_glDepthMask:
	.fnstart
.LFB69:
	.loc 3 642 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L203
.LPIC59:
	add	r2, pc, r2
	.loc 3 643 0
	ldr	r3, .L203+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 644 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	uxtb	r3, r3
	mov	r0, r3
	bl	glDepthMask(PLT)
	.loc 3 646 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L204:
	.align	2
.L203:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC59+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE69:
	.fnend
	.size	glse_glDepthMask, .-glse_glDepthMask
	.section	.text.glse_glDepthRangef,"ax",%progbits
	.align	2
	.global	glse_glDepthRangef
	.type	glse_glDepthRangef, %function
glse_glDepthRangef:
	.fnstart
.LFB70:
	.loc 3 650 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L206
.LPIC60:
	add	r2, pc, r2
	.loc 3 651 0
	ldr	r3, .L206+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 652 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	fmsr	s15, r3	@ int
	fuitos	s14, s15
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	fmsr	s15, r3	@ int
	fuitos	s15, s15
	fmrs	r0, s14
	fmrs	r1, s15
	bl	glDepthRangef(PLT)
	.loc 3 654 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L207:
	.align	2
.L206:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC60+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE70:
	.fnend
	.size	glse_glDepthRangef, .-glse_glDepthRangef
	.section	.text.glse_glStencilFunc,"ax",%progbits
	.align	2
	.global	glse_glStencilFunc
	.type	glse_glStencilFunc, %function
glse_glStencilFunc:
	.fnstart
.LFB71:
	.loc 3 658 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L209
.LPIC61:
	add	r2, pc, r2
	.loc 3 659 0
	ldr	r3, .L209+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 660 0
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	glStencilFunc(PLT)
	.loc 3 662 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L210:
	.align	2
.L209:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC61+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE71:
	.fnend
	.size	glse_glStencilFunc, .-glse_glStencilFunc
	.section	.text.glse_glStencilOp,"ax",%progbits
	.align	2
	.global	glse_glStencilOp
	.type	glse_glStencilOp, %function
glse_glStencilOp:
	.fnstart
.LFB72:
	.loc 3 666 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L212
.LPIC62:
	add	r2, pc, r2
	.loc 3 667 0
	ldr	r3, .L212+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 668 0
	ldr	r3, [fp, #-8]
	ldr	r1, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	glStencilOp(PLT)
	.loc 3 670 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L213:
	.align	2
.L212:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC62+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE72:
	.fnend
	.size	glse_glStencilOp, .-glse_glStencilOp
	.section	.text.glse_glPolygonOffset,"ax",%progbits
	.align	2
	.global	glse_glPolygonOffset
	.type	glse_glPolygonOffset, %function
glse_glPolygonOffset:
	.fnstart
.LFB73:
	.loc 3 674 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L215
.LPIC63:
	add	r2, pc, r2
	.loc 3 675 0
	ldr	r3, .L215+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 676 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]	@ float
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]	@ float
	mov	r0, r2	@ float
	mov	r1, r3	@ float
	bl	glPolygonOffset(PLT)
	.loc 3 678 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L216:
	.align	2
.L215:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC63+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE73:
	.fnend
	.size	glse_glPolygonOffset, .-glse_glPolygonOffset
	.section	.text.glse_glStencilMask,"ax",%progbits
	.align	2
	.global	glse_glStencilMask
	.type	glse_glStencilMask, %function
glse_glStencilMask:
	.fnstart
.LFB74:
	.loc 3 682 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L218
.LPIC64:
	add	r2, pc, r2
	.loc 3 683 0
	ldr	r3, .L218+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 684 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	glStencilMask(PLT)
	.loc 3 686 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L219:
	.align	2
.L218:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC64+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE74:
	.fnend
	.size	glse_glStencilMask, .-glse_glStencilMask
	.section	.text.glse_glLineWidth,"ax",%progbits
	.align	2
	.global	glse_glLineWidth
	.type	glse_glLineWidth, %function
glse_glLineWidth:
	.fnstart
.LFB75:
	.loc 3 690 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L221
.LPIC65:
	add	r2, pc, r2
	.loc 3 691 0
	ldr	r3, .L221+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 692 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]	@ float
	mov	r0, r3	@ float
	bl	glLineWidth(PLT)
	.loc 3 694 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L222:
	.align	2
.L221:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC65+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE75:
	.fnend
	.size	glse_glLineWidth, .-glse_glLineWidth
	.section	.text.glse_glHint,"ax",%progbits
	.align	2
	.global	glse_glHint
	.type	glse_glHint, %function
glse_glHint:
	.fnstart
.LFB76:
	.loc 3 698 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L224
.LPIC66:
	add	r2, pc, r2
	.loc 3 699 0
	ldr	r3, .L224+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 700 0
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #8]
	mov	r0, r2
	mov	r1, r3
	bl	glHint(PLT)
	.loc 3 702 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L225:
	.align	2
.L224:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC66+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE76:
	.fnend
	.size	glse_glHint, .-glse_glHint
	.section	.text.glse_glClearDepthf,"ax",%progbits
	.align	2
	.global	glse_glClearDepthf
	.type	glse_glClearDepthf, %function
glse_glClearDepthf:
	.fnstart
.LFB77:
	.loc 3 706 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	ldr	r2, .L227
.LPIC67:
	add	r2, pc, r2
	.loc 3 707 0
	ldr	r3, .L227+4
	ldr	r3, [r2, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-8]
	.loc 3 708 0
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #4]	@ float
	mov	r0, r3	@ float
	bl	glClearDepthf(PLT)
	.loc 3 710 0
	sub	sp, fp, #4
	.cfi_def_cfa 13, 8
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L228:
	.align	2
.L227:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC67+8)
	.word	glsec_global(GOT)
	.cfi_endproc
.LFE77:
	.fnend
	.size	glse_glClearDepthf, .-glse_glClearDepthf
	.section	.text.glse_glReadPixels,"ax",%progbits
	.align	2
	.global	glse_glReadPixels
	.type	glse_glReadPixels, %function
glse_glReadPixels:
	.fnstart
.LFB78:
	.loc 3 714 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, fp, lr}
	.save {r4, r5, fp, lr}
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #12
	add	fp, sp, #12
	.cfi_def_cfa 11, 4
	.pad #24
	sub	sp, sp, #24
	ldr	r4, .L230
.LPIC68:
	add	r4, pc, r4
	.loc 3 715 0
	ldr	r3, .L230+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #32]
	str	r3, [fp, #-20]
	.loc 3 716 0
	ldr	r3, .L230+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-16]
	.loc 3 717 0
	ldr	r3, [fp, #-20]
	ldr	r0, [r3, #4]
	ldr	r3, [fp, #-20]
	ldr	ip, [r3, #8]
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #12]
	mov	r5, r3
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #16]
	mov	lr, r3
	ldr	r3, [fp, #-20]
	ldr	r1, [r3, #20]
	ldr	r3, [fp, #-20]
	ldr	r2, [r3, #24]
	ldr	r3, [fp, #-16]
	add	r3, r3, #4
	str	r1, [sp]
	str	r2, [sp, #4]
	str	r3, [sp, #8]
	mov	r1, ip
	mov	r2, r5
	mov	r3, lr
	bl	glReadPixels(PLT)
	.loc 3 719 0
	ldr	r3, .L230+8
	ldr	r3, [r4, r3]
	mov	r2, r3
	ldr	r3, [fp, #-16]
	str	r2, [r3]
	.loc 3 720 0
	ldr	r3, .L230+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3]
	mov	r0, #0
	mov	r1, #8
	mov	r2, r3
	bl	glse_cmd_send_data(PLT)
	.loc 3 723 0
	sub	sp, fp, #12
	.cfi_def_cfa 13, 16
	@ sp needed
	ldmfd	sp!, {r4, r5, fp, pc}
.L231:
	.align	2
.L230:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC68+8)
	.word	glsec_global(GOT)
	.word	glReadPixels(GOT)
	.cfi_endproc
.LFE78:
	.fnend
	.size	glse_glReadPixels, .-glse_glReadPixels
	.section	.rodata
	.align	2
.LC0:
	.ascii	"GLStreamingNative\000"
	.align	2
.LC1:
	.ascii	"Error: Command Flush %i\000"
	.section	.text.glse_cmd_flush,"ax",%progbits
	.align	2
	.global	glse_cmd_flush
	.type	glse_cmd_flush, %function
glse_cmd_flush:
	.fnstart
.LFB79:
	.loc 3 742 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.setfp fp, sp, #8
	add	fp, sp, #8
	.cfi_def_cfa 11, 4
	.pad #12
	sub	sp, sp, #12
	ldr	r4, .L281
.LPIC69:
	add	r4, pc, r4
	.loc 3 743 0
	ldr	r3, .L281+4
	ldr	r3, [r4, r3]
	mov	r2, #0
	str	r2, [r3, #8]
	.loc 3 744 0
	mov	r3, #0
	str	r3, [fp, #-20]
	.loc 3 745 0
	b	.L233
.L280:
.LBB3:
	.loc 3 747 0
	ldr	r3, .L281+4
	ldr	r3, [r4, r3]
	ldr	r2, [r3]
	ldr	r3, .L281+4
	ldr	r3, [r4, r3]
	ldr	r3, [r3, #8]
	add	r3, r2, r3
	str	r3, [fp, #-16]
	.loc 3 748 0
	ldr	r3, .L281+4
	ldr	r3, [r4, r3]
	ldr	r2, [fp, #-16]
	str	r2, [r3, #32]
	.loc 3 749 0
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	cmp	r3, #70
	addls	pc, pc, r3, asl #2
	b	.L234
.L236:
	b	.L235
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L237
	b	.L238
	b	.L239
	b	.L240
	b	.L241
	b	.L242
	b	.L243
	b	.L244
	b	.L245
	b	.L234
	b	.L234
	b	.L246
	b	.L247
	b	.L248
	b	.L234
	b	.L249
	b	.L234
	b	.L234
	b	.L250
	b	.L234
	b	.L251
	b	.L252
	b	.L253
	b	.L254
	b	.L255
	b	.L256
	b	.L257
	b	.L258
	b	.L259
	b	.L260
	b	.L261
	b	.L262
	b	.L234
	b	.L263
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L234
	b	.L264
	b	.L265
	b	.L266
	b	.L267
	b	.L268
	b	.L234
	b	.L234
	b	.L269
	b	.L270
	b	.L271
	b	.L272
	b	.L273
	b	.L234
	b	.L274
	b	.L275
	b	.L276
	b	.L277
	b	.L278
	b	.L279
	.p2align 1
.L235:
	.loc 3 752 0
	mov	r3, #1
	str	r3, [fp, #-20]
	.loc 3 753 0
	b	.L233
.L238:
	.loc 3 755 0
	bl	glse_glAttachShader(PLT)
	.loc 3 756 0
	mov	r0, #12
	bl	pop_batch_command(PLT)
	.loc 3 757 0
	b	.L233
.L237:
	.loc 3 759 0
	bl	glse_glActiveTexture(PLT)
	.loc 3 760 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 761 0
	b	.L233
.L240:
	.loc 3 763 0
	bl	glse_glBindBuffer(PLT)
	.loc 3 764 0
	mov	r0, #12
	bl	pop_batch_command(PLT)
	.loc 3 765 0
	b	.L233
.L242:
	.loc 3 767 0
	bl	glse_glBindTexture(PLT)
	.loc 3 768 0
	mov	r0, #12
	bl	pop_batch_command(PLT)
	.loc 3 769 0
	b	.L233
.L239:
	.loc 3 771 0
	bl	glse_glBindAttribLocation(PLT)
	.loc 3 772 0
	mov	r0, #268
	bl	pop_batch_command(PLT)
	.loc 3 773 0
	b	.L233
.L241:
	.loc 3 775 0
	bl	glse_glBindFramebuffer(PLT)
	.loc 3 776 0
	mov	r0, #12
	bl	pop_batch_command(PLT)
	.loc 3 777 0
	b	.L233
.L244:
	.loc 3 779 0
	bl	glse_glBlendFuncSeparate(PLT)
	.loc 3 780 0
	mov	r0, #20
	bl	pop_batch_command(PLT)
	.loc 3 781 0
	b	.L233
.L243:
	.loc 3 783 0
	bl	glse_glBlendEquationSeparate(PLT)
	.loc 3 784 0
	mov	r0, #12
	bl	pop_batch_command(PLT)
	.loc 3 785 0
	b	.L233
.L246:
	.loc 3 787 0
	bl	glse_glClear(PLT)
	.loc 3 788 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 789 0
	b	.L233
.L247:
	.loc 3 791 0
	bl	glse_glClearColor(PLT)
	.loc 3 792 0
	mov	r0, #20
	bl	pop_batch_command(PLT)
	.loc 3 793 0
	b	.L233
.L249:
	.loc 3 795 0
	bl	glse_glCompileShader(PLT)
	.loc 3 796 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 797 0
	b	.L233
.L251:
	.loc 3 799 0
	bl	glse_glDeleteProgram(PLT)
	.loc 3 800 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 801 0
	b	.L233
.L252:
	.loc 3 803 0
	bl	glse_glDeleteShader(PLT)
	.loc 3 804 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 805 0
	b	.L233
.L253:
	.loc 3 807 0
	bl	glse_glDeleteTextures(PLT)
	.loc 3 808 0
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	pop_batch_command(PLT)
	.loc 3 809 0
	b	.L233
.L254:
	.loc 3 811 0
	bl	glse_glDepthFunc(PLT)
	.loc 3 812 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 813 0
	b	.L233
.L257:
	.loc 3 815 0
	bl	glse_glDisable(PLT)
	.loc 3 816 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 817 0
	b	.L233
.L258:
	.loc 3 819 0
	bl	glse_glDisableVertexAttribArray(PLT)
	.loc 3 820 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 821 0
	b	.L233
.L259:
	.loc 3 823 0
	bl	glse_glDrawArrays(PLT)
	.loc 3 824 0
	mov	r0, #16
	bl	pop_batch_command(PLT)
	.loc 3 825 0
	b	.L233
.L260:
	.loc 3 827 0
	bl	glse_glDrawElements(PLT)
	.loc 3 828 0
	mov	r0, #20
	bl	pop_batch_command(PLT)
	.loc 3 829 0
	b	.L233
.L261:
	.loc 3 831 0
	bl	glse_glEnable(PLT)
	.loc 3 832 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 833 0
	b	.L233
.L262:
	.loc 3 835 0
	bl	glse_glEnableVertexAttribArray(PLT)
	.loc 3 836 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 837 0
	b	.L233
.L263:
	.loc 3 839 0
	bl	glse_glFlush(PLT)
	.loc 3 840 0
	mov	r0, #4
	bl	pop_batch_command(PLT)
	.loc 3 841 0
	b	.L233
.L266:
	.loc 3 843 0
	bl	glse_glLinkProgram(PLT)
	.loc 3 844 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 845 0
	b	.L233
.L267:
	.loc 3 847 0
	bl	glse_glPixelStorei(PLT)
	.loc 3 848 0
	mov	r0, #12
	bl	pop_batch_command(PLT)
	.loc 3 849 0
	b	.L233
.L272:
	.loc 3 851 0
	bl	glse_glTexImage2D(PLT)
	.loc 3 852 0
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	pop_batch_command(PLT)
	.loc 3 853 0
	b	.L233
.L273:
	.loc 3 855 0
	bl	glse_glTexParameteri(PLT)
	.loc 3 856 0
	mov	r0, #16
	bl	pop_batch_command(PLT)
	.loc 3 857 0
	b	.L233
.L274:
	.loc 3 859 0
	bl	glse_glUniform1f(PLT)
	.loc 3 860 0
	mov	r0, #12
	bl	pop_batch_command(PLT)
	.loc 3 861 0
	b	.L233
.L275:
	.loc 3 863 0
	bl	glse_glUniform4fv(PLT)
	.loc 3 864 0
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	pop_batch_command(PLT)
	.loc 3 865 0
	b	.L233
.L276:
	.loc 3 867 0
	bl	glse_glUniformMatrix4fv(PLT)
	.loc 3 868 0
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	pop_batch_command(PLT)
	.loc 3 869 0
	b	.L233
.L277:
	.loc 3 871 0
	bl	glse_glUseProgram(PLT)
	.loc 3 872 0
	mov	r0, #8
	bl	pop_batch_command(PLT)
	.loc 3 873 0
	b	.L233
.L278:
	.loc 3 875 0