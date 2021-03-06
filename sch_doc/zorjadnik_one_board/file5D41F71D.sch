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
L zorjadnik:POT-zorjadnik RV1
U 1 1 5D42E9FD
P 2700 1450
AR Path="/5D42E9FD" Ref="RV1"  Part="1" 
AR Path="/5D41F71E/5D42E9FD" Ref="RV1"  Part="1" 
F 0 "RV1" V 2525 1450 50  0000 C CNN
F 1 "POT" V 2600 1450 50  0000 C CNN
F 2 "escor:СП3-4" H 2700 1450 50  0001 C CNN
F 3 "" H 2700 1450 50  0001 C CNN
	1    2700 1450
	-1   0    0    1   
$EndComp
$Comp
L zorjadnik:+3.3V-power1 #PWR021
U 1 1 5D42EA04
P 2700 1300
F 0 "#PWR021" H 2700 1150 50  0001 C CNN
F 1 "+3.3V" H 2700 1440 50  0000 C CNN
F 2 "" H 2700 1300 50  0001 C CNN
F 3 "" H 2700 1300 50  0001 C CNN
	1    2700 1300
	1    0    0    -1  
$EndComp
$Comp
L led_digits:LED_3digit D1
U 1 1 5D42EA0A
P 4850 3050
F 0 "D1" H 4850 3500 60  0000 C CNN
F 1 "LED_3digit" H 4850 2600 60  0000 C CNN
F 2 "escor:FYT-3631_minimal" H 4850 3050 60  0001 C CNN
F 3 "" H 4850 3050 60  0001 C CNN
	1    4850 3050
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik:+3.3V-power1 #PWR023
U 1 1 5D42EA17
P 3500 1950
F 0 "#PWR023" H 3500 1800 50  0001 C CNN
F 1 "+3.3V" H 3500 2090 50  0000 C CNN
F 2 "" H 3500 1950 50  0001 C CNN
F 3 "" H 3500 1950 50  0001 C CNN
	1    3500 1950
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik:GND-power1 #PWR027
U 1 1 5D42EA59
P 3500 6050
F 0 "#PWR027" H 3500 5800 50  0001 C CNN
F 1 "GND" H 3500 5900 50  0000 C CNN
F 2 "" H 3500 6050 50  0001 C CNN
F 3 "" H 3500 6050 50  0001 C CNN
	1    3500 6050
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik:C-zorjadnik C6
U 1 1 5D42EA93
P 3650 2200
AR Path="/5D42EA93" Ref="C6"  Part="1" 
AR Path="/5D41F71E/5D42EA93" Ref="C6"  Part="1" 
F 0 "C6" H 3675 2300 50  0000 L CNN
F 1 "100nF" H 3675 2100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3688 2050 50  0001 C CNN
F 3 "" H 3650 2200 50  0001 C CNN
	1    3650 2200
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik:GND-power1 #PWR032
U 1 1 5D42EA9A
P 3650 2400
F 0 "#PWR032" H 3650 2150 50  0001 C CNN
F 1 "GND" H 3650 2250 50  0000 C CNN
F 2 "" H 3650 2400 50  0001 C CNN
F 3 "" H 3650 2400 50  0001 C CNN
	1    3650 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1950 3500 2000
Wire Wire Line
	3050 3300 3100 3300
Wire Wire Line
	3100 3000 3050 3000
Wire Wire Line
	2950 3200 3100 3200
Wire Wire Line
	3500 2000 3650 2000
Connection ~ 3500 2000
$Comp
L zorjadnik:GND-power1 #PWR034
U 1 1 5D42EAEA
P 2700 1600
F 0 "#PWR034" H 2700 1350 50  0001 C CNN
F 1 "GND" H 2700 1450 50  0000 C CNN
F 2 "" H 2700 1600 50  0001 C CNN
F 3 "" H 2700 1600 50  0001 C CNN
	1    2700 1600
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik:GND-power1 #PWR035
U 1 1 5D42EAF0
P 3050 3350
F 0 "#PWR035" H 3050 3100 50  0001 C CNN
F 1 "GND" H 3050 3200 50  0000 C CNN
F 2 "" H 3050 3350 50  0001 C CNN
F 3 "" H 3050 3350 50  0001 C CNN
	1    3050 3350
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik:CircuitBreaker_1P-Device1 CB2
U 1 1 5D430D68
P 2850 2100
F 0 "CB2" V 2800 2100 50  0000 L CNN
F 1 "select" V 2900 2100 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 2850 2100 50  0001 C CNN
F 3 "" H 2850 2100 50  0001 C CNN
	1    2850 2100
	0    1    1    0   
