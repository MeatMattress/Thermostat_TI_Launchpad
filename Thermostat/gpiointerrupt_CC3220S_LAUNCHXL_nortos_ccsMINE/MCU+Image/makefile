################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./gpiointerrupt.obj" \
"./syscfg/ti_drivers_config.obj" \
"./main_nortos.obj" \
"../cc32xxs_nortos.cmd" \
$(GEN_CMDS__FLAG) \
-lti_utils_build_linker.cmd.genlibs \
-l"ti/devices/cc32xx/driverlib/ccs/Release/driverlib.a" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.out \

EXE_OUTPUTS__QUOTED += \
"gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.out" \

BIN_OUTPUTS += \
gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.hex \

BIN_OUTPUTS__QUOTED += \
"gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.out"

# Tool invocations
gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.map" -i"C:/ti/simplelink_cc32xx_sdk_4_40_00_07/source" -i"C:/ti/simplelink_cc32xx_sdk_4_40_00_07/kernel/nortos" -i"C:/Users/123tb/git/TI_Launchpad_Morse/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE/MCU+Image/syscfg" -i"C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/lib" --diag_suppress=10063 --diag_wrap=off --display_error_number --warn_sections --xml_link_info="gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE_linkInfo.xml" --entry_point=resetISR --rom_model -o "gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: Arm Hex Utility'
	"C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armhex" --diag_wrap=off -o "gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "gpiointerrupt.obj" "syscfg\ti_drivers_config.obj" "main_nortos.obj" 
	-$(RM) "gpiointerrupt.d" "syscfg\ti_drivers_config.d" "main_nortos.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armobjcopy -O binary --only-section .text --only-section .const --only-section .cinit --only-section .resetVecs gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.out gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.bin
	-C:/ti/simplelink_cc32xx_sdk_4_40_00_07/source/ti/drivers/net/imagecreator/bin/SLImageCreator.exe syscfg create_image --sdk_path C:/ti/simplelink_cc32xx_sdk_4_40_00_07 --json C:\Users\123tb\git\TI_Launchpad_Morse\gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE\MCU+Image/syscfg/ti_drivers_net_wifi_config.json --file C:\Users\123tb\git\TI_Launchpad_Morse\gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE\MCU+Image/syscfg/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.sli --mcu  C:\Users\123tb\git\TI_Launchpad_Morse\gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE\MCU+Image/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE.bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

