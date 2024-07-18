use crate::gost::transformations::*;

struct StreebogHasherCtx {
    hash: [u8; 64],
    n: [u8; 64],
    sigma: [u8; 64],
    data: Vec<u8>,
}

pub struct StreebogHasher512 {
    ctx: StreebogHasherCtx,
    is_finished: bool,
    result: [u8; 64],
}

impl StreebogHasher512 {
    pub fn new() -> StreebogHasher512 {
        StreebogHasher512 {
            ctx: StreebogHasherCtx {
                hash: [0 as u8; 64],
                n: [0 as u8; 64],
                sigma: [0 as u8; 64],
                data: Vec::new(),
            },
            is_finished: false,
            result: [0 as u8; 64],
        }
    }

    pub fn hash(&mut self, mut input_str: String) -> [u8; 64] {
        let bytes_to_add = 64 - (input_str.len() % 64);
        let byte_vec = vec![1; bytes_to_add];
        input_str.push_str(std::str::from_utf8(&byte_vec).unwrap());
        let data = input_str.as_bytes();
        let data_len = data.len()/64;
        let mut d_bound = 0;
        let mut h_bound = 64;

        for _ in 0..data_len {
            self.update(&data[d_bound..h_bound]);

            d_bound += 64;
            h_bound += 64;
        }

        self.finish();

        return self.result;
    }

    fn update(&mut self, data_chunk: &[u8]) {
        if !self.is_finished {
            let mut bytes512 = [0 as u8; 64];
            bytes512[1] = 0x2;
            self.ctx.data.extend_from_slice(data_chunk);
            let mut data_len: usize;
            loop {
                data_len = self.ctx.data.len();
                if data_len < 64 {
                    return;
                }        
                let mut data_chunk_in_work = [0 as u8; 64];
                for i in 0..64 {
                    data_chunk_in_work[i] = self.ctx.data[i];
                }
                self.ctx.hash = g_n(self.ctx.n, self.ctx.hash, data_chunk_in_work);
                self.ctx.n = add_modulo512(self.ctx.n, bytes512);
                self.ctx.sigma = add_modulo512(self.ctx.sigma, data_chunk_in_work);
                self.ctx.data = self.ctx.data.split_off(64);
            }
        }
    }

    fn finish(&mut self) {
        if !self.is_finished {
            let padded_data = self.pad_data(self.ctx.data.clone());
            let data_len = self.ctx.data.len() as i32 * 8;
            let mut bytes_len = [0 as u8; 64];
            bytes_len[0] = data_len as u8 & 0xff;
            bytes_len[1] = (data_len >> 8) as u8;
            self.ctx.hash = g_n(self.ctx.n, self.ctx.hash, padded_data);
            self.ctx.n = add_modulo512(self.ctx.n, bytes_len);
            self.ctx.sigma = add_modulo512(self.ctx.sigma, padded_data);
            self.ctx.hash = g_n([0 as u8; 64], self.ctx.hash, self.ctx.n);
            self.ctx.hash = g_n([0 as u8; 64], self.ctx.hash, self.ctx.sigma);
            let result_temp = &self.ctx.hash[..];
            let mut result = Vec::new();
            result.extend_from_slice(result_temp);

            for i in self.result
                    .iter_mut()
                    .zip(result.iter().rev()) {
                *i.0 = *i.1;
            }
            self.is_finished = true;
        };
    }

    fn pad_data(&self, data: Vec<u8>) -> [u8; 64] {
        let mut padded_data = [0 as u8; 64];
        let data_len = data.len();
        for i in 0..data_len {
            padded_data[i] = data[i];
        }
        padded_data[data_len] = 0x1;
        padded_data
    }
}