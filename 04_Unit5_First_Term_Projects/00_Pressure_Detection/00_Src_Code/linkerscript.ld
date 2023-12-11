/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : linkerscript.ld
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


MEMORY
{
		flash(RX) : ORIGIN = 0x08000000 , LENGTH = 128K
		sram(RWX) : ORIGIN = 0x20000000 , LENGTH = 20K
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
		  	  _STACK_TOP = . ;
	}> sram
}