use std::fmt;
use std::u32;
use byteorder::{ByteOrder,LittleEndian};

// Round 1 constants
const C1: [u32; 16] = [
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821
];

// Round 2 constants
const C2: [u32; 16] = [
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a
];

// Round 3 constants
const C3: [u32; 16] = [
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665
];

// Round 4 constants
const C4: [u32; 16] = [
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
];

#[derive(Clone, Copy, Eq, Hash, PartialEq)]
pub struct Digest([u8; 16]);

macro_rules! implement {
    ($kind:ident, $format:expr) => {
        impl fmt::$kind for Digest {
            fn fmt(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                for byte in &self.0 {
                    write!(formatter, $format, byte)?;
                }
                Ok(())
            }
        }
    };
}

implement!(LowerHex, "{:02x}");
implement!(UpperHex, "{:02X}");


struct Input(Vec<u8>);

impl Input {
    fn get_value(&self) -> &Vec<u8> {
        &self.0
    }
    
    fn bit_len(&self) -> usize {
        self.0.len() << 3
    }
    
    fn append_padding(&mut self) {
        let data = &mut self.0;

        data.push(0x80);
        while data.len() % 64 != 56 {
            data.push(0x00);
        }
    }

    fn append_length(&mut self, bit_length: usize) {
        let data = &mut self.0;
        let first_word: u32 = bit_length as u32;
        let second_word: u32 = match bit_length.checked_shr(32) {
            Some(val) => val as u32,
            None => 0
        };

        let mut first_word_slice: [u8; 4] = [0; 4];
        LittleEndian::write_u32(&mut first_word_slice, first_word);
        let mut second_word_slice: [u8; 4] = [0; 4];
        LittleEndian::write_u32(&mut second_word_slice, second_word);
        
        data.extend(&first_word_slice);
        data.extend(&second_word_slice);
    }
}

struct Context {
    input: Vec<u32>,
    state: [u32; 4]
}

impl Context {
    fn new(input: &[u8]) -> Context {
        // Initialization of buffer state ABCD for Step 3
        const INIT_VALUES: [u32; 4] = [0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476];
        let converted_input: Vec<u32> = Context::read_input_as_u32(input);
        
        Context {
            input: converted_input,
            state: INIT_VALUES
        }
    }

    fn read_input_as_u32(input: &[u8]) -> Vec<u32> {
        let mut u32_output: Vec<u32> = Vec::new();
    
        for (idx, _) in input.iter().step_by(4).enumerate() {
            let idx = idx * 4;
            let byte_slice = &input[idx..idx+4];
            u32_output.push(LittleEndian::read_u32(byte_slice));
        }
        u32_output
    }
    
    fn digest(&self) -> Digest {
        let mut digest = [0; 16];
        
        for (idx, word) in self.state.iter().enumerate() {
            let idx = idx * 4;
            digest[idx] = *word as u8;
            digest[idx+1] = (*word >> 8) as u8;
            digest[idx+2] = (*word >> 16) as u8;
            digest[idx+3] = (*word >> 24) as u8;
        }
        Digest(digest)
    }
    
    fn compute(&mut self) {
        let Context {input, state} = self;
        
        for (idx, _) in input.iter().step_by(16).enumerate() {
            let idx = idx * 16;
            let block = &input[idx..idx+16];
            Context::process(block, state);
        }
    }
    
