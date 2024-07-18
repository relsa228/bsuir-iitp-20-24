use image::save_buffer_with_format;
use std::vec;
use std::fs::File;
use std::io::{BufWriter, BufReader};
use std::io::prelude::*;

extern crate rustfft;
use rustfft::algorithm::Radix4;
use rustfft::num_complex::Complex;
use rustfft::num_traits::Zero;
use rustfft::FFT;


pub struct FftStego {}

impl FftStego {
    fn dct_rustfft(input: &Vec<Vec<u8>>) -> Vec<Vec<f64>> {
        let mut result: Vec<Vec<f64>> = vec![vec![0.0; 8]; 8];
        let n = input.len();
        let planner = Radix4::new(n, true);
        let mut signal = vec![Complex::zero(); n];
        let mut spectrum = signal.clone();
    
        for (i, row) in input.iter().enumerate() {
            for (j, &value) in row.iter().enumerate() {
                signal[j] = Complex::new(value as f64, 0.0);
            }
    
            planner.process(&mut signal, &mut spectrum);
    
            for (j, value) in spectrum.iter().enumerate() {
                result[i][j] = value.re;
            }
        }
    
        result
    }
    
    
    fn idct_rustfft(input: &Vec<Vec<f64>>) -> Vec<Vec<u8>> {
        let n = input.len();
        let mut result: Vec<Vec<f64>> = vec![ vec![0.0; 8]; 8];
        let planner = Radix4::new(n, false);
        let mut signal = vec![Complex::zero(); n];
        let mut spectrum = signal.clone();
    
        for (i, row) in input.iter().enumerate() {
            for (j, &value) in row.iter().enumerate() {
                signal[j] = Complex::new(value, 0.0);
            }
    
            planner.process(&mut signal, &mut spectrum);
    
            for (j, value) in spectrum.iter().enumerate() {
                result[i][j] = value.re;
            }
        }
    
        //let important_byte = result[7][7];
    
        // Коррекция яркости
        let brightness_correction = 0.125; // Уменьшаем яркость на n%
        for row in result.iter_mut() {
            for value in row.iter_mut() {
                *value *= brightness_correction;
            }
        }
    
        let result_norm: Vec<Vec<u8>> = result.iter().map(|row| row.iter().map(|&value| value.round() as u8).collect()).collect();
    
        //result_norm[7][7] = important_byte.round() as u8;
    
        result_norm
    }
    
    fn vec_to_matrix_vec(v: Vec<u8>) -> Vec<Vec<Vec<u8>>> {
        let mut res = Vec::new();
        let mut i = 0;
        while i < v.len() {
            let mut matrix = Vec::new();
            for _ in 0..8 {
                let mut row = Vec::new();
                for _ in 0..8 {
                    if i < v.len() {
                        row.push(v[i]);
                        i += 1;
                    } else {
                        //row.push(0);
                    }
                }
                matrix.push(row);
            }
            res.push(matrix);
        }
        res
    }
    
    fn convert_vec_vec_vec_u8_to_vec_u8(v: Vec<Vec<Vec<u8>>>) -> Vec<u8> {
        let mut res = Vec::new();
        for matrix in v {
            for row in matrix {
                for byte in row {
                    res.push(byte);
                }
            }
        }
        res
    }

    fn correct_vec_set(bytes_encr: Vec<u8>, bytes: Vec<u8>) {
        let mut correct_vec: Vec<i32> = vec![];

        for i in 0..bytes.len() {
            correct_vec.push(bytes[i] as i32 - bytes_encr[i] as i32);
        }

        let f = File::create("correct_vec.txt").unwrap();
        let mut writer = BufWriter::new(f);

        for &num in &correct_vec {
            writeln!(writer, "{}", num).unwrap();
        }
    }

    fn correct_vec_get() -> Vec<i32> {
        let mut correct_vec: Vec<i32> = vec![];
        let f = File::open("correct_vec.txt").unwrap();
        let reader = BufReader::new(f);

        for line in reader.lines() {
            let line = line.unwrap();

            match line.parse::<i32>() {
                Ok(i) => correct_vec.push(i),
                Err(_) => println!("type error")
            }
        }

        correct_vec
    }

    pub fn decrypt(file_name: &str) -> String {
        let im_encr = image::open(file_name).unwrap().to_rgb8();
        let mut bytes_out: Vec<u8> = vec![];

        let mut vec_of_matrix = FftStego::vec_to_matrix_vec(im_encr.clone().into_raw().clone());
        let mut vec_transform = vec![];

        for i in 0..vec_of_matrix.clone().len() - 1 {
            vec_transform.push(FftStego::dct_rustfft(&vec_of_matrix[i].clone()));
        }

        vec_of_matrix = vec![];

        for i in 0..vec_transform.clone().len() {
            vec_of_matrix.push(FftStego::idct_rustfft(&vec_transform[i].clone()));
        }

        let correct_vec: Vec<i32> = FftStego::correct_vec_get();
        
        for i in 0..correct_vec.len() {
            bytes_out.push((vec_of_matrix[i][7][7] as i32 + correct_vec[i]) as u8);
        }

        let result_str: String = String::from_utf8(bytes_out).unwrap();

        result_str
    }

    pub fn encrypt(file_name: &str, message: &str) {
        let im = image::open(file_name).unwrap().to_rgb8();

        let bytes: Vec<u8> = message.as_bytes().to_vec();
        let mut rgb: Vec<u8> = im.clone().into_raw();
        let mut vec_of_matrix = FftStego::vec_to_matrix_vec(rgb.clone());
        let mut vec_transform = vec![];


        for i in 0..bytes.len() {
            vec_of_matrix[i][7][7] = bytes[i];
        }
        
        for i in 0..vec_of_matrix.clone().len() - 1 {
            vec_transform.push(FftStego::dct_rustfft(&vec_of_matrix[i].clone()));
        }

        vec_of_matrix = vec![];

        for i in 0..vec_transform.clone().len() {
            vec_of_matrix.push(FftStego::idct_rustfft(&vec_transform[i].clone()));
        }

        let mut vec_of_bytes: Vec<u8> = FftStego::convert_vec_vec_vec_u8_to_vec_u8(vec_of_matrix);

        let diff = rgb.len() - vec_of_bytes.len();
        let extra_bytes = rgb.split_off(diff);
        vec_of_bytes.extend(extra_bytes);

        save_buffer_with_format("encryption.jpeg", &vec_of_bytes, im.width(), im.height(), image::ColorType::Rgb8, image::ImageFormat::Jpeg).unwrap();

        let im_encr = image::open("encryption.jpeg").unwrap().to_rgb8();
        let mut bytes_encr: Vec<u8> = vec![];

        let mut vec_of_matrix = FftStego::vec_to_matrix_vec(im_encr.clone().into_raw().clone());
        let mut vec_transform = vec![];

        for i in 0..vec_of_matrix.clone().len() - 1 {
            vec_transform.push(FftStego::dct_rustfft(&vec_of_matrix[i].clone()));
        }

        vec_of_matrix = vec![];

        for i in 0..vec_transform.clone().len() {
            vec_of_matrix.push(FftStego::idct_rustfft(&vec_transform[i].clone()));
        }

        for i in 0..bytes.len() {
            bytes_encr.push(vec_of_matrix[i][7][7]);
        }

        FftStego::correct_vec_set(bytes_encr, bytes);
    }
}