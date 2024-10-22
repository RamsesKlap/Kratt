# For anyone interested in openocd usage for any other target, visit these sites:
# https://openocd.org/doc/html/About.html#What-is-OpenOCD_003f
# https://openocd.org/doc/html/Flash-Programming.html
openocd -f board/ti_ek-tm4c123gxl.cfg -c "program gcc/main.axf verify reset exit"