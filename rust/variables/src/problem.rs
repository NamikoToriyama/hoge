fn temperature() {
    let k_celsius: f32 = 30.0;
    // Celsius to Fahrenheit
    let k_Fahrenheit = k_celsius*1.8 + 32.0;
    println!("Celsius: {}, Fahrenheit: {}", k_celsius, k_Fahrenheit);
    
    let k_Fahrenheit: f32 = 100.0;
    let k_celsius: f32 = (k_Fahrenheit - 32.0)/1.8;
    println!("Celsius: {}, Fahrenheit: {}", k_celsius, k_Fahrenheit);
}

fn fiv(n : i32) -> i32 {
    if n == 1 {
        return 1;
    }
    if n == 2 {
        return 1;
    }
    return fiv(n-2) + fiv(n-1);
}

fn call_fibonacci() {
    let n: i32 = 10;
    println!("fiv {} = {}", n, fiv(n));
}
