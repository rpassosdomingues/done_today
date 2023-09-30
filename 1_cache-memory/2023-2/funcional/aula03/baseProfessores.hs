type Professor = (Int, String, String, Char)
--(matricula, nome, titulacao, sexo) = (m, n, t, s)

base :: Int -> Professor
base professor
	| (professor == 0) = (1793, "Pedro Paulo", "MESTRE",'M')
	| (professor == 1) = (1797, "Joana S. Alencar", "MESTRE",'M')
	| (professor == 2) = (1534, "Joao de Medeiros", "DOUTOR",'F')
	| (professor == 3) = (1267, "Claudio Cesar de Sá", "DOUTOR",'M')
	| (professor == 4) = (1737, "Paula de Medeiros", "MESTRE",'F')
	| (professor == 5) = (1888, "Rita de Matos", "MESTRE",'F')
	| (professor == 6) = (1356, "Rodolfo Roberto", "DOUTOR", 'M')
	| (professor == 7) = (1586, "Célia Maria de Sousa", "DOUTOR", 'F')
	| (professor == 8) = (1800, "Josimar Justino", "MESTRE", 'M')
	| (professor == 9) = (1698, "Tereza C. Andrade", "MESTRE",'F')
	| (professor == 10)= ( 0, "" , "" ,'0')

--contaDoutores

ehDoutor :: Professor -> Int
ehDoutor (_,_,t,_)
	| (t == "DOUTOR") = 1
	|       otherwise = 0

contaDoutores :: Int -> Int
contaDoutores professor
	| (professor == 0) = ehDoutor (base 0)
	|        otherwise = ehDoutor (base professor) + contaDoutores (professor - 1)

--contaMulheres

ehMulher :: Professor -> Int
ehMulher (_,_,_,s)
	| (s == 'F') = 1
	| otherwise  = 0

contaMulheres :: Int -> Int
contaMulheres professor
	| (professor == 0) = ehMulher (base 0)
	|        otherwise = ehMulher (base professor) + contaMulheres (professor - 1)

--contaMestresMasculino

ehMestre :: Professor -> Int
ehMestre (_,_,t,_)
	| (t == "MESTRE") = 1
	|       otherwise = 0

ehMasculino :: Professor -> Int
ehMasculino (_,_,_,s)
	| (s == 'M') = 1
	| otherwise  = 0

contaMestresMasculino :: Int -> Int
contaMestresMasculino professor
	| (professor == 0) = ehMestre (base 0) * ehMasculino (base 0)
	|        otherwise = ehMestre (base professor) * ehMasculino (base professor) + contaMestresMasculino (professor - 1)

--professorMaisAntigo

menorMatricula :: Int -> Int -> Int
menorMatricula x y
	| x <= y    = x
	| otherwise = y

professorMaisAntigo :: Int -> Professor
professorMaisAntigo professor
	| (professor == 0) = base 0
	|        otherwise = let antigo = professorMaisAntigo (professor - 1)
                             atual = base professor
                         in if fst atual < fst antigo then atual else antigo
