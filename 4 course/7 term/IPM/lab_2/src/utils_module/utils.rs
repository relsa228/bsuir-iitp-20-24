use byteorder::{LittleEndian, WriteBytesExt};
use crate::encrypt_module::cipher_consts;


pub fn convert_to_vec_u32(inpt_vec: Vec<Vec<u32>>) -> Vec<u32> {
    let mut vec: Vec<u32> = Vec::new();
    for inner_vec in inpt_vec {
        vec.extend(inner_vec);
    }

    vec
}

pub fn convert_to_string(inpt_vec: Vec<Vec<u32>>) -> String {
    let vec = convert_to_vec_u32(inpt_vec);
    
    let mut bytes = Vec::new();
    for i in vec {
        bytes.write_u32::<LittleEndian>(i).unwrap();
    }

    return String::from_utf8(bytes).unwrap();
}

pub fn parse_str_to_wrk_vec(s: &str) -> Vec<Vec<u32>> {
    s.split_whitespace()
        .map(|x| x.parse::<u32>().unwrap())
        .collect::<Vec<u32>>()
        .chunks(4)
        .map(|x| x.to_vec())
        .collect::<Vec<Vec<u32>>>()
}

pub fn parse_plain_text_to_vec(mut t: String) -> Vec<Vec<u32>> {
    t += &" ".repeat(
        (cipher_consts::BLOCK_SIZE - t.len() % cipher_consts::BLOCK_SIZE) % cipher_consts::BLOCK_SIZE);
    
    return t.as_bytes().chunks(cipher_consts::BLOCK_SIZE).map(|chunk| {
        chunk.chunks(4).map(|four_bytes| u32::from_le_bytes([four_bytes[0], 
                                                                four_bytes[1], 
                                                                    four_bytes[2], 
                                                                        four_bytes[3]])).collect()
    }).collect();
}

pub fn pretify_str_for_vec(vec: Vec<Vec<u32>>) -> String {
    let mut result: String = Default::default();

    for i in 0..vec.len() {
        result.push_str(vec[i].iter().map(|x| x.to_string()).collect::<Vec<String>>().join(" ").as_str());
        result.push_str(" ");
    }

    return result;
}