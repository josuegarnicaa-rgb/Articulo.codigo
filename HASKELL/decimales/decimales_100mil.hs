import System.IO (readFile)
import Control.Exception (evaluate)
import Control.DeepSeq (rnf)

-- Algoritmo Quicksort
quicksort :: Ord a => [a] -> [a]
quicksort [] = []
quicksort (p:xs) = quicksort menores ++ [p] ++ quicksort mayores
  where
    menores = filter (< p) xs
    mayores = filter (>= p) xs

main :: IO ()
main = do
  -- 1. Leemos todo el contenido del archivo txt
  contenido <- readFile "decimales_100mil.txt"
  
  -- 2. Convertimos el texto en una lista de enteros
  -- 'words' separa el texto por espacios o saltos de línea
  -- 'map read' convierte cada fragmento de texto en un número Float
  let listaNumeros = map read (words contenido) :: [Float]
  
  putStrLn "Iniciando ordenamiento..."
  
  -- 3. Forzamos la evaluación del algoritmo para medir el tiempo real
  listaOrdenada <- evaluate (quicksort listaNumeros)
  --'rnf' (reduce to normal form) para asegurarnos que Haskell realmente ordene todo en este preciso momento.
  evaluate (rnf listaOrdenada)
  
  putStrLn "Ordenamiento completado."