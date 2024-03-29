EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:VAC #PWR?
U 1 1 5F450A3E
P 1050 2600
F 0 "#PWR?" H 1050 2500 50  0001 C CNN
F 1 "VAC" H 1050 2875 50  0000 C CNN
F 2 "" H 1050 2600 50  0001 C CNN
F 3 "" H 1050 2600 50  0001 C CNN
	1    1050 2600
	1    0    0    -1  
$EndComp
$Comp
L power:VAC #PWR?
U 1 1 5F450C66
P 1250 2600
F 0 "#PWR?" H 1250 2500 50  0001 C CNN
F 1 "VAC" H 1250 2875 50  0000 C CNN
F 2 "" H 1250 2600 50  0001 C CNN
F 3 "" H 1250 2600 50  0001 C CNN
	1    1250 2600
	1    0    0    -1  
$EndComp
$Comp
L device:Thermistor TH?
U 1 1 5F4559BE
P 1500 2950
F 0 "TH?" V 1400 2950 50  0000 C CNN
F 1 "Thermistor" V 1600 2950 50  0000 C CNN
F 2 "" H 1500 2950 50  0001 C CNN
F 3 "" H 1500 2950 50  0001 C CNN
	1    1500 2950
	0    1    1    0   
$EndComp
$Comp
L device:Fuse F?
U 1 1 5F4580CB
P 1500 2650
F 0 "F?" V 1400 2600 50  0000 C CNN
F 1 "Fuse" V 1400 2750 50  0000 C CNN
F 2 "" V 1430 2650 50  0001 C CNN
F 3 "" H 1500 2650 50  0001 C CNN
	1    1500 2650
	0    1    1    0   
$EndComp
$Comp
L device:C C?
U 1 1 5F45BEA6
P 1750 2800
F 0 "C?" H 1750 2900 50  0000 L CNN
F 1 "0.22" H 1750 2700 50  0000 L CNN
F 2 "" H 1788 2650 50  0001 C CNN
F 3 "" H 1750 2800 50  0001 C CNN
	1    1750 2800
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 5F45C9B9
P 2000 2800
F 0 "R?" H 2050 2850 50  0000 L CNN
F 1 "1M" H 2050 2750 50  0000 L CNN
F 2 "" V 1930 2800 50  0001 C CNN
F 3 "" H 2000 2800 50  0001 C CNN
	1    2000 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2950 1050 2950
Wire Wire Line
	1250 2600 1250 2650
Wire Wire Line
	1250 2650 1350 2650
$Comp
L device:C C?
U 1 1 5F460AAD
P 2700 2800
F 0 "C?" H 2700 2900 50  0000 L CNN
F 1 "0.22" H 2700 2700 50  0000 L CNN
F 2 "" H 2738 2650 50  0001 C CNN
F 3 "" H 2700 2800 50  0001 C CNN
	1    2700 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2950 2700 2950
Connection ~ 2700 2950
$Comp
L Connector:Conn_01x01 J?
U 1 1 5F46E527
P 650 2650
F 0 "J?" H 568 2425 50  0000 C CNN
F 1 "Conn_01x01" H 568 2516 50  0000 C CNN
F 2 "" H 650 2650 50  0001 C CNN
F 3 "~" H 650 2650 50  0001 C CNN
	1    650  2650
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01 J?
U 1 1 5F46EE6C
P 650 2950
F 0 "J?" H 568 2725 50  0000 C CNN
F 1 "Conn_01x01" H 568 2816 50  0000 C CNN
F 2 "" H 650 2950 50  0001 C CNN
F 3 "~" H 650 2950 50  0001 C CNN
	1    650  2950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01 J?
U 1 1 5F47075B
P 650 3300
F 0 "J?" H 568 3075 50  0000 C CNN
F 1 "Conn_01x01" H 568 3166 50  0000 C CNN
F 2 "" H 650 3300 50  0001 C CNN
F 3 "~" H 650 3300 50  0001 C CNN
	1    650  3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	850  2950 1050 2950
Connection ~ 1050 2950
Connection ~ 1250 2650
Wire Wire Line
	1050 2600 1050 2950
Wire Wire Line
	850  2650 1250 2650
$Comp
L power:GND #PWR?
U 1 1 5F4763E8
P 2950 3350
F 0 "#PWR?" H 2950 3100 50  0001 C CNN
F 1 "GND" H 2955 3177 50  0000 C CNN
F 2 "" H 2950 3350 50  0001 C CNN
F 3 "" H 2950 3350 50  0001 C CNN
	1    2950 3350
	1    0    0    -1  
$EndComp
$Comp
L device:C C?
U 1 1 5F482AE1
P 3650 2800
F 0 "C?" V 3700 2850 50  0000 L CNN
F 1 "0.22" V 3500 2700 50  0000 L CNN
F 2 "" H 3688 2650 50  0001 C CNN
F 3 "" H 3650 2800 50  0001 C CNN
	1    3650 2800
	0    -1   -1   0   
$EndComp
$Comp
L device:L_Core_Ferrite_Small L?
U 1 1 5F482EB3
P 3650 2650
F 0 "L?" V 3750 2700 50  0000 C CNN
F 1 "dr" V 3750 2550 50  0000 C CNN
F 2 "" H 3650 2650 50  0001 C CNN
F 3 "" H 3650 2650 50  0001 C CNN
	1    3650 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3450 2800 3500 2800
Wire Wire Line
	3550 2650 3450 2650
$Comp
L device:D_Bridge_-AA+ D?
U 1 1 5F49793F
P 4200 2850
F 0 "D?" H 4050 2650 50  0000 R CNN
F 1 "GBU605" H 4500 3100 50  0000 R CNN
F 2 "" H 4200 2850 50  0001 C CNN
F 3 "" H 4200 2850 50  0001 C CNN
	1    4200 2850
	1    0    0    1   
$EndComp
Wire Wire Line
	3800 2800 3800 2650
