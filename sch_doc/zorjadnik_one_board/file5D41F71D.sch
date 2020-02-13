EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Схема дисплейного модуля"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L zorjadnik-rescue:POT-zorjadnik-rescue RV1
U 1 1 5D42E9FD
P 5200 1300
AR Path="/5D42E9FD" Ref="RV1"  Part="1" 
AR Path="/5D41F71E/5D42E9FD" Ref="RV1"  Part="1" 
F 0 "RV1" V 5025 1300 50  0000 C CNN
F 1 "POT" V 5100 1300 50  0000 C CNN
F 2 "escor:СП3-4" H 5200 1300 50  0001 C CNN
F 3 "" H 5200 1300 50  0001 C CNN
	1    5200 1300
	-1   0    0    1   
$EndComp
$Comp
L zorjadnik-rescue:+3.3V-power1 #PWR021
U 1 1 5D42EA04
P 5200 1150
F 0 "#PWR021" H 5200 1000 50  0001 C CNN
F 1 "+3.3V" H 5200 1290 50  0000 C CNN
F 2 "" H 5200 1150 50  0001 C CNN
F 3 "" H 5200 1150 50  0001 C CNN
	1    5200 1150
	1    0    0    -1  
$EndComp
$Comp
L led_digits:LED_3digit D1
U 1 1 5D42EA0A
P 7350 2900
F 0 "D1" H 7350 3350 60  0000 C CNN
F 1 "LED_3digit" H 7350 2450 60  0000 C CNN
F 2 "escor:FYT-3631_minimal" H 7350 2900 60  0001 C CNN
F 3 "" H 7350 2900 60  0001 C CNN
	1    7350 2900
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik-rescue:+3.3V-power1 #PWR023
U 1 1 5D42EA17
P 6000 1800
F 0 "#PWR023" H 6000 1650 50  0001 C CNN
F 1 "+3.3V" H 6000 1940 50  0000 C CNN
F 2 "" H 6000 1800 50  0001 C CNN
F 3 "" H 6000 1800 50  0001 C CNN
	1    6000 1800
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik-rescue:GND-power1 #PWR027
U 1 1 5D42EA59
P 6000 5900
F 0 "#PWR027" H 6000 5650 50  0001 C CNN
F 1 "GND" H 6000 5750 50  0000 C CNN
F 2 "" H 6000 5900 50  0001 C CNN
F 3 "" H 6000 5900 50  0001 C CNN
	1    6000 5900
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik-rescue:C-zorjadnik-rescue C6
U 1 1 5D42EA93
P 6150 2050
AR Path="/5D42EA93" Ref="C6"  Part="1" 
AR Path="/5D41F71E/5D42EA93" Ref="C6"  Part="1" 
F 0 "C6" H 6175 2150 50  0000 L CNN
F 1 "100nF" H 6175 1950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 1900 50  0001 C CNN
F 3 "" H 6150 2050 50  0001 C CNN
	1    6150 2050
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik-rescue:GND-power1 #PWR032
U 1 1 5D42EA9A
P 6150 2250
F 0 "#PWR032" H 6150 2000 50  0001 C CNN
F 1 "GND" H 6150 2100 50  0000 C CNN
F 2 "" H 6150 2250 50  0001 C CNN
F 3 "" H 6150 2250 50  0001 C CNN
	1    6150 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 1800 6000 1850
Wire Wire Line
	5550 3150 5600 3150
Wire Wire Line
	5600 2850 5550 2850
Wire Wire Line
	5450 3050 5600 3050
Wire Wire Line
	6000 1850 6150 1850
Connection ~ 6000 1850
$Comp
L zorjadnik-rescue:GND-power1 #PWR034
U 1 1 5D42EAEA
P 5200 1450
F 0 "#PWR034" H 5200 1200 50  0001 C CNN
F 1 "GND" H 5200 1300 50  0000 C CNN
F 2 "" H 5200 1450 50  0001 C CNN
F 3 "" H 5200 1450 50  0001 C CNN
	1    5200 1450
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik-rescue:GND-power1 #PWR035
U 1 1 5D42EAF0
P 5550 3200
F 0 "#PWR035" H 5550 2950 50  0001 C CNN
F 1 "GND" H 5550 3050 50  0000 C CNN
F 2 "" H 5550 3200 50  0001 C CNN
F 3 "" H 5550 3200 50  0001 C CNN
	1    5550 3200
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik-rescue:CircuitBreaker_1P-Device1 CB2
U 1 1 5D430D68
P 5350 1950
F 0 "CB2" V 5300 1950 50  0000 L CNN
F 1 "select" V 5400 1950 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 5350 1950 50  0001 C CNN
F 3 "" H 5350 1950 50  0001 C CNN
	1    5350 1950
	0    1    1    0   
