fn fiv(n : i32) -> i32 {
    if n == 1 {
        return 1;
    }
    if n == 2 {
        return 1;
    }
    return fiv(n-2) + fiv(n-1);
}

fn main() {
    let n: i32 = 10;
    println!("fiv {} = {}", n, fiv(n));
}
