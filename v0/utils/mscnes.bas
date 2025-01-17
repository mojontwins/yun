' Parser y compilador para los scripts de la churrera NES 1.0
' Copyleft 2010, 2011, 2012, 2013 The Mojon Twins.
' Basado en msc.exe
' Compilar con freeBasic (http://www.freebasic.net).

Const LIST_WORDS_SIZE = 20
Const LIST_CLAUSULES_SIZE = 100
Dim Shared listaPalabras (LIST_WORDS_SIZE) As String
Dim Shared listaClausulasEnter (LIST_CLAUSULES_SIZE) As Integer
Dim Shared listaClausulasFire (LIST_CLAUSULES_SIZE) As Integer
Dim Shared clausulasUsed (255) As Integer
Dim Shared actionsUsed (255) As Integer
Dim Shared maxItem As Integer
Dim Shared maxFlag As Integer
Dim Shared maxNPant As Integer
Dim Shared clausulasEnterIdx As Integer
Dim Shared clausulasFireIdx As Integer
Dim Shared clausulasEnter (LIST_CLAUSULES_SIZE) As String
Dim Shared clausulasFire (LIST_CLAUSULES_SIZE) As String
Dim AddTo (LIST_WORDS_SIZE) As Integer
Dim AddToIdx As Integer

Sub dump ()
	Dim i As Integer
	For i = 0 to LIST_WORDS_SIZE
		Print "["+listaPalabras (i) + "]";
	next i
	print
end sub

Sub stringToArray (in As String)
	Dim m as Integer
	Dim index as Integer
	Dim character as String * 1
	
	for m = 1 to LIST_WORDS_SIZE: listaPalabras (m) = "": Next m
	
	index = 0
	listaPalabras (index) = ""
	in = in + " "
	
	For m = 1 To Len (in)
		character = Ucase (Mid (in, m, 1))
		If (character >= "A" and character <= "Z") or (character >= "0" and character <="9") or character = "#" or character = "_" or character = "'" or character="<" or character=">" or character="!" or character="?" or character = "." or character = "-" or character=":" Then
			listaPalabras (index) = listaPalabras (index) + character
		Else
			listaPalabras (index) = Ltrim (Rtrim (listaPalabras (index)))
			If listaPalabras (index) <> "" Then
				index = index + 1
			End If
			If character <> " " Then 
				listaPalabras (index) = character
				index = index + 1
			End If
			listaPalabras (index) = ""
		End If
	Next m
End Sub

Sub displayMe (clausula As String) 
	Dim i As Integer
	Dim p As String
	
	For i = 1 To Len (clausula)
		p = Str (asc (mid (clausula, i, 1)))
		if Len (p) = 1 Then p = "00" + p
		If Len (p) = 2 Then p = "0" + p
		? p; 
		If i < Len (clausula) Then ? ", ";
	Next i
	Print
End Sub

Function writeMe (clausula As String) As String
	Dim res As String
	Dim i As Integer
	
	For i = 1 To Len (clausula)
		res = res + "$" + hex (asc (mid (clausula, i, 1)), 2)
		
		If i < Len (clausula) Then res = res + ", "
	Next i
	writeMe = res
End Function

Sub writeMeNice (f As Integer, clausula As String)
	Dim ct As integer
	Dim i As integer
	ct = 0
	
	For i = 1 To Len (clausula)
		if ct Mod 16 = 0 Then
			print #f, ""
			print #f, "    .byte ";
		end if
		print #f, "$" + hex (asc (mid (clausula, i, 1)), 2);
		If i < Len (clausula) and (ct Mod 16) < 15 then  print #f, ", ";
		ct = ct + 1
	Next i
	print #f, ""
	print #f, ""
End Sub

Function pval (s as string) as integer
	Dim res as integer
	if (left(s, 1) = "#") Then
		res = 128 + val (right (s, len(s) - 1))
	Else
		res = val (s)
	End If
	pval = res
end function

