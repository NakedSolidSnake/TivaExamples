################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
OSOperation/OSAdc.obj: ../OSOperation/OSAdc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="/home/solid/Desktop/examples/abstraction_freertos" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/include" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="OSOperation/OSAdc.d" --obj_directory="OSOperation" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

OSOperation/OSDisplay.obj: ../OSOperation/OSDisplay.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="/home/solid/Desktop/examples/abstraction_freertos" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/include" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="OSOperation/OSDisplay.d" --obj_directory="OSOperation" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

OSOperation/OSOperation.obj: ../OSOperation/OSOperation.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="/home/solid/Desktop/examples/abstraction_freertos" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/include" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="OSOperation/OSOperation.d" --obj_directory="OSOperation" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

OSOperation/OSSystem.obj: ../OSOperation/OSSystem.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="/home/solid/Desktop/examples/abstraction_freertos" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/include" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="OSOperation/OSSystem.d" --obj_directory="OSOperation" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

OSOperation/OSTimer.obj: ../OSOperation/OSTimer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="/home/solid/Desktop/examples/abstraction_freertos" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/include" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="OSOperation/OSTimer.d" --obj_directory="OSOperation" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

OSOperation/OSUart.obj: ../OSOperation/OSUart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="/home/solid/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="/home/solid/Desktop/examples/abstraction_freertos" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/include" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS" --include_path="/home/solid/TivaWare_C_Series-2.1.4.178/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="OSOperation/OSUart.d" --obj_directory="OSOperation" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


