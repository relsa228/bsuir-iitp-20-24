use std::env;
use std::fs;

use lab_5::md5;
use lab_5::gost::gost3411::StreebogHasher512;

fn main() {
    let args: Vec<String> = env::args().collect();
    let contents = fs::read_to_string(args[1].clone()).unwrap();

    if args[2] == "--md5" {
        println!("{:x}", md5::compute(contents));
    }
    else if args[2] == "--streebog" {
        let mut streebog_hasher = StreebogHasher512::new();
        println!("{}", streebog_hasher.hash(contents));
    }
}