Wire Wire Line
	3800 2650 3750 2650
Wire Wire Line
	3800 2650 3950 2650
Wire Wire Line
	3950 2650 3950 2550
Wire Wire Line
	3950 2550 4200 2550
Connection ~ 3800 2650
Wire Wire Line
	3950 3150 3950 3000
Wire Wire Line
	3950 3150 4200 3150
$Comp
L device:CP C?
U 1 1 5F4A7BDD
P 4900 3000
F 0 "C?" H 4950 3100 50  0000 L CNN
F 1 "220" H 4950 2900 50  0000 L CNN
F 2 "" H 4938 2850 50  0001 C CNN
F 3 "" H 4900 3000 50  0001 C CNN
	1    4900 3000
	1    0    0    -1  
$EndComp
$Comp
L device:CP C?
U 1 1 5F4A7FBA
P 4900 3300
F 0 "C?" H 4950 3400 50  0000 L CNN
F 1 "220" H 4950 3200 50  0000 L CNN
F 2 "" H 4938 3150 50  0001 C CNN
F 3 "" H 4900 3300 50  0001 C CNN
	1    4900 3300
	1    0    0    -1  
$EndComp
$Comp
L device:Varistor RV?
U 1 1 5F4C56BE
P 5200 3000
F 0 "RV?" H 5250 3050 50  0000 L CNN
F 1 "." H 5303 2955 50  0000 L CNN
F 2 "" V 5130 3000 50  0001 C CNN
F 3 "" H 5200 3000 50  0001 C CNN
	1    5200 3000
	1    0    0    -1  
$EndComp
$Comp
L device:Varistor RV?
U 1 1 5F4C6090
P 5200 3300
F 0 "RV?" H 5250 3350 50  0000 L CNN
F 1 "." H 5303 3255 50  0000 L CNN
F 2 "" V 5130 3300 50  0001 C CNN
F 3 "" H 5200 3300 50  0001 C CNN
	1    5200 3300
	1    0    0    -1  
$EndComp
Connection ~ 4900 2850
Wire Wire Line
	3900 2850 3900 3450
Wire Wire Line
	3900 3450 4550 3450
$Comp
L device:R R?
U 1 1 5F4D0BD5
P 5450 3000
F 0 "R?" H 5520 3046 50  0000 L CNN
F 1 "R" H 5520 2955 50  0000 L CNN
F 2 "" V 5380 3000 50  0001 C CNN
F 3 "" H 5450 3000 50  0001 C CNN
	1    5450 3000
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 5F4D11B2
P 5450 3300
F 0 "R?" H 5520 3346 50  0000 L CNN
F 1 "R" H 5520 3255 50  0000 L CNN
F 2 "" V 5380 3300 50  0001 C CNN
F 3 "" H 5450 3300 50  0001 C CNN
	1    5450 3300
	1    0    0    -1  
$EndComp
$Comp
L device:C C?
U 1 1 5F4DA46E
P 5750 3150
F 0 "C?" V 5800 3200 50  0000 L CNN
F 1 "0.22" V 5600 3050 50  0000 L CNN
F 2 "" H 5788 3000 50  0001 C CNN
F 3 "" H 5750 3150 50  0001 C CNN
	1    5750 3150
	0    -1   -1   0   
$EndComp
$Comp
L device:R R?
U 1 1 5F4DCB1D
P 5950 3000
F 0 "R?" H 6000 3050 50  0000 L CNN
F 1 "1M" H 6000 2950 50  0000 L CNN
F 2 "" V 5880 3000 50  0001 C CNN
F 3 "" H 5950 3000 50  0001 C CNN
	1    5950 3000
	1    0    0    -1  
$EndComp
$Comp
L device:C C?
U 1 1 5F4DD791
P 3000 4400
F 0 "C?" H 2900 4500 50  0000 L CNN
F 1 "4.7n" H 2750 4400 50  0000 L CNN
F 2 "" H 3038 4250 50  0001 C CNN
F 3 "" H 3000 4400 50  0001 C CNN
	1    3000 4400
	1    0    0    -1  
$EndComp
$Comp
L device:EMI_Filter_CommonMode FL?
U 1 1 5F453208
P 2350 2800
F 0 "FL?" H 2350 3081 50  0000 C CNN
F 1 "EMI_Filter" H 2350 2990 50  0000 C CNN
F 2 "" V 2350 2840 50  0000 C CNN
F 3 "~" V 2350 2840 50  0000 C CNN
	1    2350 2800
	1    0    0    -1  
$EndComp
$Comp
L device:EMI_Filter_CommonMode FL?
U 1 1 5F454050
P 3200 2800
F 0 "FL?" H 3200 3081 50  0000 C CNN
F 1 "EMI_Filter" H 3200 2990 50  0000 C CNN
F 2 "" V 3200 2840 50  0000 C CNN
F 3 "~" V 3200 2840 50  0000 C CNN
	1    3200 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2650 2550 2700
Wire Wire Line
	2150 2650 2150 2700
Wire Wire Line
	2150 2950 2150 2900
Wire Wire Line
	2550 2900 2550 2950
Wire Wire Line
	3400 2700 3450 2700
Wire Wire Line
	3450 2700 3450 2800
Wire Wire Line
	3450 2650 3450 2700
Connection ~ 3450 2700
Wire Wire Line
	3000 2650 3000 2700
Wire Wire Line
	3000 2950 3000 2900
Wire Wire Line
	3400 2900 3450 2900
Wire Wire Line
	3450 2900 3450 3000
Wire Wire Line
	3450 3000 3950 3000
Wire Wire Line
	6000 2850 5950 2850
Wire Wire Line
	6300 2850 6300 3150
$Comp
L device:Varistor RV?
U 1 1 5F4535DE
P 2700 3150
F 0 "RV?" V 2800 3150 50  0000 L CNN
F 1 "." H 2803 3105 50  0000 L CNN
F 2 "" V 2630 3150 50  0001 C CNN
F 3 "" H 2700 3150 50  0001 C CNN
	1    2700 3150
	1    0    0    -1  
