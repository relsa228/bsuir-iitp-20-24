use std::env;
use lab_8::FftStego;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args[2] == "-e" {
        FftStego::encrypt(&args[1], &args[3])
    }
    else if args[2] == "-d" {
        let out: String = FftStego::decrypt(&args[1]);
        println!("{}", out);
    }
}
