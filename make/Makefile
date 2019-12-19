#)              _         
#)  ___ ___ _ _|_|___ ___ 
#) |  _| .'|_'_| |_ -|_ -|
#) |_| |__,|_,_|_|___|___|
#)         raxiss (c) 2019

PROJECT                 := oricXmas2019
PROJECT_DIR             := $(shell pwd)
PROJECT_LABEL           := oricXmas2019

# # # Only for FlopyBuilder
# PROJECT_DSK           := $(PROJECT).dsk

# # # Autorun main project file
PROJECT_AUTORUN         := 1

# # # Leave DOS
PROJECT_QUITDOS         := 1

# # # 6502, 65816
CPU                     := 6502

# # # Toolchain OSDK or CC65
TOOLCHAIN               := OSDK

# # # 
START_ADDRESS           := $(shell echo $$((0x0600)))

ATAPS                   :=
BTAPS                   :=
CTAPS                   := $(PROJECT) 
OTAPS                   := 

TAPS                    := $(addsuffix .tap,$(ATAPS) $(BTAPS) $(CTAPS) $(OTAPS))

# 

$(PROJECT)_SRC          := main.c xmas.s mymplayer.s song.s
$(PROJECT)_AUTORUN      := 1
$(PROJECT)_ADDRESS      := $(START_ADDRESS)
$(PROJECT)_ACPP         := 0

#
include Makefile.local

OSDK                    := $(OSDK_DIR)
OSDK_OPT                := 0
CC65                    := $(CC65_DIR)
CC65_ALIGNED            := 0

EMU                     := ./oricutron
EMUDIR                  := $(EMUL_DIR)
EMUARG                  := -ma
EMUARG                  += --serial none 
EMUARG                  += --vsynchack off
EMUARG                  += -s $(PROJECT_DIR)/$(PROJECT).sym 
EMUARG                  += -r :$(PROJECT_DIR)/$(PROJECT).brk
EMUARG                  += #-r $(START_ADDRESS)

VPATH                   := $(VPATH) ..

PREPARE                 := prepare
FINALIZE                := finalize

#
include $($(TOOLCHAIN))/atmos.make

AFLAGS                  += $(addprefix -I,$(VPATH))
AFLAGS                  += -DASSEMBLER
AFLAGS                  += -DSTART_ADDRESS=$(START_ADDRESS)

CFLAGS                  += $(addprefix -I,$(VPATH))
CFLAGS                  += -DSTART_ADDRESS=$(START_ADDRESS)

# $(PROJECT)_AFLAGS       +=
# $(PROJECT)_CFLAGS       +=
# $(PROJECT)_LFLAGS       +=

TEMP_FILES              +=

prepare:
	@echo "Building with $(TOOLCHAIN)..."

finalize: #hxc
	@([ -e $(PROJECT)_dsk.hfe ] && cp -f $(PROJECT)_dsk.hfe DSKA0000.HFE) || echo -n
	@([ -e $(PROJECT).brk ] || touch $(PROJECT).brk) || echo -n
	@echo   "[NFO]   ----------------------"
	@printf "[MEM]   main  : #%.4X .. #%.4X\\n" $$(($(START_ADDRESS))) $$(expr `cat $(PROJECT) | wc -c` + $$(($(START_ADDRESS))))
	@echo "Done"
