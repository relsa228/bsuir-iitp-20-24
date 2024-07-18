use jubjub::{AffinePoint, Base, ExtendedPoint, Scalar, Fq, Fr};
use rand_core::RngCore;
use std::fs::File;
use std::io::prelude::*;
use std::str;
use std::io::BufReader;
use std::collections::HashMap;
use num::bigint::BigInt;
use num::Num;

const MAX_BYTES: usize = 32;

const FULL_GENERATOR: AffinePoint = AffinePoint::from_raw_unchecked(
    Base::from_raw([
        0xe4b3_d35d_f1a7_adfe,
        0xcaf5_5d1b_29bf_81af,
        0x8b0f_03dd_d60a_8187,
        0x62ed_cbb8_bf37_87c8,
    ]),
    Base::from_raw([0xb, 0x0, 0x0, 0x0]),
);

type Plaintext = String;
type BitString = [u8; MAX_BYTES];

pub fn generate_random_scalar<T: RngCore>(rng: &mut T) -> Scalar {
    let mut random_bytes = [0u8; 64];
    rng.fill_bytes(&mut random_bytes);
    return Scalar::from_bytes_wide(&random_bytes);
}

fn xor_bs(lhs: BitString, rhs: BitString) -> Vec<u8> {
    lhs.iter().zip(rhs).map(|(a, b)| a ^ b).collect()
}

#[derive(Default, Clone, Copy, Debug)]
pub struct PrivateKey(Scalar);

impl PrivateKey {
    pub fn new<T: RngCore>(rng: &mut T) -> Self {
        return PrivateKey(generate_random_scalar(rng));
    }

    pub fn serialize(&mut self) {
        let json_str = format!("{{\"0\": \"{}\"}}", self.0);
        let mut file = File::create("private_key.json").expect("Unable to create file");
        file.write(json_str.as_bytes()).expect("Unable to write data");
    }

    pub fn deserialize(filename: String) -> PrivateKey {
        let file = File::open(filename).expect("Unable to open file");
        let reader = BufReader::new(file);
        let data: HashMap<String, String> = serde_json::from_reader(reader).expect("Unable to read file");
        
        let mut i = PrivateKey::new(&mut rand::thread_rng());

        i.0 = PrivateKey::get_fq_from_str(data["0"].clone());

        return i;
    }

    fn get_fq_from_str(num: String) -> Fr {
        let num_n = num[2..].to_string();
        let big_int = BigInt::from_str_radix(&num_n, 16).unwrap();
        let byte_array = big_int.to_bytes_le().1;
        let array_u8: &[u8; 32] = byte_array.as_slice().try_into().unwrap();
        return Fr::from_bytes(array_u8).unwrap();
    }
}

#[derive(Default, Clone, Copy, Debug)]
pub struct PublicKey(ExtendedPoint);

impl PublicKey {
    pub fn new() -> Self {
        return PublicKey(FULL_GENERATOR.into());
    }

    pub fn derive(pk: PrivateKey) -> Self {
        return PublicKey(FULL_GENERATOR * pk.0);
    }

    pub fn get(self) -> ExtendedPoint {
        self.0
    }

    pub fn encrypt(self, message: &str, y: Scalar) -> Cipher {
        let mut m_b = [0u8; MAX_BYTES];
        m_b[..message.len()].clone_from_slice(&message.as_bytes());

        let shared_secret = self.0 * y;
        let gamma = FULL_GENERATOR * y;

        let (epsilon, phi) = Self::map_to_curve(&mut rand::thread_rng(), m_b);
        let delta = shared_secret + epsilon;

        return Cipher {
            delta,
            gamma,
            phi,
            padding: MAX_BYTES - message.len(),
        };
    }

    fn map_to_curve<T: RngCore>(rng: &mut T, message: BitString) -> (AffinePoint, BitString) {
        let mut encoded_point;
        let mut phi;

        loop {
            let r = generate_random_scalar(rng);
            phi = r.to_bytes();
            let x: Vec<u8> = xor_bs(phi, message);
            let guess: BitString = x.try_into().unwrap();       
            encoded_point = AffinePoint::from_bytes(guess);
            if encoded_point.is_some().unwrap_u8() == 1 {
                break;
            }
        }

        return (encoded_point.unwrap(), phi);
    }
    
    pub fn serialize(&mut self) {
        let json_str = format!("{{\"u\": \"{}\", \"v\": \"{}\", \"z\": \"{}\", \"t1\": \"{}\", \"t2\": \"{}\"}}", self.0.u, self.0.v, self.0.z, self.0.t1, self.0.t2);
        let mut file = File::create("public_key.json").expect("Unable to create file");
        file.write(json_str.as_bytes()).expect("Unable to write data");
    }