$EndComp
$Comp
L device:Varistor RV?
U 1 1 5F45B7FB
P 2950 3150
F 0 "RV?" V 3050 3150 50  0000 L CNN
F 1 "." H 3053 3105 50  0000 L CNN
F 2 "" V 2880 3150 50  0001 C CNN
F 3 "" H 2950 3150 50  0001 C CNN
	1    2950 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 2950 3000 2950
Wire Wire Line
	2700 2950 2700 3000
Wire Wire Line
	2950 3350 2950 3300
Wire Wire Line
	2950 3000 2950 2650
Connection ~ 2950 2650
Wire Wire Line
	2950 2650 3000 2650
$Comp
L device:Q_NPN_BCE Q?
U 1 1 5F46D792
P 6700 2900
F 0 "Q?" H 6600 3050 50  0000 L CNN
F 1 "D209" H 6500 2750 50  0000 L CNN
F 2 "" H 6900 3000 50  0001 C CNN
F 3 "" H 6700 2900 50  0001 C CNN
	1    6700 2900
	-1   0    0    -1  
$EndComp
$Comp
L device:Q_NPN_BCE Q?
U 1 1 5F46DA30
P 6700 3400
F 0 "Q?" H 6600 3550 50  0000 L CNN
F 1 "D209" H 6500 3250 50  0000 L CNN
F 2 "" H 6900 3500 50  0001 C CNN
F 3 "" H 6700 3400 50  0001 C CNN
	1    6700 3400
	-1   0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 5F47DE4B
P 6400 2850
F 0 "D?" V 6300 2750 50  0000 L CNN
F 1 "1N4007" H 6250 2950 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 6400 2675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 6400 2850 50  0001 C CNN
	1    6400 2850
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 5F480D32
P 6400 3350
F 0 "D?" V 6300 3250 50  0000 L CNN
F 1 "1N4007" H 6250 3450 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 6400 3175 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 6400 3350 50  0001 C CNN
	1    6400 3350
	0    1    1    0   
$EndComp
$Comp
L device:R R?
U 1 1 5F489C37
P 7050 3400
F 0 "R?" V 7150 3400 50  0000 L CNN
F 1 "2.2" V 7050 3350 50  0000 L CNN
F 2 "" V 6980 3400 50  0001 C CNN
F 3 "" H 7050 3400 50  0001 C CNN
	1    7050 3400
	0    -1   -1   0   
$EndComp
$Comp
L atx:K1010 U?
U 1 1 5F49C4AE
P 8150 2800
F 0 "U?" H 8000 3000 50  0000 C CNN
F 1 "K1010" H 8250 3000 50  0000 C CNN
F 2 "Housings_DIP:DIP-4_W7.62mm" H 7950 2600 50  0001 L CIN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 8150 2700 50  0001 L CNN
	1    8150 2800
	-1   0    0    -1  
$EndComp
$Comp
L atx:K1010 U?
U 1 1 5F49F087
P 8150 3300
F 0 "U?" H 8000 3500 50  0000 C CNN
F 1 "K1010" H 8250 3500 50  0000 C CNN
F 2 "Housings_DIP:DIP-4_W7.62mm" H 7950 3100 50  0001 L CIN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 8150 3200 50  0001 L CNN
	1    8150 3300
	-1   0    0    -1  
$EndComp
$Comp
L atx:st_1.1 L?
U 1 1 5F4A5896
P 6150 3150
F 0 "L?" V 6050 3150 50  0000 C CNN
F 1 "st_1.1" V 6249 3150 50  0000 C CNN
F 2 "" H 6150 3150 50  0001 C CNN
F 3 "" H 6150 3150 50  0001 C CNN
	1    6150 3150
	0    -1   1    0   
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 5F4C2936
P 7550 2200
F 0 "D?" V 7650 2100 50  0000 L CNN
F 1 "1N4007" H 7400 2300 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 7550 2025 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 7550 2200 50  0001 C CNN
	1    7550 2200
	0    -1   -1   0   
$EndComp
$Comp
L device:R R?
U 1 1 5F4B5BC1
P 7800 2500
F 0 "R?" V 7900 2550 50  0000 L CNN
F 1 "100k" V 7900 2350 50  0000 L CNN
F 2 "" V 7730 2500 50  0001 C CNN
F 3 "" H 7800 2500 50  0001 C CNN
	1    7800 2500
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 5F4B581B
P 7550 2500
F 0 "R?" V 7650 2550 50  0000 L CNN
F 1 "100k" V 7650 2350 50  0000 L CNN
F 2 "" V 7480 2500 50  0001 C CNN
F 3 "" H 7550 2500 50  0001 C CNN
	1    7550 2500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 5F4CDB13
P 7800 2200
F 0 "D?" V 7900 2100 50  0000 L CNN
F 1 "1N4007" H 7650 2300 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 7800 2025 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 7800 2200 50  0001 C CNN
	1    7800 2200
	0    -1   -1   0   
$EndComp
$Comp
L device:C C?
U 1 1 5F4F3F6C
P 7400 3550
F 0 "C?" H 7400 3650 50  0000 L CNN
F 1 "1uF" H 7400 3450 50  0000 L CNN
F 2 "" H 7438 3400 50  0001 C CNN
F 3 "" H 7400 3550 50  0001 C CNN
	1    7400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 3150 6400 3150
Wire Wire Line
	6600 3150 6600 3200
Wire Wire Line
	6400 3200 6400 3150
Connection ~ 6400 3150
Wire Wire Line
	6400 3150 6600 3150
Wire Wire Line
	6400 3000 6400 3150
Wire Wire Line
	6600 3100 6600 3150
Connection ~ 6600 3150
Wire Wire Line
	6400 3500 6400 3600
Wire Wire Line
	6400 3600 6600 3600
Wire Wire Line
	5450 3450 5450 3600
