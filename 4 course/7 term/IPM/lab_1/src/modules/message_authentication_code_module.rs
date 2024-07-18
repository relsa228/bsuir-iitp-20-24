mod gost_28147_module;

pub mod message_authentication_code {
    use super::gost_28147_module::gost_28147;

    pub fn get_message_authentication_code(plain_text: Vec<&[u8]>) -> Vec<u8> {
        let mut plain_work = Vec::new();
        let mut i = 0;
        while i < plain_text.len() {
            let mut temp_vec = Vec::new();
            for j in i..i + 8 {
                if j < plain_text.len() {
                    temp_vec.push(plain_text[j]);
                } else {
                    temp_vec.push(&[0]);
                }
            }
            plain_work.push(temp_vec);
            i += 8;
        }

        let mut message_authentication_code = plain_work[0].iter().map(|c| c.to_vec()).collect::<Vec<_>>()[0].clone();
        message_authentication_code = gost_28147::encode(message_authentication_code);
        for i in 1..plain_text.len() {
            for j in 0..7 {
                message_authentication_code[j] = message_authentication_code[j] ^ plain_text[i][j];
            }

            message_authentication_code = gost_28147::encode(message_authentication_code);
        }

        message_authentication_code
    }
}