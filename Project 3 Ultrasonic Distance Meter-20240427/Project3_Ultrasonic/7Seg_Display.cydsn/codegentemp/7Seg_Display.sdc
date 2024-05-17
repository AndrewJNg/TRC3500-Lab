# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Monash\Y3S2\TRC3500\TRC3500-Lab\Project 3 Ultrasonic Distance Meter-20240427\Project3_Ultrasonic\7Seg_Display.cydsn\7Seg_Display.cyprj
# Date: Fri, 17 May 2024 02:52:58 GMT
#set_units -time ns
create_clock -name {Transmitter_Clk(routed)} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/dclk_2}]]
create_clock -name {Display_Clk(routed)} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/dclk_3}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {UART_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 313 627} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {Transmitter_Clk} -source [get_pins {ClockBlock/clk_sync}] -edges {1 601 1201} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {Display_Clk} -source [get_pins {ClockBlock/clk_sync}] -edges {1 24001 48001} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 24001 48001} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} [list [get_pins {ClockBlock/dclk_glb_0}]]


# Component constraints for D:\Monash\Y3S2\TRC3500\TRC3500-Lab\Project 3 Ultrasonic Distance Meter-20240427\Project3_Ultrasonic\7Seg_Display.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Monash\Y3S2\TRC3500\TRC3500-Lab\Project 3 Ultrasonic Distance Meter-20240427\Project3_Ultrasonic\7Seg_Display.cydsn\7Seg_Display.cyprj
# Date: Fri, 17 May 2024 02:52:53 GMT