Wire Wire Line
	5450 3600 6400 3600
Connection ~ 6400 3600
Wire Wire Line
	6600 2700 6600 2650
Wire Wire Line
	6600 2650 6400 2650
Wire Wire Line
	6400 2650 6400 2700
Wire Wire Line
	6400 2650 5450 2650
Wire Wire Line
	5450 2650 5450 2850
Connection ~ 6400 2650
$Comp
L device:R R?
U 1 1 5F54D22A
P 7250 3550
F 0 "R?" V 7150 3500 50  0000 L CNN
F 1 "10k" V 7250 3450 50  0000 L CNN
F 2 "" V 7180 3550 50  0001 C CNN
F 3 "" H 7250 3550 50  0001 C CNN
	1    7250 3550
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 5F56A3D9
P 7050 2900
F 0 "R?" V 7150 2900 50  0000 L CNN
F 1 "2.2" V 7050 2850 50  0000 L CNN
F 2 "" V 6980 2900 50  0001 C CNN
F 3 "" H 7050 2900 50  0001 C CNN
	1    7050 2900
	0    -1   -1   0   
$EndComp
$Comp
L device:C C?
U 1 1 5F56A3DF
P 7400 3050
F 0 "C?" H 7400 3150 50  0000 L CNN
F 1 "1uF" H 7400 2950 50  0000 L CNN
F 2 "" H 7438 2900 50  0001 C CNN
F 3 "" H 7400 3050 50  0001 C CNN
	1    7400 3050
	1    0    0    -1  
$EndComp
$Comp
L device:D_Zener D?
U 1 1 5F56A3EE
P 7550 3050
F 0 "D?" V 7504 3129 50  0000 L CNN
F 1 "BZX84-C5V1" V 7750 2800 50  0000 L CNN
F 2 "" H 7550 3050 50  0001 C CNN
F 3 "https://en.wikipedia.org/wiki/Zener_diode" H 7550 3050 50  0001 C CNN
	1    7550 3050
	0    1    1    0   
$EndComp
$Comp
L device:R R?
U 1 1 5F56A3F8
P 7250 3050
F 0 "R?" V 7150 3000 50  0000 L CNN
F 1 "10k" V 7250 2950 50  0000 L CNN
F 2 "" V 7180 3050 50  0001 C CNN
F 3 "" H 7250 3050 50  0001 C CNN
	1    7250 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 2650 7800 3200
Wire Wire Line
	7800 3200 7850 3200
Wire Wire Line
	7850 2700 7550 2700
Wire Wire Line
	7550 2700 7550 2650
Wire Wire Line
	6600 2650 6600 2000
Wire Wire Line
	6600 2000 7550 2000
Wire Wire Line
	7800 2000 7800 2050
Connection ~ 6600 2650
Wire Wire Line
	7550 2050 7550 2000
Connection ~ 7550 2000
Wire Wire Line
	7550 2000 7800 2000
$Comp
L power:GND #PWR?
U 1 1 5F5B08CF
P 8500 2950
F 0 "#PWR?" H 8500 2700 50  0001 C CNN
F 1 "GND" H 8400 2850 50  0000 C CNN
F 2 "" H 8500 2950 50  0001 C CNN
F 3 "" H 8500 2950 50  0001 C CNN
	1    8500 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5B0C9F
P 8500 3450
F 0 "#PWR?" H 8500 3200 50  0001 C CNN
F 1 "GND" H 8400 3350 50  0000 C CNN
F 2 "" H 8500 3450 50  0001 C CNN
F 3 "" H 8500 3450 50  0001 C CNN
	1    8500 3450
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 5F5B1058
P 8650 2700
F 0 "R?" V 8750 2700 50  0000 L CNN
F 1 "100" V 8750 2550 50  0000 L CNN
F 2 "" V 8580 2700 50  0001 C CNN
F 3 "" H 8650 2700 50  0001 C CNN
	1    8650 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8450 2900 8500 2900
Wire Wire Line
	8500 2900 8500 2950
Wire Wire Line
	8450 2700 8500 2700
Wire Wire Line
	8450 3200 8500 3200
Wire Wire Line
	8450 3400 8500 3400
Wire Wire Line
	8500 3400 8500 3450
Wire Wire Line
	9050 2700 9050 3000
Wire Wire Line
	8950 3100 8950 3200
$Comp
L power:+5V #PWR?
U 1 1 5F609AFA
P 9150 2900
F 0 "#PWR?" H 9150 2750 50  0001 C CNN
F 1 "+5V" H 9150 3050 50  0000 C CNN
F 2 "" H 9150 2900 50  0001 C CNN
F 3 "" H 9150 2900 50  0001 C CNN
	1    9150 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04 J?
U 1 1 5F61810A
P 9500 3100
F 0 "J?" H 9580 3092 50  0000 L CNN
F 1 "controller" H 9580 3001 50  0000 L CNN
F 2 "" H 9500 3100 50  0001 C CNN
F 3 "~" H 9500 3100 50  0001 C CNN
	1    9500 3100
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5F61EACD
P 9250 2900
F 0 "#PWR?" H 9250 2750 50  0001 C CNN
F 1 "VCC" H 9300 3050 50  0000 C CNN
F 2 "" H 9250 2900 50  0001 C CNN
F 3 "" H 9250 2900 50  0001 C CNN
	1    9250 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 3000 9300 3000
Wire Wire Line
	8950 3100 9300 3100
Wire Wire Line
	9150 2900 9150 3200
Wire Wire Line
	9150 3200 9300 3200
Wire Wire Line
	9250 2900 9250 3300
Wire Wire Line
	9250 3300 9300 3300
