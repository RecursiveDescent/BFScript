Goto 1:
	>
Set 1 = 57:
	[-Clear]
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Move 0 = Cell 1:
	Goto 0:
		<
	[-Clear]
	Goto 1:
		>
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
	Goto 9:
		>>>>>>>>
	[-Clear]
	Goto 0:
		<<<<<<<<<
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
Goto 11:
	>
Set 11 = 47:
	[-Clear]
	+++++++++++++++++++++++++++++++++++++++++++++++
Distance (2) 1 1 0 x 0 x 0 = 9 cmp 11:
Goto 2:
	<<<<<<<<<
Set 2 = 0:
	[-Clear]
	
Goto 3:
	>
Set 3 = 0:
	[-Clear]
	
Goto 4:
	>
Set 4 = 0:
	[-Clear]
	
Goto 5:
	>
Set 5 = 0:
	[-Clear]
	
Goto 6:
	>
Set 6 = 0:
	[-Clear]
	
Goto 7:
	>
Set 7 = 0:
	[-Clear]
	
Goto 2:
	<<<<<
Set 2 = 1:
	[-Clear]
	+
Goto 3:
	>
Set 3 = 1:
	[-Clear]
	+
Move 5 = Cell 9:
	Goto 5:
		>>
	[-Clear]
	Goto 9:
		>>>>
	[
	Goto 9:
		
	-
	Goto 5:
		<<<<
	+
	Goto 9:
		>>>>
	]
Move 7 = Cell 11:
	Goto 7:
		<<
	[-Clear]
	Goto 11:
		>>>>
	[
	Goto 11:
		
	-
	Goto 7:
		<<<<
	+
	Goto 11:
		>>>>
	]
Goto 5:
	<<<<<<
[->>[-[<]]<]<<<[>]Goto 5:
	>
Loop 5:
[
	Copy 12 = Cell 0:
		Goto 12:
			>>>>>>>
		[-Clear]
		Goto 0:
			<<<<<<<<<<<<
		[
		-
		Goto 13:
			>>>>>>>>>>>>>
		+
		Goto 0:
			<<<<<<<<<<<<<
		]
		Goto 13:
			>>>>>>>>>>>>>
		[
		-
		Goto 0:
			<<<<<<<<<<<<<
		+
		Goto 12:
			>>>>>>>>>>>>
		+
		Goto 13:
			>
		]
	Goto 12:
		<
	Output (12) .
	Copy 16 = Cell 0:
		Goto 16:
			>>>>
		[-Clear]
		Goto 0:
			<<<<<<<<<<<<<<<<
		[
		-
		Goto 17:
			>>>>>>>>>>>>>>>>>
		+
		Goto 0:
			<<<<<<<<<<<<<<<<<
		]
		Goto 17:
			>>>>>>>>>>>>>>>>>
		[
		-
		Goto 0:
			<<<<<<<<<<<<<<<<<
		+
		Goto 16:
			>>>>>>>>>>>>>>>>
		+
		Goto 17:
			>
		]
	Move 14 = Cell 16:
		Goto 14:
			<<<
		[-Clear]
		Goto 16:
			>>
		[
		Goto 16:
			
		-
		Goto 14:
			<<
		+
		Goto 16:
			>>
		]
	Goto 18:
		>>
	Set 18 = 1:
		[-Clear]
		+
	Move 15 = Cell 18:
		Goto 15:
			<<<
		[-Clear]
		Goto 18:
			>>>
		[
		Goto 18:
			
		-
		Goto 15:
			<<<
		+
		Goto 18:
			>>>
		]
	Goto 15:
		<<<
	Sub 14 = 14 minus 15:
		[-
			Goto 14:
				<
			-
			Goto 15:
				>
		]
	Move 0 = Cell 14:
		Goto 0:
			<<<<<<<<<<<<<<<
		[-Clear]
		Goto 14:
			>>>>>>>>>>>>>>
		[
		Goto 14:
			
		-
		Goto 0:
			<<<<<<<<<<<<<<
		+
		Goto 14:
			>>>>>>>>>>>>>>
		]
	Copy 26 = Cell 0:
		Goto 26:
			>>>>>>>>>>>>
		[-Clear]
		Goto 0:
			<<<<<<<<<<<<<<<<<<<<<<<<<<
		[
		-
		Goto 27:
			>>>>>>>>>>>>>>>>>>>>>>>>>>>
		+
		Goto 0:
			<<<<<<<<<<<<<<<<<<<<<<<<<<<
		]
		Goto 27:
			>>>>>>>>>>>>>>>>>>>>>>>>>>>
		[
		-
		Goto 0:
			<<<<<<<<<<<<<<<<<<<<<<<<<<<
		+
		Goto 26:
			>>>>>>>>>>>>>>>>>>>>>>>>>>
		+
		Goto 27:
			>
		]
	Goto 28:
		>
	Set 28 = 47:
		[-Clear]
		+++++++++++++++++++++++++++++++++++++++++++++++
	Distance (19) 1 1 0 x 0 x 0 = 26 cmp 28:
	Goto 19:
		<<<<<<<<<
	Set 19 = 0:
		[-Clear]
		
	Goto 20:
		>
	Set 20 = 0:
		[-Clear]
		
	Goto 21:
		>
	Set 21 = 0:
		[-Clear]
		
	Goto 22:
		>
	Set 22 = 0:
		[-Clear]
		
	Goto 23:
		>
	Set 23 = 0:
		[-Clear]
		
	Goto 24:
		>
	Set 24 = 0:
		[-Clear]
		
	Goto 19:
		<<<<<
	Set 19 = 1:
		[-Clear]
		+
	Goto 20:
		>
	Set 20 = 1:
		[-Clear]
		+
	Move 22 = Cell 26:
		Goto 22:
			>>
		[-Clear]
		Goto 26:
			>>>>
		[
		Goto 26:
			
		-
		Goto 22:
			<<<<
		+
		Goto 26:
			>>>>
		]
	Move 24 = Cell 28:
		Goto 24:
			<<
		[-Clear]
		Goto 28:
			>>>>
		[
		Goto 28:
			
		-
		Goto 24:
			<<<<
		+
		Goto 28:
			>>>>
		]
	Goto 22:
		<<<<<<
	[->>[-[<]]<]<<<[>]	Move 5 = Cell 22:
		Goto 5:
			<<<<<<<<<<<<<<<<
		[-Clear]
		Goto 22:
			>>>>>>>>>>>>>>>>>
		[
		Goto 22:
			
		-
		Goto 5:
			<<<<<<<<<<<<<<<<<
		+
		Goto 22:
			>>>>>>>>>>>>>>>>>
		]
	Goto 5:
		<<<<<<<<<<<<<<<<<
]