Function procesaClausulas (f As integer, nPant As Integer) As String
	' Lee cl�usulas de la pantalla nPant del archivo abierto f
	Dim linea As String
	Dim msc_done As Integer
	Dim estado As integer
	Dim clausulas As String
	Dim clausula As String
	Dim numclausulas As Integer
	Dim longitud As Integer
	Dim ai As Integer
	
	msc_done = 0
	estado = 0
	numclausulas = 0
	longitud = 0
	clausulas = ""
	clausula = ""
	
	While not msc_done And Not eof (f)
		Line input #f, linea
		linea = Trim (linea, Any chr (32) + chr (9))
		'?estado & " " & linea
		'?linea ;"-";:displayMe clausula
		stringToArray (linea)
		
		if estado <> 1 then
			' Leyendo cl�usulas
			Select Case listaPalabras (0)
				case "IF":
					Select Case listaPalabras (1)
						Case "PLAYER_HAS_ITEM":
							clausula = clausula + chr (&H1) + chr (pval (listaPalabras (2)))
							numClausulas = numClausulas + 1
							clausulasUsed (&H1) = -1
							if maxItem < val (listaPalabras (2)) Then maxItem = val (listaPalabras (2))
						Case "PLAYER_HASN'T_ITEM":
							clausula = clausula + chr (&H2) + chr (pval (listaPalabras (2)))
							numClausulas = numClausulas + 1
							clausulasUsed (&H2) = -1
							if maxItem < val (listaPalabras (2)) Then maxItem = val (listaPalabras (2))
						Case "FLAG":
							Select Case listaPalabras (3)
								Case "=":
									if listaPalabras (4) = "FLAG" Then
										clausula = clausula + chr (&H14) + chr (pval (listaPalabras (2))) + chr (pval(listaPalabras (5)))
										clausulasUsed (&H14) = -1
										if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
										if maxFlag < val (listaPalabras (5)) Then maxFlag = val (listaPalabras (5))
									Else
										clausula = clausula + chr (&H10) + chr (pval (listaPalabras (2))) + chr (pval(listaPalabras (4)))
										clausulasUsed (&H10) = -1
										if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
										if maxFlag < val (listaPalabras (4)) Then maxFlag = val (listaPalabras (4))
									End If
								Case "<":
									If listaPalabras (4) = "FLAG" Then
										clausula = clausula + chr (&H15) + chr (pval (listaPalabras (2))) + chr (pval(listaPalabras (5)))
										clausulasUsed (&H15) = -1
										if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
										if maxFlag < val (listaPalabras (5)) Then maxFlag = val (listaPalabras (5))
									Else
										clausula = clausula + chr (&H11) + chr (pval (listaPalabras (2))) + chr (pval(listaPalabras (4)))
										clausulasUsed (&H11) = -1
										if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
										if maxFlag < val (listaPalabras (4)) Then maxFlag = val (listaPalabras (4))
									End If
								Case ">":
									If listaPalabras (4) = "FLAG" Then
										clausula = clausula + chr (&H16) + chr (pval (listaPalabras (2))) + chr (pval(listaPalabras (5)))
										clausulasUsed (&H16) = -1
										if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
										if maxFlag < val (listaPalabras (5)) Then maxFlag = val (listaPalabras (5))
									Else
										clausula = clausula + chr (&H12) + chr (pval (listaPalabras (2))) + chr (pval(listaPalabras (4)))
										clausulasUsed (&H12) = -1
										if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
										if maxFlag < val (listaPalabras (4)) Then maxFlag = val (listaPalabras (4))
									End If
								Case "<>", "!=":
									If listaPalabras (4) = "FLAG" Then
										clausula = clausula + chr (&H17) + chr (pval (listaPalabras (2))) + chr (pval(listaPalabras (5)))
										clausulasUsed (&H17) = -1
										if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
										if maxFlag < val (listaPalabras (5)) Then maxFlag = val (listaPalabras (5))
									Else
										clausula = clausula + chr (&H13) + chr (pval (listaPalabras (2))) + chr (pval(listaPalabras (4)))
										clausulasUsed (&H13) = -1
										if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
										if maxFlag < val (listaPalabras (4)) Then maxFlag = val (listaPalabras (4))
									End If
							End Select
							numClausulas = numClausulas + 1
						Case "PLAYER_TOUCHES":
							clausula = clausula + chr (&H20) + chr (pval (listaPalabras (2))) + chr (pval (listaPalabras (4)))
							clausulasUsed (&H20) = -1
							numClausulas = numClausulas + 1
						Case "PLAYER_IN_X":
							clausula = clausula + chr (&H21) + chr (val (listaPalabras (2))) + chr (val (listaPalabras (4)))
							clausulasUsed (&H21) = -1
							numClausulas = numClausulas + 1
						Case "PLAYER_IN_Y":
							clausula = clausula + chr (&H22) + chr (val (listaPalabras (2))) + chr (val (listaPalabras (4)))
							clausulasUsed (&H22) = -1
							numClausulas = numClausulas + 1
						Case "ALL_ENEMIES_DEAD"
							clausula = clausula + chr (&H30)
							clausulasUsed (&H30) = -1
							numClausulas = numClausulas + 1
						Case "ENEMIES_KILLED_EQUALS"
							clausula = clausula + chr (&H31) + chr (pval (listaPalabras (2)))
							clausulasUsed (&H31) = -1
							numClausulas = numClausulas + 1
						Case "PLAYER_HAS_OBJECTS"
							clausula = clausula + chr (&H40)
							clausulasUsed (&H40) = -1
							numClausulas = numClausulas + 1
						Case "OBJECT_COUNT"
							clausula = clausula + chr (&H41) + chr (pval (listaPalabras (3)))
							clausulasUsed (&H41) = -1
							numClausulas = numClausulas + 1
						Case "NPANT"
							clausula = clausula + chr (&H50) + chr (pval (listaPalabras (2)))
							clausulasUsed (&H50) = -1
							numClausulas = numClausulas + 1
						Case "NPANT_NOT"
							clausula = clausula + chr (&H51) + chr (pval (listaPalabras (2)))
							clausulasUsed (&H51) = -1
							numClausulas = numClausulas + 1
						Case "JUST_PUSHED"
							clausula = clausula + chr (&H60)
							clausulasUsed (&H60) = -1
							numClausulas = numClausulas + 1
						Case "TIMER"
							If listaPalabras (2) = ">=" Then
								clausula = clausula + chr (&H70) + chr (pval (listaPalabras (3)))
								clausulasUsed (&H70) = -1
								numClausulas = numClausulas + 1
							ElseIf listaPalabras (2) = "<=" Then
								clausula = clausula + chr (&H71) + chr (pval (listaPalabras (3)))
								clausulasUsed (&H71) = -1
								numClausulas = numClausulas + 1
							End If
						Case "LEVEL"
							If listaPalabras (2) = "=" Then
								clausula = clausula + Chr (&H80) + chr (pval (listaPalabras (3)))
								clausulasUsed (&H80) = -1
								numClausulas = numClausulas + 1
							End If
						Case "TRUE"
							clausula = clausula + chr (&HF0)
							clausulasUsed (&HF0) = -1
							numClausulas = numClausulas + 1
					End Select
				case "THEN":
					clausula = clausula + Chr (255)
					if numclausulas = 0 Then Print "ERROR: THEN sin cl�usulas": msc_done = -1
					estado = 1
				case "END":
					if estado = 0 then
					msc_done = -1
					end if	
			end select
		else
			' Leyendo acciones
			Select Case listaPalabras (0)
				Case "SET":
					Select Case listaPalabras (1)
						Case "ITEM":
							clausula = clausula + Chr (&H0) + Chr (pval (listaPalabras (2))) + chr (pval (listaPalabras (4)))
							actionsUsed (&H0) = -1
							if maxItem < val (listaPalabras (2)) Then maxItem = val (listaPalabras (2))
						Case "FLAG":
							clausula = clausula + Chr (&H1) + Chr (pval (listaPalabras (2))) + chr (pval (listaPalabras (4)))	
							actionsUsed (&H1) = -1
							if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
						Case "TILE":
							clausula = clausula + Chr (&H20) + Chr (pval (listaPalabras (3))) + Chr (pval (listaPalabras (5))) + Chr (pval (listaPalabras (8)))
							actionsUsed (&H20) = -1
					End Select
				Case "INC":
					Select Case listaPalabras (1)
						Case "FLAG":
							clausula = clausula + Chr (&H10) + Chr (pval (listaPalabras (2))) + chr (pval (listaPalabras (4)))	
							actionsUsed (&H10) = -1
							if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
						Case "LIFE":
							clausula = clausula + Chr (&H30) + Chr (pval (listaPalabras (2)))
							actionsUsed (&H30) = -1
						Case "OBJECTS":
							clausula = clausula + Chr (&H40) + Chr (pval (listaPalabras (2)))
							actionsUsed (&H40) = -1
					End Select
				Case "DEC":
					Select Case listaPalabras (1)
						Case "FLAG":
							clausula = clausula + Chr (&H11) + Chr (pval (listaPalabras (2))) + chr (pval (listaPalabras (4)))						
							actionsUsed (&H11) = -1
							if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
						Case "LIFE":
							clausula = clausula + Chr (&H31) + Chr (pval (listaPalabras (2)))
							actionsUsed (&H31) = -1
						Case "OBJECTS":
							clausula = clausula + Chr (&H41) + Chr (pval (listaPalabras (2)))
							actionsUsed (&H41) = -1
					End Select
				Case "ADD":
					clausula = clausula + Chr (&H12) + Chr (pval (listaPalabras (2))) + chr (pval (listaPalabras (4)))						
					actionsUsed (&H12) = -1
					if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
					if maxFlag < val (listaPalabras (4)) Then maxFlag = val (listaPalabras (4))
				Case "SUB":
					clausula = clausula + Chr (&H13) + Chr (pval (listaPalabras (2))) + chr (pval (listaPalabras (4)))						
					actionsUsed (&H13) = -1
					if maxFlag < val (listaPalabras (2)) Then maxFlag = val (listaPalabras (2))
					if maxFlag < val (listaPalabras (4)) Then maxFlag = val (listaPalabras (4))
				Case "SWAP":
					clausula = clausula + Chr (&H14) + Chr (pval (listaPalabras (1))) + chr (pval (listaPalabras (3)))
					actionsUsed (&H14) = -1
				Case "FLICKER":
					clausula = clausula + Chr (&H32)
					actionsUsed (&H32) = -1
				Case "DIZZY":
					clausula = clausula + Chr (&H33)
					actionsUsed (&H33) = -1
				Case "PRINT_TILE_AT":
					clausula = clausula + Chr (&H50) + Chr (pval (listaPalabras (2))) + Chr (pval (listaPalabras (4))) + Chr (pval (listaPalabras (7)))
					actionsUsed (&H50) = -1
				Case "SET_FIRE_ZONE":
					clausula = clausula + Chr (&H51) + Chr (pval (listaPalabras (1))) + Chr (pval (listaPalabras (3))) + Chr (pval (listaPalabras (5))) + Chr (pval (listaPalabras (7)))
					actionsUsed (&H51) = -1
				Case "SHOW_COINS":
					clausula = clausula + Chr (&H60)
					actionsUsed (&H60) = -1
				Case "HIDE_COINS":
					clausula = clausula + Chr (&H61)
					actionsUsed (&H61) = -1
				Case "ENABLE_KILL_SLOWLY"
					clausula = clausula + Chr (&H62)
					actionsUsed (&H62) = -1
				Case "DISABLE_KILL_SLOWLY"
					clausula = clausula + Chr (&H63)
					actionsUsed (&H63) = -1
				Case "ENABLE_TYPE_6"
					clausula = clausula + Chr (&H64)
					actionsUsed (&H64) = -1
				Case "DISABLE_TYPE_6"
					clausula = clausula + Chr (&H65)
					actionsUsed (&H65) = -1
				Case "ENABLE_MAKE_TYPE_6"
					clausula = clausula + Chr (&H66)
					actionsUsed (&H66) = -1
				Case "DISABLE_MAKE_TYPE_6"
					clausula = clausula + Chr (&H67)
					actionsUsed (&H67) = -1
				Case "REDRAW"
					clausula = clausula + Chr (&H6E)
					actionsUsed (&H6E) = -1
				Case "REENTER"
					clausula = clausula + Chr (&H6F)
					actionsUsed (&H6F) = -1
				Case "WARP_TO"
					clausula = clausula + Chr (&H6D) + Chr (pval (listaPalabras (1))) + Chr (pval (listaPalabras (3))) + Chr (pval (listaPalabras (5)))
					actionsUsed (&H6D) = -1
				Case "SET_TIMER"
					clausula = clausula + Chr (&H70) + Chr (pval (listaPalabras (1))) + Chr (pval (listaPalabras (3)))
					actionsUsed (&H70) = -1
				Case "TIMER_START"
					clausula = clausula + Chr (&H71)
					actionsUsed (&H71) = -1
				Case "TIMER_STOP"
					clausula = clausula + Chr (&H72)
					actionsUsed (&H72) = -1
				Case "NEXT_LEVEL":
					clausula = clausula + Chr (&HD0)
					actionsUsed (&HD0) = -1
				Case "SOUND":
					clausula = clausula + Chr (&HE0) + Chr (pval (listaPalabras (1)))
					actionsUsed (&HE0) = -1
				Case "SHOW":
					clausula = clausula + Chr (&HE1)
					actionsUsed (&HE1) = -1
				Case "RECHARGE":
					clausula = clausula + Chr (&HE2)
					actionsUsed (&HE2) = -1
				Case "TEXT":
					clausula = clausula + Chr (&HE3)
					for ai = 1 To Len (listaPalabras (1))
						if ai = 31 Then Exit For
						If Mid (listaPalabras (1), ai, 1) = "_" Then
							clausula = clausula + Chr (0)
						Else
							clausula = clausula + Chr (Asc(Mid (listaPalabras (1), ai, 1)) - 32)
						End If
					Next ai
					clausula = clausula + Chr (&HEE)
					actionsUsed (&HE3) = -1
				Case "EXTERN":
					clausula = clausula + Chr (&HE4) + Chr (Pval (listaPalabras (1)))
					actionsUsed (&HE4) = -1
				Case "GAME":
					clausula = clausula + Chr (240)
					actionsUsed (240) = -1
				Case "WIN":
					clausula = clausula + Chr (241)
					actionsUsed (241) = -1
				Case "END":
					clausula = clausula + Chr (255)
					clausula = Chr (len (clausula)) + clausula
					clausulas = clausulas + clausula
					numclausulas = 0
					estado = 0
					clausula = ""
			End Select
		End if
	wend
	procesaClausulas = Clausulas + Chr (255)
