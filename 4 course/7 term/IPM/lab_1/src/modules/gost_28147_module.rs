#[path = "../utils/consts.rs"] mod consts;

pub mod gost_28147 {
    use std::convert::TryInto;
    use std::num::Wrapping;
    use super::consts::cipher_consts;

    pub fn encode(text_block: Vec<u8>) -> Vec<u8> {
        let mut step = text_block;
        for i in 0..24 {
            step = main_step(step, cipher_consts::KEYS[i % 8]);
        }
        for i in (0..8).rev() {
            step = main_step(step, cipher_consts::KEYS[i]);
        }

        step
    }
    
    pub fn decode(text_block: Vec<u8>) -> Vec<u8> {
        let mut step = text_block[4..].to_vec();
        let mut temp = text_block[..4].to_vec();
        step.append(&mut temp);
        for key in &cipher_consts::KEYS {
            step = main_step(step, *key);
        }
        for i in (0..24).rev() {
            step = main_step(step, cipher_consts::KEYS[i % 8]);
        }
        let mut ans = step[4..].to_vec();
        let mut temp = step[..4].to_vec();
        ans.append(&mut temp);

        ans
    }
    
    fn main_step(text_block: Vec<u8>, key_element: u32) -> Vec<u8> {
        let mut n = text_block;
        let mut s = (Wrapping(
            u32::from(n[0]) << 24 | u32::from(n[1]) << 16 | u32::from(n[2]) << 8 | u32::from(n[3]),
        ) + Wrapping(key_element))
        .0;
        let mut new_s: u32 = 0;
        for mid in 0..4 {
            let cell = (s >> (mid << 3)) & 0xFF;
            new_s += (u32::from(cipher_consts::REPLACEMENT_TABLE[(mid * 2) as usize][(cell & 0x0f) as usize])
                + (u32::from(cipher_consts::REPLACEMENT_TABLE[(mid * 2 + 1) as usize][(cell >> 4) as usize]) << 4))
                << (mid << 3);
        }
        s = ((new_s << 11) + (new_s >> 21))
            ^ (u32::from(n[4]) << 24 | u32::from(n[5]) << 16 | u32::from(n[6]) << 8 | u32::from(n[7]));
        n[4] = n[0];
        n[5] = n[1];
        n[6] = n[2];
        n[7] = n[3];
        n[0] = (s >> 24).try_into().unwrap();
        n[1] = ((s >> 16) & 0xFF).try_into().unwrap();
        n[2] = ((s >> 8) & 0xFF).try_into().unwrap();
        n[3] = (s & 0xFF).try_into().unwrap();
        
        n
    }
}