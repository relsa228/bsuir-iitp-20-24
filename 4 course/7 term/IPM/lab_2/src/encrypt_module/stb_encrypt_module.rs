use crate::encrypt_module::cipher_consts;

use std::mem;

pub fn encrypt(plain_text: Vec<Vec<u32>>, key: Vec<u32>, initialization_vector: Vec<u32>) -> Vec<Vec<u32>> {
    let keys = generate_keys(key.clone());
    let mut s: Vec<u32> = encrypt_block(initialization_vector, keys.clone());
    let mut encryption: Vec<Vec<u32>> = Vec::new();

    for mut i in plain_text {
        s[0] = sqr_add(s[0], (1 % usize::pow(2, 32)) as u32);
        s[1] = sqr_add(s[1], (1 % usize::pow(2, 32)) as u32);
        s[2] = sqr_add(s[2], (1 % usize::pow(2, 32)) as u32);
        s[3] = sqr_add(s[3], (1 % usize::pow(2, 32)) as u32);
        let sf = encrypt_block(s.clone(), keys.clone());

        for j in 0..4 {
            i[j] ^= sf[j];
        }

        encryption.push(i);
    }

    encryption
}

pub fn encrypt_block(block: Vec<u32>, keys: Vec<u32>) -> Vec<u32> {
    let mut a = block[0] as u32;
    let mut b = block[1] as u32;
    let mut c = block[2] as u32;
    let mut d = block[3] as u32;

    for i in 1..9 {
        b ^= g(5, sqr_add(a, keys[7*i - 7]));
        c ^= g(21, sqr_add(d, keys[7*i - 6]));
        a = sqr_sub(a, g(13, sqr_add(b, keys[7*i - 5])));
        let e = g(21, sqr_add(sqr_add(b, c), keys[7*i - 4])) ^ (i % usize::pow(2, 32)) as u32;
        b = sqr_add(b, e);
        c = sqr_sub(c, e);
        d = sqr_add(d, g(13, sqr_add(c, keys[7*i - 3])));
        b ^= g(21, sqr_add(a, keys[7*i - 2]));
        c ^= g(5, sqr_add(d, keys[7*i - 1]));
        mem::swap(&mut a, &mut b);
        mem::swap(&mut c, &mut d);
        mem::swap(&mut b, &mut c);
    }

    let mut output = Vec::new();
    output.push(b);
    output.push(d);
    output.push(a);
    output.push(c);
    output
}

fn generate_keys(key: Vec<u32>)-> Vec<u32> {
    let mut keys: Vec<u32> = Vec::new();
    for i in 0..56 {
        keys.push(key[i%8]);
    }
    keys
}

fn g(r: u32, x: u32) -> u32 {
    let u4 = (x & 0xff) as u8;
    let u3 = ((x >> 8) & 0xff) as u8;
    let u2 = ((x >> 16) & 0xff) as u8;
    let u1 = ((x >> 24) & 0xff) as u8;

    let mut number: u32 = ((cipher_consts::SBOX[u1 as usize] as u32) << 24) | 
                            ((cipher_consts::SBOX[u2 as usize] as u32) << 16) | 
                                ((cipher_consts::SBOX[u3 as usize] as u32) << 8) | 
                                    (cipher_consts::SBOX[u4 as usize] as u32);

    for _ in 0..r {
        number = rot_hi(number);
    }

    return number;
}

fn rot_hi(u: u32) -> u32 { 
    return (u << 1) ^ (u >> 31);
}

fn sqr_add(a: u32, b: u32) -> u32 {
    let sum: u64 = (a as u64 + b as u64).into();
    return (sum & 0xFFFF_FFFF).try_into().unwrap();
}

fn sqr_sub(a: u32, b: u32) -> u32 {
    let sub: i64 = (a as i64 - b as i64).into();
    return (sub & 0xFFFF_FFFF).try_into().unwrap();
}