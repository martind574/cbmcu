/***********************************************************************************
*	Copyright 2005 Anglia Design
*	This demo code and associated components are provided as is and has no warranty,
*	implied or otherwise.  You are free to use/modify any of the provided
*	code at your own risk in your applications with the expressed limitation
*	of liability (see below)
* 
*	LIMITATION OF LIABILITY:   ANGLIA OR ANGLIA DESIGNS SHALL NOT BE LIABLE FOR ANY
*	LOSS OF PROFITS, LOSS OF USE, LOSS OF DATA, INTERRUPTION OF BUSINESS, NOR FOR
*	INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND WHETHER UNDER
*	THIS AGREEMENT OR OTHERWISE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*
*	Author			: Spencer Oliver
*	Web     		: www.anglia-designs.com
*
***********************************************************************************/

	.text
	.arm

	.global 	read_dbg_control
	.global 	read_dbg_data
	.global 	write_dbg_data

/* Read debug comms channel control reg */
	
read_dbg_control:
	MRC		p14, 0, r0, c0, c0
	MOV		pc, lr

/* Read debug comms channel, data in r0 */

read_dbg_data:
	MRC		p14, 0, r0, c1, c0
	MOV		pc, lr

/* Write to debug comms channel, data returned in r0 */

write_dbg_data:
	MCR		p14, 0, r0, c1, c0
	MOV		pc, lr

	.end
	
