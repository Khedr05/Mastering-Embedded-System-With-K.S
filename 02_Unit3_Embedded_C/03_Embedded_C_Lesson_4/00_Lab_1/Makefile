#@copyright : Sherif

CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m4 -gdwarf-2 -g 
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
projectName=unit3_lab_cortexM4

ifeq ($(OS),Windows_NT)
    CP = copy
else
    CP = cp
endif


all: $(projectName).bin
	@echo "Build Is Done"

%.o: %.c 
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@
	
$(projectName).elf: $(OBJ) $(ASOBJ) 
	$(CC)ld.exe -T linkerscript.ld $(LIBS) $(OBJ) $(ASOBJ) -o $(projectName).elf -Map=$(projectName).map
	$(CP) $(projectName).elf $(projectName).axf

$(projectName).bin: $(projectName).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin

clean:
	rm *.elf *.bin	 	