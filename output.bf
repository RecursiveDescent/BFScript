Goto 6:
	>>>>>>
Set 6 = 32:
	[-Clear]
	++++++++++++++++++++++++++++++++
Move 4 = Cell 6:
	Goto 6:
		
	[
	Goto 6:
		
	-
	Goto 4:
		<<
	+
	Goto 6:
		>>
	]
Goto 7:
	>
Set 7 = 2:
	[-Clear]
	++
Move 5 = Cell 7:
	Goto 7:
		
	[
	Goto 7:
		
	-
	Goto 5:
		<<
	+
	Goto 7:
		>>
	]
Goto 4:
	<<<
[-Clear]
Goto 5:
	>
Mul 4 = 4 times 5:
	[-
				Goto 4:
			<
++++++++++++++++++++++++++++++++
		Goto 5:
			>
	]
Move 1 = Cell 4:
	Goto 4:
		<
	[
	Goto 4:
		
	-
	Goto 1:
		<<<
	+
	Goto 4:
		>>>
	]
Goto 8:
	>>>>
Set 8 = 1:
	[-Clear]
	+
Move 2 = Cell 8:
	Goto 8:
		
	[
	Goto 8:
		
	-
	Goto 2:
		<<<<<<
	+
	Goto 8:
		>>>>>>
	]
Goto 2:
	<<<<<<
Add 1 = 1 plus 2:
	[-
		Goto 1:
			<
+
		Goto 2:
			>
	]
Move 0 = Cell 1:
	Goto 1:
		<
	[
	Goto 1:
		
	-
	Goto 0:
		<
	+
	Goto 1:
		>
	]
Copy 9 = Cell 0:
	Goto 0:
		<
	[
	-
	Goto 10:
		>>>>>>>>>>
	+
	Goto 0:
		<<<<<<<<<<
	]
	Goto 10:
		>>>>>>>>>>
	[
	-
	Goto 0:
		<<<<<<<<<<
	+
	Goto 9:
		>>>>>>>>>
	+
	Goto 10:
		>
	]
Goto 9:
	<
Output <9> .Copy 13 = Cell 0:
	Goto 0:
		<<<<<<<<<
	[
	-
	Goto 14:
		>>>>>>>>>>>>>>
	+
	Goto 0:
		<<<<<<<<<<<<<<
	]
	Goto 14:
		>>>>>>>>>>>>>>
	[
	-
	Goto 0:
		<<<<<<<<<<<<<<
	+
	Goto 13:
		>>>>>>>>>>>>>
	+
	Goto 14:
		>
	]
Move 11 = Cell 13:
	Goto 13:
		<
	[
	Goto 13:
		
	-
	Goto 11:
		<<
	+
	Goto 13:
		>>
	]
Goto 15:
	>>
Set 15 = 1:
	[-Clear]
	+
Move 12 = Cell 15:
	Goto 15:
		
	[
	Goto 15:
		
	-
	Goto 12:
		<<<
	+
	Goto 15:
		>>>
	]
Goto 12:
	<<<
Add 11 = 11 plus 12:
	[-
		Goto 11:
			<
+
		Goto 12:
			>
	]
Goto 11:
	<
Output <11> .Copy 18 = Cell 0:
	Goto 0:
		<<<<<<<<<<<
	[
	-
	Goto 19:
		>>>>>>>>>>>>>>>>>>>
	+
	Goto 0:
		<<<<<<<<<<<<<<<<<<<
	]
	Goto 19:
		>>>>>>>>>>>>>>>>>>>
	[
	-
	Goto 0:
		<<<<<<<<<<<<<<<<<<<
	+
	Goto 18:
		>>>>>>>>>>>>>>>>>>
	+
	Goto 19:
		>
	]
Move 16 = Cell 18:
	Goto 18:
		<
	[
	Goto 18:
		
	-
	Goto 16:
		<<
	+
	Goto 18:
		>>
	]
Goto 20:
	>>
Set 20 = 2:
	[-Clear]
	++
Move 17 = Cell 20:
	Goto 20:
		
	[
	Goto 20:
		
	-
	Goto 17:
		<<<
	+
	Goto 20:
		>>>
	]
Goto 17:
	<<<
Add 16 = 16 plus 17:
	[-
		Goto 16:
			<
+
		Goto 17:
			>
	]
Goto 16:
	<
Output <16> .
