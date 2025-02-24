use crate::sign::curve::Curve;
use crate::sign::point::make_positive;
use crate::gost::gost3411::StreebogHasher512;
use crate::sign::point::Point;
use lazy_static::lazy_static;
use num_bigint_dig::{BigInt, RandBigInt, Sign, ModInverse};
use num_traits::{One, Zero};
use std::str::FromStr;

pub struct Signature {
    pub sign: BigInt,
    pub r: BigInt,
    pub s: BigInt,
}

lazy_static! {
    static ref P: Point = Point::new(
        BigInt::from_str("2").unwrap(),
        BigInt::from_str(
            "4018974056539037503335449422937059775635739389905545080690979365213431566280",
        )
        .unwrap(),
    );
    static ref Q: Point = Point::new(
        BigInt::from_str(
            "57520216126176808443631405023338071176630104906313632182896741342206604859403",
        )
        .unwrap(),
        BigInt::from_str(
            "17614944419213781543809391949654080031942662045363639260709847859438286763994",
        )
        .unwrap(),
    );
}

impl Signature {
    pub fn sign(message: String, key: BigInt, curve: Curve) -> Self {
        let mut streebog_hasher = StreebogHasher512::new();
        let hash = streebog_hasher.hash(message);
        let hash = BigInt::from_bytes_le(Sign::Plus, &hash);
        let mut e = hash % &curve.q;
        if e == BigInt::zero() {
            e = BigInt::one();
        }

        let (r, s) = loop {
            let k = Self::rand_k(&curve.q);
            let big_c = P.clone().multiply(k.clone(), &curve.p, &curve.a);
            let r = big_c.x % &curve.q;
            if r == BigInt::zero() {
                continue;
            }
            let s = (&r * &key + &k * &e) % &curve.q;
            if s == BigInt::zero() {
                continue;
            }
            break (r, s);
        };

        let bytes = [r.to_bytes_le().1, s.to_bytes_le().1].concat();
        let sign = BigInt::from_bytes_le(Sign::Plus, &bytes);

        Self { sign, r, s }
    }

    pub fn verify(&mut self, message: String, curve: Curve) -> bool {
        let vec: Vec<u8> = self.sign.to_bytes_le().1;
        let half = vec.len() / 2;
        let (left, right) = vec.split_at(half);
    
        self.r = BigInt::from_bytes_le(Sign::Plus, left);
        self.s = BigInt::from_bytes_le(Sign::Plus, right);

        if !(self.r > BigInt::zero()
            && (self.r < curve.q)
            && self.s > BigInt::zero()
            && self.s < curve.q)
        {
            return false;
        }

        let mut streebog_hasher = StreebogHasher512::new();
        let hash = streebog_hasher.hash(message);

        let hash = BigInt::from_bytes_le(Sign::Plus, &hash);
        let mut e = hash % &curve.q;
        if e.is_zero() {
            e = BigInt::one();
        }

        let v = e.mod_inverse(&curve.q).unwrap();

        let z1 = (&self.s * &v) % &curve.q;
        let z2 = make_positive(-&self.r * &v % &curve.q, &curve.q);
        let big_c = P.clone().multiply(z1, &curve.p, &curve.a).add(
            &Q.clone().multiply(z2, &curve.p, &curve.a),
            &curve.p,
            &curve.a,
        );

        let big_r = big_c.x % &curve.q;

        big_r == self.r
    }

    fn rand_k(upper: &BigInt) -> BigInt {
        rand::thread_rng().gen_bigint_range(&BigInt::zero(), upper)
    }
}