$EndComp
$Comp
L zorjadnik:GND-power1 #PWR036
U 1 1 5D432F85
P 3200 2150
F 0 "#PWR036" H 3200 1900 50  0001 C CNN
F 1 "GND" H 3200 2000 50  0000 C CNN
F 2 "" H 3200 2150 50  0001 C CNN
F 3 "" H 3200 2150 50  0001 C CNN
	1    3200 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1950 3200 1950
Wire Wire Line
	3200 1950 3200 2100
Wire Wire Line
	3150 2100 3200 2100
Connection ~ 3200 2100
Wire Wire Line
	3650 2000 3650 2050
Wire Wire Line
	3650 2350 3650 2400
Wire Wire Line
	3050 3300 3050 3350
Wire Wire Line
	3200 2100 3200 2150
Entry Wire Line
	4150 2800 4250 2700
Entry Wire Line
	4150 2900 4250 2800
Entry Wire Line
	4150 3000 4250 2900
Entry Wire Line
	4150 3100 4250 3000
Entry Wire Line
	4150 3200 4250 3100
Entry Wire Line
	4150 3300 4250 3200
Entry Wire Line
	4150 3400 4250 3300
Entry Wire Line
	4150 3500 4250 3400
Entry Wire Line
	4050 3300 4150 3200
Entry Wire Line
	4050 3100 4150 3000
Entry Wire Line
	4050 3000 4150 2900
Entry Wire Line
	4050 2900 4150 2800
Wire Wire Line
	3900 2900 4050 2900
Wire Wire Line
	3900 3000 4050 3000
Wire Wire Line
	3900 3100 4050 3100
Wire Wire Line
	3900 3300 4050 3300
Wire Wire Line
	4250 3400 4350 3400
Wire Wire Line
	4250 3300 4350 3300
Wire Wire Line
	4250 3200 4350 3200
Wire Wire Line
	4350 3100 4250 3100
Wire Wire Line
	4250 3000 4350 3000
Wire Wire Line
	4350 2900 4250 2900
Wire Wire Line
	4250 2800 4350 2800
Wire Wire Line
	4350 2700 4250 2700
Text Label 4250 2700 0    50   ~ 0
A
Text Label 4250 2800 0    50   ~ 0
B
Text Label 4250 2900 0    50   ~ 0
C
Text Label 4250 3000 0    50   ~ 0
D
Text Label 4250 3100 0    50   ~ 0
E
Text Label 4250 3200 0    50   ~ 0
F
Text Label 4250 3300 0    50   ~ 0
G
Text Label 4250 3400 0    50   ~ 0
DP
Text Label 3950 3100 0    50   ~ 0
E
Text Label 3950 3300 0    50   ~ 0
D
Text Label 3950 5150 0    50   ~ 0
DP
Text Label 3950 5050 0    50   ~ 0
C
Text Label 3950 5250 0    50   ~ 0
G
Text Label 3950 5350 0    50   ~ 0
F
Text Label 3950 3000 0    50   ~ 0
A
$Comp
L zorjadnik:R-Device1 R21
U 1 1 5D6E0909
P 5550 3050
F 0 "R21" V 5550 2900 50  0000 C CNN
F 1 "200" V 5550 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5480 3050 50  0001 C CNN
F 3 "~" H 5550 3050 50  0001 C CNN
	1    5550 3050
	0    1    1    0   
$EndComp
$Comp
L zorjadnik:R-Device1 R22
U 1 1 5D6EBD26
P 5550 2950
F 0 "R22" V 5450 2950 50  0000 C CNN
F 1 "200" V 5550 2950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5480 2950 50  0001 C CNN
F 3 "~" H 5550 2950 50  0001 C CNN
	1    5550 2950
	0    1    1    0   
$EndComp
$Comp
L zorjadnik:R-Device1 R20
U 1 1 5D6F1DFE
P 5550 3150
F 0 "R20" V 5450 3150 50  0000 C CNN
F 1 "200" V 5550 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5480 3150 50  0001 C CNN
F 3 "~" H 5550 3150 50  0001 C CNN
	1    5550 3150
	0    -1   -1   0   
