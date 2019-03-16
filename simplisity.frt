: is_simple
	dup 0 < if drop -1 else
		dup 2 < if drop 0 else
			1 >r 
				repeat  
					dup
					r> 1 + dup >r
					% 0 =
				until 
			r> = 
		then
	then ;	
	