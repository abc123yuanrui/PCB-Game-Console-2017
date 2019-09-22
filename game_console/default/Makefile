################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../game_console.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
game_console.o

OBJS_AS_ARGS +=  \
game_console.o

C_DEPS +=  \
game_console.d

C_DEPS_AS_ARGS +=  \
game_console.d

OUTPUT_FILE_PATH +=game_console.elf

OUTPUT_FILE_PATH_AS_ARGS +=game_console.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler



./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 0.0.0
	$(QUOTE)E:\WINAVR\bin\avr-gcc.exe$(QUOTE)  -x c -DF_CPU=7379300UL  -I"E:\AtmelStudio\7.0\Packs\atmel\ATmega_DFP\1.2.132\include"  -Os -ffunction-sections -fdata-sections -Wall  -mmcu=atmega16  -c -gdwarf-2 -fsigned-char -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 0.0.0
	$(QUOTE)E:\WINAVR\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="game_console.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections  -mmcu=atmega16   
	@echo Finished building target: $@
	"E:\WINAVR\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "game_console.elf" "game_console.hex"
	"E:\WINAVR\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "game_console.elf" "game_console.eep" || exit 0
	"E:\WINAVR\bin\avr-objdump.exe" -h -S "game_console.elf" > "game_console.lss"
	"E:\WINAVR\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "game_console.elf" "game_console.srec"
	"E:\WINAVR\bin\avr-size.exe" "game_console.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "game_console.elf" "game_console.a" "game_console.hex" "game_console.lss" "game_console.eep" "game_console.map" "game_console.srec" "game_console.usersignatures"
	