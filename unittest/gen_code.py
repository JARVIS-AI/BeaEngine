import string
import re;
p = re.compile('\s+');

f = open ("table.dasm")
k = 0;

fc = open ("codes.inc", "w");
fo = open ("opcodes.inc", "w");

for line in f.readlines ():
    inp = p.sub (' ', string.strip (line));
    k = k + 1;
    tokens = string.split (inp);
    opcode = tokens [0];
    txt = "";
    for t in tokens [1:]:
        txt = txt + t + " "
    n = len (opcode) / 2;
    ccode = "{";
    for i in range (0, n):
        a = opcode [2*i]
        b = opcode [(2*i)  +1]
        ccode = ccode + "0x" + a + b;
        if i < n - 1:
            ccode = ccode + ",";
    ccode = ccode + "};";
    xx = "unsigned char bytes_" + str (k) + " [] = " + ccode + "\n";
    yy = "bytes_" + str (k);
    fo.write (xx);
    zz = "DASM (" + yy + ", \"" +string.strip (txt) + "\");\n";
    fc.write (zz);
    
