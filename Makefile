all:
	gcc aesenc.c -O1 -maes -o aesenc
	gcc aesdec.c -O1 -maes -o aesdec
	gcc gen_round_keys.c -O1 -maes -o gen_round_keys