$Comp
L device:CP C?
U 1 1 5F65812A
P 3800 2350
F 0 "C?" H 3918 2396 50  0000 L CNN
F 1 "100" H 3918 2305 50  0000 L CNN
F 2 "" H 3838 2200 50  0001 C CNN
F 3 "" H 3800 2350 50  0001 C CNN
	1    3800 2350
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 5F659D1E
P 4550 2650
F 0 "D?" V 4450 2550 50  0000 L CNN
F 1 "1N4007" H 4400 2750 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 4550 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4550 2650 50  0001 C CNN
	1    4550 2650
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 5F65A3D1
P 4900 2650
F 0 "D?" V 4800 2550 50  0000 L CNN
F 1 "1N4007" H 4750 2750 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 4900 2475 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4900 2650 50  0001 C CNN
	1    4900 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 2150 3800 2200
Wire Wire Line
	3800 2650 3800 2500
$Comp
L atx:DM311 U?
U 1 1 5F6AD66D
P 2150 4750
F 0 "U?" H 1950 5000 50  0000 C CNN
F 1 "DM311" H 2350 5000 50  0000 C CNN
F 2 "" H 2150 4750 50  0001 C CNN
F 3 "" H 2150 4750 50  0001 C CNN
	1    2150 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2850 4900 2800
Wire Wire Line
	6850 3200 6850 3150
Wire Wire Line
	6850 3150 6600 3150
$Comp
L device:D_Zener D?
U 1 1 610D528D
P 7550 3550
F 0 "D?" V 7504 3629 50  0000 L CNN
F 1 "BZX84-C5V1" V 7750 3300 50  0000 L CNN
F 2 "" H 7550 3550 50  0001 C CNN
F 3 "https://en.wikipedia.org/wiki/Zener_diode" H 7550 3550 50  0001 C CNN
	1    7550 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	6600 3600 6600 3700
Wire Wire Line
	8800 3200 8950 3200
Wire Wire Line
	8800 2700 9050 2700
$Comp
L device:R R?
U 1 1 5F5B14A0
P 8650 3200
F 0 "R?" V 8750 3200 50  0000 L CNN
F 1 "100" V 8750 3050 50  0000 L CNN
F 2 "" V 8580 3200 50  0001 C CNN
F 3 "" H 8650 3200 50  0001 C CNN
	1    8650 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4550 3450 4550 3400
$Comp
L device:CP C?
U 1 1 6115F9F6
P 4700 3250
F 0 "C?" V 4750 3100 50  0000 L CNN
F 1 "330" V 4750 3300 50  0000 L CNN
F 2 "" H 4738 3100 50  0001 C CNN
F 3 "" H 4700 3250 50  0001 C CNN
	1    4700 3250
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 61164379
P 4550 3250
F 0 "R?" V 4650 3250 50  0000 L CNN
F 1 "220k" V 4550 3150 50  0000 L CNN
F 2 "" V 4480 3250 50  0001 C CNN
F 3 "" H 4550 3250 50  0001 C CNN
	1    4550 3250
	-1   0    0    1   
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 611AF83C
P 1150 4300
F 0 "D?" V 1050 4200 50  0000 L CNN
F 1 "1N4007" H 1000 4400 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 1150 4125 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 1150 4300 50  0001 C CNN
	1    1150 4300
	-1   0    0    1   
$EndComp
$Comp
L atx:st_1.1 L?
U 1 1 611BCA29
P 2600 4100
F 0 "L?" H 2652 4146 50  0000 L CNN
F 1 "t_2.1" H 2652 4055 50  0000 L CNN
F 2 "" H 2600 4100 50  0001 C CNN
F 3 "" H 2600 4100 50  0001 C CNN
	1    2600 4100
	1    0    0    -1  
$EndComp
$Comp
L atx:st_1.1 L?
U 1 1 611BFBB2
P 3450 4300
F 0 "L?" H 3600 4200 50  0000 R CNN
F 1 "t_2.3" V 3550 4450 50  0000 R CNN
F 2 "" H 3450 4300 50  0001 C CNN
F 3 "" H 3450 4300 50  0001 C CNN
	1    3450 4300
	-1   0    0    1   
$EndComp
$Comp
L atx:st_1.2 L?
U 1 1 611C3F02
P 650 4500
F 0 "L?" H 708 4571 50  0000 L CNN
F 1 "t_2.2" H 708 4480 50  0000 L CNN
F 2 "" H 650 4500 50  0001 C CNN
F 3 "" H 650 4500 50  0001 C CNN
	1    650  4500
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 611D2805
P 850 4300
F 0 "R?" V 950 4300 50  0000 L CNN
F 1 "100" V 850 4250 50  0000 L CNN
F 2 "" V 780 4300 50  0001 C CNN
F 3 "" H 850 4300 50  0001 C CNN
	1    850  4300
	0    -1   -1   0   
$EndComp
$Comp
L device:D_Zener D?
U 1 1 611E79BB
P 1350 4500
F 0 "D?" V 1250 4500 50  0000 L CNN
F 1 "BZX84-C5V1" V 1450 4000 50  0000 L CNN
F 2 "" H 1350 4500 50  0001 C CNN
F 3 "https://en.wikipedia.org/wiki/Zener_diode" H 1350 4500 50  0001 C CNN
	1    1350 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 5050 2150 5100
$Comp
L atx:K1010 U?
U 1 1 61233B3A
P 3400 4950
F 0 "U?" H 3250 5150 50  0000 C CNN
F 1 "K1010" H 3500 5150 50  0000 C CNN
F 2 "Housings_DIP:DIP-4_W7.62mm" H 3200 4750 50  0001 L CIN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 3400 4850 50  0001 L CNN
	1    3400 4950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2550 4850 2600 4850
Wire Wire Line
	2600 4850 2600 4750
Wire Wire Line
	2550 4750 2600 4750
Connection ~ 2600 4750
Wire Wire Line
	2600 4750 2600 4650
Wire Wire Line
	2550 4650 2600 4650
Connection ~ 2600 4650
Wire Wire Line
	2600 4650 2600 4600
