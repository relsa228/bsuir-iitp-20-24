use lab_7::{generate_random_scalar, PrivateKey, PublicKey, Cipher};
use std::env;
use std::fs;
use std::fs::File;
use std::io::prelude::*;


fn main() {
    let args: Vec<String> = env::args().collect();
    if args[1] == "-g" {
        let mut pk = PrivateKey::new(&mut rand::thread_rng());
        pk.serialize();

        let mut pub_key = PublicKey::derive(pk);
        pub_key.serialize();

        println!("Generation complete");
    }

    else if args[2] == "-e" {
        let plain_text_file = &args[1];

        let pub_key_file = &args[3];
        let pub_key = PublicKey::deserialize(pub_key_file.to_string());

        let y = generate_random_scalar(&mut rand::thread_rng());

        let contents = fs::read_to_string(plain_text_file).expect("Something went wrong reading the file");
        let mut cipher = pub_key.encrypt(&contents, y);
        cipher.serialize();

        let shared_secret = pub_key.get() * y;
        println!("Shared secret: {}", shared_secret)
    }

    else if args[2] == "-d" {
        let cipher_text_file = &args[1];

        let private_key_file = &args[3];
        let private_key = PrivateKey::deserialize(private_key_file.to_string());

        let cipher = Cipher::deserialize(cipher_text_file.to_string());
        let (plaintext, computed_secret) = cipher.decrypt(private_key);

        let mut file = File::create("output.txt").expect("Something went wrong creating the file");
        file.write_all(plaintext.as_bytes()).expect("Something went wrong writing the file");
        file.flush().expect("Something went wrong saving the file");

        println!("Computed secret: {}", computed_secret)
    }
}