    fn process(input: &[u32], state: &mut [u32]) {
        fn f(u: u32, v: u32, w: u32) -> u32 {
            (u & v) | (!u & w)
        }

        fn g(u: u32, v: u32, w: u32) -> u32 {
            (u & w) | (v & !w)
        }

        fn h(u: u32, v: u32, w: u32) -> u32 {
            u ^ v ^ w
        }

        fn i(u: u32, v: u32, w: u32) -> u32 {
            v ^ (u | !w)
        }

        fn op_f(w: u32, x: u32, y: u32, z: u32, m: u32, s: u32) -> u32 {
            w.wrapping_add(f(x, y, z)).wrapping_add(m).rotate_left(s).wrapping_add(x)
        }

        fn op_g(w: u32, x: u32, y: u32, z: u32, m: u32, s: u32) -> u32 {
            w.wrapping_add(g(x, y, z)).wrapping_add(m).rotate_left(s).wrapping_add(x)
        }

        fn op_h(w: u32, x: u32, y: u32, z: u32, m: u32, s: u32) -> u32 {
            w.wrapping_add(h(x, y, z)).wrapping_add(m).rotate_left(s).wrapping_add(x)
        }

        fn op_i(w: u32, x: u32, y: u32, z: u32, m: u32, s: u32) -> u32 {
            w.wrapping_add(i(x, y, z)).wrapping_add(m).rotate_left(s).wrapping_add(x)
        }
        
        let (mut a, mut b, mut c, mut d) = (state[0], state[1], state[2], state[3]);

        // round 1
        for i in (0..16).step_by(4) {
            a = op_f(a, b, c, d, input[i].wrapping_add(C1[i]), 7);
            d = op_f(d, a, b, c, input[i + 1].wrapping_add(C1[i + 1]), 12);
            c = op_f(c, d, a, b, input[i + 2].wrapping_add(C1[i + 2]), 17);
            b = op_f(b, c, d, a, input[i + 3].wrapping_add(C1[i + 3]), 22);
        }

        // round 2
        let mut t = 1;
        for i in (0..16).step_by(4) {
            a = op_g(a, b, c, d, input[t & 0x0f].wrapping_add(C2[i]), 5);
            d = op_g(d, a, b, c, input[(t + 5) & 0x0f].wrapping_add(C2[i + 1]), 9);
            c = op_g(c, d, a, b, input[(t + 10) & 0x0f].wrapping_add(C2[i + 2]), 14);
            b = op_g(b, c, d, a, input[(t + 15) & 0x0f].wrapping_add(C2[i + 3]), 20);
            t += 20;
        }

        // round 3
        t = 5;
        for i in (0..16).step_by(4) {
            a = op_h(a, b, c, d, input[t & 0x0f].wrapping_add(C3[i]), 4);
            d = op_h(d, a, b, c, input[(t + 3) & 0x0f].wrapping_add(C3[i + 1]), 11);
            c = op_h(c, d, a, b, input[(t + 6) & 0x0f].wrapping_add(C3[i + 2]), 16);
            b = op_h(b, c, d, a, input[(t + 9) & 0x0f].wrapping_add(C3[i + 3]), 23);
            t += 12;
        }

        // round 4
        t = 0;
        for i in (0..16).step_by(4) {
            a = op_i(a, b, c, d, input[t & 0x0f].wrapping_add(C4[i]), 6);
            d = op_i(d, a, b, c, input[(t + 7) & 0x0f].wrapping_add(C4[i + 1]), 10);
            c = op_i(c, d, a, b, input[(t + 14) & 0x0f].wrapping_add(C4[i + 2]), 15);
            b = op_i(b, c, d, a, input[(t + 21) & 0x0f].wrapping_add(C4[i + 3]), 21);
            t += 28;
        }

        state[0] = state[0].wrapping_add(a);
        state[1] = state[1].wrapping_add(b);
        state[2] = state[2].wrapping_add(c);
        state[3] = state[3].wrapping_add(d);
    }
}

pub fn compute<T: AsRef<[u8]> + fmt::Debug>(input: T) -> Digest {
    let mut byte_input: Input = Input(input.as_ref().to_vec());
    let data_len = byte_input.bit_len();
    
    // Step 1: Append Padding Bits.
    byte_input.append_padding();
    // Step 2: Append length
    byte_input.append_length(data_len);
    // Step 3: Initialize MD Buffer
    let mut context = Context::new(byte_input.get_value());
    // Step 4: Process Message in 16-Word Blocks
    context.compute();
    context.digest()
}