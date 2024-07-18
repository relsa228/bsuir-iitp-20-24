use std::slice;

use crate::gost::const_data;
use crate::gost::precomp_data;

pub fn xor512(l: [u8; 64], r: [u8; 64]) -> [u8; 64] {
    let mut result = [0 as u8; 64];
    for i in 0..64 {
        result[i] = l[i] ^ r[i];
    }
    result
}

pub fn add_modulo512(l: [u8; 64], r: [u8; 64]) -> [u8; 64] {
    let mut result = [0 as u8; 64];
    let mut t = 0;
    for i in 0..64 {
        t = l[i] as i32 + r[i] as i32 + (t >> 8);
        result[i] = t as u8;
    }
    result
}

pub fn s(a: [u8; 64]) -> [u8; 64] {
    let mut result = [0 as u8; 64];
    for i in 0..64 {
        result[i] = const_data::PI[a[i] as usize];
    }
    result
}

pub fn p(a: [u8; 64]) -> [u8; 64] {
    let mut result = [0 as u8; 64];
    for i in 0..64 {
        result[i] = a[const_data::TAU[i] as usize];
    }
    result
}

pub fn l(a: [u8; 64]) -> [u8; 64] {
    let ptr = &a[0] as *const u8 as *mut u64;
    let a_u64 = unsafe { slice::from_raw_parts_mut::<u64>(ptr, 8) };
    let i_constants: [usize; 8] = [7, 15, 23, 31, 39, 47, 55, 63];
    for (i, a_element) in (0..8).zip(a_u64.iter_mut()) {
        let mut temp = 0 as u64;
        for j in 0..8 {
            temp ^= precomp_data::A_PRECOMP[j][a[i_constants[i] - j] as usize];
        }
        *a_element = temp;
    }
    a
}

pub fn key_schedule(k: [u8; 64], i: usize) -> [u8; 64] {
    // Temporary workaround, cuz in C all arrays reversed
    fn _xor512(l: [u8; 64], r: [u8; 64]) -> [u8; 64] {
        let mut result = [0 as u8; 64];
        for i in 0..64 {
            result[i] = l[i] ^ r[63 - i];
        }
        result
    }
    l(p(s(_xor512(k, const_data::C[i]))))
}

pub fn e(k_init: [u8; 64], m: [u8; 64]) -> [u8; 64] {
    let mut k = k_init;
    let mut temp = xor512(k, m);
    for i in 0..12 {
        temp = l(p(s(temp)));
        k = key_schedule(k, i);
        temp = xor512(temp, k);
    }
    temp
}

pub fn g_n(n: [u8; 64], h: [u8; 64], m: [u8; 64]) -> [u8; 64] {
    xor512(xor512(e(l(p(s(xor512(h, n)))), m), h), m)
}