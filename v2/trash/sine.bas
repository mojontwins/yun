open "sine.txt" For Output As #1

Dim As Integer i
For i = 0 To 63
	Print #1, "0x" & Lcase (Hex(Int (16 * sin (i*2*3.14159265359/63)),2 )) + ", ";
Next i
Print #1, ""
 Close
 
 