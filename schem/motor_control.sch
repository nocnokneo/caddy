v 20110115 2
N 44800 43500 45900 43500 4
C 41500 48000 1 0 0 input-1.sym
{
T 41500 48300 5 10 1 1 0 0 1
device=Motor Control 1a
}
C 41500 47400 1 0 0 input-1.sym
{
T 41500 47700 5 10 1 1 0 0 1
device=Motor Control 1b
}
C 41500 48600 1 0 0 input-1.sym
{
T 41500 48900 5 10 1 1 0 0 1
device=Motor Enable 1
}
C 42800 46500 1 90 0 resistor-1.sym
{
T 42400 46800 5 10 0 0 90 0 1
device=RESISTOR
T 42500 46700 5 10 1 1 90 0 1
refdes=R2
T 43000 46700 5 10 1 1 90 0 1
value=10k
}
C 43700 46500 1 90 0 resistor-1.sym
{
T 43300 46800 5 10 0 0 90 0 1
device=RESISTOR
T 43400 46700 5 10 1 1 90 0 1
refdes=R3
T 43900 46700 5 10 1 1 90 0 1
value=10k
}
C 43000 46100 1 0 0 ground.sym
C 46500 48900 1 90 0 resistor-1.sym
{
T 46100 49200 5 10 0 0 90 0 1
device=RESISTOR
T 46200 49100 5 10 1 1 90 0 1
refdes=R4
T 46800 49100 5 10 1 1 90 0 1
value=10k
}
C 46800 44600 1 0 0 L298_1.sym
{
T 50500 49100 5 10 1 1 0 6 1
refdes=U1
T 47200 49400 5 10 0 0 0 0 1
device=L298
T 47200 50600 5 10 0 0 0 0 1
footprint=MULTIWATT15
}
N 46400 49900 46400 49800 4
N 42300 48700 46400 48700 4
N 46400 48400 46400 48900 4
N 46400 48400 46900 48400 4
N 42300 48100 46900 48100 4
N 42300 47500 46400 47500 4
N 46400 47500 46400 47800 4
N 46400 47800 46900 47800 4
N 42700 46400 43600 46400 4
N 42700 46400 42700 46500 4
N 43600 46400 43600 46500 4
N 42700 47400 42700 47500 4
N 43600 47400 43600 47500 4
C 48300 49400 1 0 0 generic-power.sym
{
T 48500 49650 5 10 1 1 0 3 1
net=V_batt
}
C 49100 50000 1 0 0 5V-plus-1.sym
N 48500 49400 48500 49300 4
N 49300 50000 49300 49300 4
C 56200 48000 1 0 1 input-1.sym
{
T 56200 48300 5 10 1 1 0 6 1
device=Motor Control 2a
}
C 56200 47400 1 0 1 input-1.sym
{
T 56200 47700 5 10 1 1 0 6 1
device=Motor Control 2b
}
C 56200 48600 1 0 1 input-1.sym
{
T 56200 48900 5 10 1 1 0 6 1
device=Motor Enable 2
}
C 54800 46500 1 270 1 resistor-1.sym
{
T 55200 46800 5 10 0 0 90 2 1
device=RESISTOR
T 54600 46800 5 10 1 1 90 2 1
refdes=R7
T 55100 46800 5 10 1 1 90 2 1
value=10k
}
C 53900 46500 1 270 1 resistor-1.sym
{
T 54300 46800 5 10 0 0 90 2 1
device=RESISTOR
T 53700 46800 5 10 1 1 90 2 1
refdes=R6
T 54200 46800 5 10 1 1 90 2 1
value=10k
}
C 54700 46100 1 0 1 ground.sym
C 51300 48900 1 270 1 resistor-1.sym
{
T 51700 49200 5 10 0 0 90 2 1
device=RESISTOR
T 51100 49100 5 10 1 1 90 2 1
refdes=R5
T 51600 49100 5 10 1 1 90 2 1
value=10k
}
N 51400 49900 51400 49800 4
N 50800 46600 53600 46600 4
N 50800 46300 51400 46300 4
N 55400 48700 51400 48700 4
N 51400 48400 51400 48900 4
N 51400 48400 50800 48400 4
N 55400 48100 50800 48100 4
N 55400 47500 51400 47500 4
N 51400 47500 51400 47800 4
N 51400 47800 50800 47800 4
N 54900 46400 54000 46400 4
N 54900 46400 54900 46500 4
N 54000 46400 54000 46500 4
N 54900 47400 54900 47500 4
N 54000 47400 54000 47500 4
N 46400 49900 49300 49900 4
N 49300 49900 51400 49900 4
C 45800 44600 1 90 0 dc_motor-1.sym
{
T 44800 45000 5 10 0 0 90 0 1
device=DC_MOTOR
T 45400 44500 5 10 1 1 180 0 1
refdes=M1
}
C 45000 45000 1 90 0 diode-1.sym
{
T 44400 45400 5 10 0 0 90 0 1
device=DIODE
T 44500 45300 5 10 1 1 90 0 1
refdes=D1
}
C 46100 45000 1 90 0 diode-1.sym
{
T 45500 45400 5 10 0 0 90 0 1
device=DIODE
T 45600 45300 5 10 1 1 90 0 1
refdes=D3
}
C 45100 43000 1 0 0 ground.sym
N 44800 44500 44800 45000 4
N 45900 44500 45900 45000 4
C 45100 46000 1 0 0 generic-power.sym
{
T 45300 46250 5 10 1 1 0 3 1
net=V_batt
}
N 44800 46000 45900 46000 4
N 45900 43500 45900 43600 4
N 45300 43300 45300 43500 4
N 44800 43500 44800 43600 4
N 45800 44800 45900 44800 4
C 46100 43600 1 90 0 diode-1.sym
{
T 45500 44000 5 10 0 0 90 0 1
device=DIODE
T 45600 43900 5 10 1 1 90 0 1
refdes=D4
}
C 45000 43600 1 90 0 diode-1.sym
{
T 44400 44000 5 10 0 0 90 0 1
device=DIODE
T 44500 43900 5 10 1 1 90 0 1
refdes=D2
}
N 44800 46000 44800 45900 4
N 45900 46000 45900 45900 4
N 46900 45700 46900 44700 4
N 46900 44700 50800 44700 4
N 50800 44700 50800 45700 4
C 48600 44200 1 0 0 ground.sym
N 48800 44500 48800 44700 4
N 46900 46600 44100 46600 4
N 44100 44800 44100 46600 4
N 44100 44800 44800 44800 4
N 46900 46300 46400 46300 4
N 46400 46300 46400 44800 4
N 46400 44800 45900 44800 4
N 52000 43500 53100 43500 4
C 53000 44600 1 90 0 dc_motor-1.sym
{
T 52000 45000 5 10 0 0 90 0 1
device=DC_MOTOR
T 52600 44500 5 10 1 1 180 0 1
refdes=M2
}
C 52200 45000 1 90 0 diode-1.sym
{
T 51600 45400 5 10 0 0 90 0 1
device=DIODE
T 51700 45300 5 10 1 1 90 0 1
refdes=D5
}
C 53300 45000 1 90 0 diode-1.sym
{
T 52700 45400 5 10 0 0 90 0 1
device=DIODE
T 52800 45300 5 10 1 1 90 0 1
refdes=D7
}
C 52300 43000 1 0 0 ground.sym
N 52000 44500 52000 45000 4
N 53100 44500 53100 45000 4
C 52300 46000 1 0 0 generic-power.sym
{
T 52500 46250 5 10 1 1 0 3 1
net=V_batt
}
N 52000 46000 53100 46000 4
N 53100 43500 53100 43600 4
N 52500 43300 52500 43500 4
N 52000 43500 52000 43600 4
N 53000 44800 53100 44800 4
C 53300 43600 1 90 0 diode-1.sym
{
T 52700 44000 5 10 0 0 90 0 1
device=DIODE
T 52800 43900 5 10 1 1 90 0 1
refdes=D8
}
C 52200 43600 1 90 0 diode-1.sym
{
T 51600 44000 5 10 0 0 90 0 1
device=DIODE
T 51700 43900 5 10 1 1 90 0 1
refdes=D6
}
N 52000 46000 52000 45900 4
N 53100 46000 53100 45900 4
N 51400 46300 51400 44800 4
N 51400 44800 52000 44800 4
N 53600 44800 53600 46600 4
N 53600 44800 53100 44800 4
