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

{-
--contaMestresMasculino

ehMestre :: Professor -> Bool
ehMestre (_,_,t,_) = (t == "MESTRE")

ehMasculino :: Professor -> Bool
ehMasculino (_,_,_,s) = (s == 'M')

ehMestreMasculino :: Professor -> Bool
ehMestreMasculino (_,_,t,s) = ehMestre (base professor) && ehMasculino (base professor)

contaMestresMasculino :: Professor -> Int
contaMestresMasculino professor
	| (professor == 0) = ehMestreMasculino (base 0)
	|        otherwise = ehMestreMasculino (base professor) + contaMestresMasculino (professor - 1)
-}

{-
--professorMaisAntigo
menor :: Int -> Int
menor x y
	| x <= y	= x
	| otherwise	= y

menorMatricula :: Int -> Professor
menorMatricula professor
   | professor == 0	= professor 1
   |      otherwise = menorMatricula (base professor) (menorMatricula (professor-1))

professorMaisAntigo
-}