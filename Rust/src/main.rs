#![allow(non_snake_case)]

fn main() {
    let (mut a, mut b, mut c) = (1, 1, 0);

    println!("{}\n{}", a, b);

    for _ in 0..30 {
        c = a + b;
        println!("{}", c);
        a = b;
        b = c;
    }
}
