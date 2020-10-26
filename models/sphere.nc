(Exported by FreeCAD)
(Post Processor: PathScripts.post.linuxcnc_post)
(Output Time:2020-10-26 02:17:10.967414)
(begin preamble)
G17 G54 G40 G49 G80 G90
G21
(begin operation: Job)
(machine: not set, mm/min)
(Helix)
(helix cut operation)
G0 Z10.000
G0 X2.500 Y0.000
G0 Z8.000
G1 Z5.000
G2 X-2.500 Y0.000 Z3.750 I-2.500 J0.000
G2 X2.500 Y0.000 Z2.500 I2.500 J0.000
G2 X-2.500 Y0.000 Z1.250 I-2.500 J0.000
G2 X2.500 Y0.000 Z0.000 I2.500 J0.000
G2 X-2.500 Y0.000 Z0.000 I-2.500 J0.000
G2 X2.500 Y0.000 Z0.000 I2.500 J0.000
G0 Z8.000
G0 Z10.000
(finish operation: Job)
(begin postamble)
M05
G17 G54 G90 G80 G40
M2
