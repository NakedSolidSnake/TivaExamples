################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="/home/solid/Desktop/examples/abstraction_freertos" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/examples/boards/ek-tm4c123gxl" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/third_party" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/third_party/FreeRTOS/Source/include" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/third_party/FreeRTOS" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="/home/solid/Desktop/examples/abstraction_freertos" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/examples/boards/ek-tm4c123gxl" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/third_party" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/third_party/FreeRTOS/Source/include" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/third_party/FreeRTOS" --include_path="/home/solid/TivaWare_C_Series-2.1.3.156/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="startup_ccs.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


