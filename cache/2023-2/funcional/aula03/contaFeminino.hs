type Meu_tipo = (String, Float, Char)

pessoa :: Float -> Meu_tipo
pessoa rg
	| rg == 1 = ("Joao Silva",12,'m')
	| rg == 2 = ("Jonas Souza",81,'m')
	| rg == 3 = ("Joice Silva",12,'f')
	| rg == 4 = ("Janete Souza",10,'f')
	| rg == 5 = ("Jocileide Strauss",21,'f')
	| otherwise = ("Nao ha mais ninguem",0,'x')

ehFeminino :: Meu_tipo -> Int
ehFeminino (_,_,s)
	| (s == 'f') = 1
	| otherwise  = 0

contaFeminino :: Float -> Int
contaFeminino rg
	| (rg == 1) = ehFeminino (pessoa 1)
	| otherwise = ehFeminino (pessoa rg) + contaFeminino (rg - 1)