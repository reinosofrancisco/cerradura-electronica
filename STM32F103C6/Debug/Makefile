###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = STM32F103C6
COMPILER = "Keil for ARM"
TARGET = Debug
SHELL = C:\WINDOWS\system32\cmd.exe

## Tools general options
ASMFLAGS=--cpu=cortex-m3 --thumb -g
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -I../../../../../../Keil_v5/ARM/CMSIS/Include -g
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/main.o: TOOL=CC
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/main.c
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/SYSTEM~1.o: TOOL=CC
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/system_stm32f1xx.c
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/STARTU~1.o: TOOL=ASM
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/startup_stm32f103.s
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/KEYPAD~1.o: TOOL=CC
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/keypadScan.c
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/lcd.o: TOOL=CC
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/lcd.c
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/MEF.o: TOOL=CC
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/MEF.c
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/seos.o: TOOL=CC
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/seos.c
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/timer.o: TOOL=CC
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/timer.c
#     C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/Debug/utils.o: TOOL=CC
#        C:/Users/Reino/Desktop/Cerradura Electronica/STM32F103C6/utils.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o SYSTEM~1.o STARTU~1.o KEYPAD~1.o lcd.o MEF.o seos.o timer.o utils.o 
	$(LD)  $(LDFLAGS)  "main.o" "SYSTEM~1.o" "STARTU~1.o" "KEYPAD~1.o" "lcd.o" "MEF.o" "seos.o" "timer.o" "utils.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

SYSTEM~1.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "SYSTEM~1.o"

STARTU~1.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "STARTU~1.o"

KEYPAD~1.o:	../keypadScan.c 
	$(CC) $(CCFLAGS)  "../keypadScan.c" -c -o "KEYPAD~1.o"

lcd.o:	../lcd.c 
	$(CC) $(CCFLAGS)  "../lcd.c" -c -o "lcd.o"

MEF.o:	../MEF.c 
	$(CC) $(CCFLAGS)  "../MEF.c" -c -o "MEF.o"

seos.o:	../seos.c 
	$(CC) $(CCFLAGS)  "../seos.c" -c -o "seos.o"

timer.o:	../timer.c 
	$(CC) $(CCFLAGS)  "../timer.c" -c -o "timer.o"

utils.o:	../utils.c 
	$(CC) $(CCFLAGS)  "../utils.c" -c -o "utils.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf SYSTEM~1.o
	rm -rf STARTU~1.o
	rm -rf KEYPAD~1.o
	rm -rf lcd.o
	rm -rf MEF.o
	rm -rf seos.o
	rm -rf timer.o
	rm -rf utils.o
