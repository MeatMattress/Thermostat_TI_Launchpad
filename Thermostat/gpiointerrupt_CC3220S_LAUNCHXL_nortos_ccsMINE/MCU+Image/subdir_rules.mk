################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/123tb/git/TI_Launchpad_Morse/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE" --include_path="C:/Users/123tb/git/TI_Launchpad_Morse/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/kernel/nortos/posix" --include_path="C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/source/ti/drivers" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/examples/nortos/CC3220S_LAUNCHXL/drivers" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/examples/rtos/CC3220S_LAUNCHXL/drivers" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/123tb/git/TI_Launchpad_Morse/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE/MCU+Image/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1097446209: ../gpiointerrupt.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/Texas_Instruments/CCS/ccs/utils/sysconfig_1.7.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_4_40_00_07/.metadata/product.json" -o "syscfg" --compiler ccs "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1097446209 ../gpiointerrupt.syscfg
syscfg/ti_drivers_config.h: build-1097446209
syscfg/ti_utils_build_linker.cmd.genlibs: build-1097446209
syscfg/syscfg_c.rov.xs: build-1097446209
syscfg/ti_utils_runtime_model.gv: build-1097446209
syscfg/ti_utils_runtime_Makefile: build-1097446209
syscfg/: build-1097446209

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/123tb/git/TI_Launchpad_Morse/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE" --include_path="C:/Users/123tb/git/TI_Launchpad_Morse/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/kernel/nortos/posix" --include_path="C:/Texas_Instruments/CCS/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/source/ti/drivers" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/examples/nortos/CC3220S_LAUNCHXL/drivers" --include_path="C:/ti/simplelink_cc32xx_sdk_4_40_00_07/examples/rtos/CC3220S_LAUNCHXL/drivers" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/123tb/git/TI_Launchpad_Morse/gpiointerrupt_CC3220S_LAUNCHXL_nortos_ccsMINE/MCU+Image/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1450887471: ../image.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/Texas_Instruments/CCS/ccs/utils/sysconfig_1.7.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_4_40_00_07/.metadata/product.json" -o "syscfg" --compiler ccs "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_net_wifi_config.json: build-1450887471 ../image.syscfg
syscfg/: build-1450887471


