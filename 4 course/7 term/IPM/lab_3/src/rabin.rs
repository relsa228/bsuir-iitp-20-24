use num::BigInt;
use num::bigint::Sign;
use std::cmp::Ordering;
use num_primes::Generator;
use crate::euclidean;


pub fn encrypt(x: BigInt, n: BigInt) -> BigInt {
    let res = (x.pow(2)) % n;
    res
}

pub fn decrypt(m: BigInt, p: BigInt, q: BigInt, n: BigInt) -> Vec<BigInt> {
    let mut ans: Vec<BigInt> = Vec::new();

    let mq = m.modpow(&((q.clone() + BigInt::from(1))/BigInt::from(4)), &q.clone());
    let mp = m.modpow(&((p.clone() + BigInt::from(1))/BigInt::from(4)), &p.clone());

    let (yq, yp, _) = euclidean::extended_euclidean(q.clone(), p.clone());

    let mut r: BigInt = yp.clone() * p.clone() * mq.clone() + yq.clone() * q.clone() * mp.clone();
    r = r.modpow(&BigInt::from(1), &n);

    let mut s: BigInt = yp * p * mq - yq * q * mp;
    s = s.modpow(&BigInt::from(1), &n);

    ans.push(r.clone());
    ans.push(n.clone() - r);
    ans.push(s.clone());
    ans.push(n.clone() - s);

    ans    
}

pub fn key_gen(big_int: BigInt) -> (BigInt, BigInt, BigInt) {
    let mut q: BigInt;
    let mut p: BigInt;
    let n: BigInt;

    loop {
        let mut buff = Generator::new_prime(1024);
        q = BigInt::from_bytes_be(Sign::Plus,&buff.to_bytes_be());

        buff = Generator::new_prime(1024);
        p = BigInt::from_bytes_be(Sign::Plus,&buff.to_bytes_be());

        if (p.clone() * q.clone()).cmp(&big_int) == Ordering::Greater {
            if p.modpow(&BigInt::from(1 as u8), &BigInt::from(4 as u8)) == BigInt::from(3 as u8) && 
                q.modpow(&BigInt::from(1 as u8), &BigInt::from(4 as u8)) == BigInt::from(3 as u8) {
                break;
            }
        }
    }
 
    n = p.clone() * q.clone();

    return (n, p, q)
}