End Function

Dim f As Integer
Dim i As Integer
Dim nPant As Integer
Dim linea As String
Dim clausulas As String
dim o as String

Dim inFileName As String
Dim outFileName As String
Dim maxpants As Integer

' TODO: Comprobaci�n de la entrada
'inFileName = "test.spt"
'outFileName = "msc.h"
inFileName = command (1)
maxpants = pval (command (2))

if command (1) = "" or maxpants = 0 then
	print "msc 4.7 / 3.99.2"
	print "uso: msc input maxpants"
	system
end if

maxItem = 0
maxFlag = 0
maxNPant = 0

For i = 0 to LIST_CLAUSULES_SIZE
	listaClausulasEnter (i) = -1
	listaClausulasFire (i) = -1
Next i

' Abrimos el archivo de entrada
f = Freefile
Open inFileName for input as #f

' Esto es una m�quina de estados.

While not eof (f)

	Line input #f, linea
	linea = Trim (linea, Any chr (32) + chr (9))
	stringToArray (linea)

	' ESTADO 1: Buscando ENTERING SCREEN x � PRESS_FIRE AT SCREEN x
	Select Case listaPalabras (0)
		Case "ENTERING":
			If listaPalabras (1) = "GAME" Then
				AddToIdx = 1
				AddTo (0) = maxpants
			ElseIf listaPalabras (1) = "ANY" Then
				AddToIdx = 1
				AddTo (0) = maxpants + 1
			Else
				AddToIdx = 0
				For i = 2 to LIST_WORDS_SIZE
					If listaPalabras (i) <> "" And listaPalabras (i) <> "," Then
						AddTo (AddToIdx) = val (listaPalabras (i))
						AddToIdx = AddToIdx + 1
					End If
				Next i
			End If
			clausulas = procesaClausulas (f, 0)
			clausulasEnter (clausulasEnterIdx) = clausulas	
			For i = 0 To AddToIdx - 1
				listaClausulasEnter (AddTo(i)) = clausulasEnterIdx
			Next i
			
			clausulasEnterIdx = clausulasEnterIdx + 1
		Case "ON_TIMER_OFF":
			clausulas = procesaClausulas (f, 0)
			clausulasEnter (clausulasEnterIdx) = clausulas
			listaClausulasEnter (maxpants + 2) = clausulasEnterIdx
			clausulasEnterIdx = clausulasEnterIdx + 1
			
		Case "PRESS_FIRE":
			If listaPalabras (2) = "ANY" Then
				AddToIdx = 1
				AddTo (0) = maxpants
			Else
				AddToIdx = 0
				For i = 3 to LIST_WORDS_SIZE
					If listaPalabras (i) <> "" And listaPalabras (i) <> "," Then
						AddTo (AddToIdx) = val (listaPalabras (i))
						AddToIdx = AddToIdx + 1
					End If
				Next i
			End If
			clausulas = procesaClausulas (f, 0)
			clausulasFire (clausulasFireIdx) = clausulas
			
			For i = 0 To AddToIdx - 1
				listaClausulasFire (AddTo(i)) = clausulasFireIdx
			Next i
			
			clausulasFireIdx = clausulasFireIdx + 1
		Case "PLAYER_GETS_COIN":
			clausulas = procesaClausulas (f, 0)
			clausulasFire (clausulasFireIdx) = clausulas
			listaClausulasFire (maxpants + 1) = clausulasFireIdx
			clausulasFireIdx = clausulasFireIdx + 1
		
		Case "PLAYER_KILLS_ENEMY":
			clausulas = procesaClausulas (f, 0)
			clausulasFire (clausulasFireIdx) = clausulas
			listaClausulasFire (maxpants + 2) = clausulasFireIdx
			clausulasFireIdx = clausulasFireIdx + 1
		
	End Select