    pub fn deserialize(filename: String) -> PublicKey {
        let file = File::open(filename).expect("Unable to open file");
        let reader = BufReader::new(file);
        let data: HashMap<String, String> = serde_json::from_reader(reader).expect("Unable to read file");
        
        let mut i = PublicKey::new();

        i.0.u = PublicKey::get_fq_from_str(data["u"].clone());
        i.0.v = PublicKey::get_fq_from_str(data["v"].clone());
        i.0.z = PublicKey::get_fq_from_str(data["z"].clone());
        i.0.t1 = PublicKey::get_fq_from_str(data["t1"].clone());
        i.0.t2 = PublicKey::get_fq_from_str(data["t2"].clone());

        return i;
    }

    fn get_fq_from_str(num: String) -> Fq {
        let num_n = num[2..].to_string();
        let big_int = BigInt::from_str_radix(&num_n, 16).unwrap();
        let byte_array = big_int.to_bytes_le().1;
        let array_u8: &[u8; 32] = byte_array.as_slice().try_into().unwrap();
        return Fq::from_bytes(array_u8).unwrap();
    }
}

pub struct Cipher {
    pub phi: BitString,
    pub padding: usize,
    pub delta: ExtendedPoint,
    pub gamma: ExtendedPoint,
}

impl Cipher {
    pub fn new() -> Self {
        return Self {phi: [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0], padding:0, delta:FULL_GENERATOR.into(), gamma:FULL_GENERATOR.into() };
    }

    pub fn decrypt(&self, pk: PrivateKey) -> (Plaintext, ExtendedPoint) {
        let epsilon = self.delta - self.gamma * pk.0;
        
        let point = AffinePoint::from(epsilon).to_bytes();
        let shared_secret = self.delta - epsilon;
        let m_b: Vec<u8> = xor_bs(point, self.phi);
        let plaintext =
            String::from_utf8_lossy(&m_b[0..m_b.len().checked_sub(self.padding).unwrap()])
                .to_string();

        return (plaintext, shared_secret);
    }

    pub fn serialize(&mut self) {
        let json_str = format!("{{  
    \"phi\": {{\"0\": \"{:?}\"}}, 
    \"padding\": {{\"0\": \"{}\"}}, 
    \"delta\": {{\"u\": \"{}\", \"v\": \"{}\", \"z\": \"{}\", \"t1\": \"{}\", \"t2\": \"{}\"}},
    \"gamma\": {{\"u\": \"{}\", \"v\": \"{}\", \"z\": \"{}\", \"t1\": \"{}\", \"t2\": \"{}\"}}
}}", self.phi, self.padding, self.delta.u, self.delta.v, self.delta.z, self.delta.t1, self.delta.t2, self.gamma.u, self.gamma.v, self.gamma.z, self.gamma.t1, self.gamma.t2);
        let mut file = File::create("cypher.json").expect("Unable to create file");
        file.write(json_str.as_bytes()).expect("Unable to write data");
    }

    pub fn deserialize(filename: String) -> Cipher {
        let file = File::open(filename).expect("Unable to open file");
        let reader = BufReader::new(file);
        let data: HashMap<String, HashMap<String, String>> = serde_json::from_reader(reader).expect("Unable to read file");
        
        let mut i = Cipher::new();

        let bytes: Vec<u8> = data["phi"]["0"]
            .trim_start_matches('[')
            .trim_end_matches(']')
            .split(", ")
            .map(|x| x.parse().unwrap())
            .collect();

        let array_u8: &[u8; 32] = bytes.as_slice().try_into().unwrap();
        i.phi = *array_u8;

        i.padding = data["padding"]["0"].parse().unwrap();

        Cipher::deserialize_extended_points(data["delta"].clone(), &mut i.delta);

        Cipher::deserialize_extended_points(data["gamma"].clone(), &mut i.gamma);

        return i;
    }

    fn deserialize_extended_points(data: HashMap<String, String>, point: &mut ExtendedPoint) {
        point.u = Cipher::get_fq_from_str(data["u"].clone());
        point.v = Cipher::get_fq_from_str(data["v"].clone());
        point.z = Cipher::get_fq_from_str(data["z"].clone());
        point.t1 = Cipher::get_fq_from_str(data["t1"].clone());
        point.t2 = Cipher::get_fq_from_str(data["t2"].clone());
    }

    fn get_fq_from_str(num: String) -> Fq {
        let num_n = num[2..].to_string();
        let big_int = BigInt::from_str_radix(&num_n, 16).unwrap();
        let byte_array = big_int.to_bytes_le().1;
        let array_u8: &[u8; 32] = byte_array.as_slice().try_into().unwrap();
        return Fq::from_bytes(array_u8).unwrap();
    }
}