$Comp
L Diode:1N4007 D?
U 1 1 6126EB1C
P 2800 4600
F 0 "D?" H 2650 4550 50  0000 L CNN
F 1 "1N4007" H 2650 4700 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 2800 4425 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2800 4600 50  0001 C CNN
	1    2800 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2650 4600 2600 4600
Connection ~ 2600 4600
$Comp
L device:D_Zener D?
U 1 1 61289E45
P 3150 4400
F 0 "D?" V 3050 4400 50  0000 L CNN
F 1 "BZX84-C5V1" H 3000 4300 50  0000 L CNN
F 2 "" H 3150 4400 50  0001 C CNN
F 3 "https://en.wikipedia.org/wiki/Zener_diode" H 3150 4400 50  0001 C CNN
	1    3150 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3150 4600 3150 4550
Wire Wire Line
	2950 4600 3000 4600
Wire Wire Line
	3000 4550 3000 4600
Connection ~ 3000 4600
Wire Wire Line
	3000 4600 3150 4600
$Comp
L power:GNDPWR #PWR?
U 1 1 612E13E7
P 5450 3650
F 0 "#PWR?" H 5450 3450 50  0001 C CNN
F 1 "GNDPWR" H 5450 3500 50  0000 C CNN
F 2 "" H 5450 3600 50  0001 C CNN
F 3 "" H 5450 3600 50  0001 C CNN
	1    5450 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3600 5450 3650
Connection ~ 5450 3600
Wire Wire Line
	1750 5050 1750 4800
Wire Wire Line
	1750 4800 1800 4800
Connection ~ 2150 5100
$Comp
L device:R R?
U 1 1 61308B88
P 1750 4500
F 0 "R?" H 1800 4550 50  0000 L CNN
F 1 "1M" H 1800 4450 50  0000 L CNN
F 2 "" V 1680 4500 50  0001 C CNN
F 3 "" H 1750 4500 50  0001 C CNN
	1    1750 4500
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 6130AE3E
P 1750 4100
F 0 "R?" H 1800 4150 50  0000 L CNN
F 1 "1M" H 1800 4050 50  0000 L CNN
F 2 "" V 1680 4100 50  0001 C CNN
F 3 "" H 1750 4100 50  0001 C CNN
	1    1750 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4700 1750 4700
Wire Wire Line
	1750 4700 1750 4650
$Comp
L device:C C?
U 1 1 6136E69F
P 2850 4950
F 0 "C?" H 2750 5050 50  0000 L CNN
F 1 "0.01" V 2700 4850 50  0000 L CNN
F 2 "" H 2888 4800 50  0001 C CNN
F 3 "" H 2850 4950 50  0001 C CNN
	1    2850 4950
	1    0    0    -1  
$EndComp
$Comp
L device:D_Zener D?
U 1 1 6136EA81
P 3000 4950
F 0 "D?" V 3100 4950 50  0000 L CNN
F 1 "BZX84-C5V1" V 3100 4400 50  0000 L CNN
F 2 "" H 3000 4950 50  0001 C CNN
F 3 "https://en.wikipedia.org/wiki/Zener_diode" H 3000 4950 50  0001 C CNN
	1    3000 4950
	0    -1   -1   0   
$EndComp
$Comp
L device:CP C?
U 1 1 612028EA
P 1550 4500
F 0 "C?" H 1550 4600 50  0000 L CNN
F 1 "100" H 1550 4400 50  0000 L CNN
F 2 "" H 1588 4350 50  0001 C CNN
F 3 "" H 1550 4500 50  0001 C CNN
	1    1550 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  5100 1350 5100
Wire Wire Line
	1550 4300 1550 4350
Wire Wire Line
	2150 4300 2150 4450
Wire Wire Line
	1350 4350 1350 4300
Wire Wire Line
	1350 4300 1550 4300
Connection ~ 1550 4300
Wire Wire Line
	650  4350 650  4300
Wire Wire Line
	650  4300 700  4300
Wire Wire Line
	650  5100 650  4600
Wire Wire Line
	1350 4300 1300 4300
Connection ~ 1350 4300
Wire Wire Line
	1350 4650 1350 5100
Connection ~ 1350 5100
Wire Wire Line
	1350 5100 1550 5100
Wire Wire Line
	1550 4650 1550 5100
Connection ~ 1550 5100
Wire Wire Line
	1550 5100 2150 5100
Wire Wire Line
	1750 4250 1750 4350
Wire Wire Line
	1550 4300 2150 4300
Wire Wire Line
	1750 3950 1750 3900
Wire Wire Line
	1750 3900 2600 3900
Wire Wire Line
	3000 3900 3000 4250
Wire Wire Line
	2600 3900 2600 3950
Connection ~ 2600 3900
Wire Wire Line
	2600 3900 3000 3900
Wire Wire Line
	3150 3900 3000 3900
Wire Wire Line
	3150 3900 3150 4250
Connection ~ 3000 3900
Wire Wire Line
	2650 4800 2650 5050
Wire Wire Line
	3050 5100 3050 5050
Wire Wire Line
	3050 5050 3100 5050
Wire Wire Line
	3100 4850 3050 4850
Wire Wire Line
	3050 4850 3050 4800
$Comp
L power:GNDPWR #PWR?
U 1 1 61475F4E
P 2150 5150
F 0 "#PWR?" H 2150 4950 50  0001 C CNN
F 1 "GNDPWR" H 2150 5000 50  0000 C CNN
F 2 "" H 2150 5100 50  0001 C CNN
F 3 "" H 2150 5100 50  0001 C CNN
	1    2150 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 5150 2150 5100
$Comp
L device:C C?
U 1 1 614AE429
P 6150 2850
F 0 "C?" V 6200 2900 50  0000 L CNN
F 1 "0.22" V 6000 2750 50  0000 L CNN
F 2 "" H 6188 2700 50  0001 C CNN
F 3 "" H 6150 2850 50  0001 C CNN
	1    6150 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2600 4250 2600 4600
