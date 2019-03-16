: copy_after
	swap dup rot swap ;
: radical
	1 1 >r
	repeat
		1 + 
		copy_after
		copy_after
		% not  
		if
			repeat 
				copy_after
				copy_after
				/ 
				-rot swap drop 
				copy_after
				copy_after
				% 	
			until 
			dup r> * >r
		then
		copy_after 1 =
	until	
	drop drop r> ;