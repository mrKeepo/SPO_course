: concat
	dup count
	rot
	dup count
	rot
	swap
	dup rot
	+ heap-alloc
	rot dup
	rot dup
	rot string-copy
	swap 
	heap-free
	dup rot
	+ rot
	dup rot
	swap
	string-copy
	heap-free ;