$Comp
L power:GND #PWR?
U 1 1 61543A57
P 4900 5600
F 0 "#PWR?" H 4900 5350 50  0001 C CNN
F 1 "GND" H 4905 5427 50  0000 C CNN
F 2 "" H 4900 5600 50  0001 C CNN
F 3 "" H 4900 5600 50  0001 C CNN
	1    4900 5600
	1    0    0    -1  
$EndComp
$Comp
L references:TL431LP D?
U 1 1 6154514C
P 4250 5200
F 0 "D?" V 4300 5350 50  0000 R CNN
F 1 "TL431LP" V 4150 5550 50  0000 R CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 4250 5050 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/tl431.pdf" H 4250 5200 50  0001 C CIN
	1    4250 5200
	0    1    -1   0   
$EndComp
$Comp
L device:C C?
U 1 1 6157459B
P 4450 5050
F 0 "C?" V 4400 4900 50  0000 L CNN
F 1 "0.1" V 4500 4850 50  0000 L CNN
F 2 "" H 4488 4900 50  0001 C CNN
F 3 "" H 4450 5050 50  0001 C CNN
	1    4450 5050
	0    -1   1    0   
$EndComp
$Comp
L device:R R?
U 1 1 6158DCB0
P 4650 5350
F 0 "R?" H 4700 5300 50  0000 L CNN
F 1 "5.99k" V 4650 5250 50  0000 L CNN
F 2 "" V 4580 5350 50  0001 C CNN
F 3 "" H 4650 5350 50  0001 C CNN
	1    4650 5350
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61598B02
P 3450 4500
F 0 "#PWR?" H 3450 4250 50  0001 C CNN
F 1 "GND" H 3455 4327 50  0000 C CNN
F 2 "" H 3450 4500 50  0001 C CNN
F 3 "" H 3450 4500 50  0001 C CNN
	1    3450 4500
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 615E0693
P 3650 4100
F 0 "D?" V 3550 4000 50  0000 L CNN
F 1 "1N4007" H 3500 4200 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_Horizontal_RM10" H 3650 3925 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3650 4100 50  0001 C CNN
	1    3650 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3450 4500 3450 4450
Wire Wire Line
	3450 4100 3500 4100
Wire Wire Line
	3450 4150 3450 4100
$Comp
L device:R R?
U 1 1 61638666
P 4650 4850
F 0 "R?" H 4700 4900 50  0000 L CNN
F 1 "5.1k" V 4650 4750 50  0000 L CNN
F 2 "" V 4580 4850 50  0001 C CNN
F 3 "" H 4650 4850 50  0001 C CNN
	1    4650 4850
	-1   0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 6166D428
P 4250 4850
F 0 "R?" H 4300 4900 50  0000 L CNN
F 1 "2.2k" V 4250 4750 50  0000 L CNN
F 2 "" V 4180 4850 50  0001 C CNN
F 3 "" H 4250 4850 50  0001 C CNN
	1    4250 4850
	-1   0    0    -1  
$EndComp
$Comp
L device:CP C?
U 1 1 616EA904
P 4100 5250
F 0 "C?" H 4100 5350 50  0000 L CNN
F 1 "22uF" V 4150 5000 50  0000 L CNN
F 2 "" H 4138 5100 50  0001 C CNN
F 3 "" H 4100 5250 50  0001 C CNN
	1    4100 5250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4100 5100 4100 5050
Wire Wire Line
	4100 5050 4250 5050
Wire Wire Line
	4250 5100 4250 5050
Connection ~ 4250 5050
Wire Wire Line
	4250 5050 4300 5050
Wire Wire Line
	4250 5050 4250 5000
$Comp
L device:R R?
U 1 1 6173E640
P 3850 4650
F 0 "R?" H 3700 4600 50  0000 L CNN
F 1 "390" V 3850 4550 50  0000 L CNN
F 2 "" V 3780 4650 50  0001 C CNN
F 3 "" H 3850 4650 50  0001 C CNN
	1    3850 4650
	1    0    0    -1  
$EndComp
Connection ~ 4100 5050
Wire Wire Line
	4350 5200 4650 5200
Wire Wire Line
	4650 5200 4650 5050
Wire Wire Line
	4600 5050 4650 5050
Connection ~ 4650 5050
Wire Wire Line
	4650 5050 4650 5000
Wire Wire Line
	4650 5500 4650 5550
Wire Wire Line
	4650 5550 4250 5550
Wire Wire Line
	4250 5550 4250 5300
Wire Wire Line
	4100 5400 4100 5550
Wire Wire Line
	4100 5550 4250 5550
Connection ~ 4250 5550
Connection ~ 4650 5550
$Comp
L device:L_Small L?
U 1 1 617CCD2D
P 4100 4100
F 0 "L?" V 4200 4050 50  0000 C CNN
F 1 "L" V 4200 4150 50  0000 C CNN
F 2 "" H 4100 4100 50  0001 C CNN
F 3 "" H 4100 4100 50  0001 C CNN
	1    4100 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3850 4100 3800 4100
Wire Wire Line
	3700 4850 3850 4850
Wire Wire Line
	3850 4850 3850 4800
Wire Wire Line
	3850 4100 3850 4500
$Comp
L device:CP C?
U 1 1 6185DD5A
P 3950 4300
F 0 "C?" H 3950 4400 50  0000 L CNN
F 1 "1000uF" H 3950 4200 50  0000 L CNN
F 2 "" H 3988 4150 50  0001 C CNN
F 3 "" H 3950 4300 50  0001 C CNN
	1    3950 4300
	1    0    0    -1  
$EndComp
$Comp
L device:CP C?
U 1 1 61863D42
P 4750 4300
F 0 "C?" H 4750 4400 50  0000 L CNN
F 1 "1000uF" V 4700 3950 50  0000 L CNN
F 2 "" H 4788 4150 50  0001 C CNN
F 3 "" H 4750 4300 50  0001 C CNN
	1    4750 4300
	1    0    0    -1  
