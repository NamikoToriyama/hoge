use std::io; // std package
use std::cmp::Ordering;
use rand::{Rng};

fn main() {
    /*
    println!("Hello, world!");
    println!("Please input your guess.");

    let mut guess = String::new(); // stringの変数を用意
    // この書き方ができる
    // let foo = 5 // immutable
    // let mut bar = 5; // mutable

    // hoge
    // &は参照型 read_lineで標準入力をlineで受け取る
    // mut guessで可変にする必要がある
    // io::stdin().read_line(&mut guess) -> Result type {ok || err}
    io::stdin().read_line(&mut guess)
        .expect("Failed to read line"); // 行の読み込み と失敗例を書いている
    
    println!("You guessed: {}", guess);
    */
    println!("Guess the number!");
    let secret_number = rand::thread_rng().gen_range(1, 101);// rand::thread_rng 乱数生成機

    println!("The secret number is: {}", secret_number);

    loop{
        println!("Please input your guess.");
        let mut guess = String::new();
    
        io::stdin().read_line(&mut guess).expect("Failed to read line");
    
        // 文字列を数値にする
        // trimで改行コードを削除。parseで数値にしている
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("You guessed: {}", guess);
    
        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),       //小さすぎ！
            Ordering::Greater => println!("Too big!"),      //大きすぎ！
            Ordering::Equal => {println!("You win!");break},        //やったね！
        }
    }
}
