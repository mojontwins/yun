' Extract Palette Sequence from PNG

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#define RGBA_R( c ) ( CUInt( c ) Shr 16 And 255 )
#define RGBA_G( c ) ( CUInt( c ) Shr  8 And 255 )
#define RGBA_B( c ) ( CUInt( c )        And 255 )
#define RGBA_A( c ) ( CUInt( c ) Shr 24         )

Dim Shared As Integer nesPal (63) = { _
	&HFF7F7F7F, &HFF0000FF, &HFF0000BF, &HFF472BBF, &HFF970087, &HFFAB0023, &HFFAB1300, &HFF8B1700, _
	&HFF533000, &HFF007800, &HFF006B00, &HFF005B00, &HFF004358, &HFF000000, &HFF000000, &HFF000000, _
	&HFFBFBFBF, &HFF0078F8, &HFF0058F8, &HFF6B47FF, &HFFDB00CD, &HFFE7005B, &HFFF83800, &HFFE75F13, _
	&HFFAF7F00, &HFF00B800, &HFF00AB00, &HFF00AB47, &HFF008B8B, &HFF2C2C2C, &HFF000000, &HFF000000, _
	&HFFF8F8F8, &HFF3FBFFF, &HFF6B88FF, &HFF9878F8, &HFFF878F8, &HFFF85898, &HFFF87858, &HFFFFA347, _
	&HFFF8B800, &HFFB8F818, &HFF5BDB57, &HFF58F898, &HFF00EBDB, &HFF787878, &HFF000000, &HFF000000, _
	&HFFFFFFFF, &HFFA7E7FF, &HFFB8B8F8, &HFFD8B8F8, &HFFF8B8F8, &HFFFBA7C3, &HFFF0D0B0, &HFFFFE3AB, _
	&HFFFBDB7B, &HFFD8F878, &HFFB8F8B8, &HFFB8F8D8, &HFF00FFFF, &HFFF8D8F8, &HFF000000, &HFF000000 _ 
}

Function nesColour (c As Integer) As uByte
	Dim As uByte i
	
	If c = 0 Then
		nesColour = &H0F
	End If
	
	For i = 0 To 63
		If nesPal (i) = c Then 
			If i = &H0D Then i = &H0F	' Safe
			nesColour = i
			Exit Function
		End If
	Next i
	nesColour = &HFF
End Function

Sub usage
	Puts "ExPalSeq v0.1"
	Puts "    exports a palette sequence from a png file."
	Puts ""
	Puts "$ expalseq.exe palseq.png palseq.h sufix"
	Puts ""
	Puts "Where:"
	Puts "    palseq.png is a 4xN image with a palette sequence."
	Puts "    palseq.h is the output filename (C source)."
	Puts "    sufix is a sufix to be added to identifiers in the generated source."
End Sub

Dim As Any Ptr img
Dim As Integer w, h, x, y, c, i, j, fo
Dim As String sufix

If Command (3) = "" Then usage: End

' Setup screen
screenres 640, 480, 32, , -1

' Read input image
img = png_load (Command (1))
If ImageInfo (img, w, h, , , , ) Then
	' Error!
End If

If w <> 4 Then usage: End


fo = FreeFile
Open Command (2) For Output As #fo

sufix = Command (3)
Print #fo, "// " & Command (2)
Print #fo, "// Exported from " & Command (1) & " using expalseq.exe v0.1"
Print #fo, ""
Print #fo, "#define PALSEQ_SIZE_" & uCase (sufix) & " " & h
Print #fo, ""
Print #fo, "const unsigned char palseq_" & lCase (sufix) & " [] = {"

For y = 0 To h - 1
	Print #fo, "	";
	For x = 0 To 3
		c = Point (x, y, img)
		Print #fo, "0x" & Lcase (Hex (nesColour (c), 2));
		If y < h - 1 Or x < 3 Then Print #fo, ", ";
	Next x
	Print #fo, ""
Next y

Print #fo, "};"

Close #fo

Puts "ExPalSeq, sequence of " & h & " palettes exported to " & Command (2) & "."
