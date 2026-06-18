use std::cmp::Ordering;

pub fn quicksort_by<T, F>(datos: &mut [T], comparar: F)
where
    T: Clone,
    F: Fn(&T, &T) -> Ordering + Copy,
{
    if datos.len() <= 1 {
        return;
    }

    let mut pila: Vec<(isize, isize)> = Vec::new();
    pila.push((0, datos.len() as isize - 1));

    while let Some((inicio, fin)) = pila.pop() {
        if inicio >= fin {
            continue;
        }

        let pivote_indice = inicio + (fin - inicio) / 2;
        let pivote = datos[pivote_indice as usize].clone();

        let mut menor = inicio;
        let mut actual = inicio;
        let mut mayor = fin;

        while actual <= mayor {
            match comparar(&datos[actual as usize], &pivote) {
                Ordering::Less => {
                    datos.swap(menor as usize, actual as usize);
                    menor += 1;
                    actual += 1;
                }
                Ordering::Greater => {
                    datos.swap(actual as usize, mayor as usize);
                    mayor -= 1;
                }
                Ordering::Equal => {
                    actual += 1;
                }
            }
        }

        if inicio < menor - 1 {
            pila.push((inicio, menor - 1));
        }

        if mayor + 1 < fin {
            pila.push((mayor + 1, fin));
        }
    }
}

pub fn esta_ordenado_by<T, F>(datos: &[T], comparar: F) -> bool
where
    F: Fn(&T, &T) -> Ordering,
{
    datos
        .windows(2)
        .all(|par| comparar(&par[0], &par[1]) != Ordering::Greater)
}