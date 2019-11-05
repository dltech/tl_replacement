A replacement for a driver in old ATX power suplies. May be conected direcly to
the coils of isolaton transformer. Powered by Vsb and controls only one channel
by current and volage. Includes submodule with display and simple menu. 
Functions:
Short circuit protection (checks every 0.1ms).
Current and voltage stabilization.
Mode for control charging 12V and 6V lead acid batteries.

It is based on libopencm3 libraries
# Instructions
 1. git clone https://github.com/libopencm3/libopencm3-template.git zarjadnik
 2. cd zarjadnik
 3. git submodule update --init # (Only needed once)
 4. make -C libopencm3 # (Only needed once)
 5. make -C zarjadnik