Wend

' Fin
Close #f

' Y cuando tenemos todo esto lleno, tenemos que sacar 
' el c�digo que interpreta los scripts y los scripts
' en s� en #asm con etiquetas y luego un array de etiquetas.

' Esta es, en realidad, la parte complicada y eso. Pero
' tampoco es demasiado moco de pavo.

'f = FreeFile
'open "msc-config.h" for output as #f
'
'print #f, "// msc.h"
'print #f, "// Generado por Mojon Script Compiler de la Churrera 4.7 / 3.99.2"
'print #f, "// Copyleft 2013 The Mojon Twins"
'print #f, " "
'If maxItem > 0 then
'	print #f, "#define MSC_MAXITEMS    " + str (maxitem)
'	print #f, " "
'	print #f, "typedef struct {"
'	print #f, "    unsigned char status;"
'	print #f, "    unsigned char supertile;"
'	print #f, "    unsigned char n_pant;"
'	print #f, "    unsigned char x, y;"
'	print #f, "} ITEM;"
'	print #f, "ITEM items [MSC_MAXITEMS];"
'end if
'print #f, " "
'print #f, "unsigned char script_result = 0;"
'print #f, "unsigned char script_something_done = 0;"
'print #f, " "
'close #f

open "scripts.s" for output as #f
print #f, "; scripts.s"
print #f, "; Generado por Mojon Script Compiler de la Churrera NES"
print #f, "; Copyleft 2013/2014 The Mojon Twins"
print #f, " "
print #f, "; Script data & pointers"
print #f, " "
print #f, ".export _e_scripts"
print #f, ".export _f_scripts"
print #f, " "


For i = 0 to clausulasEnterIdx - 1
	print #f, "mscce_" + Trim (Str (i)) + ":"
	'print #f, "    defb " + writeMe (clausulasEnter (i))
	writeMeNice f, clausulasEnter (i)
Next i
For i = 0 To clausulasFireIdx - 1
	print #f, "msccf_" + Trim (Str (i)) + ":"
	'print #f, "    defb " + writeMe (clausulasFire (i))
	writeMeNice f, clausulasFire (i)
Next i

print #f, " "
print #f, "_e_scripts:"
o = ".word "
for i = 0 to maxpants + 2
	if listaClausulasEnter (i) <> -1 Then
		o = o + "mscce_"+trim(str(listaClausulasEnter (i)))
	else
		o = o + "0"
	end if
	if i < maxpants + 2 then o = o +", "
next i
print #f, "    " + o