$EndComp
$Comp
L zorjadnik-rescue:GND-power1 #PWR036
U 1 1 5D432F85
P 5700 2000
F 0 "#PWR036" H 5700 1750 50  0001 C CNN
F 1 "GND" H 5700 1850 50  0000 C CNN
F 2 "" H 5700 2000 50  0001 C CNN
F 3 "" H 5700 2000 50  0001 C CNN
	1    5700 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1800 5700 1800
Wire Wire Line
	5700 1800 5700 1950
Wire Wire Line
	5650 1950 5700 1950
Connection ~ 5700 1950
Wire Wire Line
	6150 1850 6150 1900
Wire Wire Line
	6150 2200 6150 2250
Wire Wire Line
	5550 3150 5550 3200
Wire Wire Line
	5700 1950 5700 2000
Entry Wire Line
	6650 2650 6750 2550
Entry Wire Line
	6650 2750 6750 2650
Entry Wire Line
	6650 2850 6750 2750
Entry Wire Line
	6650 2950 6750 2850
Entry Wire Line
	6650 3050 6750 2950
Entry Wire Line
	6650 3150 6750 3050
Entry Wire Line
	6650 3250 6750 3150
Entry Wire Line
	6650 3350 6750 3250
Entry Wire Line
	6550 3150 6650 3050
Entry Wire Line
	6550 2950 6650 2850
Entry Wire Line
	6550 2850 6650 2750
Entry Wire Line
	6550 2750 6650 2650
Wire Wire Line
	6400 2750 6550 2750
Wire Wire Line
	6400 2850 6550 2850
Wire Wire Line
	6400 2950 6550 2950
Wire Wire Line
	6400 3150 6550 3150
Wire Wire Line
	6750 3250 6850 3250
Wire Wire Line
	6750 3150 6850 3150
Wire Wire Line
	6750 3050 6850 3050
Wire Wire Line
	6850 2950 6750 2950
Wire Wire Line
	6750 2850 6850 2850
Wire Wire Line
	6850 2750 6750 2750
Wire Wire Line
	6750 2650 6850 2650
Wire Wire Line
	6850 2550 6750 2550
Text Label 6750 2550 0    50   ~ 0
A
Text Label 6750 2650 0    50   ~ 0
B
Text Label 6750 2750 0    50   ~ 0
C
Text Label 6750 2850 0    50   ~ 0
D
Text Label 6750 2950 0    50   ~ 0
E
Text Label 6750 3050 0    50   ~ 0
F
Text Label 6750 3150 0    50   ~ 0
G
Text Label 6750 3250 0    50   ~ 0
DP
Text Label 6450 2950 0    50   ~ 0
E
Text Label 6450 3150 0    50   ~ 0
D
Text Label 6450 5000 0    50   ~ 0
DP
Text Label 6450 4900 0    50   ~ 0
C
Text Label 6450 5100 0    50   ~ 0
G
Text Label 6450 5200 0    50   ~ 0
F
Text Label 6450 2850 0    50   ~ 0
A
$Comp
L zorjadnik-rescue:R-Device1 R21
U 1 1 5D6E0909
P 8050 2900
F 0 "R21" V 8050 2750 50  0000 C CNN
F 1 "200" V 8050 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7980 2900 50  0001 C CNN
F 3 "~" H 8050 2900 50  0001 C CNN
	1    8050 2900
	0    1    1    0   
$EndComp
$Comp
L zorjadnik-rescue:R-Device1 R22
U 1 1 5D6EBD26
P 8050 2800
F 0 "R22" V 7950 2800 50  0000 C CNN
F 1 "200" V 8050 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7980 2800 50  0001 C CNN
F 3 "~" H 8050 2800 50  0001 C CNN
	1    8050 2800
	0    1    1    0   
