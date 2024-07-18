use num::BigInt;
use std::cmp::Ordering;

pub fn extended_euclidean(a: BigInt, b: BigInt) -> (BigInt, BigInt, BigInt) {
    let mut u_2: BigInt = BigInt::from(1 as u8);
    let mut v_2: BigInt = BigInt::from(0 as u8);
    
    let mut u_1: BigInt = BigInt::from(0 as u8);
    let mut v_1: BigInt = BigInt::from(1 as u8);
    
    let mut x_2: BigInt = a;
    let mut x_1: BigInt = b;
    let mut x = x_2.clone() % x_1.clone();
    
    while x.cmp(&BigInt::from(0 as u8)) == Ordering::Greater {
        let q = x_2.clone() / x_1.clone();
        let u_0 = u_2 - q.clone() * u_1.clone();
        let v_0 = v_2 - q.clone() * v_1.clone();

        u_2 = u_1;
        u_1 = u_0;
    
        v_2 = v_1;
        v_1 = v_0;
    
        x_2 = x_1;
        x_1 = x;
    
        x = x_2.clone() % x_1.clone();
    }
    
    return (u_1, v_1, x_1);
}

pub fn inverse_mod_n(a: BigInt, n:BigInt) -> BigInt {
    let (_, v, _) = extended_euclidean(n.clone(), a);
    return ((v % n.clone()) + n.clone() ) % n;
}