print #f, " "
print #f, "_f_scripts:"
o = ".word "
for i = 0 to maxpants + 2
	if listaClausulasFire (i) <> -1 Then
		o = o + "msccf_"+trim(str(listaClausulasFire (i)))
	else
		o = o + "0"
	end if
	if i < maxpants + 2 then o = o +", "
next i
print #f, "    " + o
print #f, " "

close #f

open "mscnes.h" for output as #f
print #f, "// mscnes.h"
print #f, "// Generated by Mojon Script Compiler MK1 NES"
print #f, "// Copyleft 2013/2014, 2019 The Mojon Twins"
print #f, " "

print #f, "unsigned char msc_done = 0;"
print #f, "unsigned char msc_cont = 0;"
print #f, "unsigned char msc_x, msc_y, msc_n, msc_m, msc_c;"
print #f, "unsigned char *next_script;"
print #f, " "
print #f, "void msc_init_all (void) {"
print #f, "    for (gpit = 0; gpit < MAX_FLAGS; gpit ++)"
print #f, "        flags [gpit] = 0;"
print #f, "}"
print #f, " "
print #f, "unsigned char read_byte (void) {"
print #f, "    return *script++;"
print #f, "}"
print #f, " "
print #f, "unsigned char read_vbyte (void) {"
print #f, "    msc_c = read_byte ();"
print #f, "    if (msc_c & 128) return flags [msc_c & 127];"
print #f, "    return msc_c;"
print #f, "}"
print #f, " "
print #f, "void run_script (void) {"
print #f, "    msc_m = 0;"
print #f, " "
print #f, "    if (script == 0)"
print #f, "        return; "
print #f, " "
print #f, "    script_something_done = 0;"
print #f, " "
print #f, "    while (1) {"
print #f, "        msc_c = read_byte ();"
print #f, "        if (msc_c == 0xFF) break;"
print #f, "        next_script = script + msc_c;"
print #f, "        msc_done = msc_cont = 0;"
print #f, "        while (!msc_done) {"
print #f, "            msc_c = read_byte ();"
print #f, "            switch (msc_c) {"

if clausulasUsed (&H1) Then
	print #f, "                case 0x01:"
	print #f, "                    // IF PLAYER_HAS_ITEM msc_x"
	print #f, "                    // Opcode: 01 msc_x"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_done = (items [msc_x].status == 0);"
	print #f, "                    break;"
end if

if clausulasUsed (&H2) Then
	print #f, "                case 0x02:"
	print #f, "                    // IF PLAYER_HASN'T_ITEM msc_x"
	print #f, "                    // Opcode: 02 msc_x"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_done = (items [msc_x].status != 0);"
	print #f, "                    break;"
end if

if clausulasUsed (&H10) Then
	print #f, "                case 0x10:"
	print #f, "                    // IF FLAG msc_x = msc_n"
	print #f, "                    // Opcode: 10 msc_x msc_n"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_n = read_vbyte ();"	
	print #f, "                    msc_done = (flags [msc_x] != msc_n);"
	print #f, "                    break;"
end if

if clausulasUsed (&H11) Then
	print #f, "                case 0x11:"
	print #f, "                    // IF FLAG msc_x < msc_n"
	print #f, "                    // Opcode: 11 msc_x msc_n"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_n = read_vbyte ();"	
	print #f, "                    msc_done = (flags [msc_x] >= msc_n);"
	print #f, "                    break;"
end if

if clausulasUsed (&H12) Then
	print #f, "                case 0x12:"
	print #f, "                    // IF FLAG msc_x > msc_n"
	print #f, "                    // Opcode: 12 msc_x msc_n"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_n = read_vbyte ();"	
	print #f, "                    msc_done = (flags [msc_x] <= msc_n);"
	print #f, "                    break;"
end if

if clausulasUsed (&H13) Then
	print #f, "                case 0x13:"
	print #f, "                    // IF FLAG msc_x <> msc_n"
	print #f, "                    // Opcode: 13 msc_x msc_n"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_n = read_vbyte ();"	
	print #f, "                    msc_done = (flags [msc_x] == msc_n);"
	print #f, "                    break;"
end if

if clausulasUsed (&H14) Then
	print #f, "                case 0x14:"
	print #f, "                    // IF FLAG msc_x = FLAG msc_y"
	print #f, "                    // Opcode: 14 msc_x msc_n"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_y = read_vbyte ();"	
	print #f, "                    msc_done = (flags [msc_x] != flags [msc_y]);"
	print #f, "                    break;"
end if

if clausulasUsed (&H15) Then
	print #f, "                case 0x15:"
	print #f, "                    // IF FLAG msc_x < FLAG msc_y"
	print #f, "                    // Opcode: 15 msc_x msc_n"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_y = read_vbyte ();"	
	print #f, "                    msc_done = (flags [msc_x] >= flags [msc_y]);"
	print #f, "                    break;"
end if

if clausulasUsed (&H16) Then
	print #f, "                case 0x16:"
	print #f, "                    // IF FLAG msc_x > FLAG msc_y"
	print #f, "                    // Opcode: 16 msc_x msc_n"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_y = read_vbyte ();"	
	print #f, "                    msc_done = (flags [msc_x] <= flags [msc_y]);"
	print #f, "                    break;"
end if

if clausulasUsed (&H17) Then
	print #f, "                case 0x17:"
	print #f, "                    // IF FLAG msc_x <> FLAG msc_y"
	print #f, "                    // Opcode: 17 msc_x msc_n"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_y = read_vbyte ();"	
	print #f, "                    msc_done = (flags [msc_x] == flags [msc_y]);"
	print #f, "                    break;"
end if

if clausulasUsed (&H20) Then
	print #f, "                case 0x20:"
	print #f, "                    // IF PLAYER_TOUCHES msc_x, msc_y"
	print #f, "                    // Opcode: 20 msc_x msc_y"
	print #f, "                    msc_x = read_vbyte ();"
	print #f, "                    msc_y = read_vbyte ();"	
	print #f, "                    msc_done = (!((px >> 6) >= (msc_x << 4) - 15 && (px >> 6) <= (msc_x << 4) + 15 && (py >> 6) >= (msc_y << 4) - 15 && (py >> 6) <= (msc_y << 4) + 15));"
	print #f, "                    break;"