$EndComp
$Comp
L zorjadnik-rescue:R-Device1 R20
U 1 1 5D6F1DFE
P 8050 3000
F 0 "R20" V 7950 3000 50  0000 C CNN
F 1 "200" V 8050 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7980 3000 50  0001 C CNN
F 3 "~" H 8050 3000 50  0001 C CNN
	1    8050 3000
	0    -1   -1   0   
$EndComp
$Comp
L zorjadnik-rescue:74HC595-74xx1 U4
U 1 1 5D50D654
P 6000 5200
AR Path="/5D50D654" Ref="U4"  Part="1" 
AR Path="/5D41F71E/5D50D654" Ref="U4"  Part="1" 
F 0 "U4" H 5700 5750 50  0000 C CNN
F 1 "74HC595" H 5700 4550 50  0000 C CNN
F 2 "Package_SO:SOP-16_4.55x10.3mm_P1.27mm" H 6000 5200 50  0001 C CNN
F 3 "" H 6000 5200 50  0001 C CNN
	1    6000 5200
	1    0    0    -1  
$EndComp
Entry Wire Line
	6550 5200 6650 5100
Entry Wire Line
	8300 2800 8400 2700
Entry Wire Line
	8300 2900 8400 2800
Entry Wire Line
	8300 3000 8400 2900
Entry Wire Line
	6550 5300 6650 5200
Entry Wire Line
	6550 5400 6650 5300
Entry Wire Line
	6550 5500 6650 5400
Wire Wire Line
	7850 2800 7900 2800
Wire Wire Line
	7850 2900 7900 2900
Wire Wire Line
	7850 3000 7900 3000
NoConn ~ 6400 2550
NoConn ~ 6400 4800
NoConn ~ 6400 5700
Text Label 8200 2800 0    50   ~ 0
D1
Text Label 8200 2900 0    50   ~ 0
D2
Text Label 8200 3000 0    50   ~ 0
D3
Wire Wire Line
	8200 2800 8300 2800
Wire Wire Line
	8200 2900 8300 2900
Wire Wire Line
	8200 3000 8300 3000
Text Label 6450 2750 0    50   ~ 0
D1
Text Label 6450 5500 0    50   ~ 0
B
Text Label 6450 5300 0    50   ~ 0
D2
Text Label 6450 5400 0    50   ~ 0
D3
Wire Wire Line
	6400 3450 6450 3450
Wire Wire Line
	5550 4800 5600 4800
Wire Wire Line
	5450 5300 5600 5300
Wire Wire Line
	5350 5000 5600 5000
Wire Bus Line
	6650 3550 8400 3550
Wire Wire Line
	6400 5200 6550 5200
$Comp
L zorjadnik-rescue:+3.3V-power1 #PWR0109
U 1 1 5D629A6A
P 6000 4100
F 0 "#PWR0109" H 6000 3950 50  0001 C CNN
F 1 "+3.3V" H 6000 4240 50  0000 C CNN
F 2 "" H 6000 4100 50  0001 C CNN
F 3 "" H 6000 4100 50  0001 C CNN
	1    6000 4100
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik-rescue:C-zorjadnik-rescue C?
U 1 1 5D629A70
P 6150 4350
AR Path="/5D629A70" Ref="C?"  Part="1" 
AR Path="/5D41F71E/5D629A70" Ref="C9"  Part="1" 
F 0 "C9" H 6175 4450 50  0000 L CNN
F 1 "100nF" H 6175 4250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 4200 50  0001 C CNN
F 3 "" H 6150 4350 50  0001 C CNN
	1    6150 4350
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik-rescue:GND-power1 #PWR0110
U 1 1 5D629A76
P 6150 4500
F 0 "#PWR0110" H 6150 4250 50  0001 C CNN
F 1 "GND" H 6150 4350 50  0000 C CNN
F 2 "" H 6150 4500 50  0001 C CNN
F 3 "" H 6150 4500 50  0001 C CNN
	1    6150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4100 6000 4150
Wire Wire Line
	6150 4200 6150 4150
Wire Wire Line
	6150 4150 6000 4150
Connection ~ 6000 4150
$Comp
L zorjadnik-rescue:GND-power1 #PWR0111
U 1 1 5D6460F2
P 6000 3650
F 0 "#PWR0111" H 6000 3400 50  0001 C CNN
F 1 "GND" H 6000 3500 50  0000 C CNN
F 2 "" H 6000 3650 50  0001 C CNN
F 3 "" H 6000 3650 50  0001 C CNN
	1    6000 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3850 5550 3850
