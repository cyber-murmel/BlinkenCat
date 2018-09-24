MCU ?= attiny85
AVRDUDE_PROGRAMMER ?= usbasp
PORT ?= /dev/ttyUSB0

AVRCC ?= avr-gcc
AVRFLASH ?= avrdude
AVROBJCOPY ?= avr-objcopy

MCU_FLAGS = -mmcu=${MCU} -DF_CPU=8000000UL

SHARED_FLAGS = ${MCU_FLAGS} -I. -Os -Wall -Wextra -pedantic
SHARED_FLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
SHARED_FLAGS += -flto -mstrict-X

ifeq (${LANG},DE)
	SHARED_FLAGS += -DLANG_DE
endif

CFLAGS += ${SHARED_FLAGS} -std=c99

ASFLAGS += ${MCU_FLAGS} -wA,--warn
LDFLAGS += -Wl,--gc-sections

AVRFLAGS += -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
AVRFLAGS += -U flash:w:build/main.hex
AVRFLAGS += -P ${PORT}
#AVRFLAGS += -U eeprom:w:main.eep

HEADERS  = $(wildcard src/*.h)
ASFILES  = $(wildcard src/*.S)
CFILES   = $(wildcard src/*.c)
OBJECTS  = ${CFILES:src/%.c=build/%.o} ${CXXFILES:src/%.cc=build/%.o} ${ASFILES:src/%.S=build/%.o}

all: build build/main.elf

build:
	mkdir -p build

build/%.hex: build/%.elf
	${AVROBJCOPY} -O ihex -R .eeprom $< $@

build/%.o: src/%.c ${HEADERS}
	${AVRCC} ${CFLAGS} -o $@ $< -c -Wl,-Map=main.map,--cref

build/main.elf: ${OBJECTS}
	${AVRCC} ${CFLAGS} -o $@ $^ ${LDFLAGS}
	@echo
	@avr-size --format=avr --mcu=${MCU} $@

flash: program

program: build/main.hex #main.eep
	${AVRFLASH} -p ${MCU} -c ${AVRDUDE_PROGRAMMER} ${AVRFLAGS}

clean:
	rm -rf build

.PHONY: all program secsize funsize clean