end if

if clausulasUsed (&H21) Then
	print #f, "                case 0x21:"
	print #f, "                    // IF PLAYER_IN_X x1, x2"
	print #f, "                    // Opcode: 21 x1 x2"
	print #f, "                    msc_x = read_byte ();"
	print #f, "                    msc_y = read_byte ();"	
	print #f, "                    msc_done = (!((px >> 6) >= msc_x && (px >> 6) <= msc_y));"
	print #f, "                    break;"
end if
	
if clausulasUsed (&H22) Then
	print #f, "                case 0x22:"
	print #f, "                    // IF PLAYER_IN_Y y1, y2"
	print #f, "                    // Opcode: 22 y1 y2"
	print #f, "                    msc_x = read_byte ();"
	print #f, "                    msc_y = read_byte ();"	
	print #f, "                    msc_done = (!((py >> 6) >= msc_x && (py >> 6) <= msc_y));"
	print #f, "                    break;"
end if

if clausulasUsed (&H30) Then
	print #f, "                case 0x30:"
	print #f, "                    // IF ALL_ENEMIES_DEAD"
	print #f, "                    // Opcode: 30"
	print #f, "                    msc_done = (pkilled != BADDIES_COUNT);"
	print #f, "                    break;"
end if

if clausulasUsed (&H31) Then
	print #f, "                case 0x31:"
	print #f, "                    // IF ENEMIES_KILLED_EQUALS msc_n"
	print #f, "                    // Opcode: 31 msc_n"
	print #f, "                    msc_n = read_vbyte ();"
	print #f, "                    msc_done = (pkilled != msc_n);"
	print #f, "                    break;"
End If

if clausulasUsed (&H40) Then
	print #f, "                case 0x40:"
	print #f, "                     // IF PLAYER_HAS_OBJECTS"
	print #f, "                     // Opcode: 40"
	print #f, "                     msc_done = (pobjs == 0);"
	print #f, "                     break;"
End If

If clausulasUsed (&H41) Then
	print #f, "                case 0x41:"
	print #f, "                     // IF OBJECT_COUNT = msc_n"
	print #f, "                     // Opcode: 41 msc_n"
	print #f, "                     msc_n = read_vbyte ();"
	print #f, "                     msc_done = (pobjs != msc_n);"
	print #f, "                     break;"
End If

If clausulasUsed (&H50) Then
	print #f, "                case 0x50:"
	print #f, "                     // IF NPANT msc_n"
	print #f, "                     // Opcode: 50 msc_n"
	print #f, "                     msc_n = read_vbyte ();"
	print #f, "                     msc_done = (n_pant != msc_n);"
	print #f, "                     break;"
End If

If clausulasUsed (&H51) Then
	print #f, "                case 0x51:"
	print #f, "                     // IF NPANT_NOT msc_n"
	print #f, "                     // Opcode: 51 msc_n"
	print #f, "                     msc_n = read_vbyte ();"
	print #f, "                     msc_done = (n_pant == msc_n);"
	print #f, "                     break;"
End If

If clausulasUsed (&H60) Then
	print #f, "                case 0x60:"
	print #f, "                     // IF JUST_PUSHED"
	print #f, "                     // Opcode: 60"
	print #f, "                     msc_done = (!just_pushed);"
	print #f, "                     break;"
End If

If clausulasUsed (&H70) Then
	print #f, "                case 0x70:"
	print #f, "                     // IF TIMER >= msc_x"
	print #f, "                     msc_n = read_vbyte ();"
	print #f, "                     msc_done = (ctimer.t < msc_n);"
	print #f, "                     break;"
End If

If clausulasUsed (&H71) Then
	print #f, "                case 0x71:"
	print #f, "                     // IF TIMER <= msc_x"
	print #f, "                     msc_n = read_vbyte ();"
	print #f, "                     msc_done = (ctimer.t > msc_n);"
	print #f, "                     break;"
End If

If clausulasUsed (&H80) Then
	print #f, "                case 0x80:"
	print #f, "                     // IF LEVEL = msc_n"
	print #f, "                     // Opcode: 80 msc_n"
	print #f, "                     msc_n = read_vbyte ();"
	print #f, "                     msc_done = (msc_n != level);"
	print #f, "                     break;"
End If

if clausulasUsed (&HF0) Then
	print #f, "                case 0xF0:"
	print #f, "                     // IF TRUE"
	print #f, "                     // Opcode: F0"
	print #f, "                     break;"
End If

print #f, "                case 0xFF:"
print #f, "                    // THEN"
print #f, "                    // Opcode: FF"
print #f, "                    msc_done = 1;"
print #f, "                    msc_cont = 1;"
print #f, "                    script_something_done = 1;"
print #f, "                    break;"

print #f, "            }"
print #f, "        }"

print #f, "        if (msc_cont) {"
print #f, "            msc_done = 0;"
print #f, "            while (!msc_done) {"
print #f, "                msc_c = read_byte ();"
print #f, "                switch (msc_c) {"

if actionsUsed (&H0) Then
	print #f, "                    case 0x00:"
	print #f, "                        // SET ITEM msc_x msc_n"
	print #f, "                        // Opcode: 00 msc_x msc_n"
	print #f, "                        msc_x = read_vbyte ();"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        items [msc_x].status = msc_n;"
	print #f, "                        break;"
End If

if actionsUsed (&H1) Then
	print #f, "                    case 0x01:"
	print #f, "                        // SET FLAG msc_x = msc_n"
	print #f, "                        // Opcode: 01 msc_x msc_n"
	print #f, "                        msc_x = read_vbyte ();"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        flags [msc_x] = msc_n;"
	print #f, "                        break;"
End If

if actionsUsed (&H10) Then
	print #f, "                    case 0x10:"
	print #f, "                        // INC FLAG msc_x, msc_n"
	print #f, "                        // Opcode: 10 msc_x msc_n"
	print #f, "                        msc_x = read_vbyte ();"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        flags [msc_x] += msc_n;"
	print #f, "                        break;"
End If

if actionsUsed (&H11) Then
	print #f, "                    case 0x11:"
	print #f, "                        // DEC FLAG msc_x, msc_n"
	print #f, "                        // Opcode: 11 msc_x msc_n"
	print #f, "                        msc_x = read_vbyte ();"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        flags [msc_x] -= msc_n;"
	print #f, "                        break;"
