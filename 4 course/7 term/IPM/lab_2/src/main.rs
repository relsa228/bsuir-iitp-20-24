mod encrypt_module;
mod utils_module;

use encrypt_module::stb_encrypt_module;
use encrypt_module::cipher_consts;

use utils_module::utils;

use std::env;
use std::fs;
use std::io::Write;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        print!("Error: Not enough args")
    } else {
        let encr_mode = args.contains(&"-e".to_string());
        let decr_mode = args.contains(&"-d".to_string());
        let from_file = args.contains(&"-f".to_string());

        let mut t = args[1].clone();
        let mut filepath = "".to_string();

        if from_file {
            filepath = t.clone();
            t = fs::read_to_string(filepath.clone())
                .expect("Something went wrong reading the file");
        }

        if encr_mode {
            let raw_text = utils::parse_plain_text_to_vec(t.clone());
            let encryption: Vec<Vec<u32>> = stb_encrypt_module::encrypt(raw_text.clone(), 
                cipher_consts::KEY.to_vec(), 
                    cipher_consts::INITIALIZATION_VECTOR.to_vec());
            let result_encryption = utils::pretify_str_for_vec(encryption.clone());

            if !from_file {
                println!(
                    "Encoded text (pretty hex): {}\n--------------",
                    encryption.iter().cloned().fold("".to_string(), |a, x| a
                        + &x.into_iter()
                                .fold("".to_string(), |b, y| b + &format!("{:02X} ", y))[..23]));
                print!("Encoded text: {}\n", result_encryption);
            }
            else {
                let mut file = fs::File::create(filepath.clone()).expect("Something went wrong opening the file");
                file.write_all(result_encryption.as_bytes()).expect("Something went wrong writing the file");
            }
            print!("Initialization vector: {}\n", cipher_consts::INITIALIZATION_VECTOR.iter().map(|x| x.to_string()).collect::<Vec<String>>().join(" ").as_str())
        }

        if decr_mode {
            let input_vect = utils::parse_str_to_wrk_vec(&t);
            let decryption: Vec<Vec<u32>> = stb_encrypt_module::encrypt(input_vect.clone(), 
                cipher_consts::KEY.to_vec(), 
                    cipher_consts::INITIALIZATION_VECTOR.to_vec());
                    
            if !from_file {
                println!(
                    "Decoded text: {}",
                    decryption.iter().cloned().fold("".to_string(), |a, x| a
                        + &x.into_iter()
                                .fold("".to_string(), |b, y| b + &format!("{:02X} ", y))[..23]));
                println!("Recovered text: {}\n", utils::convert_to_string(decryption));
            }
            else {
                let mut file = fs::File::create(filepath.clone()).expect("Something went wrong opening the file");
                file.write_all(utils::convert_to_string(decryption).as_bytes()).expect("Something went wrong writing the file");
            }
        }
    }
}