$EndComp
$Comp
L device:R R?
U 1 1 6186427E
P 4900 4300
F 0 "R?" H 4950 4350 50  0000 L CNN
F 1 "100" V 4900 4200 50  0000 L CNN
F 2 "" V 4830 4300 50  0001 C CNN
F 3 "" H 4900 4300 50  0001 C CNN
	1    4900 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 4100 3950 4100
Wire Wire Line
	3950 4100 3950 4150
Connection ~ 3850 4100
Wire Wire Line
	4000 4100 3950 4100
Connection ~ 3950 4100
Wire Wire Line
	4200 4100 4250 4100
Wire Wire Line
	4250 4100 4250 4700
Wire Wire Line
	3700 5050 4100 5050
Wire Wire Line
	4650 4100 4250 4100
Connection ~ 4250 4100
Wire Wire Line
	4650 4100 4750 4100
Wire Wire Line
	4750 4100 4750 4150
Connection ~ 4650 4100
Wire Wire Line
	4750 4100 4900 4100
Wire Wire Line
	4900 4100 4900 4150
Connection ~ 4750 4100
Wire Wire Line
	4750 5550 4650 5550
Wire Wire Line
	4900 5550 4750 5550
Connection ~ 4750 5550
Wire Wire Line
	4750 4450 4750 5550
Wire Wire Line
	4900 4450 4900 5550
Wire Wire Line
	3950 5550 4100 5550
Wire Wire Line
	3950 4450 3950 5550
Connection ~ 4100 5550
Wire Wire Line
	4900 5600 4900 5550
Connection ~ 4900 5550
Wire Wire Line
	1700 2950 2150 2950
Wire Wire Line
	1650 2650 2150 2650
Wire Wire Line
	2550 2650 2950 2650
Wire Wire Line
	4900 2850 5200 2850
Wire Wire Line
	4900 3150 5200 3150
Wire Wire Line
	5900 3150 5950 3150
Wire Wire Line
	850  3300 2950 3300
Wire Wire Line
	7200 2900 7250 2900
Wire Wire Line
	6850 3200 7250 3200
Wire Wire Line
	6600 3700 7250 3700
Wire Wire Line
	2150 5100 2850 5100
Wire Wire Line
	2650 4800 2850 4800
Wire Wire Line
	7200 3400 7250 3400
Connection ~ 7250 3700
Wire Wire Line
	7250 3700 7400 3700
Connection ~ 7400 3700
Wire Wire Line
	7400 3700 7550 3700
Connection ~ 7250 3400
Wire Wire Line
	7250 3400 7400 3400
Connection ~ 7400 3400
Wire Wire Line
	7400 3400 7550 3400
Connection ~ 7550 3400
Wire Wire Line
	7550 3400 7850 3400
Connection ~ 7550 2900
Wire Wire Line
	7550 2900 7850 2900
Connection ~ 7400 2900
Wire Wire Line
	7400 2900 7550 2900
Connection ~ 7250 2900
Wire Wire Line
	7250 2900 7400 2900
Connection ~ 7250 3200
Wire Wire Line
	7250 3200 7400 3200
Connection ~ 7400 3200
Wire Wire Line
	7400 3200 7550 3200
Connection ~ 5950 3150
Wire Wire Line
	5950 3150 6000 3150
Connection ~ 5200 2850
Wire Wire Line
	5200 2850 5450 2850
Connection ~ 5200 3150
Wire Wire Line
	5200 3150 5450 3150
Connection ~ 5450 3150
Wire Wire Line
	5450 3150 5600 3150
Connection ~ 5200 3450
Wire Wire Line
	5200 3450 5450 3450
Connection ~ 4900 3150
Connection ~ 4900 3450
Wire Wire Line
	4900 3450 5200 3450
Connection ~ 5450 2850
Connection ~ 5450 3450
Connection ~ 6300 3150
Connection ~ 6600 3600
Wire Wire Line
	4700 3400 4700 3450
Wire Wire Line
	4700 3450 4900 3450
Wire Wire Line
	4550 3450 4700 3450
Connection ~ 4550 3450
Connection ~ 4700 3450
Wire Wire Line
	4500 2850 4900 2850
Wire Wire Line
	4900 2500 4900 2150
Wire Wire Line
	4550 3100 4550 3050
Wire Wire Line
	4700 3100 4700 3050
Wire Wire Line
	4700 3050 4550 3050
Connection ~ 4550 3050
Wire Wire Line
	4550 3050 4550 2800
Wire Wire Line
	4550 2500 4550 2150
Wire Wire Line
	4550 2150 4900 2150
Wire Wire Line
	3800 2150 4550 2150
Connection ~ 4550 2150
$Comp
L power:+VDC #PWR?
U 1 1 612A16B8
P 5200 2600
F 0 "#PWR?" H 5200 2500 50  0001 C CNN
F 1 "+VDC" H 5200 2875 50  0000 C CNN
F 2 "" H 5200 2600 50  0001 C CNN
F 3 "" H 5200 2600 50  0001 C CNN
	1    5200 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2600 5200 2850
$Comp
L power:+VDC #PWR?
U 1 1 612B318E
P 1750 3850
F 0 "#PWR?" H 1750 3750 50  0001 C CNN
F 1 "+VDC" H 1750 4125 50  0000 C CNN
F 2 "" H 1750 3850 50  0001 C CNN
F 3 "" H 1750 3850 50  0001 C CNN
	1    1750 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3900 1750 3850
Connection ~ 1750 3900
Connection ~ 2850 4800
Wire Wire Line
	2850 4800 3000 4800
Connection ~ 2850 5100
Wire Wire Line
	2850 5100 3000 5100
Connection ~ 3000 4800
Wire Wire Line
	3000 4800 3050 4800
Connection ~ 3000 5100
Wire Wire Line
	3000 5100 3050 5100
Connection ~ 4650 5200
Wire Wire Line
	1750 5050 2650 5050
Wire Wire Line
	4650 4700 4650 4100
$EndSCHEMATC