Wire Wire Line
	6450 3450 6450 3850
$Comp
L zorjadnik-rescue:GND-power1 #PWR0112
U 1 1 5D657AAB
P 5550 5500
F 0 "#PWR0112" H 5550 5250 50  0001 C CNN
F 1 "GND" H 5550 5350 50  0000 C CNN
F 2 "" H 5550 5500 50  0001 C CNN
F 3 "" H 5550 5500 50  0001 C CNN
	1    5550 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 5500 5550 5400
Wire Wire Line
	5550 5400 5600 5400
Connection ~ 6650 3550
Wire Wire Line
	6400 5400 6550 5400
Wire Wire Line
	6400 5300 6550 5300
Wire Wire Line
	6400 5500 6550 5500
Wire Wire Line
	6400 5100 6550 5100
Entry Wire Line
	6550 5100 6650 5000
Wire Wire Line
	6400 4900 6550 4900
Wire Wire Line
	6400 5000 6550 5000
Entry Wire Line
	6650 4800 6550 4900
Entry Wire Line
	6650 4900 6550 5000
NoConn ~ 6400 3250
NoConn ~ 6400 3050
NoConn ~ 6400 2650
Wire Wire Line
	6000 4150 6000 4400
Wire Wire Line
	5550 3850 5550 4800
Connection ~ 6000 4400
Wire Wire Line
	6000 4400 6000 4600
Wire Wire Line
	5600 5100 5500 5100
Wire Wire Line
	5500 5100 5500 4400
Wire Wire Line
	5500 4400 6000 4400
$Comp
L zorjadnik-rescue:CircuitBreaker_1P-Device1 CB1
U 1 1 5D430003
P 5350 1800
F 0 "CB1" V 5300 1800 50  0000 L CNN
F 1 "mode" V 5400 1800 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 5350 1800 50  0001 C CNN
F 3 "" H 5350 1800 50  0001 C CNN
	1    5350 1800
	0    1    1    0   
$EndComp
$Comp
L zorjadnik-rescue:74HC595-74xx1 U3
U 1 1 5D42E9F5
P 6000 2950
AR Path="/5D42E9F5" Ref="U3"  Part="1" 
AR Path="/5D41F71E/5D42E9F5" Ref="U3"  Part="1" 
F 0 "U3" H 5700 3500 50  0000 C CNN
F 1 "74HC595" H 5700 2300 50  0000 C CNN
F 2 "Package_SO:SOP-16_4.55x10.3mm_P1.27mm" H 6000 2950 50  0001 C CNN
F 3 "" H 6000 2950 50  0001 C CNN
	1    6000 2950
	1    0    0    -1  
$EndComp
Text GLabel 4650 1300 0    50   Input ~ 0
pot
Text GLabel 4650 1800 0    50   Input ~ 0
mode_but
Text GLabel 4650 1950 0    50   Input ~ 0
sel_but
Wire Wire Line
	6000 1850 6000 2250
Wire Wire Line
	5350 2750 5600 2750
Wire Wire Line
	5550 2850 5550 2250
Wire Wire Line
	5550 2250 6000 2250
Connection ~ 6000 2250
Wire Wire Line
	6000 2250 6000 2350
Text GLabel 4650 3050 0    50   Input ~ 0
SCK
Wire Wire Line
	5350 2750 5350 3050
Wire Wire Line
	4650 3050 5350 3050
Connection ~ 5350 3050
Wire Wire Line
	5350 3050 5350 5000
Text GLabel 4650 3150 0    50   Input ~ 0
ST_CP
Wire Wire Line
	5450 3050 5450 3150
Wire Wire Line
	4650 3150 5450 3150
Connection ~ 5450 3150
Wire Wire Line
	5450 3150 5450 5300
Text GLabel 4650 2550 0    50   Input ~ 0
MOSI
Wire Wire Line
	4650 2550 5600 2550
Wire Wire Line
	4650 1300 5050 1300
Wire Wire Line
	4650 1800 5050 1800
Wire Wire Line
	4650 1950 5050 1950
Wire Bus Line
	8400 2700 8400 3550
Wire Bus Line
	6650 3550 6650 5400
Wire Bus Line
	6650 2450 6650 3550
$EndSCHEMATC