End If

if actionsUsed (&H12) Then
	print #f, "                    case 0x12:"
	print #f, "                        // ADD FLAGS msc_x, msc_y"
	print #f, "                        // Opcode: 12 msc_x msc_y"
	print #f, "                        msc_x = read_vbyte ();"
	print #f, "                        msc_y = read_vbyte ();"
	print #f, "                        flags [msc_x] = flags [msc_x] + flags [msc_y];"
	print #f, "                        break;"
End If

if actionsUsed (&H13) Then
	print #f, "                    case 0x13:"
	print #f, "                        // SUB FLAGS msc_x, msc_y"
	print #f, "                        // Opcode: 13 msc_x msc_y"
	print #f, "                        msc_x = read_vbyte ();"
	print #f, "                        msc_y = read_vbyte ();"
	print #f, "                        flags [msc_x] = flags [msc_x] - flags [msc_y];"
	print #f, "                        break;"
End If

if actionsUsed (&H14) Then
	print #f, "                    case 0x14:"
	print #f, "                        // SWAP FLAGS msc_x, msc_y"
	print #f, "                        // Opcode: 14 msc_x msc_y"
	print #f, "                        msc_x = read_vbyte ();"
	print #f, "                        msc_y = read_vbyte ();"
	print #f, "                        msc_n = flags [msc_x];"
	print #f, "                        flags [msc_x] = flags [msc_y];"
	print #f, "                        flags [msc_y] = msc_n;"
	print #f, "                        break;"
End If

if actionsUsed (&H20) Then
	print #f, "                    case 0x20:"
	print #f, "                        // SET TILE (msc_x, msc_y) = msc_n"
	print #f, "                        // Opcode: 20 msc_x msc_y msc_n"
	print #f, "                        _x = read_vbyte ();"
	print #f, "                        _y = read_vbyte ();"
	print #f, "                        _t = read_vbyte ();"
	print #f, "                        //clear_update_list ();"
	print #f, "                        //update_index = 0;"
	print #f, "                        map_set ();"
	print #f, "                        break;"
End If

if actionsUsed (&H30) Then
	print #f, "                    case 0x30:"
	print #f, "                        // INC LIFE msc_n"
	print #f, "                        // Opcode: 30 msc_n"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        plife += msc_n;"
	print #f, "                        break;"
End If

if actionsUsed (&H31) Then
	print #f, "                    case 0x31:"
	print #f, "                        // DEC LIFE msc_n"
	print #f, "                        // Opcode: 31 msc_n"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        plife -= msc_n;"
	print #f, "                        break;"
End If

if actionsUsed (&H32) Then
	print #f, "                    case 0x32:"
	print #f, "                        // FLICKER"
	print #f, "                        // Opcode: 32"
	print #f, "                        pestado |= EST_PARP;"
	print #f, "                        pct_estado = 32;"
	print #f, "                        break;"
End If

if actionsUsed (&H33) Then
	print #f, "                    case 0x33:"
	print #f, "                        // DIZZY"
	print #f, "                        // Opcode: 33"
	print #f, "                        pestado |= EST_DIZZY;"
	print #f, "                        pct_estado = 32;"
	print #f, "                        break;"
End If

if actionsUsed (&H40) Then
	print #f, "                    case 0x40:"
	print #f, "                        // INC OBJECTS msc_n"
	print #f, "                        // Opcode: 40 msc_n"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        pobjs += msc_n;"
	print #f, "                        draw_objs ();"
	print #f, "                        break;"
End If

if actionsUsed (&H41) Then
	print #f, "                    case 0x41:"
	print #f, "                        // DEC OBJECTS msc_n"
	print #f, "                        // Opcode: 41 msc_n"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        pobjs -= msc_n;"
	print #f, "                        draw_objs ();"
	print #f, "                        break;"
End If

if actionsUsed (&H50) then
	print #f, "                    case 0x50:"
	print #f, "                        // PRINT_TILE_AT (msc_X, msc_Y) = msc_N"
	print #f, "                        // Opcode: 50 msc_x msc_y msc_n"
	print #f, "                        msc_x = read_vbyte ();"
	print #f, "                        msc_y = read_vbyte ();"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        draw_coloured_tile (msc_x, msc_y, msc_n);"
	print #f, "                        break;"
end if

if actionsUsed (&H51) Then
	print #f, "                    case 0x51:"
	print #f, "                        // SET_FIRE_ZONE x1, y1, x2, y2"
	print #f, "                        // Opcode: 51 x1 y1 x2 y2"
	print #f, "                        fzx1 = read_byte ();"
	print #f, "                        fzy1 = read_byte ();"
	print #f, "                        fzx2 = read_byte ();"
	print #f, "                        fzy2 = read_byte ();"
	print #f, "                        f_zone_ac = 1;"
	print #f, "                        break;"
End If

if actionsUsed (&H60) Then
	print #f, "                    case 0x60:"
	print #f, "                        // SHOW_COINS"
	print #f, "                        // Opciode: 60"
	print #f, "                        scenery_info.show_coins = 1;"
	print #f, "                        break;"
End If

if actionsUsed (&H61) Then
	print #f, "                    case 0x61:"
	print #f, "                        // HIDE_COINS"
	print #f, "                        // Opcode: 61"
	print #f, "                        scenery_info.show_coins = 0;"
	print #f, "                        break;"
End If

If actionsUsed (&H62) Then
	print #f, "                    case 0x62:"
	print #f, "                        // ENABLE_KILL_SLOWLY"
	print #f, "                        // Opcode: 62"
	print #f, "                        scenery_info.evil_kills_slowly = 1;"
	print #f, "                        break;"
End If

If actionsUsed (&H63) Then
	print #f, "                    case 0x63:"
	print #f, "                        // DISABLE_KILL_SLOWLY"
	print #f, "                        // Opcode: 63"
	print #f, "                        scenery_info.evil_kills_slowly = 0;"
	print #f, "                        break;"
End If

If actionsUsed (&H64) Then
	print #f, "                    case 0x64:"
	print #f, "                        // ENABLE_TYPE_6"
	print #f, "                        // Opcode: 64"
	print #f, "                        scenery_info.allow_type_6 = 1;"
	print #f, "                        break;"
