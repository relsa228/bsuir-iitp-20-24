#[path = "modules/gost_28147_module.rs"] mod gost_28147_module;
#[path = "modules/message_authentication_code_module.rs"] mod message_authentication_code_module;

use gost_28147_module::gost_28147;
use message_authentication_code_module::message_authentication_code;
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
            print_message_authentication_code(t.clone());

            t += &" ".repeat((8 - t.len() % 8) % 8);
            let text_bytes = t.bytes().collect::<Vec<_>>();
            let plain_text = text_bytes.chunks(8).collect::<Vec<_>>();
            let encoded_text = plain_text
                .iter()
                .map(|c| gost_28147::encode(c.to_vec()))
                .collect::<Vec<_>>();
            let mut result_encryption = "".to_string();
            
            for i in 0..encoded_text.len() {
                result_encryption.push_str(encoded_text[i].iter().map(|x| x.to_string()).collect::<Vec<String>>().join(" ").as_str());
                result_encryption.push_str(" ");
            }

            if !from_file {
                println!(
                    "Encoded text (pretty): {}",
                    encoded_text.iter().cloned().fold("".to_string(), |a, x| a
                        + "["
                        + &x.into_iter()
                                .fold("".to_string(), |b, y| b + &format!("{:02X} ", y))[..23]
                        + "]")
                );
                print!("Encoded text: {}\n", result_encryption)
            }
            else {
                let mut file = fs::File::create(filepath.clone()).expect("Something went wrong opening the file");
                file.write_all(result_encryption.as_bytes()).expect("Something went wrong writing the file");
            }
        }

        if decr_mode {
            let mut input_vect = t.split_whitespace().map(|x| x.parse::<u8>().unwrap()).collect::<Vec<u8>>();
            
            let mut new_vec = Vec::new();
            while !input_vect.is_empty() {
                let mut sub_vec = Vec::new();
                for _ in 0..8 {
                    if let Some(val) = input_vect.pop() {
                        sub_vec.push(val);
                    } else {
                        sub_vec.push(0);
                    }
                }
                sub_vec.reverse();
                new_vec.push(sub_vec);
            }
            new_vec.reverse();

            let decoded_text = new_vec
                                                .iter()
                                                    .map(|c| gost_28147::decode(c.to_vec()))
                                                        .collect::<Vec<_>>();
            let recovered_text = String::from_utf8(decoded_text.iter().cloned().flatten().collect::<Vec<_>>()).unwrap();

            print_message_authentication_code(recovered_text.clone());

            if !from_file {
                println!(
                    "Decoded text: {}\n",
                    decoded_text.iter().cloned().fold("".to_string(), |a, x| a
                        + "["
                        + &x.into_iter()
                                .fold("".to_string(), |b, y| b + &format!("{:02X} ", y))[..23]
                        + "]")
                );
    
                println!("Recovered text: {}\n", recovered_text);
            }
            else {
                let mut file = fs::File::create(filepath.clone()).expect("Something went wrong opening the file");
                file.write_all(recovered_text.as_bytes()).expect("Something went wrong writing the file");
            }
        }
    }
}

fn print_message_authentication_code(text: String) {
    let mut check = text.clone();

    check += &" ".repeat((8 - check.len() % 8) % 8);
    let text_bytes = check.bytes().collect::<Vec<_>>();
    let plain_text = text_bytes.chunks(8).collect::<Vec<_>>();

    let mac = message_authentication_code::get_message_authentication_code(plain_text.clone());
    println!( "Message authentication code (pretty): [ {}]", mac.iter().cloned().fold("".to_string(), |a, x| a + &format!("{:02X} ", x)));

    let result_message_authentication_code = mac.iter().map(|x| x.to_string()).collect::<Vec<String>>().join(" ");
    print!("Message authentication code: {}\n\n", result_message_authentication_code);
}