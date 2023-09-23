--menor :: Float -> Float
--menor x y
--   | x <= y		= x
--   | otherwise	= y

{-
type Nome = String	-- Sinônimo para String [Nome]
type Idade = Int	-- Sinônimo para Int [Idade]
type CPF = Integer	-- Sinônimo para Integer [CPF]

cadastro :: CPF -> (Nome, Idade)
cadastro cpf
   | cpf == 11111111111		= ("Jose", 12)
   | cpf == 11111111111		= ("Joao", 77)
   | cpf == 22222222222		= ("Maria", 50)
   | otherwise			= ("Desconhecido", 0)
-}

type Meu_tipo = (String, Float, Char)

menor :: Float -> Float
menor x y
| x1 <= x2	= x
| otherwise	= y
   where
	x1 = idade x
	x2 = idade y

pessoa :: Float -> Meu_tipo
pessoa rg
	| rg == 1 = ("Joao Silva",12,'m')
	| rg == 2 = ("Jonas Souza",81,'m')
	| rg == 3 = ("Joice Silva",12,'f')
	| rg == 4 = ("Janete Souza",10,'f')
	| rg == 5 = ("Jocileide Strauss",21,'f')
	| otherwise = ("Nao há mais ninguem",0,'x')

idade :: Meu_tipo -> Float
idade (nome, idade, sexo) = i

sexo :: Meu_tipo -> Char
sexo (nome,idade,s) = s

ehFeminino :: Meu_tipo -> Bool
ehFeminino (n,i,s) = s == 'f'

contaFeminino :: Float -> Int
contaFeminino n
   | n == 1 && ehFeminino == True = --contaFeminino++


menorIdade :: Float -> Meu_tipo
menorIdade x
   | x == 1	= pessoa 1
   | otherwise	= menor (pessoa x) (menor idade (x-1))

somaIdade :: Float -> Float
somaIdade n
   | n == 1	= idade (pessoa n)
   | otherwise	= idade (pessoa n) + somaIdade (n-1)

mediaIdade :: Int -> Float 
mediaIdade quantidade = (somaIdade x)/quantidade


base :: Int -> (Int, String, String, Char)
base x
	|x == 0 = (1793, "Pedro Paulo", "MESTRE",'M')
	|x == 1 = (1797, "Joana S. Alencar", "MESTRE",'M')
	|x == 2 = (1534, "Joao de Medeiros", "DOUTOR",'F')
	|x == 3 = (1267, "Claudio Cesar de Sá", "DOUTOR",'M')
	|x == 4 = (1737, "Paula de Medeiros", "MESTRE",'F')
	|x == 5 = (1888, "Rita de Matos", "MESTRE",'F')
	|x == 6 = (1356, "Rodolfo Roberto", "DOUTOR", 'M')
	|x == 7 = (1586, "Célia Maria de Sousa", "DOUTOR", 'F')
	|x == 8 = (1800, "Josimar Justino", "MESTRE", 'M')
	|x == 9 = (1698, "Tereza C. Andrade", "MESTRE",'F')
	|x == 10 = ( 0, "" , "" ,'0')