# MEMO

## 変数について
再代入はmutableにすればできる
 ```
let x = 5;
println!("The value of x is: {}", x);
x = 6; // Since assign x to CONST, error occurs.
println!("The value of x is: {}", x);

let mut x = 5;
println!("The value of x is: {}", x);
x = 6;
println!("The value of x is: {}", x);
    
```

定数の宣言のしかた
```
// 型を宣言する
// 大文字で_で区切りをつける
const MAX_POINTS: u32 = 100_000;
println!("MAX_POINTS is: {}", MAX_POINTS);
```

シャドーイング
```
// constだけど再宣言すれば代入できる
let x = 5;
let x = x + 1;
let x = x * 2;
println!("The value of x is: {}", x);
```

```
let spaces = "   ";
spaces = spaces.len();
```

## データ型
```
let guess: u32 = "42".parse().expect("Not a number");
println!("num: {}", guess);
let x = 2.0; // f64

let y: f32 = 3.0; // f32

// 足し算
let sum = 5 + 10;

// 引き算
let difference = 95.5 - 4.3;

// 掛け算
let product = 4 * 30;

// 割り算
let quotient = 56.7 / 32.2;

// 余り
let remainder = 43 % 5;

let t = true;

let f: bool = false; // 明示的型注釈付きで

let c = 'z';
let z = 'ℤ';
let heart_eyed_cat = '😻';    //ハート目の猫
println!("{}",heart_eyed_cat);

// タプル型
let tup: (i32, f64, u8) = (500, 6.4, 1);
// パターンマッチングで取り出せる
let (x, y, z) = tup;
println!("The value of y is: {}", y);

// 配列
let a = [1, 2, 3, 4, 5];
println!("The value of element is: {}", a[0]);
```

## 関数
```
fn main() {
    println!("hello world");
    foo_function();
    let y = add(1, 2);
}

// 関数はスネークケースで宣言する
fn foo_function(){
    println!("foo");
}

fn add(x: i32, y: i32) -> i32 {
    println!("{} + {} = {}", x, y, x+y);
    return x+y;
}
```
### StatementsとExpressions
```
fn five() -> i32 {
    5   // これで戻り値になる
}

fn main() {
    let x = five();

    println!("The value of x is: {}", x);
}
```
StatementsとExpressionsの違いは`;`をつけるかどうかで決まる。
```
fn main() {
    let x = plus_one(5);

    println!("The value of x is: {}", x);
}

fn plus_one(x: i32) -> i32 {
    x + 1
    // x + 1; //エラーが出る
}
```

## フロー制御
### if
カッコいらない。
```
if number < 5 {
    println!("condition was true");       // 条件は真でした
} else {
    println!("condition was false");      // 条件は偽でした
}
```
独特な書き方。三項演算子っぽい。
```
let condition = false;
// 三項演算子みたいなやつだこれ
// 返り値の型が合わないとエラーでる
let number = if condition {5} else {6};

// numberの値は、{}です
println!("The value of number is: {}", number);
```

### ループ
- 無限ループ
```
loop {
        println!("again!");   // また
}
```
- whileでループする
```
let a = [10, 20, 30, 40, 50];
let mut index = 0;

while index < 5 {
    println!("the value is: {}", a[index]);
    index = index + 1;
}
```
- 拡張for的な書き方もできる
```
let a = [10, 20, 30, 40, 50];

for element in a.iter() {
    println!("the value is: {}", element);
};
```
- `for number in (1..4).rev() {`として、1-3の配列のreverseができる。便利。