$EndComp
$Comp
L zorjadnik:74HC595-74xx1 U4
U 1 1 5D50D654
P 3500 5350
AR Path="/5D50D654" Ref="U4"  Part="1" 
AR Path="/5D41F71E/5D50D654" Ref="U4"  Part="1" 
F 0 "U4" H 3200 5900 50  0000 C CNN
F 1 "74HC595" H 3200 4700 50  0000 C CNN
F 2 "Package_SO:SOP-16_4.55x10.3mm_P1.27mm" H 3500 5350 50  0001 C CNN
F 3 "" H 3500 5350 50  0001 C CNN
	1    3500 5350
	1    0    0    -1  
$EndComp
Entry Wire Line
	4050 5350 4150 5250
Entry Wire Line
	5800 2950 5900 2850
Entry Wire Line
	5800 3050 5900 2950
Entry Wire Line
	5800 3150 5900 3050
Entry Wire Line
	4050 5450 4150 5350
Entry Wire Line
	4050 5550 4150 5450
Entry Wire Line
	4050 5650 4150 5550
Wire Wire Line
	5350 2950 5400 2950
Wire Wire Line
	5350 3050 5400 3050
Wire Wire Line
	5350 3150 5400 3150
NoConn ~ 3900 2700
NoConn ~ 3900 4950
NoConn ~ 3900 5850
Text Label 5700 2950 0    50   ~ 0
D1
Text Label 5700 3050 0    50   ~ 0
D2
Text Label 5700 3150 0    50   ~ 0
D3
Wire Wire Line
	5700 2950 5800 2950
Wire Wire Line
	5700 3050 5800 3050
Wire Wire Line
	5700 3150 5800 3150
Text Label 3950 2900 0    50   ~ 0
D1
Text Label 3950 5650 0    50   ~ 0
B
Text Label 3950 5450 0    50   ~ 0
D2
Text Label 3950 5550 0    50   ~ 0
D3
Wire Wire Line
	3900 3600 3950 3600
Wire Wire Line
	3050 4950 3100 4950
Wire Wire Line
	2950 5450 3100 5450
Wire Wire Line
	2850 5150 3100 5150
Wire Wire Line
	3900 5350 4050 5350
$Comp
L zorjadnik:+3.3V-power1 #PWR0109
U 1 1 5D629A6A
P 3500 4250
F 0 "#PWR0109" H 3500 4100 50  0001 C CNN
F 1 "+3.3V" H 3500 4390 50  0000 C CNN
F 2 "" H 3500 4250 50  0001 C CNN
F 3 "" H 3500 4250 50  0001 C CNN
	1    3500 4250
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik:C-zorjadnik C?
U 1 1 5D629A70
P 3650 4500
AR Path="/5D629A70" Ref="C?"  Part="1" 
AR Path="/5D41F71E/5D629A70" Ref="C9"  Part="1" 
F 0 "C9" H 3675 4600 50  0000 L CNN
F 1 "100nF" H 3675 4400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3688 4350 50  0001 C CNN
F 3 "" H 3650 4500 50  0001 C CNN
	1    3650 4500
	1    0    0    -1  
$EndComp
$Comp
L zorjadnik:GND-power1 #PWR0110
U 1 1 5D629A76
P 3650 4650
F 0 "#PWR0110" H 3650 4400 50  0001 C CNN
F 1 "GND" H 3650 4500 50  0000 C CNN
F 2 "" H 3650 4650 50  0001 C CNN
F 3 "" H 3650 4650 50  0001 C CNN
	1    3650 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4250 3500 4300
Wire Wire Line
	3650 4350 3650 4300
Wire Wire Line
	3650 4300 3500 4300
Connection ~ 3500 4300
$Comp
L zorjadnik:GND-power1 #PWR0111
U 1 1 5D6460F2
P 3500 3800
F 0 "#PWR0111" H 3500 3550 50  0001 C CNN
F 1 "GND" H 3500 3650 50  0000 C CNN
F 2 "" H 3500 3800 50  0001 C CNN
F 3 "" H 3500 3800 50  0001 C CNN
	1    3500 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4000 3050 4000
