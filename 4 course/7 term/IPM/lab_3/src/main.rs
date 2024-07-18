use lab_3::rabin;

use num::BigInt;
use num::bigint::Sign;

use std::env;
use std::fs;
use std::io::{Write, BufReader, BufRead};

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 4 {
        print!("Error: Not enough args");
        return;
    }
    
    let encr_mode = args.contains(&"-e".to_string());
    let decr_mode = args.contains(&"-d".to_string());

    let filepath = args[1].clone();
    let key_file = args[3].clone();
    let text = fs::read_to_string(filepath.clone()).expect("Something went wrong reading the file");

    if encr_mode {
        let n: BigInt;
        let byte_arr = text.as_bytes();
        let big_int = BigInt::from_bytes_be(Sign::Plus, byte_arr);

        if is_file_empty(&key_file) {
            let keys = rabin::key_gen(big_int.clone()); 
            let mut key_file = fs::File::create(key_file.clone()).expect("Something went wrong opening the key file");
            writeln!(key_file, "{}", keys.0).unwrap();
            writeln!(key_file, "{}", keys.1).unwrap();
            writeln!(key_file, "{}", keys.2).unwrap();

            n = keys.0;
        }
        else {
            let file = fs::File::open(key_file.clone()).expect("Something went wrong opening the key file");
            let reader = BufReader::new(file);
            let mut lines = reader.lines();
            n = lines.next().unwrap().unwrap().parse::<BigInt>().unwrap();
        }

        let encryption = rabin::encrypt(big_int.clone(), n.clone());
        let encryption_prettify = encryption.to_bytes_be().1.iter().map(|b| b.to_string()).collect::<Vec<String>>().join(" ");

        let mut encr_file = fs::File::create(filepath.clone()).expect("Something went wrong opening the file");
        encr_file.write_all(&encryption_prettify.as_bytes()).expect("Something went wrong writing the file");
        
        println!("Encryption is ready. Your public key: {}", n);
        
        drop(encr_file);
        drop(key_file);
    }
    else if decr_mode {
        if is_file_empty(&key_file) {
            print!("Error: key-file is empty!");
            return;
        }

        let keys: (BigInt, BigInt, BigInt);
        let byte_arr: Vec<u8> = text.split(' ').map(|b| b.parse().unwrap()).collect();
        let encryption = BigInt::from_bytes_be(Sign::Plus, &byte_arr);

        let file = fs::File::open(key_file.clone()).expect("Something went wrong opening the key file");
        let reader = BufReader::new(file);
        let mut lines = reader.lines();
        let n = lines.next().unwrap().unwrap().parse::<BigInt>().unwrap();
        let q = lines.next().unwrap().unwrap().parse::<BigInt>().unwrap();
        let p = lines.next().unwrap().unwrap().parse::<BigInt>().unwrap();

        keys = (n, q, p);

        let decryption = rabin::decrypt(encryption, keys.1, keys.2, keys.0);

        for i in decryption {
            let byte_set = i.to_bytes_be().1;
            let result = match std::str::from_utf8(&byte_set) {
                Ok(v) => v,
                Err(_e) => "error",
            };
    
            if result != "error" {
                let mut file = fs::File::create(filepath.clone()).expect("Something went wrong opening the file");
                file.write_all(result.as_bytes()).expect("Something went wrong writing the file");
            }
        }
    };
}

fn is_file_empty(filepath: &str) -> bool {
    let file = fs::File::open(filepath).unwrap();
    let mut reader = BufReader::new(file);
    let mut line = String::new();
    reader.read_line(&mut line).unwrap();
    
    return line.is_empty()
}