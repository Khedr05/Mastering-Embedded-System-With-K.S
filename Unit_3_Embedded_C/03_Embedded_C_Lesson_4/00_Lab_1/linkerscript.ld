/* linker_script cortexM4

   Sherif Ashraf Khedr	
*/

MEMORY
{
		flash(RX) : ORIGIN = 0x00000000 , LENGTH = 512M
		sram(RWX) : ORIGIN = 0x20000000 , LENGTH = 512M
}

SECTIONS
{

	.text : {
		  			*(.vectors*)	
		  			*(.text*)	
		  			*(.rodata*)
		  			_E_TEXT = . ;	
	}> flash

	.data : {
				_S_DATA = . ;
		  		*(.data*)
		  		. = ALIGN(4) ;
		  		_E_DATA = . ;
	}> sram AT> flash

	.bss : {
			  _S_BSS = . ;
		  	  *(.bss*)
		  	  _E_BSS = . ;
		  	  . = ALIGN(4) ;
		  	  . = . + 0x1000 ;
	}> sram
}