Wire Wire Line
	3950 3600 3950 4000
$Comp
L zorjadnik:GND-power1 #PWR0112
U 1 1 5D657AAB
P 3050 5650
F 0 "#PWR0112" H 3050 5400 50  0001 C CNN
F 1 "GND" H 3050 5500 50  0000 C CNN
F 2 "" H 3050 5650 50  0001 C CNN
F 3 "" H 3050 5650 50  0001 C CNN
	1    3050 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 5650 3050 5550
Wire Wire Line
	3050 5550 3100 5550
Wire Wire Line
	3900 5550 4050 5550
Wire Wire Line
	3900 5450 4050 5450
Wire Wire Line
	3900 5650 4050 5650
Wire Wire Line
	3900 5250 4050 5250
Entry Wire Line
	4050 5250 4150 5150
Wire Wire Line
	3900 5050 4050 5050
Wire Wire Line
	3900 5150 4050 5150
Entry Wire Line
	4150 4950 4050 5050
Entry Wire Line
	4150 5050 4050 5150
NoConn ~ 3900 3400
NoConn ~ 3900 3200
NoConn ~ 3900 2800
Wire Wire Line
	3500 4300 3500 4550
Wire Wire Line
	3050 4000 3050 4950
Connection ~ 3500 4550
Wire Wire Line
	3500 4550 3500 4750
Wire Wire Line
	3100 5250 3000 5250
Wire Wire Line
	3000 5250 3000 4550
Wire Wire Line
	3000 4550 3500 4550
$Comp
L zorjadnik:CircuitBreaker_1P-Device1 CB1
U 1 1 5D430003
P 2850 1950
F 0 "CB1" V 2800 1950 50  0000 L CNN
F 1 "mode" V 2900 1950 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 2850 1950 50  0001 C CNN
F 3 "" H 2850 1950 50  0001 C CNN
	1    2850 1950
	0    1    1    0   
$EndComp
$Comp
L zorjadnik:74HC595-74xx1 U3
U 1 1 5D42E9F5
P 3500 3100
AR Path="/5D42E9F5" Ref="U3"  Part="1" 
AR Path="/5D41F71E/5D42E9F5" Ref="U3"  Part="1" 
F 0 "U3" H 3200 3650 50  0000 C CNN
F 1 "74HC595" H 3200 2450 50  0000 C CNN
F 2 "Package_SO:SOP-16_4.55x10.3mm_P1.27mm" H 3500 3100 50  0001 C CNN
F 3 "" H 3500 3100 50  0001 C CNN
	1    3500 3100
	1    0    0    -1  
$EndComp
Text GLabel 2150 1450 0    50   Input ~ 0
pot
Text GLabel 2150 1950 0    50   Input ~ 0
mode_but
Text GLabel 2150 2100 0    50   Input ~ 0
sel_but
Wire Wire Line
	3500 2000 3500 2400
Wire Wire Line
	2850 2900 3100 2900
Wire Wire Line
	3050 3000 3050 2400
Wire Wire Line
	3050 2400 3500 2400
Connection ~ 3500 2400
Wire Wire Line
	3500 2400 3500 2500
Text GLabel 2150 3200 0    50   Input ~ 0
SCK
Wire Wire Line
	2850 2900 2850 3200
Wire Wire Line
	2150 3200 2850 3200
Connection ~ 2850 3200
Wire Wire Line
	2850 3200 2850 5150
Text GLabel 2150 3300 0    50   Input ~ 0
ST_CP
Wire Wire Line
	2950 3200 2950 3300
Wire Wire Line
	2150 3300 2950 3300
Connection ~ 2950 3300
Wire Wire Line
	2950 3300 2950 5450
Text GLabel 2150 2700 0    50   Input ~ 0
MOSI
Wire Wire Line
	2150 2700 3100 2700
Wire Wire Line
	2150 1450 2550 1450
Wire Wire Line
	2150 1950 2550 1950
Wire Wire Line
	2150 2100 2550 2100
Entry Bus Bus
	4150 3900 4250 3800
Entry Bus Bus
	5800 3800 5900 3700
Wire Bus Line
	5800 3800 4250 3800
Wire Bus Line
	5900 2850 5900 3700
Wire Bus Line
	4150 2600 4150 5550
$EndSCHEMATC
