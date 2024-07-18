use std::env;
use std::fs;

use lab_6::sign::curve::Curve;
use lab_6::sign::signature::Signature;
use num_bigint_dig::BigInt;
use std::str::FromStr;

fn main() {
    let args: Vec<String> = env::args().collect();
    let message = fs::read_to_string(args[1].clone()).unwrap();
    let mut sign_verify: BigInt = BigInt::from(0);
    let mut verify: bool = false;
    
    if args.len() == 4 && args[2] == "--verify" {
        sign_verify = BigInt::from_str(&args[3]).expect("Введенное значение не является подписью");
        verify = true;
    }

    let key = BigInt::from_str("55441196065363246126355624130324183196576709222340016572108097750006097525544").unwrap();
    let curve = Curve::new(
        BigInt::from_str("7").unwrap(),
        BigInt::from_str(
            "43308876546767276905765904595650931995942111794451039583252968842033849580414",
        )
        .unwrap(),
        BigInt::from_str(
            "57896044618658097711785492504343953926634992332820282019728792003956564821041",
        )
        .unwrap(),
        BigInt::from_str(
            "57896044618658097711785492504343953927082934583725450622380973592137631069619",
        )
        .unwrap(),
        BigInt::from_str(
            "57896044618658097711785492504343953927082934583725450622380973592137631069619",
        )
        .unwrap(),
    );

    let mut sign = Signature::sign(message.clone(), key, curve.clone());

    if !verify {
        println!("Подпись: {}", sign.sign);
    }

    if verify {
        sign.sign = sign_verify;
        println!("Верификация: {}", sign.verify(message, curve))
    }
}
