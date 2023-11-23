#@copyright : Sherif

CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2 
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
projectName=sherif

all: $(projectName).bin
	@echo "Build Is Done"

%.o: %.c 
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@
	
$(projectName).elf: $(OBJ) $(ASOBJ) 
	$(CC)ld.exe -T linkerscript.ld $(LIBS) $(OBJ) $(ASOBJ) -o $(projectName).elf -Map=$(projectName).map

$(projectName).bin: $(projectName).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin

clean:
	rm *.elf *.bin	 	