End If

If actionsUsed (&H65) Then
	print #f, "                    case 0x65:"
	print #f, "                        // DISABLE_TYPE_6"
	print #f, "                        // Opcode: 65"
	print #f, "                        scenery_info.allow_type_6 = 0;"
	print #f, "                        break;"
End If

If actionsUsed (&H66) THen 
	print #f, "                    case 0x66:"
	print #f, "                        // ENABLE_MAKE_TYPE_6"
	print #f, "                        // Opcode: 66"
	print #f, "                        scenery_info.make_type_6 = 1;"
	print #f, "                        break;"
End If

If actionsUsed (&H67) THen 
	print #f, "                    case 0x67:"
	print #f, "                        // DISABLE_MAKE_TYPE_6"
	print #f, "                        // Opcode: 67"
	print #f, "                        scenery_info.make_type_6 = 0;"
	print #f, "                        break;"
End If

If actionsUsed (&H6D) Then
	print #f, "                    case 0x6D:"
	print #f, "                        // WARP_TO msc_n"
	print #f, "                        // Opcode: 6D msc_n"
	print #f, "                        n_pant = read_vbyte ();"
	print #f, "                        px = read_vbyte () << 10;"
	print #f, "                        py = read_vbyte () << 10;"
	print #f, "                        script_result = 3; msc_done = 1;"
	print #f, "                        break;"
End If

if actionsUsed (&H6E) Then
	print #f, "                    case 0x6E:"
	print #f, "                        // REDRAW"
	print #f, "                        // Opcode: 6E"
	print #f, "                        draw_scr_background ();"
	print #f, "                        break;"
End If

if actionsUsed (&H6F) Then
	print #f, "                    case 0x6F:"
	print #f, "                        // REENTER"
	print #f, "                        // Opcode: 6F"
	print #f, "                        script_result = 3; msc_done = 1;"
	print #f, "                        break;"
End If

if actionsUsed (&H70) Then
	print #f, "                    case 0x70:"
	print #f, "                        // SET_TIMER a, b"
	print #f, "                        // Opcode: 0x70 a b"
	print #f, "                        ctimer.t = read_vbyte ();"
	print #f, "                        ctimer.frames = read_vbyte ();"
	print #f, "                        ctimer.count = ctimer.zero = 0;"
	print #f, "                        break;"
End If

If actionsUsed (&H71) Then
	print #f, "                    case 0x71:"
	print #f, "                        // TIMER_START"
	print #f, "                        // Opcode: 0x71"
	print #f, "                        ctimer.on = 1;"
	print #f, "                        break;"
End If

If actionsUsed (&H72) Then
	print #f, "                    case 0x72:"
	print #f, "                        // TIMER_START"
	print #f, "                        // Opcode: 0x72"
	print #f, "                        ctimer.on = 0;"
	print #f, "                        break;"
End If

if actionsUsed (&HD0)  Then
	print #f, "                    case 0xD0:"
	print #f, "                        // NEXT_LEVEL"
	print #f, "                        // Opcode: D0"
	print #f, "                        n_pant ++;"
	print #f, "                        init_player_values ();"
	print #f, "                        draw_scr ();"
	print #f, "                        break;"
End If

if actionsUsed (&HE0) Then
	print #f, "                    case 0xE0:"
	print #f, "                        // SOUND msc_n"
	print #f, "                        // Opcode: E0 msc_n"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        sfx_play (msc_n, 1);"
	print #f, "                        break;"
End If

If actionsUsed (&HE1) Then
	print #f, "                    case 0xE1:"
	print #f, "                        // SHOW"
	print #f, "                        // Opcode: E1"
	print #f, "                        ppu_waitnmi ();"
	print #f, "                        clear_update_list ();"
	print #f, "                        update_index = 0;"
	print #f, "                        break;"
End If

if actionsUsed (&HE2) Then
	print #f, "                    case 0xE2:"
	print #f, "                        // RECHARGE"
	print #f, "                        plife = PLAYER_LIFE;"
	print #f, "                        break;"
End If

if actionsUsed (&HE3) Then
	print #f, "                    case 0xE3:"
	print #f, "                        msc_x = 0;"
	print #f, "                        gp_addr = 0x2000 + (LINE_OF_TEXT << 5) + LINE_OF_TEXT_X;"
	print #f, "                        clear_update_list ();"
	print #f, "                        update_index = 0;"
	print #f, "                        while (1) {"
	print #f, "                           msc_n = read_byte ();"
	print #f, "                           if (msc_n == 0xEE) break;"
	print #f, "                           update_list [update_index++] = MSB (gp_addr);"
	print #f, "                           update_list [update_index++] = LSB (gp_addr ++);"
	print #f, "                           update_list [update_index++] = msc_n;"
	print #f, "                           msc_x ++;"
	print #f, "                        }"                
	print #f, "                        ppu_waitnmi ();"
	print #f, "                        clear_update_list ();"
	print #f, "                        update_index = 0;"
	print #f, "                        break;"
End If

if actionsUsed (&HE4) Then
	print #f, "                    case 0xE4:"
	print #f, "                        // EXTERN msc_n"
	print #f, "                        // Opcode: 0xE4 msc_n"
	print #f, "                        msc_n = read_vbyte ();"
	print #f, "                        do_extern_action (msc_n);"
	print #f, "                        break;"
End IF

if actionsUsed (&HF0) Then
	print #f, "                    case 0xF0:"
	print #f, "                        script_result = 2;"
	print #f, "                        msc_done = 1;"
	print #f, "                        break;"
End If

if actionsUsed (&HF1) Then
	print #f, "                    case 0xF1:"
	print #f, "                        script_result = 1;"
	print #f, "                        msc_done = 1;"
	print #f, "                        break;"
End If

print #f, "                    case 0xFF:"
print #f, "                        msc_done = 1;"
print #f, "                        break;"
print #f, "                }"
print #f, "            }"
print #f, "        }"
print #f, "        script = next_script;"
print #f, "    }"
'print #f, "    if (script_result == 3) {"
'print #f, "        script_result = 0;"
'print #f, "        draw_scr ();"
'print #f, "    }"
print #f, "}"

' Fin
Close #f

' Joer, qu� guarrada, pero no veas c�mo funciona... Incredibly evil.
' Po eso. 
