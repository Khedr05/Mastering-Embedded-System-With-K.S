/*
	startup_cortexM3.s
	Sherif Ashraf Khedr
*/


/* SRAM -> 0x20000000 */

.section .vectors
.word 0x20001000		/* Stack Top Address */
.word _reset			/* 1 Reset 			 */
.word  vector_handler	/* 2 NMI 			 */
.word  vector_handler	/* 3 Hard Fault 	 */
.word  vector_handler	/* 4 MM Fault 		 */
.word  vector_handler	/* 5 Bus Fault 		 */
.word  vector_handler	/* 6 Usage Fault  	 */
.word  vector_handler	/* 7 RESERVED 	 	 */
.word  vector_handler	/* 8 RESERVED 		 */
.word  vector_handler	/* 9 RESERVED 		 */
.word  vector_handler	/* 10 RESERVED 		 */
.word  vector_handler	/* 11 SV call 		 */
.word  vector_handler	/* 12 Debug RESERVED */
.word  vector_handler	/* 13 RESERVED 	 	 */
.word  vector_handler	/* 14 PendSV 		 */
.word  vector_handler	/* 15 SysTick 		 */
.word  vector_handler	/* 16 IRQ0 			 */
.word  vector_handler	/* 17 IRQ1 			 */
.word  vector_handler	/* 18 IRQ2 			 */
.word  vector_handler	/* 19 ... 			 */
	   					/* On to IRQ67 		 */

.section .text

_reset:
		bl main 
		b .
		
.thumb_func	
vector_handler:
	   b _reset


